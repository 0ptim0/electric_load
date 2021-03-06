#pragma once
#include "stm32_conf.h"

#define LOAD_ADDR       0x40
#define LOAD_TM_CMD     0x83

#define MAX_VOLTAGE     200
#define MIN_VOLTAGE     0
#define MAX_CURRENT     100
#define MIN_CURRENT     0

#define LOAD_CURRENT_SENSE       50
#define LOAD_VOLTAGE_SENSE       51.8083

#define PIN_USART_TX    {GPIOB, {GPIO_PIN_10, GPIO_MODE_AF_PP, GPIO_PULLUP, GPIO_SPEED_FREQ_HIGH}}
#define PIN_USART_RX    {GPIOB, {GPIO_PIN_11, GPIO_MODE_AF_INPUT, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH}}

#define PIN_SEG_A       {GPIOA, {GPIO_PIN_3, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH}}
#define PIN_SEG_B       {GPIOB, {GPIO_PIN_2, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH}}
#define PIN_SEG_C       {GPIOB, {GPIO_PIN_1, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH}}
#define PIN_SEG_D       {GPIOA, {GPIO_PIN_6, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH}}
#define PIN_SEG_E       {GPIOA, {GPIO_PIN_7, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH}}
#define PIN_SEG_F       {GPIOA, {GPIO_PIN_4, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH}}
#define PIN_SEG_G       {GPIOB, {GPIO_PIN_0, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH}}
#define PIN_SEG_DOT     {GPIOA, {GPIO_PIN_5, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH}}

#define PIN_DIG1_1      {GPIOB, {GPIO_PIN_12, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH}}
#define PIN_DIG1_2      {GPIOB, {GPIO_PIN_15, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH}}
#define PIN_DIG1_3      {GPIOB, {GPIO_PIN_14, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH}}
#define PIN_DIG1_4      {GPIOB, {GPIO_PIN_13, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH}}

#define PIN_DIG2_1      {GPIOA, {GPIO_PIN_8, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH}}
#define PIN_DIG2_2      {GPIOA, {GPIO_PIN_9, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH}}
#define PIN_DIG2_3      {GPIOA, {GPIO_PIN_10, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH}}

const gpio_cfg_t tx = PIN_USART_TX;
const gpio_cfg_t rx = PIN_USART_RX;

const usart_cfg_t usart_cfg = {USART3, &tx, &rx, 115200, 25};

const indicator_cfg_t indicator1_cfg = 
    {
        {PIN_SEG_A, PIN_SEG_B, PIN_SEG_C, PIN_SEG_D, PIN_SEG_E, PIN_SEG_F, PIN_SEG_G, PIN_SEG_DOT},
        {PIN_DIG1_1, PIN_DIG1_2, PIN_DIG1_3, PIN_DIG1_4}, IND_DIGIT_4, IND_PRECISION_1, IND_PERIOD_10_MS
    };

const indicator_cfg_t indicator2_cfg = 
    {
        {PIN_SEG_A, PIN_SEG_B, PIN_SEG_C, PIN_SEG_D, PIN_SEG_E, PIN_SEG_F, PIN_SEG_G, PIN_SEG_DOT},
        {PIN_DIG2_1, PIN_DIG2_2, PIN_DIG2_3, NULL}, IND_DIGIT_3, IND_PRECISION_1, IND_PERIOD_10_MS
    };
