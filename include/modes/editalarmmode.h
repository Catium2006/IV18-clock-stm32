#pragma once

#include "devices/key.h"
#include "devices/display.h"

struct deviceConfig;
extern deviceConfig config;

inline void setAlarm(uint32_t t) {
    config.alarm = t;
}

inline void editAlarmMode() {
    uint32_t sec  = config.alarm;
    uint8_t  _hh_ = sec / 3600;
    uint8_t  _mm_ = (sec - _hh_ * 3600) / 60;
    uint8_t  _ss_ = sec - _hh_ * 3600 - _mm_ * 60;

    uint8_t curidx = 1;
    uint8_t buf[10];

    buf[1] = _ss_ % 10;
    buf[2] = _ss_ / 10;

    buf[4] = _mm_ % 10;
    buf[5] = _mm_ / 10;

    buf[7] = _hh_ % 10;
    buf[8] = _hh_ / 10;

    uint8_t _cnt_ = 0;

    while (1) {
        if (checkKey(P_KEY_SETTING)) {
            //保存并退出
            setAlarm(sec);
            saveDeviceConfig();
            delayWithDisplay(20);
            break;
        }
        if (checkKey(P_KEY_MODE)) {
            //不保存退出
            delayWithDisplay(20);
            break;
        }
        if (checkKey(P_KEY_NEXT)) {
            delayWithDisplay(20);
            //换到下一位
            curidx++;
            if (curidx == 3) {
                curidx = 4;
            }
            if (curidx == 6) {
                curidx = 7;
            }
            if (curidx > 8) {
                curidx = 1;
            }
        }
        if (checkKey(P_KEY_UP)) {
            delayWithDisplay(20);
            //当前位加一
            buf[curidx]++;
            if (buf[curidx] > 9) {
                buf[curidx] = 0;
            }
        }
        _ss_ = buf[1] + buf[2] * 10;
        _mm_ = buf[4] + buf[5] * 10;
        _hh_ = buf[7] + buf[8] * 10;
        if (_ss_ > 60) {
            buf[2] = 0;
        }
        if (_mm_ > 60) {
            buf[5] = 0;
        }
        if (_hh_ > 24) {
            buf[8] = 0;
        }
        _ss_ = buf[1] + buf[2] * 10;
        _mm_ = buf[4] + buf[5] * 10;
        _hh_ = buf[7] + buf[8] * 10;
        sec  = _hh_ * 3600 + _mm_ * 60 + _ss_;
        //现在要显示当前缓冲内容
        for (int i = 1; i <= 8; i++) {
            setChar(i, buf[i] + '0');
        }
        setChar(3, '-');
        setChar(6, '-');
        // 亮
        if (_cnt_ >= 40) {
            orChar(curidx, '.');
        }
        // 暗
        if (_cnt_ == 80) {
            setChar(curidx, buf[curidx] + '0');
            _cnt_ = 0;
        }
        _cnt_++;
        flush();
    }
}