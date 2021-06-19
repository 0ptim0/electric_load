#include "stm32_base.h"

// TODO work with dot: Think about form variables (bin or dec) and return value or change by link.
void float2digits(float number, uint8_t (&dig)[4], uint8_t precision, uint8_t digits) {
    int overflow = 0;
    switch (precision) {
        case 0:
            break;
        case 1:
            number *= 10;
            break;
        case 2:
            number *= 100;
            break;
        case 3:
            number *= 1000;
            break;
        default:
            number *= 10;
            break;
    }

    if((number - (int)number) >= 0.5) {
        number += 1;
    }
    
    dig[3] = ((int)number / 1000);
    dig[2] = ((int)number - dig[3] * 1000) / 100;
    dig[1] = ((int)number - dig[3] * 1000 - dig[2] * 100) / 10;
    dig[0] = ((int)number - dig[3] * 1000 - dig[2] * 100 - dig[1] * 10) / 1;

    if((4 - digits) > 9) {
        dig[0] = -1;
    }
}

void float2uint8(float *number, uint8_t *buf) {
    buf = (uint8_t *)number;
    buf = (unsigned char *)number;
}