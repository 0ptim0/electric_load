#include <stm32f103xb.h>

typedef struct pin_t{
    GPIO_TypeDef *GPIOx;
    uint32_t LL_PIN;
} pin_t;

typedef struct indicator_t{
    pin_t a; 
    pin_t b; 
    pin_t c; 
    pin_t d; 
    pin_t e; 
    pin_t f; 
    pin_t g; 
    pin_t dot; 
    pin_t dig1; 
    pin_t dig2; 
    pin_t dig3; 
    pin_t dig4; 
    uint8_t precision; 
} indicator_t;

class indicator{
    private:
        indicator_t i;
        void float2digits(float number);
    public:
        void set(uint8_t);
        void init(void);
        void print(float number);
};
