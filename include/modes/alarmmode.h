#pragma once

#include "devices/key.h"
#include "devices/buzzer.h"
#include "devices/display.h"

//这个函数应该作为类似"服务"的方式调用,不参与主要模式循环
inline void alarm() {
    showInt(0);
    int t = 0;
    while (1) {
        if (checkKey(P_KEY_A) || checkKey(P_KEY_B) || checkKey(P_KEY_C) || checkKey(P_KEY_D)) {
            //按下任意键退出
            delayWithDisplay(20);
            if (checkKey(P_KEY_A) || checkKey(P_KEY_B) || checkKey(P_KEY_C) || checkKey(P_KEY_D)) {
                //按下任意键退出
                break;
            }
            break;
        }
        beep(1000, 200);
        delayWithDisplay(20);
        beep(1000, 200);
        delayWithDisplay(40);
        showInt(t);
        t++;
    }
}

inline void checkAlarm() {
    //如果启用闹钟
    if (config.alarm != 0) {
        uint32_t t = getSecOfDay();
        if (t == config.alarm) {
            alarm();
        }
    }
}