#pragma once
#include <Arduino.h>
#include "power.h"
#include "pins.h"
#include "display_signal.h"
#include "config.h"

//判断字符在字符集中是否可见
inline bool isCharVisible(char c) {

    return charval[c] != 0;
}

//控制位的输出
inline void shiftIndex(uint16_t val) {
    for (int i = 0; i < 9; i++) {
        digitalWrite(P_VFD_DATA, val & (1 << (8 - i)));
        digitalWrite(P_VFD_CLOCK, LOW);
        digitalWrite(P_VFD_CLOCK, HIGH);
    }
}

//控制段的输出,与上一个函数本质相同
inline void shiftVal(uint16_t val) {
    for (int i = 0; i < 8; i++) {
        digitalWrite(P_VFD_DATA, val & (1 << (7 - i)));
        digitalWrite(P_VFD_CLOCK, LOW);
        digitalWrite(P_VFD_CLOCK, HIGH);
    }
}

//屏幕内容缓冲
uint16_t content[16];

//刷新显示,调用一次耗时10ms
inline void flush() {
    for (int i = 1; i <= 9; i++) {
        delay(1);                          //延时一下效果最好,1ms正好够升压电路存储电能,亮度合适,刷新率也高
        shiftVal(content[i]);              //输出第i段上的数码管段位信息
        shiftIndex(__index__[i]);          //选择第i段
        digitalWrite(P_VFD_STROBE, HIGH);  //控制一次显示,要对这个脚做脉冲
        digitalWrite(P_VFD_STROBE, LOW);
    }
    delay(1);
}

//延时的同时保持显示
inline void delayWithDisplay(uint16_t x10ms) {
    for (int i = 1; i <= x10ms; i++) {
        flush();
    }
}

//设置字符,返回是否有对应字符的显示情况
inline uint8_t setChar(uint8_t idx, char c) {
    content[idx] = charval[c];
    return content[c];
}

//把某一位或上新字符
inline uint16_t orChar(uint8_t idx, char c) {
    content[idx] |= charval[c];
    return content[idx];
}

//把某一位与上新字符
inline uint16_t andChar(uint8_t idx, char c) {
    content[idx] &= charval[c];
    return content[idx];
}

//把某一位与上新字符
inline uint16_t xorChar(uint8_t idx, char c) {
    content[idx] ^= charval[c];
    return content[idx];
}

bool __display_on__ = 0;

//调整输出亮度(占空比)
inline void setLight(uint8_t l) {
    l = max((uint8_t)20, l);
    l = min((uint8_t)250, l);
    analogWrite(P_VFD_BLANK, 255 - l);  //低电平才亮,高电平不亮
}

//启用显示(亮屏)
inline void enableDisplay() {
    __display_on__ = 1;
    setLight(config.light);
}

/*禁用显示(息屏)
 */
inline void disableDisplay() {
    __display_on__ = 0;
    analogWrite(P_VFD_BLANK, 0);
}

//返回屏幕是否工作
inline bool isDisplayOn() {
    return __display_on__;
}

//清屏
inline void clear() {
    for (int i = 0; i <= 15; i++) {
        content[i] = 0;
    }
    flush();
}

/*显示整数
传入zero参数控制显示前导0
*/
inline void showInt(int t, bool zero = 0) {
    bool f = 0;
    if (t < 0) {
        f = 1;
        t = -t;
    }
    int z = 0;
    for (int i = 1; i <= 8; i++) {
        int j = t % 10;
        setChar(i, j + '0');
        t /= 10;
        z = i + 1;
        if (t == 0 && !zero) {
            while (i <= 8) {
                i++;
                setChar(i, 0);
            }
            break;
        }
    }
    if (f) {
        setChar(z, '-');
    }
}

//左移显示内容,两侧自动去除
inline void pushLeft(int t = 1) {
    while (t--) {
        for (int i = 8; i >= 1; i--) {
            content[i] = content[i - 1];
        }
    }
}

//右移显示内容,两侧自动去除
inline void pushRight(int t = 1) {
    while (t--) {
        for (int i = 1; i <= 8; i++) {
            content[i] = content[i + 1];
        }
    }
}

/*
滚动显示字符串(阻塞的)
传入dly参数控制单画面停留时间(x10ms)
*/
inline void scrollString(char* s, int siz, int dly = 20) {
    for (int i = 0; i < siz; i++) {
        setChar(0, s[i]);
        pushLeft();
        for (int j = 1; j <= dly; j++) {
            flush();
        }
    }
}
