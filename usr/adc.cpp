#include "stm32_conf.h"
#include "gpio.h"
#include "adc.h"

void adc::Init(void){
    if(ADC_InitStructure.Instance == ADC1) {
        __HAL_RCC_ADC1_CLK_ENABLE();
    } else if(ADC_InitStructure.Instance == ADC2) {
        __HAL_RCC_ADC2_CLK_ENABLE();
    }
    ConfigInit();
}

void adc::ConfigInit(void) {
    ADC_InitStructure.Init.ScanConvMode = ENABLE;
    ADC_InitStructure.Init.ContinuousConvMode = ENABLE;
    ADC_InitStructure.Init.DataAlign = ADC_DATAALIGN_RIGHT;
    ADC_InitStructure.Init.NbrOfConversion = 2;
    ADC_InitStructure.Init.ExternalTrigConv = ADC_SOFTWARE_START;
    // TODO Add DMA from HAL
    /*LL_ADC_REG_SetContinuousMode(adc_conf.ADC, LL_ADC_REG_CONV_CONTINUOUS); // TODO In argument
    LL_ADC_SetDataAlignment(adc_conf.ADC, LL_ADC_DATA_ALIGN_RIGHT);
    LL_ADC_SetSequencersScanMode(adc_conf.ADC, LL_ADC_SEQ_SCAN_ENABLE);
    LL_ADC_REG_SetSequencerLength(adc_conf.ADC, LL_ADC_REG_SEQ_SCAN_ENABLE_2RANKS); // TODO In argument
    if(USE_DMA) { // TODO DMA in other class
        LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA1);
        LL_ADC_REG_SetDMATransfer(adc_conf.ADC, LL_ADC_REG_DMA_TRANSFER_UNLIMITED);
        LL_DMA_SetPeriphAddress(DMA1, LL_DMA_CHANNEL_1, LL_ADC_DMA_GetRegAddr(adc_conf.ADC, LL_ADC_DMA_REG_REGULAR_DATA));
        LL_DMA_SetMemoryAddress(DMA1, LL_DMA_CHANNEL_1, (uint32_t)&(adc_conf.data));
        LL_DMA_SetDataTransferDirection(DMA1, LL_DMA_CHANNEL_1, LL_DMA_DIRECTION_PERIPH_TO_MEMORY);
        LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_1, 2);
        LL_DMA_SetPeriphIncMode(DMA1, LL_DMA_CHANNEL_1, LL_DMA_PERIPH_NOINCREMENT);
        LL_DMA_SetMemoryIncMode(DMA1, LL_DMA_CHANNEL_1, LL_DMA_MEMORY_INCREMENT);
        LL_DMA_SetPeriphSize(DMA1, LL_DMA_CHANNEL_1, LL_DMA_PDATAALIGN_HALFWORD);
        LL_DMA_SetMemorySize(DMA1, LL_DMA_CHANNEL_1, LL_DMA_MDATAALIGN_HALFWORD);
        LL_DMA_SetMode(DMA1, LL_DMA_CHANNEL_1, LL_DMA_MODE_CIRCULAR);
        LL_DMA_SetChannelPriorityLevel(DMA1, LL_DMA_CHANNEL_1, LL_DMA_PRIORITY_HIGH);
        NVIC_SetPriority(DMA1_Channel1_IRQn, 11);
        NVIC_EnableIRQ(DMA1_Channel1_IRQn);
        LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_1);
    }
    LL_ADC_REG_SetTriggerSource(adc_conf.ADC, LL_ADC_REG_TRIG_SOFTWARE);
    LL_ADC_REG_SetSequencerRanks(adc_conf.ADC, LL_ADC_REG_RANK_1, LL_ADC_CHANNEL_8);
    LL_ADC_REG_SetSequencerRanks(adc_conf.ADC, LL_ADC_REG_RANK_2, LL_ADC_CHANNEL_9);
    LL_ADC_SetChannelSamplingTime(adc_conf.ADC, LL_ADC_CHANNEL_8, SAMPLING_TIME);
    LL_ADC_SetChannelSamplingTime(adc_conf.ADC, LL_ADC_CHANNEL_9, SAMPLING_TIME);
    LL_ADC_Enable(adc_conf.ADC);
    LL_ADC_REG_StartConversionSWStart(adc_conf.ADC);*/
    HAL_ADC_Init(&ADC_InitStructure);
}