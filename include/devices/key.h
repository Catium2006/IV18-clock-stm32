#pragma once
#include <Arduino.h>
#include "pins.h"

#define P_KEY_MODE      P_KEY_A
#define P_KEY_SETTING   P_KEY_B
#define P_KEY_NEXT      P_KEY_C
#define P_KEY_UP        P_KEY_D

//判断是否按下按钮,调用后建议延时100ms防止误判为第二次按下
bool checkKey(uint32_t key) {
    return digitalRead(key) ;
}