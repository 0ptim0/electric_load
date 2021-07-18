#include "usart.h"

static SemaphoreHandle_t mutex;
static SemaphoreHandle_t semaphore;
static QueueHandle_t queue;

void usart::Init() {
    if(mutex == NULL) mutex = xSemaphoreCreateMutex();
    if(queue == NULL) queue = xQueueCreate(this->length, sizeof(uint8_t));
    if(semaphore == NULL) semaphore = xSemaphoreCreateBinary();

    if(USART_InitStructure.Instance == USART1) {
        __HAL_RCC_USART1_CLK_ENABLE();
        NVIC_SetPriority(USART1_IRQn, 12);
        HAL_NVIC_EnableIRQ(USART1_IRQn);
    } else if(USART_InitStructure.Instance == USART2) {
        __HAL_RCC_USART2_CLK_ENABLE();
        NVIC_SetPriority(USART2_IRQn, 12);
        HAL_NVIC_EnableIRQ(USART2_IRQn);
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
    if(xSemaphoreTake(mutex, timeout) == pdTRUE) {

        HAL_UART_Transmit_IT(&USART_InitStructure, pdata, length);

        if(xSemaphoreTake(semaphore, pdMS_TO_TICKS(timeout)) == pdFALSE) {
            xSemaphoreGive(mutex);
            return pdFALSE;
        } else {
            xSemaphoreGive(mutex);
            return pdTRUE;
        }
    } else {
        return pdFALSE;
    }
}

int usart::Receive(uint8_t *pdata, uint16_t length) {
    HAL_UART_Receive_IT(&USART_InitStructure, pdata, length);
}

void usart::EchoStart() {
    HAL_UART_Receive_IT(&USART_InitStructure, &(this->echo_buf), 1);
}

void usart::RxCpltCallback() {
    if(this->echo_buf == '\r') {
        HAL_UART_Transmit_IT(&USART_InitStructure, (uint8_t *)"\r\n> ", 4);
    } else {
        HAL_UART_Transmit_IT(&USART_InitStructure, &(this->echo_buf), 1);
    }
    HAL_UART_Receive_IT(&USART_InitStructure, &(this->echo_buf), 1);
}

void usart::TxCpltCallback() {

}

// TODO Read error flags
int usart::Handle() {
    static uint8_t buf;
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    HAL_UART_IRQHandler(&USART_InitStructure);
    if(USART_InitStructure.gState == HAL_UART_STATE_READY) {
        xSemaphoreGiveFromISR(semaphore, &xHigherPriorityTaskWoken);
        if(xHigherPriorityTaskWoken == pdTRUE) {
            portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
        }
    }
}
