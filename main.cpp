#include "stm32_conf.h"

rcc_class rcc;
adc_class adc(ADC1);
usart_class usart(&usart_cfg);
indicator_class indicator1(&indicator1_cfg);
indicator_class indicator2(&indicator2_cfg);

struct meas_t {
    float voltage;
    float current;
};

meas_t meas;

void Proccesing(void *pvParameters) {
    adc.Init();
    while(1){
        meas.voltage = adc.buf[0] * ADC_SCALE;
        meas.current = adc.buf[1] * ADC_SCALE;
        vTaskDelay(50);
    }
}

void Indicator1Print(void *pvParameters) {
    indicator1.Init();
    while(1){
        indicator1.Print(meas.voltage);
    }
}

void Indicator2Print(void *pvParameters) {
    indicator2.Init();
    while(1){
        indicator2.Print(meas.current);
    }
}

void SendMeas(void *pvParameters) {
    int status;

    GPIO_InitTypeDef GPIO_InitStructure;

    usart.Init();

    while(1) {
        usart.Transmit((uint8_t *)(&meas.voltage), 4);
        usart.Transmit((uint8_t *)(&meas.current), 4);
        vTaskDelay(200);
    }
}

int main(void) {
    HAL_Init();
    rcc.InitClock();
    xTaskCreate(Indicator1Print, "Indicator1", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    xTaskCreate(Indicator2Print, "Indicator2", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    xTaskCreate(Proccesing, "ADC proccesing", configMINIMAL_STACK_SIZE, NULL, 3, NULL);
    xTaskCreate(SendMeas, "Sending", configMINIMAL_STACK_SIZE, NULL, 2, NULL);
    vTaskStartScheduler();
    while(1){  
    }
}

extern "C" {
    void USART3_IRQHandler(void) {
        usart.Handler();
    }
}
