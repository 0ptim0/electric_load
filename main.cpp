#include "stm32f103_conf.h"

indicator Indicator;
adc adc1;
float i = 0;

void vTask1(void *pvParameters) {
    while(1){
        Indicator.Print(i);
    }
}

void vTask2(void *pvParameters) {
    while(1){
        i = adc1.adc_conf.data[0] * 3.3 / (0x0fff);
        vTaskDelay(100);
    }
}

int main(void) {
    rcc_config();
    Indicator.Init();
    Indicator.SetPrecision(1);
    adc1.Init();
    xTaskCreate(vTask1, "LED control", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    xTaskCreate(vTask2, "Increment", configMINIMAL_STACK_SIZE, NULL, 2, NULL);
    vTaskStartScheduler();
    while(1){  
    }
}

void DMA1_Channel1_IRQHandler(void) {
}
