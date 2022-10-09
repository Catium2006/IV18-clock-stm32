#pragma once

#include <Arduino.h>

/*
    针脚定义
    PA0     温度计模拟输入
    PA1     荧光驱动DATA_IN
    PA2     荧光驱动STROBE
    PA3     荧光驱动CLOCK
    PA6     荧光管灯丝PWM
    PA7     荧光驱动BLANKING

    PA8     升压使能EN

    PB12    按键1       MODE
    PB13    按键2       SETTING
    PB14    按键3       NEXT
    PB15    按键4       UP

    PB6     BUZZER_PWM

    PB9     RTC_SCLK
    PB8     RTC_I/O
    PB7     RTC_RST

    PB0     天线
*/

#define P_TEMP PA0

#define P_VFD_DATA PA1
#define P_VFD_STROBE PA2
#define P_VFD_CLOCK PA3
#define P_VFD_BLANK PA7
#define P_VFD_FILAMENT PA6

#define P_POWER_EN PA8

#define P_KEY_A PB12
#define P_KEY_B PB13
#define P_KEY_C PB14
#define P_KEY_D PB15

#define P_RTC_SCLK PB9
#define P_RTC_IO PB8
#define P_RTC_RST PB7

#define P_BUZZER PB6

#define P_ANT PB0

#define P_LED PC13

void initPin() {
    //设置LED
    pinMode(P_LED, OUTPUT);
    //设置升压使能
    pinMode(P_POWER_EN, OUTPUT);
    //设置温度计模拟输入
    pinMode(P_TEMP, INPUT);
    //设置VFD驱动
    pinMode(P_VFD_BLANK, OUTPUT);
    pinMode(P_VFD_CLOCK, OUTPUT);
    pinMode(P_VFD_STROBE, OUTPUT);
    pinMode(P_VFD_DATA, OUTPUT);
    pinMode(P_VFD_FILAMENT, OUTPUT);
    //设置蜂鸣器驱动
    pinMode(P_BUZZER, OUTPUT);
    //设置按键检测
    //因为无下拉电阻,所以要下拉
    pinMode(P_KEY_A, INPUT_PULLDOWN);
    pinMode(P_KEY_B, INPUT_PULLDOWN);
    pinMode(P_KEY_C, INPUT_PULLDOWN);
    pinMode(P_KEY_D, INPUT_PULLDOWN);
    // RTC有专人负责,不在这里调用(RTCDS1302模块)
    // rtc.begin()
    //设置天线为浮空输入,每次检测天线上的电压
    pinMode(P_ANT, INPUT_FLOATING);
}