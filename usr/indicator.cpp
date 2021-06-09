#include "indicator.h"
#include "convert.h"

// TODO optimizate code
void indicator::Init(void) {
    for(int i = 0; i < ind.digits; i++) {
        PinInit(ind.digit[i]);
    }
    for(int i = 0; i < 8; i++) {
        PinInit(ind.segment[i]);
    }
}

void indicator::SetPrecision(uint8_t prec) {
    prec = (prec > 3 ? 3 : prec);
    prec = (prec < 0 ? 0 : prec);
    ind.precision = prec;
}

void indicator::SetDigits(uint8_t dig) {
    dig = (dig > 4 ? 4 : dig);
    dig = (dig < 0 ? 0 : dig);
    ind.digits = dig;
}

void indicator::Print(float number) {
    float2digits(number, dig, ind.precision, ind.digits);
    for(int i = 0; i < ind.digits; i++) {
        ChangeDigit();
        PrintDigit(dig[i]);
        if(ind.precision == i) {
            SetDot();
        }
        vTaskDelay(5);
    }
}

// TODO add norm decoder
void indicator::PrintDigit(uint8_t digit) {
    ResetAllSegments();
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


void indicator::ChangeDigit(void) {
    HAL_GPIO_WritePin(ind.digit[now].GPIOx, ind.digit[now].GPIO_PIN, GPIO_PIN_RESET);
    if(now == (ind.digits - 1)) {
        now = 0;
    } else {
        now++;
    }
    HAL_GPIO_WritePin(ind.digit[now].GPIOx, ind.digit[now].GPIO_PIN, GPIO_PIN_SET);
}

void indicator::ResetAllSegments(void) {
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