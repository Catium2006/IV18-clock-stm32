#pragma once
#include "devices/key.h"
#include "devices/display.h"
#include "devices/rtc.h"

inline void editTimeMode() {
    RtcDateTime rtcDateTime = rtc.GetDateTime();
    uint16_t    _yy_        = rtcDateTime.Year();
    uint8_t     _MM_        = rtcDateTime.Month();
    uint8_t     _dd_        = rtcDateTime.Day();
    uint8_t     _hh_        = rtcDateTime.Hour();
    uint8_t     _mm_        = rtcDateTime.Minute();
    uint8_t     _ss_        = rtcDateTime.Second();
    uint8_t     curidx      = 1;  //当前正在编辑哪一位
    uint8_t     buf[20];

    buf[1] = _ss_ % 10;
    buf[2] = _ss_ / 10;

    buf[4] = _mm_ % 10;
    buf[5] = _mm_ / 10;

    buf[7] = _hh_ % 10;
    buf[8] = _hh_ / 10;

    buf[9]  = _dd_ % 10;
    buf[10] = _dd_ / 10;

    buf[11] = _MM_ % 10;
    buf[12] = _MM_ / 10;

    buf[13] = _yy_ % 10;
    _yy_ /= 10;
    buf[14] = _yy_ % 10;
    _yy_ /= 10;
    buf[15] = _yy_ % 10;
    _yy_ /= 10;
    buf[16] = _yy_;

    uint8_t _cnt_ = 0;

    while (1) {
        if (checkKey(P_KEY_SETTING)) {
            //保存并退出
            setTime(_yy_, _MM_, _dd_, _hh_, _mm_, _ss_);
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
            if (curidx > 16) {
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
        _dd_ = buf[9] + buf[10] * 10;
        _MM_ = buf[11] + buf[12] * 10;
        _yy_ = buf[13] + buf[14] * 10 + buf[15] * 100 + buf[16] * 1000;
        //现在要显示当前缓冲内容
        if (curidx <= 8) {
            for (int i = 1; i <= 8; i++) {
                setChar(i, buf[i] + '0');
            }
            setChar(3, '-');
            setChar(6, '-');
            setChar(9, 0);
        } else {
            for (int i = 9; i <= 16; i++) {
                setChar(i - 8, buf[i] + '0');
            }
            //多亮一个原点以示区别
            setChar(9, '.');
        }
        // 亮
        if (_cnt_ >= 40) {
            if (curidx <= 8) {
                orChar(curidx, '.');
            } else {
                orChar(curidx - 8, '.');
            }
        }
        // 暗
        if (_cnt_ == 80) {
            _cnt_ = 0;
        }
        _cnt_++;
        flush();
    }
}