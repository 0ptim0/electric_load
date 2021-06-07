#include "stm32_base.h"
#include "gpio.h"

#define a   0b00000001
#define b   0b00000010
#define c   0b00000100
#define d   0b00001000
#define e   0b00010000
#define f   0b00100000
#define g   0b01000000
#define dot 0b10000000
#define DIG_NUM 8

typedef struct {
    pin_t segment[8]; // a,b,c,d,e,f,d,dot
    pin_t digit[DIG_NUM];
    uint8_t digits = [DIG_NUM];
    uint8_t precision; 
} indicator_t;

class indicator {
private:
    void PinInit(pin_t pin);
    void PrintDigit(int pin);
    void Set(int pin);
    void SetDot(void);
    void ResetAllSegments(void);
    void ChangeDigit(void);
    int dig[4] = {0, 0, 0, 0};
    int now = -1;
public:
    indicator_t ind;
    indicator() {
        ind.segment[0] = {GPIOA, LL_GPIO_PIN_0};
        ind.segment[1] = {GPIOA, LL_GPIO_PIN_1};
        ind.segment[2] = {GPIOA, LL_GPIO_PIN_2};
        ind.segment[3] = {GPIOA, LL_GPIO_PIN_3};
        ind.segment[4] = {GPIOA, LL_GPIO_PIN_4};
        ind.segment[5] = {GPIOA, LL_GPIO_PIN_5};
        ind.segment[6] = {GPIOA, LL_GPIO_PIN_6};
        ind.segment[7] = {GPIOA, LL_GPIO_PIN_7};
        ind.digit[0] = {GPIOA, LL_GPIO_PIN_8};
        ind.digit[1] = {GPIOA, LL_GPIO_PIN_9};
        ind.digit[2] = {GPIOA, LL_GPIO_PIN_10};
        ind.digit[3] = {GPIOA, LL_GPIO_PIN_11};
        ind.precision = 1;
        ind.digits = 4;
    }
    void SetPrecision(int prec);
    void SetDigits(int dig);
    void Init(void);
    void Print(float number);
};
