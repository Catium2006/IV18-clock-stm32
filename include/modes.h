#pragma once

#include "modes/clockmode.h"
#include "modes/timermode.h"
#include "modes/tempmode.h"
#include "modes/edittimemode.h"
#include "modes/editlightmode.h"
#include "modes/editalarmmode.h"
#include "modes/alarmmode.h"
#include "modes/editpsmode.h"

using namespace std;

//设备的运行模式
static const uint8_t MODE_SHUTDOWN           = 1;
static const uint8_t MODE_CLOCK              = 2;
static const uint8_t MODE_TIMER              = 3;
static const uint8_t MODE_TEMP               = 4;
static const uint8_t MODE_EDIT_TIME          = 5;
static const uint8_t MODE_EDIT_LIGHT         = 6;
static const uint8_t MODE_EDIT_ALARM         = 7;
static const uint8_t MODE_EDIT_POWERSCHEDULE = 8;

uint8_t MODE = 1;

inline void nextMode() {
    MODE++;
    if (MODE > MODE_EDIT_POWERSCHEDULE) {
        MODE = MODE_SHUTDOWN;
    }
}

inline void switchMode() {
    //如果切换模式
    if (checkKey(P_KEY_MODE)) {
        clear();
        nextMode();
        if (MODE == MODE_SHUTDOWN) {
            powerOff();
        } else {
            powerOn();
        }
        switch (MODE) {
        case MODE_SHUTDOWN: {
            break;
        }
        case MODE_CLOCK: {
            setLight(config.light);
            setChar(3, 'C');
            setChar(2, 'L');
            setChar(1, 'O');
            // CLO
            break;
        }
        case MODE_TIMER: {
            setLight(250);
            setChar(2, 'S');
            setChar(1, 't');
            // CNT
            break;
        }
        case MODE_TEMP: {
            setLight(250);
            setChar(2, 't');
            setChar(1, 'E');
            // CNT
            break;
        }
        case MODE_EDIT_TIME: {
            setLight(250);
            setChar(2, 'E');
            setChar(1, 'E');
            // EE
            break;
        }
        case MODE_EDIT_LIGHT: {
            setLight(250);
            setChar(2, 'E');
            setChar(1, 'L');
            // EL
            break;
        }
        case MODE_EDIT_ALARM: {
            setLight(250);
            setChar(2, 'E');
            setChar(1, 'A');
            // EA
            break;
        }
        case MODE_EDIT_POWERSCHEDULE: {
            setLight(250);
            setChar(2, 'E');
            setChar(1, 'P');
            break;
        }
        }
        //显示0.4秒模式名称
        delayWithDisplay(40);
    }
    switch (MODE) {
    case MODE_SHUTDOWN: {
        break;
    }
    case MODE_CLOCK: {
        clockMode();
        break;
    }
    case MODE_TIMER: {
        timerMode();
        break;
    }
    case MODE_TEMP: {
        tempMode();
        break;
    }
    case MODE_EDIT_TIME: {
        if (checkKey(P_KEY_SETTING)) {
            delayWithDisplay(30);
            editTimeMode();
            clear();
            setChar(2, 'E');
            setChar(1, 'E');
        }
        break;
    }
    case MODE_EDIT_LIGHT: {
        if (checkKey(P_KEY_SETTING)) {
            delayWithDisplay(30);
            editLightMode();
            clear();
            setChar(2, 'E');
            setChar(1, 'L');
        }
        break;
    }
    case MODE_EDIT_ALARM: {
        if (checkKey(P_KEY_SETTING)) {
            delayWithDisplay(30);
            editAlarmMode();
            clear();
            setChar(2, 'E');
            setChar(1, 'A');
        }
        break;
    }
    case MODE_EDIT_POWERSCHEDULE: {
        if (checkKey(P_KEY_SETTING)) {
            delayWithDisplay(30);
            editPSMode();
            clear();
            setChar(2, 'E');
            setChar(1, 'P');
        }
        break;
    }
    }
}
