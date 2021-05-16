#include "stm32f103_conf.h"
#include "gpio.h"
#include "adc.h"

void adc::Init(void){
    if(adc.ADC == ADC1) {
        LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_ADC1);
    } else if(adc.ADC == ADC2) {
        LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_ADC2);
    }
}

void adc::ConfigInit(void) {
    LL_ADC_SetChannelSamplingTime(adc.ADC, LL_ADC_CHANNEL_0, SAMPLING_TIME);
    LL_ADC_SetChannelSamplingTime(adc.ADC, LL_ADC_CHANNEL_1, SAMPLING_TIME);
    LL_ADC_SetChannelSamplingTime(adc.ADC, LL_ADC_CHANNEL_2, SAMPLING_TIME);
    LL_ADC_SetChannelSamplingTime(adc.ADC, LL_ADC_CHANNEL_3, SAMPLING_TIME);
    LL_ADC_SetChannelSamplingTime(adc.ADC, LL_ADC_CHANNEL_4, SAMPLING_TIME);
    LL_ADC_SetChannelSamplingTime(adc.ADC, LL_ADC_CHANNEL_5, SAMPLING_TIME);
    LL_ADC_SetChannelSamplingTime(adc.ADC, LL_ADC_CHANNEL_6, SAMPLING_TIME);
    LL_ADC_SetChannelSamplingTime(adc.ADC, LL_ADC_CHANNEL_7, SAMPLING_TIME);
    LL_ADC_SetChannelSamplingTime(adc.ADC, LL_ADC_CHANNEL_8, SAMPLING_TIME);
    LL_ADC_SetChannelSamplingTime(adc.ADC, LL_ADC_CHANNEL_9, SAMPLING_TIME);
}

void adc::PinInit(pin_t pin) {
    if(pin.GPIOx == GPIOA) {
        LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOA);
    } else if(pin.GPIOx == GPIOB) {
        LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOB);
    } else if(pin.GPIOx == GPIOC) {
        LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOC);
    } else if(pin.GPIOx == GPIOD) {
        LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOD);
    } else if(pin.GPIOx == GPIOE) {
        LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOE);
    }
    LL_GPIO_SetPinMode(pin.GPIOx, pin.LL_PIN, LL_GPIO_MODE_ANALOG);
    LL_GPIO_SetPinSpeed(pin.GPIOx, pin.LL_PIN, LL_GPIO_SPEED_FREQ_HIGH);
}