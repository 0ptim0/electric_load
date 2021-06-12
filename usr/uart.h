#include "stm32_base.h"
#include "gpio.h"
#pragma once

#define UART_TRANSACTION_TIMEOUT_ms 1000
#define UART_QUEUE_LENGTH 1024

class uart {
private:
    UART_HandleTypeDef UART_InitStructure;
    SemaphoreHandle_t semaphore;
    SemaphoreHandle_t mutex;
    QueueHandle_t queue;
    int timeout;
    int buf_size;
    /*int rx_length;
    int err;
    int address;
    int buffer[USART_QUEUE_LENGTH];
    void Acquire();
    void Release();
    void ClockInit();
    void ClockDeinit();
    void NVIC_Enable();
    void NVIC_Disable();
    void PinInit();
    void PinReinit();
    void Init();
    void Deinit();
    void IRQ_Handler();*/
public:
    uart(USART_TypeDef *USART, int baudrate) {
        timeout = UART_TRANSACTION_TIMEOUT_ms;
        buf_size = UART_QUEUE_LENGTH;
        UART_InitStructure.Instance = USART;
        UART_InitStructure.Init.BaudRate = baudrate;
        /*ClockInit();
        Init();
        semaphore = xSemaphoreCreateBinary();
        mutex = xSemaphoreCreateMutex();
        queue = xQueueCreate(USART_QUEUE_LENGTH, sizeof(uint8_t));*/
    }
    /*SemaphoreHandle_t semaphore;
    SemaphoreHandle_t mutex;
    QueueHandle_t queue;
    int Print(char *string);
    int Print(int number);
    int Print(float number);*/
};
