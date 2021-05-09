#include <stm32f103xb.h>
#define a ind.segment[0]
#define b ind.segment[1]
#define c ind.segment[2]
#define d ind.segment[3]
#define e ind.segment[4]
#define f ind.segment[5]
#define g ind.segment[6]
#define dot ind.segment[7]

typedef struct pin_struct{
    GPIO_TypeDef *GPIOx;
    int LL_PIN;
} pin_t;

typedef struct indicator_struct{
    pin_t segment[8]; // a,b,c,d,e,f,d,dot
    pin_t digit[4];
    int digits;
    int precision; 
} indicator_t;

class indicator {
    private:
        void ClockInit(pin_t pin);
        void ModeInit(pin_t pin);
        void Set(pin_t pin);
        void Reset(pin_t pin);
        void ResetAll(void);
        int dig[4] = {0, 0, 0, 0};
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
