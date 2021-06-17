#include "stm32_base.h"
#include "gpio.h"
#pragma once

#define UART_TRANSACTION_TIMEOUT_ms 1000
#define UART_QUEUE_LENGTH 1024

//void USART3_IRQHandler(void);

class usart {
private:
    UART_HandleTypeDef USART_InitStructure;
    int timeout;
    int buf_size;
    void Acquire();
    void Release();
public:
public:
    usart(USART_TypeDef *USART, int baudrate) {
        timeout = UART_TRANSACTION_TIMEOUT_ms;
        buf_size = UART_QUEUE_LENGTH;
        USART_InitStructure.Instance = USART;
        USART_InitStructure.Init.BaudRate = baudrate;
    }
    usart(USART_TypeDef *USART, int baudrate, int max_length, int max_timeout) {
        timeout = max_timeout;
        buf_size = max_length;
        USART_InitStructure.Instance = USART;
        USART_InitStructure.Init.BaudRate = baudrate;
    }
    void Init();
    int Transmit(uint8_t *pdata, uint16_t length);
};
