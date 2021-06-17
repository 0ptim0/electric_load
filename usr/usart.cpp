#include "usart.h"

SemaphoreHandle_t mutex;
SemaphoreHandle_t semaphore;
QueueHandle_t queue;

void usart::Acquire() {
    xSemaphoreTake(mutex, timeout);
}

void usart::Release() {
    xSemaphoreGive(mutex);
}

void usart::Init() {
    mutex = xSemaphoreCreateMutex();
    queue = xQueueCreate(this->buf_size, sizeof(uint8_t));
    semaphore = xSemaphoreCreateBinary();
    if(USART_InitStructure.Instance == USART1) {
        __HAL_RCC_USART1_CLK_ENABLE();
        HAL_NVIC_EnableIRQ(USART1_IRQn);
        NVIC_SetPriority(USART1_IRQn, 12);
    } else if(USART_InitStructure.Instance == USART2) {
        __HAL_RCC_USART2_CLK_ENABLE();
        HAL_NVIC_EnableIRQ(USART2_IRQn);
        NVIC_SetPriority(USART2_IRQn, 12);
    } else if(USART_InitStructure.Instance == USART3) {
        __HAL_RCC_USART3_CLK_ENABLE();
        NVIC_SetPriorityGrouping(0);
        NVIC_SetPriority(USART3_IRQn, 12);
        HAL_NVIC_EnableIRQ(USART3_IRQn);
    }

    USART_InitStructure.Init.Mode = UART_MODE_TX_RX;
    USART_InitStructure.Init.OverSampling = UART_OVERSAMPLING_16;
    USART_InitStructure.Init.Parity = UART_PARITY_NONE;
    USART_InitStructure.Init.StopBits = UART_STOPBITS_1;
    USART_InitStructure.Init.WordLength = UART_WORDLENGTH_8B;
    HAL_UART_Init(&USART_InitStructure);
}

int usart::Transmit(uint8_t *pdata, uint16_t length) {
    Acquire();
    xSemaphoreGive(semaphore);

    HAL_UART_Transmit_IT(&USART_InitStructure, pdata, length);

    if(xSemaphoreTake(semaphore, pdMS_TO_TICKS(timeout)) == pdFALSE) {
        Release();
        return pdFALSE;
    } else {
        Release();
        return pdTRUE;
    }
}
// TODO Read error flags
int usart::Handle() {
    static uint8_t buf;
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    HAL_UART_IRQHandler(&USART_InitStructure);

    xSemaphoreGiveFromISR(semaphore, &xHigherPriorityTaskWoken);
    if(xHigherPriorityTaskWoken == pdTRUE) {
        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    }
}
