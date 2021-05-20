#include "stm32f103xb.h"
#include "gpio.h"
#pragma once

#define SAMPLING_TIME LL_ADC_SAMPLINGTIME_239CYCLES_5
#define USE_DMA 1

typedef struct {
    ADC_TypeDef *ADC;
    pin_t channel[15];
    uint32_t data[15];
} adc_t;

class adc {
    private:
        adc_t adc_conf;
        void PinInit(pin_t pin);
        void ConfigInit(void);
    public:
        adc() {
            adc_conf.ADC = ADC1;
            adc_conf.channel[0] = {GPIOA, LL_GPIO_PIN_0};
            adc_conf.channel[1] = {GPIOA, LL_GPIO_PIN_1};
            adc_conf.channel[2] = {GPIOA, LL_GPIO_PIN_2};
            adc_conf.channel[3] = {GPIOA, LL_GPIO_PIN_3};
            adc_conf.channel[4] = {GPIOA, LL_GPIO_PIN_4};
            adc_conf.channel[5] = {GPIOA, LL_GPIO_PIN_5};
            adc_conf.channel[6] = {GPIOA, LL_GPIO_PIN_6};
            adc_conf.channel[7] = {GPIOA, LL_GPIO_PIN_7};
            adc_conf.channel[8] = {GPIOB, LL_GPIO_PIN_0};
            adc_conf.channel[9] = {GPIOB, LL_GPIO_PIN_1};
        }
        void Init(void);
};