#pragma once
#include "devices/display.h"
#include "devices/key.h"

inline void editLightMode() {
    clear();
    uint8_t l     = config.light;
    uint8_t _cnt_ = 0;
    while (1) {
        if (checkKey(P_KEY_SETTING)) {
            //保存并退出
            config.light = l;
            saveDeviceConfig();
            delayWithDisplay(20);
            break;
        }
        if (checkKey(P_KEY_MODE)) {
            //不保存退出
            delayWithDisplay(20);
            break;
        }
        if (checkKey(P_KEY_UP)) {
            delayWithDisplay(20);
            //当前位加一
            l += 10;
            if (l > 250) {
                l = 10;
            }
        }
        setLight(l);
        showInt(l);
        pushRight();
        // 亮
        if (_cnt_ >= 40) {
            orChar(1, '.');
        }
        // 暗
        if (_cnt_ == 80) {
            _cnt_ = 0;
        }
        _cnt_++;
        setChar(4, '8');
        setChar(5, '8');
        setChar(6, '-');
        setChar(7, '8');
        setChar(8, '8');
        flush();
    }
    setLight(250);
}