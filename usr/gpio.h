#include "stm32_base.h"
#pragma once

typedef struct {
    GPIO_TypeDef *GPIOx;
    int LL_PIN;
} pin_t;
