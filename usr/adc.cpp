#include "stm32f103_conf.h"
#include "gpio.h"
#include "adc.h"

void adc::Init(void){
    if(adc_conf.ADC == ADC1) {
        LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_ADC1);
    } else if(adc_conf.ADC == ADC2) {
        LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_ADC2);
    }
    PinInit(adc_conf.channel[8]);
    PinInit(adc_conf.channel[9]);
    
}

void adc::ConfigInit(void) {
    LL_ADC_REG_SetContinuousMode(adc_conf.ADC, LL_ADC_REG_CONV_CONTINUOUS); // TODO In argument
    LL_ADC_SetDataAlignment(adc_conf.ADC, LL_ADC_DATA_ALIGN_RIGHT);
    LL_ADC_SetSequencersScanMode(adc_conf.ADC, LL_ADC_SEQ_SCAN_ENABLE);
    LL_ADC_REG_SetSequencerLength(adc_conf.ADC, LL_ADC_REG_SEQ_SCAN_ENABLE_2RANKS); // TODO In argument
    if(USE_DMA) { // TODO DMA in other class
        LL_ADC_REG_SetDMATransfer(adc_conf.ADC, LL_ADC_REG_DMA_TRANSFER_UNLIMITED);
        LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA1);
        LL_DMA_SetPeriphAddress(DMA1, LL_DMA_CHANNEL_1, LL_ADC_DMA_GetRegAddr(adc_conf.ADC, LL_ADC_DMA_REG_REGULAR_DATA));
        LL_DMA_SetMemoryAddress(DMA1, LL_DMA_CHANNEL_1, (uint32_t)&(adc_conf.data));
        LL_DMA_SetDataTransferDirection(DMA1, LL_DMA_CHANNEL_1, LL_DMA_DIRECTION_PERIPH_TO_MEMORY);
        LL_DMA_SetMemoryIncMode(DMA1, LL_DMA_CHANNEL_1, LL_DMA_MEMORY_INCREMENT);

    }
    LL_ADC_SetChannelSamplingTime(adc_conf.ADC, LL_ADC_CHANNEL_8, SAMPLING_TIME);
    LL_ADC_SetChannelSamplingTime(adc_conf.ADC, LL_ADC_CHANNEL_9, SAMPLING_TIME);
    LL_ADC_EnableIT_EOS(adc_conf.ADC);
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