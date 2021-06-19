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

typedef struct {
    pin_t segment[8]; // a,b,c,d,e,f,d,dot
    pin_t digit[DIG_NUM];
    uint8_t digits;
    uint8_t precision;
    uint8_t period_ms;
} indicator_t;

class indicator {
private:
    void PinInit(pin_t pin);
    void PrintDigit(uint8_t pin);
    void OnDigit(uint8_t digit);
    void Set(uint8_t pin);
    void SetDot(void);
    void ResetSegments(void);
    void ResetDigits(void);
    uint8_t dig[4];
public:
    indicator_t ind;
    indicator(uint8_t digits, uint8_t precision, uint8_t period_ms) {
        ind.segment[0] = {GPIOA, GPIO_PIN_0};
        ind.segment[1] = {GPIOA, GPIO_PIN_1};
        ind.segment[2] = {GPIOA, GPIO_PIN_2};
        ind.segment[3] = {GPIOA, GPIO_PIN_3};
        ind.segment[4] = {GPIOA, GPIO_PIN_4};
        ind.segment[5] = {GPIOA, GPIO_PIN_5};
        ind.segment[6] = {GPIOA, GPIO_PIN_6};
        ind.segment[7] = {GPIOA, GPIO_PIN_7};
        ind.digit[0] = {GPIOA, GPIO_PIN_8};
        ind.digit[1] = {GPIOA, GPIO_PIN_9};
        ind.digit[2] = {GPIOA, GPIO_PIN_10};
        ind.digit[3] = {GPIOA, GPIO_PIN_11};
        ind.precision = precision;
        ind.digits = digits;
        ind.period_ms = period_ms;
    }
    void SetDigit(uint8_t number, GPIO_TypeDef *GPIO, uint16_t GPIO_PIN);
    void Init(void);
    void Print(float number);
};
