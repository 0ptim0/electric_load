#include "stm32_conf.h"

rcc_class rcc;
adc_class adc(ADC1);
usart_class usart(&usart_cfg);
indicator_class indicator1(&indicator1_cfg);
indicator_class indicator2(&indicator2_cfg);

float meas[2];

void IndicatorPrint(void *pvParameters) {
    adc.Init();
    indicator1.Init();
    indicator2.Init();
    while(1){
        meas[0] = adc.buf[0] * ADC_SCALE;
        meas[1] = adc.buf[1] * ADC_SCALE;
        indicator1.Print(meas[0]);
        indicator2.Print(meas[1]);
    }
}

void SendMeas(void *pvParameters) {
    int status;

    GPIO_InitTypeDef GPIO_InitStructure;

    usart.Init();

    while(1) {
        usart.Transmit((uint8_t *)(meas + 1), 4);
        usart.Transmit((uint8_t *)(meas), 4);
        vTaskDelay(200);
    }
}

int main(void) {
    HAL_Init();
    rcc.InitClock();
    xTaskCreate(IndicatorPrint, "Indicator", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    xTaskCreate(SendMeas, "Sending", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    vTaskStartScheduler();
    while(1){  
    }
}

extern "C" {
    void USART3_IRQHandler(void) {
        usart.Handler();
    }
}
