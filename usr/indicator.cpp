#include "indicator.h"

static SemaphoreHandle_t mutex;

// TODO optimizate code
void indicator::Init(void) {
    for(int i = 0; i < ind.digits; i++) {
        PinInit(ind.digit[i]);
    }
    for(int i = 0; i < 8; i++) {
        PinInit(ind.segment[i]);
    }
    if(mutex == NULL) {
        mutex = xSemaphoreCreateMutex();
    }
}

void indicator::Print(float number) {
    if(xSemaphoreTake(mutex, pdMS_TO_TICKS(ind.period_ms)) == pdTRUE) {
    float2digits(number, dig, ind.precision, ind.digits);
    for(int i = 0; i < ind.digits; i++) {
        OnDigit(i);
        PrintDigit(dig[i]);
        if(ind.precision == i && ind.precision != 0) {
            SetDot();
        }
        vTaskDelay(ind.period_ms);
    }
    ResetSegments();
    ResetDigits();
    xSemaphoreGive(mutex);
    }
    portYIELD();
}

void indicator::SetDigit(uint8_t number, GPIO_TypeDef *GPIO, uint16_t GPIO_PIN) {
    ind.digit[number - 1].GPIOx = GPIO;
    ind.digit[number - 1].GPIO_PIN = GPIO_PIN;
}

// TODO add norm decoder
void indicator::PrintDigit(uint8_t digit) {
    ResetSegments();
    switch(digit) {
        case 0:
            Set(a | b | c | d | e | f);
            break;
        case 1:
            Set(b | c);
            break;
        case 2:
            Set(a | b | g | e | d);
            break;
        case 3:
            Set(a | b | c | d | g);
            break;
        case 4:
            Set(b | c | f | g);
            break;
        case 5:
            Set(a | c | d | f | g);
            break;
        case 6:
            Set(a | c | d | e | f | g);
            break;
        case 7:
            Set(a | b | c);
            break;
        case 8:
            Set(a | b | c | d | e | f | g);
            break;
        case 9:
            Set(a | b | c | d | f | g);
            break;
    }
}

void indicator::Set(uint8_t pin) {
    for(int i = 0; i < 8; i++) {
        if(pin & (1 << i)) {
            HAL_GPIO_WritePin(ind.segment[i].GPIOx, ind.segment[i].GPIO_PIN, GPIO_PIN_SET);
        }
        else {
            HAL_GPIO_WritePin(ind.segment[i].GPIOx, ind.segment[i].GPIO_PIN, GPIO_PIN_RESET);
        }
    }
}

void indicator::SetDot(void) {
    HAL_GPIO_WritePin(ind.segment[7].GPIOx, ind.segment[7].GPIO_PIN, GPIO_PIN_SET);
}


void indicator::OnDigit(uint8_t digit) {
    if(digit > 0) {
        HAL_GPIO_WritePin(ind.digit[digit - 1].GPIOx, ind.digit[digit - 1].GPIO_PIN, GPIO_PIN_RESET);
    }
    HAL_GPIO_WritePin(ind.digit[digit].GPIOx, ind.digit[digit].GPIO_PIN, GPIO_PIN_SET);
}

void indicator::ResetDigits(void) {
    for(int i = 0; i < ind.digits; i++) {
        HAL_GPIO_WritePin(ind.digit[i].GPIOx, ind.digit[i].GPIO_PIN, GPIO_PIN_RESET);
    }
}

void indicator::ResetSegments(void) {
    Set(0b00000000);
}

void indicator::PinInit(pin_t pin) {
    GPIO_InitTypeDef GPIO_InitStructure;
    if(pin.GPIOx == GPIOA) {
        __HAL_RCC_GPIOA_CLK_ENABLE();
    } else if(pin.GPIOx == GPIOB) {
        __HAL_RCC_GPIOB_CLK_ENABLE();
    } else if(pin.GPIOx == GPIOC) {
        __HAL_RCC_GPIOC_CLK_ENABLE();
    } else if(pin.GPIOx == GPIOD) {
        __HAL_RCC_GPIOD_CLK_ENABLE();
    } else if(pin.GPIOx == GPIOE) {
        __HAL_RCC_GPIOE_CLK_ENABLE();
    }
    GPIO_InitStructure.Pin = pin.GPIO_PIN;
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(pin.GPIOx, &GPIO_InitStructure);
}