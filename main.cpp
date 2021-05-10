#include "stm32f103_conf.h"

indicator Indicator;
float i = 0;

void vTask1(void *pvParameters) {
    while(1){
        Indicator.Print(i);
    }
}


void vTask2(void *pvParameters) {
    while(1){
        i += 1;
        vTaskDelay(100);
    }
}


int main(void) {
    rcc_config();
    gpio_config();
    Indicator.Init();
    Indicator.SetPrecision(0);
    xTaskCreate(vTask1, "LED control", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    xTaskCreate(vTask2, "Increment", configMINIMAL_STACK_SIZE, NULL, 2, NULL);
    vTaskStartScheduler();
    while(1){  
    }
}
