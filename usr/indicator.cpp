#include "indicator.h"

static SemaphoreHandle_t mutex;

indicator_class::indicator_class(const indicator_cfg_t *const cfg) 
            : cfg(cfg)           
{
    for(int i = 0; i < 8; i++) {
        seg[i].SetConf(&cfg->seg[i]);
        if(i < cfg->digits) {
            dig[i].SetConf(&cfg->dig[i]);
        }
    }
}

int indicator_class::Init(void) {
    int rv = 0;

    for(int i = 0; i < 8; i++) {
        rv |= seg[i].SetConf(&cfg->seg[i]);
        if(i < cfg->digits) {
            rv |= dig[i].SetConf(&cfg->dig[i]);
        }
    }
    
    if(mutex == NULL) mutex = xSemaphoreCreateMutex();
    else return EINVAL;
    
    return rv;
}

void indicator_class::Print(float number) {
    if(xSemaphoreTake(mutex, pdMS_TO_TICKS(cfg->timeout)) == pdTRUE) {
        float2digits(number, digits, cfg->precision, cfg->digits);
        for(int i = 0; i < cfg->digits; i++) {
            OnDigit(i);
            PrintDigit(digits[i]);
            if(cfg->precision == i && cfg->precision != 0) {
                SetDot();
            }
            vTaskDelay(cfg->timeout);
            ResetDigits();
            xSemaphoreGive(mutex);
            portYIELD();
        }
        ResetSegments();
        ResetDigits();
    }
}

// TODO add norm decoder
void indicator_class::PrintDigit(uint8_t digit) {
    ResetSegments();
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

void indicator_class::Set(uint8_t pin) {
    for(int i = 0; i < 8; i++) {
        if(pin & (1 << i)) {
            seg[i].SetOn();
        }
        else {
            seg[i].SetOff();
        }
    }
}

void indicator_class::SetDot(void) {
    seg[7].SetOn();
}


void indicator_class::OnDigit(uint8_t digit) {
    if(digit > 0) {
        dig[digit - 1].SetOff();
    }
    dig[digit].SetOn();
}

void indicator_class::ResetDigits(void) {
    for(int i = 0; i < cfg->digits; i++) {
        dig[i].SetOff();
    }
}

void indicator_class::ResetSegments(void) {
    Set(0b00000000);
}
