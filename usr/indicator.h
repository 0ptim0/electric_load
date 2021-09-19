#include "stm32_base.h"
#include "gpio.h"
#pragma once

#define a   0b00000001
#define b   0b00000010
#define c   0b00000100
#define d   0b00001000
#define e   0b00010000
#define f   0b00100000
#define g   0b01000000
#define dot 0b10000000
#define DIG_NUM 8 // TODO Parametrize this

#define IND_DIGIT_1 1
#define IND_DIGIT_2 2
#define IND_DIGIT_3 3
#define IND_DIGIT_4 4

#define IND_PRECISION_0 0
#define IND_PRECISION_1 1
#define IND_PRECISION_2 2
#define IND_PRECISION_3 3

#define IND_PERIOD_1_MS  1
#define IND_PERIOD_5_MS  5
#define IND_PERIOD_10_MS 10

struct indicator_cfg_t {
    const gpio_cfg_t seg[8];
    const gpio_cfg_t dig[4];
    uint8_t digits;
    uint8_t precision;
    uint8_t timeout;
};

class indicator_class {
private:
    const indicator_cfg_t *const cfg;
    gpio_class seg[8];
    gpio_class dig[4];
private:
    void PrintDigit(uint8_t pin);
    void OnDigit(uint8_t digit);
    void Set(uint8_t pin);
    void SetDot(void);
    void ResetSegments(void);
    void ResetDigits(void);
    uint8_t digits[4];
public:
    indicator_class(const indicator_cfg_t *const cfg);
    int Init(void);
    void SetDigit(uint8_t number, GPIO_TypeDef *GPIO, uint16_t GPIO_PIN);
    void Print(float number);
};
