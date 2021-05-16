#include <stm32f103xb.h>
#pragma once

typedef struct {
    GPIO_TypeDef *GPIOx;
    int LL_PIN;
} pin_t;
