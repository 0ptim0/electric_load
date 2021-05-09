#include "stm32f103_conf.h"

void vTask1(void *pvParameters) {
    
    while(1){

    }
}

int main(void) {
    rcc_config();
    gpio_config();
    xTaskCreate(vTask1, "LED control", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    vTaskStartScheduler();
    while(1){  
    }
}
