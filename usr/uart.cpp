#include "uart.h"

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
