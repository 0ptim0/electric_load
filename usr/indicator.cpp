#include "stm32f103_conf.h"
#include <stdarg.h>
/*
static void PinClockInit(pin_t pin);
static void PinModeInit(pin_t pin);

void IndicatorInit(indicator_t indicator) {
    for(int i = 0; (i < (8 + indicator.digits)); i++) {
        PinClockInit(indicator.pin[i]);
        PinModeInit(indicator.pin[i]);
    }
}

void IndicatorPrint(float number, indicator_t indicator) {
    switch (indicator.precision) {
        case 1:
            number *= 10;
            break;
        case 2:
            number *= 100;
            break;
    }
    int dig1, dig2, dig3, dig4 = 0;
    dig1 = ((int)number / 1000);
    dig2 = ((int)number - dig1 * 1000) / 100;
    dig3 = ((int)number - dig1 * 1000 - dig2 * 100) / 10;
    dig4 = ((int)number - dig1 * 1000 - dig2 * 100 - dig3 * 10) / 1;
    if(dig1 > 9) {
        dig1 = dig2 = dig3 = dig4 = 9;
    }
}


static void PinModeInit(pin_t pin) {
    LL_GPIO_SetPinMode(pin.GPIOx, pin.LL_PIN, LL_GPIO_MODE_OUTPUT);
    LL_GPIO_SetPinOutputType(pin.GPIOx, pin.LL_PIN, LL_GPIO_OUTPUT_PUSHPULL);
    LL_GPIO_SetPinSpeed(pin.GPIOx, pin.LL_PIN, LL_GPIO_SPEED_FREQ_HIGH);
}

static void PinClockInit(pin_t pin) {
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
}*/