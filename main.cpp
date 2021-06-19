#include "stm32_conf.h"

rcc Rcc1;
adc Adc1(ADC1);
indicator Indicator1(IND_DIGIT_1, IND_PRECISION_0, IND_PERIOD_5_MS);
indicator Indicator2(IND_DIGIT_1, IND_PRECISION_0, IND_PERIOD_5_MS);
usart Usart3(USART3, 115200);

float value;

void IndicatorPrint1(void *pvParameters) {
    Indicator1.SetDigit(1, GPIOA, GPIO_PIN_8);
    Indicator1.Init();
    while(1){
        Indicator1.Print(1);
    }
}

void IndicatorPrint2(void *pvParameters) {
    Indicator2.SetDigit(1, GPIOA, GPIO_PIN_9);
    Indicator2.Init();
    while(1){
        Indicator2.Print(0);
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
    int status;
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
    static uint8_t buf[8] = "Hello\n\r";
    while(1){
        vTaskDelay(1000);
        status = Usart3.Transmit(buf, 8);
    }
}

int main(void) {
    HAL_Init();
    Rcc1.Init();
    xTaskCreate(IndicatorPrint1, "Indicator", configMINIMAL_STACK_SIZE, NULL, 2, NULL);
    xTaskCreate(IndicatorPrint2, "Indicator", configMINIMAL_STACK_SIZE, NULL, 2, NULL);
    xTaskCreate(Measurement, "Measurement", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    xTaskCreate(Print, "Print", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    vTaskStartScheduler();
    while(1){  
    }
}
extern "C" {
void USART3_IRQHandler(void) {
    Usart3.Handle();
}
}
