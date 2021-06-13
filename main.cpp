#include "stm32_conf.h"

rcc Rcc1;
adc Adc1(ADC1);
indicator Indicator1(IND_DIGIT_2, IND_PRECISION_1, IND_PERIOD_5_MS);
usart Usart3(USART3, 115200);

float value;

void Indicator(void *pvParameters) {
    Indicator1.SetDigit(1, GPIOA, GPIO_PIN_8);
    Indicator1.SetDigit(2, GPIOA, GPIO_PIN_9);
    Indicator1.Init();
    while(1){
        Indicator1.Print(value);
    }
}

void Measurement(void *pvParameters) {
    Adc1.Init();
    while(1){
        vTaskDelay(1000);
        value = Adc1.buf[0] * 3.3 / (0x0FFF);
        vTaskDelay(1000);
        value = Adc1.buf[1] * 3.3 / (0x0FFF);
    }
}

void Print(void *pvParameters) {
    GPIO_InitTypeDef GPIO_InitStructure;
    __HAL_RCC_GPIOB_CLK_ENABLE();
    GPIO_InitStructure.Pin = GPIO_PIN_10;
    GPIO_InitStructure.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStructure.Speed = GPIO_SPEED_HIGH;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_InitStructure.Pin = GPIO_PIN_11;
    GPIO_InitStructure.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStructure.Speed = GPIO_SPEED_HIGH;
    Usart3.Init();
    HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);
    static uint8_t buf = 0;
    while(1){
        vTaskDelay(1);
        Usart3.Transmit(&buf, 1);
        buf++;
    }
}

int main(void) {
    HAL_Init();
    Rcc1.Init();
    xTaskCreate(Indicator, "Indicator", configMINIMAL_STACK_SIZE, NULL, 2, NULL);
    xTaskCreate(Measurement, "Measurement", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    xTaskCreate(Print, "Print", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    vTaskStartScheduler();
    while(1){  
    }
}