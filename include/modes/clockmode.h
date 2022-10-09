#pragma once
#include "devices/display.h"
#include "devices/key.h"
#include "devices/rtc.h"
inline void clockMode() {
    if (!rtc.GetIsRunning()) {
        //如果时钟工作不正常那么报错
        setChar(3, 'E');
        setChar(2, 'r');
        setChar(1, 'r');
        return;
    }
    RtcDateTime rtcDateTime = rtc.GetDateTime();
    uint8_t     sec         = rtcDateTime.Second();
    uint8_t     mnt         = rtcDateTime.Minute();
    uint8_t     hou         = rtcDateTime.Hour();
    uint8_t     dat         = rtcDateTime.Day();
    uint8_t     mon         = rtcDateTime.Month();
    uint16_t    yer         = rtcDateTime.Year();
    if (checkKey(P_KEY_NEXT)) {
        int t = yer * 10000 + mon * 100 + dat;
        showInt(t);
    } else {
        //否则正常显示时间
        // HH-mm-ss
        char c;
        c = '0' + hou / 10;
        hou %= 10;
        setChar(8, c);
        c = '0' + hou;
        setChar(7, c);
        setChar(6, '-');
        c = '0' + mnt / 10;
        mnt %= 10;
        setChar(5, c);
        c = '0' + mnt;
        setChar(4, c);
        setChar(3, '-');
        c = '0' + sec / 10;
        sec %= 10;
        setChar(2, c);
        c = '0' + sec;
        setChar(1, c);
    }
}
