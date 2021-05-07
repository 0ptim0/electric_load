#include "stm32f103_conf.h"

int main(void) {
    rcc_config();
    gpio_config();
    //xTaskCreate(vTask1, "LED control", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    //vTaskStartScheduler();
    while(1){  
    }
}
