#include "stm32_conf.h"

indicator Indicator;
//adc adc1;
//usart usart2(USART2, 115200);

float i = 0;

void vTask1(void *pvParameters) {
    while(1){
        Indicator.Print(i);
    }
}

void vTask2(void *pvParameters) {
    while(1){
        //i = adc1.adc_conf.data[0] * 3.3 / (0x0fff);
        vTaskDelay(1000);
        //i = adc1.adc_conf.data[1] * 3.3 / (0x0fff);
        vTaskDelay(1000);
    }
}

void vTask3(void *pvParameters) {
    __HAL_RCC_GPIOC_CLK_ENABLE();
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.Pin = GPIO_PIN_13;
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Speed= GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStructure);
    while(1){
        //usart2.Print("\nHELLO\n");
        vTaskDelay(1000);
        HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
    }
}

int main(void) {
    HAL_Init();
    rcc_config();
    Indicator.Init();
    Indicator.SetPrecision(1);
    //adc1.Init();
    //xTaskCreate(vTask1, "LED control", configMINIMAL_STACK_SIZE, NULL, 3, NULL);
    //xTaskCreate(vTask2, "Increment", configMINIMAL_STACK_SIZE, NULL, 2, NULL);
    xTaskCreate(vTask3, "Send", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    vTaskStartScheduler();
    while(1){  
    }
}