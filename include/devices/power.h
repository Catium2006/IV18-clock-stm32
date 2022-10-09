#pragma once
#include <Arduino.h>
#include "config.h"
#include "pins.h"
#include "key.h"

bool __highVoltageOn__;

//启用升压
inline void enableHighVoltage() {
    __highVoltageOn__ = 1;
    digitalWrite(P_POWER_EN, HIGH);
}

//禁用升压
inline void disableHighVoltage() {
    __highVoltageOn__ = 0;
    digitalWrite(P_POWER_EN, LOW);
}

//返回升压电路是否在工作状态
inline bool isHighVoltageOn() {
    return __highVoltageOn__;
}

//控制荧光管灯丝
inline void enableFilament() {
    digitalWrite(P_VFD_FILAMENT, HIGH);
}
//控制荧光管灯丝
inline void disableFilament() {
    digitalWrite(P_VFD_FILAMENT, LOW);
}

//断电(灯丝和高压)
void powerOff() {
    disableHighVoltage();
    disableFilament();
}

//通电(灯丝和高压)
void powerOn() {
    enableFilament();
    enableHighVoltage();
}

extern uint32_t getSecOfDay();

//电源计划,实现定时开关机
inline void checkPowerSchedule() {
    if (config.t1 != 0) {
        //如果启用自动关机
        uint32_t sec;
        sec = getSecOfDay();
        if (sec == config.t1) {
            powerOff();
            while (1) {
                //如果有按下按钮则跳出
                if (checkKey(P_KEY_A) || checkKey(P_KEY_B) || checkKey(P_KEY_C) || checkKey(P_KEY_D)) {
                    delay(300);
                    if (checkKey(P_KEY_A) || checkKey(P_KEY_B) || checkKey(P_KEY_C) || checkKey(P_KEY_D)) {
                        powerOn();
                        return;
                    }
                }
                sec = getSecOfDay();
                //如果启用自动开机
                if (config.t2 != 0) {
                    //如果该开机了
                    if (sec == config.t2) {
                        powerOn();
                        return;
                    }
                }
                delay(200);
            }
        }
    }
}