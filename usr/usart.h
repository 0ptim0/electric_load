#include "stm32_base.h"
#include "gpio.h"
#pragma once

#define UART_TRANSACTION_TIMEOUT_ms 1000
#define UART_QUEUE_LENGTH 1024

class usart {
private:
    UART_HandleTypeDef USART_InitStructure;
    SemaphoreHandle_t semaphore;
    SemaphoreHandle_t mutex;
    QueueHandle_t queue;
    int timeout;
    int buf_size;
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
    uint8_t Transmit(uint8_t *pdata, uint16_t length);
};
