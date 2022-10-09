#pragma once
#include "devices/display.h"
#include "devices/key.h"

inline void editPSMode() {
    uint8_t buf[20];
    uint8_t curidx = 1;

    uint32_t t1 = config.t1;
    uint32_t t2 = config.t2;

    uint8_t _hh_ = t1 / 3600;
    uint8_t _mm_ = (t1 - _hh_ * 3600) / 60;
    uint8_t _ss_ = t1 - _hh_ * 3600 - _mm_ * 60;

    buf[1] = _ss_ % 10;
    buf[2] = _ss_ / 10;

    buf[4] = _mm_ % 10;
    buf[5] = _mm_ / 10;

    buf[7] = _hh_ % 10;
    buf[8] = _hh_ / 10;

    _hh_ = t2 / 3600;
    _mm_ = (t2 - _hh_ * 3600) / 60;
    _ss_ = t2 - _hh_ * 3600 - _mm_ * 60;

    buf[1 + 8] = _ss_ % 10;
    buf[2 + 8] = _ss_ / 10;

    buf[4 + 8] = _mm_ % 10;
    buf[5 + 8] = _mm_ / 10;

    buf[7 + 8] = _hh_ % 10;
    buf[8 + 8] = _hh_ / 10;

    uint8_t _cnt_ = 0;
    while (1) {
        if (checkKey(P_KEY_SETTING)) {
            //保存并退出
            config.t1 = t1;
            config.t2 = t2;
            saveDeviceConfig();
            delayWithDisplay(30);
            break;
        }
        if (checkKey(P_KEY_MODE)) {
            //不保存退出
            delayWithDisplay(30);
            break;
        }
        if (checkKey(P_KEY_NEXT)) {
            delayWithDisplay(30);
            //换到下一位
            curidx++;
            if (curidx == 3) {
                curidx = 4;
            }
            if (curidx == 6) {
                curidx = 7;
            }
            if (curidx == 3 + 8) {
                curidx = 4 + 8;
            }
            if (curidx == 6 + 8) {
                curidx = 7 + 8;
            }
            if (curidx > 16) {
                curidx = 1;
            }
        }
        if (checkKey(P_KEY_UP)) {
            delayWithDisplay(30);
            //当前位加一
            buf[curidx]++;
            if (buf[curidx] > 9) {
                buf[curidx] = 0;
            }
        }
        if (curidx <= 8) {
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
            t1   = _hh_ * 3600 + _mm_ * 60 + _ss_;
        } else {
            _ss_ = buf[1 + 8] + buf[2 + 8] * 10;
            _mm_ = buf[4 + 8] + buf[5 + 8] * 10;
            _hh_ = buf[7 + 8] + buf[8 + 8] * 10;
            if (_ss_ > 60) {
                buf[2 + 8] = 0;
            }
            if (_mm_ > 60) {
                buf[5 + 8] = 0;
            }
            if (_hh_ > 24) {
                buf[8 + 8] = 0;
            }
            _ss_ = buf[1 + 8] + buf[2 + 8] * 10;
            _mm_ = buf[4 + 8] + buf[5 + 8] * 10;
            _hh_ = buf[7 + 8] + buf[8 + 8] * 10;
            t2 = _hh_ * 3600 + _mm_ * 60 + _ss_;
        }
        //现在要显示当前缓冲内容
        if (curidx <= 8) {
            for (int i = 1; i <= 8; i++) {
                setChar(i, buf[i] + '0');
            }
            setChar(9, 0);
        } else {
            for (int i = 9; i <= 16; i++) {
                setChar(i - 8, buf[i] + '0');
            }
            setChar(9, '.');
        }
        setChar(3, '-');
        setChar(6, '-');
        // 亮
        if (_cnt_ >= 50) {
            if (curidx <= 8) {
                orChar(curidx, '.');
            } else {
                orChar(curidx - 8, '.');
            }
        }
        // 暗
        if (_cnt_ == 100) {
            _cnt_ = 0;
        }
        _cnt_++;
        flush();
    }
}