#include "stm32_conf.h"

rcc Rcc1;
adc Adc1;
indicator Indicator1(IND_DIGIT_1, IND_PRECISION_0, IND_PERIOD_5_MS);
indicator Indicator2(IND_DIGIT_1, IND_PRECISION_0, IND_PERIOD_5_MS);
//usart Usart2(USART2, 115200);

float i1 = 0;
float i2 = 0;

void vTask1(void *pvParameters) {
    Indicator1.SetDigit(1, GPIOA, GPIO_PIN_8);
    Indicator2.SetDigit(1, GPIOA, GPIO_PIN_9);
    Indicator1.Init();
    Indicator2.Init();
    while(1){
        Indicator1.Print(i1);
        Indicator2.Print(i2);
    }
}

void vTask2(void *pvParameters) {
    Adc1.Init(ADC1);
    while(1){
        vTaskDelay(10);
        i1 = Adc1.buf[0] * 3.3 / (0x0FFF);
        i2 = Adc1.buf[1] * 3.3 / (0x0FFF);
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
    Rcc1.Init();
    //adc1.Init();
    xTaskCreate(vTask1, "LED control", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    xTaskCreate(vTask2, "Increment", configMINIMAL_STACK_SIZE, NULL, 2, NULL);
    //xTaskCreate(vTask3, "Send", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    vTaskStartScheduler();
    while(1){  
    }
}