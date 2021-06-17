#include "usart.h"

SemaphoreHandle_t mutex;
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
        //HAL_NVIC_EnableIRQ(USART3_IRQn);
    }

    USART_InitStructure.Init.Mode = UART_MODE_TX_RX;
    USART_InitStructure.Init.OverSampling = UART_OVERSAMPLING_16;
    USART_InitStructure.Init.Parity = UART_PARITY_NONE;
    USART_InitStructure.Init.StopBits = UART_STOPBITS_1;
    USART_InitStructure.Init.WordLength = UART_WORDLENGTH_8B;
    HAL_UART_Init(&USART_InitStructure);
}

int usart::Transmit(uint8_t *pdata, uint16_t length) {
    LL_USART_EnableIT_TXE(USART3);
    LL_USART_EnableIT_TC(USART3);
    NVIC_EnableIRQ(USART3_IRQn);
    LL_USART_Enable(USART3);
    //HAL_UART_Transmit_IT(&USART_InitStructure, pdata, length);
}

/*void uart::ClockInit() {
    taskENTER_CRITICAL() ;
    if(usart_conf.USART == USART1) {
        LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_USART1);
        #define USART_IRQ1
    } else if(usart_conf.USART == USART2) {
        LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART2);
        #define USART_IRQ2
    } else if(usart_conf.USART == USART3) {
        LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART3);
        #define USART_IRQ3
    }
    taskEXIT_CRITICAL();
}*/

/*int uart::Print(char *string) {
    Acquire();
    xQueueSend(queue, string, 0);
    LL_USART_EnableIT_TXE(usart_conf.USART);
    LL_USART_EnableIT_TC(usart_conf.USART);
    NVIC_Enable();
    LL_USART_Enable(USART2);

    if(xSemaphoreTake(semaphore, pdMS_TO_TICKS(USART_TRANSACTION_TIMEOUT_ms))) {
        Release();
        return 0;
    } else {
        Release();
        return 1;
    }
}

void uart::Acquire() {
    xSemaphoreTake(mutex, portMAX_DELAY);
}

void uart::Release() {
    xSemaphoreGive(mutex);
}

void uart::ClockInit() {
    taskENTER_CRITICAL();
    if(usart_conf.USART == USART1) {
        LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_USART1);
        #define USART_IRQ1
    } else if(usart_conf.USART == USART2) {
        LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART2);
        #define USART_IRQ2
    } else if(usart_conf.USART == USART3) {
        LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART3);
        #define USART_IRQ3
    }
    taskEXIT_CRITICAL();
}

void uart::ClockDeinit() {
    taskENTER_CRITICAL();
    if(usart_conf.USART == USART1) {
        LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_USART1);
    } else if(usart_conf.USART == USART2) {
        LL_APB2_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_USART2);
    } else if(usart_conf.USART == USART3) {
        LL_APB2_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_USART3);
    }
    taskEXIT_CRITICAL();
}

void uart::NVIC_Enable() {
    if(usart_conf.USART == USART1) {
        NVIC_EnableIRQ(USART1_IRQn);
    } else if(usart_conf.USART == USART2) {
        NVIC_EnableIRQ(USART2_IRQn);
    } else if(usart_conf.USART == USART3) {
        NVIC_EnableIRQ(USART3_IRQn);
    }
}

void uart::NVIC_Disable() {
    if(usart_conf.USART == USART1) {
        NVIC_DisableIRQ(USART1_IRQn);
    } else if(usart_conf.USART == USART2) {
        NVIC_DisableIRQ(USART2_IRQn);
    } else if(usart_conf.USART == USART3) {
        NVIC_DisableIRQ(USART3_IRQn);
    }
}

void uart::PinInit() {
    for(int i = 0; i < 2; i++) {
        if(usart_conf.rxtx[i].GPIOx == GPIOA) {
            LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOA);
        } else if(usart_conf.rxtx[i].GPIOx == GPIOB) {
            LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOB);
        }
    }
    LL_GPIO_SetPinMode(usart_conf.rxtx[0].GPIOx, usart_conf.rxtx[0].LL_PIN, LL_GPIO_MODE_ALTERNATE);
    LL_GPIO_SetPinSpeed(usart_conf.rxtx[0].GPIOx, usart_conf.rxtx[0].LL_PIN, LL_GPIO_SPEED_FREQ_HIGH);
    LL_GPIO_SetPinMode(usart_conf.rxtx[1].GPIOx, usart_conf.rxtx[1].LL_PIN, LL_GPIO_MODE_ALTERNATE);
    LL_GPIO_SetPinSpeed(usart_conf.rxtx[1].GPIOx, usart_conf.rxtx[1].LL_PIN, LL_GPIO_SPEED_FREQ_HIGH);
}

void uart::Init() {
    PinInit();
    UART_InitStructure.
    LL_USART_ConfigAsyncMode(usart_conf.USART);
    LL_USART_SetTransferDirection(usart_conf.USART, LL_USART_DIRECTION_TX_RX);
    LL_USART_ConfigCharacter(usart_conf.USART, LL_USART_DATAWIDTH_8B, LL_USART_PARITY_NONE, LL_USART_STOPBITS_1);
    LL_USART_SetBaudRate(usart_conf.USART, 
                        USART_CLOCK,
                        usart_conf.baudrate);

    NVIC_Enable();
    LL_USART_Enable(usart_conf.USART);

    LL_USART_EnableIT_IDLE(usart_conf.USART);
    LL_USART_EnableIT_RXNE(usart_conf.USART);
}

void uart::IRQ_Handler() {
    static uint8_t buf;
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    if(LL_USART_IsActiveFlag_TXE(usart_conf.USART)) {
        if(xQueueReceiveFromISR(queue, &buf, &xHigherPriorityTaskWoken) != errQUEUE_EMPTY) {
            LL_USART_TransmitData8(usart_conf.USART, buf);
            return;
        } else if(LL_USART_IsActiveFlag_TC(usart_conf.USART)) {
            LL_USART_DisableIT_TC(usart_conf.USART);
            LL_USART_DisableIT_TXE(usart_conf.USART);
            LL_USART_Disable(usart_conf.USART);
            xSemaphoreGiveFromISR(semaphore, &xHigherPriorityTaskWoken);
            if(xHigherPriorityTaskWoken == pdTRUE) {
                portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
            }
        }
    }
}*/
