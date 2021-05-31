#include "usart.h"

void usart::Acquire() {
    xSemaphoreTake(mutex, portMAX_DELAY);
}

void usart::Release() {
    xSemaphoreGive(mutex);
}

void usart::ClockInit() {
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

void usart::ClockDeinit() {
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

void usart::NVIC_Enable() {
    if(usart_conf.USART == USART1) {
        NVIC_EnableIRQ(USART1_IRQn);
    } else if(usart_conf.USART == USART2) {
        NVIC_EnableIRQ(USART2_IRQn);
    } else if(usart_conf.USART == USART3) {
        NVIC_EnableIRQ(USART3_IRQn);
    }
}

void usart::NVIC_Disable() {
    if(usart_conf.USART == USART1) {
        NVIC_DisableIRQ(USART1_IRQn);
    } else if(usart_conf.USART == USART2) {
        NVIC_DisableIRQ(USART2_IRQn);
    } else if(usart_conf.USART == USART3) {
        NVIC_DisableIRQ(USART3_IRQn);
    }
}

void usart::PinInit() {
    for(int i = 0; i < 2; i++) {
        if(usart_conf.rxtx[i].GPIOx == GPIOA) {
            LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOA);
        } else if(usart_conf.rxtx[i].GPIOx == GPIOB) {
            LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOB);
        }        
    }
    if(usart_conf.USART == USART1) {
        LL_GPIO_SetPinMode(usart_conf.rxtx[0].GPIOx, usart_conf.rxtx[0].LL_PIN, LL_GPIO_MODE_ALTERNATE);
        LL_GPIO_SetPinSpeed(usart_conf.rxtx[0].GPIOx, usart_conf.rxtx[0].LL_PIN, LL_GPIO_SPEED_FREQ_HIGH);
        LL_GPIO_SetPinMode(usart_conf.rxtx[1].GPIOx, usart_conf.rxtx[1].LL_PIN, LL_GPIO_MODE_ALTERNATE);
        LL_GPIO_SetPinSpeed(usart_conf.rxtx[1].GPIOx, usart_conf.rxtx[1].LL_PIN, LL_GPIO_SPEED_FREQ_HIGH);
    } else if(usart_conf.USART == USART2) {
        LL_GPIO_SetPinMode(usart_conf.rxtx[2].GPIOx, usart_conf.rxtx[2].LL_PIN, LL_GPIO_MODE_ALTERNATE);
        LL_GPIO_SetPinSpeed(usart_conf.rxtx[2].GPIOx, usart_conf.rxtx[2].LL_PIN, LL_GPIO_SPEED_FREQ_HIGH);
        LL_GPIO_SetPinMode(usart_conf.rxtx[3].GPIOx, usart_conf.rxtx[3].LL_PIN, LL_GPIO_MODE_ALTERNATE);
        LL_GPIO_SetPinSpeed(usart_conf.rxtx[3].GPIOx, usart_conf.rxtx[3].LL_PIN, LL_GPIO_SPEED_FREQ_HIGH);
    } else if(usart_conf.USART == USART3) {
        LL_GPIO_SetPinMode(usart_conf.rxtx[4].GPIOx, usart_conf.rxtx[4].LL_PIN, LL_GPIO_MODE_ALTERNATE);
        LL_GPIO_SetPinSpeed(usart_conf.rxtx[4].GPIOx, usart_conf.rxtx[4].LL_PIN, LL_GPIO_SPEED_FREQ_HIGH);
        LL_GPIO_SetPinMode(usart_conf.rxtx[5].GPIOx, usart_conf.rxtx[5].LL_PIN, LL_GPIO_MODE_ALTERNATE);
        LL_GPIO_SetPinSpeed(usart_conf.rxtx[5].GPIOx, usart_conf.rxtx[5].LL_PIN, LL_GPIO_SPEED_FREQ_HIGH);
    }
}

void usart::Init() {
    PinInit();
    /* CONFIG FOR ASYNC MODE */
    LL_USART_ConfigAsyncMode(usart_conf.USART);
    /* FULL DUPLEX REGIMES */
    LL_USART_SetTransferDirection(usart_conf.USART, LL_USART_DIRECTION_TX_RX);
    /* START + 8B + STOP, NO PARITY */
    LL_USART_ConfigCharacter(usart_conf.USART, LL_USART_DATAWIDTH_8B, LL_USART_PARITY_NONE, LL_USART_STOPBITS_1);
    /* USART BAUDRATE */
    LL_USART_SetBaudRate(usart_conf.USART, 
                        ((usart_conf.USART == USART1) ? 
                        LL_RCC_GetSysClkSource() / LL_RCC_GetAPB2Prescaler() : 
                        LL_RCC_GetSysClkSource() / LL_RCC_GetAPB1Prescaler()),
                        usart_conf.baudrate);

    NVIC_Enable();
    LL_USART_Enable(usart_conf.USART);

    LL_USART_EnableIT_IDLE(usart_conf.USART);
    LL_USART_EnableIT_RXNE(usart_conf.USART);
}
 
#ifdef USART_IRQ1
void usart::USART1_IRQHandler(void) {
    static uint8_t _buf;
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    if(LL_USART_IsActiveFlag_TXE(USART2)) {
        if(xQueueReceiveFromISR(queue, &_buf, &xHigherPriorityTaskWoken) != errQUEUE_EMPTY) {
            LL_USART_TransmitData8(USART2, _buf);
            return;
        } else if(LL_USART_IsActiveFlag_TC(USART2)) {
            LL_USART_DisableIT_TC(USART2);
            LL_USART_DisableIT_TXE(USART2);
            LL_USART_Disable(USART2);
            xSemaphoreGiveFromISR(semaphore, &xHigherPriorityTaskWoken);
            if(xHigherPriorityTaskWoken == pdTRUE) {
                portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
            }
        }
    }
}
#endif

#ifdef USART_IRQ2
void usart::USART2_IRQHandler(void) {
    static uint8_t _buf;
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    if(LL_USART_IsActiveFlag_TXE(USART2)) {
        if(xQueueReceiveFromISR(queue, &_buf, &xHigherPriorityTaskWoken) != errQUEUE_EMPTY) {
            LL_USART_TransmitData8(USART2, _buf);
            return;
        } else if(LL_USART_IsActiveFlag_TC(USART2)) {
            LL_USART_DisableIT_TC(USART2);
            LL_USART_DisableIT_TXE(USART2);
            LL_USART_Disable(USART2);
            xSemaphoreGiveFromISR(semaphore, &xHigherPriorityTaskWoken);
            if(xHigherPriorityTaskWoken == pdTRUE) {
                portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
            }
        }
    }
}
#endif

#ifdef USART_IRQ3
void usart::USART3_IRQHandler(void) {
    static uint8_t _buf;
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    if(LL_USART_IsActiveFlag_TXE(USART2)) {
        if(xQueueReceiveFromISR(queue, &_buf, &xHigherPriorityTaskWoken) != errQUEUE_EMPTY) {
            LL_USART_TransmitData8(USART2, _buf);
            return;
        } else if(LL_USART_IsActiveFlag_TC(USART2)) {
            LL_USART_DisableIT_TC(USART2);
            LL_USART_DisableIT_TXE(USART2);
            LL_USART_Disable(USART2);
            xSemaphoreGiveFromISR(semaphore, &xHigherPriorityTaskWoken);
            if(xHigherPriorityTaskWoken == pdTRUE) {
                portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
            }
        }
    }
}
#endif
