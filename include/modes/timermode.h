#pragma once
#include "devices/display.h"
#include "devices/key.h"
#include "devices/rtc.h"
uint32_t    __cha_timer__;
uint32_t    __last_timer__;
uint8_t     __cnt_timer__;
uint8_t     __t_timer__;
inline void timerMode() {
    __t_timer__++;
    int     tt   = __cha_timer__;
    uint8_t _hh_ = tt / 3600;
    uint8_t _mm_ = (tt - _hh_ * 3600) / 60;
    uint8_t _ss_ = tt - _hh_ * 3600 - _mm_ * 60;
    char    buf[10];
    buf[1] = '0' + (_ss_ % 10);
    buf[2] = '0' + (_ss_ / 10);
    buf[3] = '-';
    buf[4] = '0' + (_mm_ % 10);
    buf[5] = '0' + (_mm_ / 10);
    buf[6] = '-';
    buf[7] = '0' + (_hh_ % 10);
    buf[8] = '0' + (_hh_ / 10);
    for (int i = 1; i <= 8; i++) {
        setChar(i, buf[i]);
    }
    uint32_t curSec = getSecOfDay();
    if (__cnt_timer__ == 1) {
        __cha_timer__ += curSec - __last_timer__;
    }
    if (__cnt_timer__ == 2) {
        //左侧圆点闪烁
        if (__t_timer__ > 40) {
            setChar(9, '.');
        }
        if (__t_timer__ > 80) {
            setChar(9, 0);
            __t_timer__ = 0;
        }
    }
    if (__cnt_timer__ == 3) {
        __cha_timer__ = 0;
    }
    if (__cnt_timer__ > 3) {
        __cnt_timer__ = 0;
    }
    //按一下开始计时,再按一下停止,再按一下清除,再按一下重新开始
    if (checkKey(P_KEY_NEXT)) {
        __cnt_timer__++;
        delayWithDisplay(20);
    }
    __last_timer__ = curSec;
}
