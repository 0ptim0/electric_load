#include "stm32_base.h"
#include "gpio.h"
#pragma once

#define SAMPLING_TIME LL_ADC_SAMPLINGTIME_239CYCLES_5
#define USE_DMA 1

class adc {
private:
    ADC_HandleTypeDef ADC_InitStructure;
    void ConfigInit(void);
public:
    uint16_t buf[2];
    void Init(ADC_TypeDef *ADC);
};