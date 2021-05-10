#include "stm32f103_conf.h"

// TODO: optimizate code

void indicator::Init(void) {
    for(int i = 0; i < ind.digits; i++) {
        ClockInit(ind.digit[i]);
        ModeInit(ind.digit[i]);
    }
    for(int i = 0; i < 8; i++) {
        ClockInit(ind.segment[i]);
        ModeInit(ind.segment[i]);
    }
}

void indicator::SetPrecision(int prec) {
    prec = (prec > 3 ? 3 : prec);
    prec = (prec < 0 ? 0 : prec);
    ind.precision = prec;
}

void indicator::SetDigits(int dig) {
    dig = (dig > 4 ? 4 : dig);
    dig = (dig < 0 ? 0 : dig);
    ind.digits = dig;
}

void indicator::Print(float number) {
    float2digits(number, dig, ind.precision, ind.digits);
    for(int i = 0; i < ind.digits; i++) {
        ChangeDigit();
        PrintDigit(dig[i]);
        vTaskDelay(5);
    }
}

// TODO: add norm decoder
void indicator::PrintDigit(int digit) {
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

void indicator::Set(int pin) {
    for(int i = 0; i < 8; i++) {
        if(pin & (1 << i)) {
            LL_GPIO_SetOutputPin(ind.segment[i].GPIOx, ind.segment[i].LL_PIN);
        }
        else {
            LL_GPIO_ResetOutputPin(ind.segment[i].GPIOx, ind.segment[i].LL_PIN);
        }
    }
}

void indicator::ChangeDigit(void) {
    LL_GPIO_ResetOutputPin(ind.digit[now].GPIOx, ind.digit[now].LL_PIN);
    if(now == (ind.digits - 1)) {
        now = 0;
    } else {
        now++;
    }
    LL_GPIO_SetOutputPin(ind.digit[now].GPIOx, ind.digit[now].LL_PIN);
}

void indicator::ResetAllSegments(void) {
    Set(0b00000000);
}

void indicator::ModeInit(pin_t pin) {
    LL_GPIO_SetPinMode(pin.GPIOx, pin.LL_PIN, LL_GPIO_MODE_OUTPUT);
    LL_GPIO_SetPinOutputType(pin.GPIOx, pin.LL_PIN, LL_GPIO_OUTPUT_PUSHPULL);
    LL_GPIO_SetPinSpeed(pin.GPIOx, pin.LL_PIN, LL_GPIO_SPEED_FREQ_HIGH);
}

void indicator::ClockInit(pin_t pin) {
    if(pin.GPIOx == GPIOA) {
        LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOA);
    } else if(pin.GPIOx == GPIOB) {
        LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOB);
    } else if(pin.GPIOx == GPIOC) {
        LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOC);
    } else if(pin.GPIOx == GPIOD) {
        LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOD);
    } else if(pin.GPIOx == GPIOE) {
        LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOE);
    }
}