#include "stm32_conf.h"

rcc_class rcc;
adc_class adc(ADC1);
usart_class usart(&usart_cfg);
indicator_class indicator1(&indicator1_cfg);
indicator_class indicator2(&indicator2_cfg);
wake_class wake;
wake_packet_t tm;

float current;
float voltage;
static filt_ma<2, 100, float> meas_filter;

struct meas_t {
    uint32_t voltage;
    uint32_t current;
};

meas_t meas;

void Proccesing(void *pvParameters) {
    float adc_voltage;
    float adc_current;

    adc.Init();
    while(1) {
        adc_voltage = static_cast<uint32_t>(adc.buf[1] * ADC_SCALE * 1000);
        adc_current = static_cast<uint32_t>(adc.buf[0] * ADC_SCALE * 1000);
        meas_filter.set_signal(in1, adc_voltage);
        meas_filter.set_signal(in2, adc_current);
        meas_filter.update();
        meas.voltage = meas_filter.get_signal(out1);
        meas.current = meas_filter.get_signal(out2);
        vTaskDelay(10);
    }
}

void Indicator1Print(void *pvParameters) {
    indicator1.Init();
    while(1) {
        voltage = meas.voltage / 1000.0 * 52.16279;
        voltage = deadzone(voltage, 0.1, 0);
        voltage = maxmin(voltage, MAX_VOLTAGE, MIN_VOLTAGE);
        if(voltage < 1) {
            indicator1.PrintNull();
        } else {
            indicator1.Print(voltage);
        }
    }
}

void Indicator2Print(void *pvParameters) {
    indicator2.Init();
    while(1) {
        current = meas.current / 1000.0;
        current = deadzone(current, 0.1, 0);
        current = maxmin(current, MAX_CURRENT, MIN_CURRENT);
        if(voltage < 1) {
            indicator2.PrintNull();
        } else {
            indicator2.Print(current);
        }
    }
}

void SendMeas(void *pvParameters) {

    usart.Init();

    tm.to = LOAD_ADDR;
    tm.cmd = LOAD_TM_CMD;
    tm.data = (uint8_t *)&meas;
    tm.length = 8;

    while(1) {
        if(!wake.Packing(&tm)) {
            usart.Transmit(wake.GetBufPtr(), wake.GetBufLength());
        }
        vTaskDelay(50);
    }
}

int main(void) {
    HAL_Init();
    rcc.InitClock();
    xTaskCreate(Indicator1Print, "Indicator1", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    xTaskCreate(Indicator2Print, "Indicator2", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    xTaskCreate(Proccesing, "ADC proccesing", configMINIMAL_STACK_SIZE, NULL, 3, NULL);
    xTaskCreate(SendMeas, "Sending", configMINIMAL_STACK_SIZE, NULL, 2, NULL);
    vTaskStartScheduler();
    while(1){  
    }
}

extern "C" {
    void USART3_IRQHandler(void) {
        usart.Handler();
    }
}
