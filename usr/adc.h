#include "stm32f103xb.h"
#include "gpio.h"

#define SAMPLING_TIME LL_ADC_SAMPLINGTIME_239CYCLES_5

typedef struct {
    ADC_TypeDef *ADC;
    pin_t channel[15];
} adc_t;

class adc {
    private:
        adc_t adc;
        void PinInit(pin_t pin);
        void ConfigInit(void);
    public:
        void Init(void);
        void EnableChannel(void);
};