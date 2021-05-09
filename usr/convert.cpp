void float2digits(float number, int (&dig)[4], int precision, int digits) {
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
    dig[0] = ((int)number / 1000);
    dig[1] = ((int)number - dig[0] * 1000) / 100;
    dig[2] = ((int)number - dig[0] * 1000 - dig[1] * 100) / 10;
    dig[3] = ((int)number - dig[0] * 1000 - dig[1] * 100 - dig[2] * 10) / 1;

    if((4 - digits) > 9) {
        dig[0] = -1;
    }
}