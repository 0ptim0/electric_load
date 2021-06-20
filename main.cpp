#include "stm32_conf.h"

rcc Rcc1;
adc Adc1(ADC1);
indicator Indicator1(IND_DIGIT_1, IND_PRECISION_0, IND_PERIOD_5_MS);
indicator Indicator2(IND_DIGIT_1, IND_PRECISION_0, IND_PERIOD_5_MS);
usart Usart3(USART3, 115200);

float measurement[2] = {0, 0};

void IndicatorPrint(void *pvParameters) {
    Adc1.Init();
    Indicator1.SetDigit(1, GPIOA, GPIO_PIN_8);
    Indicator2.SetDigit(1, GPIOA, GPIO_PIN_9);
    Indicator1.Init();
    Indicator2.Init();
    while(1){
        measurement[0] = Adc1.buf[0] * 3.3 / (0x0FFF);
        measurement[1] = Adc1.buf[1] * 3.3 / (0x0FFF);
        Indicator1.Print(measurement[0]);
        Indicator2.Print(measurement[1]);
    }
}

void UARTSend(void *pvParameters) {
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

    while(1) {
        vTaskDelay(1000);
        status = Usart3.Transmit((uint8_t *)(measurement + 1), 4);
        status = Usart3.Transmit((uint8_t *)measurement, 4);
    }
}

int main(void) {
    HAL_Init();
    Rcc1.Init();
    xTaskCreate(IndicatorPrint, "Indicator", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    xTaskCreate(UARTSend, "Sending", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    vTaskStartScheduler();
    while(1){  
    }
}
extern "C" {
void USART3_IRQHandler(void) {
    Usart3.Handle();
}
}
