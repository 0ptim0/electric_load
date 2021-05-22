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
    ConfigInit();
    //PinInit(adc_conf.channel[9]);
}

void adc::ConfigInit(void) {
    LL_ADC_REG_SetContinuousMode(adc_conf.ADC, LL_ADC_REG_CONV_CONTINUOUS); // TODO In argument
    LL_ADC_SetDataAlignment(adc_conf.ADC, LL_ADC_DATA_ALIGN_RIGHT);
    LL_ADC_SetSequencersScanMode(adc_conf.ADC, LL_ADC_SEQ_SCAN_DISABLE);
    LL_ADC_REG_SetSequencerLength(adc_conf.ADC, LL_ADC_REG_SEQ_SCAN_DISABLE); // TODO In argument
    if(USE_DMA) { // TODO DMA in other class
        LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA1);
        LL_ADC_REG_SetDMATransfer(adc_conf.ADC, LL_ADC_REG_DMA_TRANSFER_UNLIMITED);
        LL_DMA_SetPeriphAddress(DMA1, LL_DMA_CHANNEL_1, LL_ADC_DMA_GetRegAddr(adc_conf.ADC, LL_ADC_DMA_REG_REGULAR_DATA));
        LL_DMA_SetMemoryAddress(DMA1, LL_DMA_CHANNEL_1, (uint32_t)&(adc_conf.data));
        LL_DMA_SetDataTransferDirection(DMA1, LL_DMA_CHANNEL_1, LL_DMA_DIRECTION_PERIPH_TO_MEMORY);
        LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_1, 1);
        LL_DMA_SetPeriphIncMode(DMA1, LL_DMA_CHANNEL_1, LL_DMA_PERIPH_NOINCREMENT);
        LL_DMA_SetMemoryIncMode(DMA1, LL_DMA_CHANNEL_1, LL_DMA_MEMORY_INCREMENT);
        LL_DMA_SetPeriphSize(DMA1, LL_DMA_CHANNEL_1, LL_DMA_PDATAALIGN_HALFWORD);
        LL_DMA_SetMemorySize(DMA1, LL_DMA_CHANNEL_1, LL_DMA_MDATAALIGN_HALFWORD);
        LL_DMA_SetMode(DMA1, LL_DMA_CHANNEL_1, LL_DMA_MODE_CIRCULAR);
        LL_DMA_SetChannelPriorityLevel(DMA1, LL_DMA_CHANNEL_1, LL_DMA_PRIORITY_HIGH);
        NVIC_SetPriority(DMA1_Channel1_IRQn, 11);
        NVIC_EnableIRQ(DMA1_Channel1_IRQn);
        //LL_DMA_EnableIT_TC(DMA1, LL_DMA_CHANNEL_1);
        LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_1);
    }
    LL_ADC_REG_SetTriggerSource(adc_conf.ADC, LL_ADC_REG_TRIG_SOFTWARE);
    LL_ADC_REG_SetSequencerRanks(adc_conf.ADC, LL_ADC_REG_RANK_1, LL_ADC_CHANNEL_8);
    LL_ADC_SetChannelSamplingTime(adc_conf.ADC, LL_ADC_CHANNEL_8, SAMPLING_TIME);
    LL_ADC_Enable(adc_conf.ADC);
    LL_ADC_REG_StartConversionSWStart(adc_conf.ADC);
    //LL_ADC_EnableIT_EOS(adc_conf.ADC);
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