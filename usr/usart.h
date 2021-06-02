#include "stm32_base.h"
#include "gpio.h"
#pragma once

#define USART_TRANSACTION_TIMEOUT_ms 1000
#define USART_QUEUE_LENGTH 1024
#define USART_CLOCK 72000000

typedef struct {
    USART_TypeDef *USART;
    int baudrate;
    pin_t rxtx[2];
} usart_t;

class usart {
private:
    usart_t usart_conf;
    int rx_length;
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
    void IRQ_Handler();
public:
    usart(USART_TypeDef *USART, int baudrate) {
        usart_conf.USART = USART;
        usart_conf.baudrate = baudrate;
        usart_conf.rxtx[0] = {GPIOA, LL_GPIO_PIN_3};
        usart_conf.rxtx[1] = {GPIOA, LL_GPIO_PIN_2};
        ClockInit();
        Init();
        semaphore = xSemaphoreCreateBinary();
        mutex = xSemaphoreCreateMutex();
        queue = xQueueCreate(USART_QUEUE_LENGTH, sizeof(uint8_t));
    }
    SemaphoreHandle_t semaphore;
    SemaphoreHandle_t mutex;
    QueueHandle_t queue;
    int Print(char *string);
    int Print(int number);
    int Print(float number);
};
