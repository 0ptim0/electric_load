#include <stm32f103xb.h>

typedef struct pin_struct{
    GPIO_TypeDef *GPIOx;
    int LL_PIN;
} pin_t;
