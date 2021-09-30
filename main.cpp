#include "stm32_conf.h"

rcc_class rcc;
adc_class adc(ADC1);
usart_class usart(&usart_cfg);
indicator_class indicator1(&indicator1_cfg);
indicator_class indicator2(&indicator2_cfg);
wake_class wake;
wake_packet_t tm;

struct meas_t {
    uint32_t voltage;
    uint32_t current;
};

meas_t meas;

void Proccesing(void *pvParameters) {
    adc.Init();
    while(1){
        meas.voltage = static_cast<uint32_t>(adc.buf[0] * ADC_SCALE * 1000);
        meas.current = static_cast<uint32_t>(adc.buf[1] * ADC_SCALE * 1000);
        vTaskDelay(50);
    }
}

void Indicator1Print(void *pvParameters) {
    indicator1.Init();
    while(1){
        indicator1.Print(meas.voltage / 1000.0);
    }
}

void Indicator2Print(void *pvParameters) {
    indicator2.Init();
    while(1){
        indicator2.Print(meas.current / 1000.0);
    }
}

void SendMeas(void *pvParameters) {
    uint8_t data[2];
    data[0] =  0xAB;
    data[1] =  0xCD;

    usart.Init();

    tm.to = LOAD_ADDR;
    tm.cmd = LOAD_TM_CMD;
    tm.data = data;
    tm.length = 2;

    while(1) {
        if(!wake.Packing(&tm)) {
            usart.Transmit(wake.GetBufPtr(), wake.GetBufLength());
        }
        vTaskDelay(50);
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
