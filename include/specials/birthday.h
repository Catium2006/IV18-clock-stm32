#pragma once

#include "iv18clock.h"
void birthday() {
    while (1) {
        scrollString(" HAPPY BIrtHDAY to XX XX XXXX ", 32, 30);
        if (checkKey(P_KEY_A) || checkKey(P_KEY_B) || checkKey(P_KEY_C) || checkKey(P_KEY_D)) {
            delayWithDisplay(30);
            if (checkKey(P_KEY_A) || checkKey(P_KEY_B) || checkKey(P_KEY_C) || checkKey(P_KEY_D)) {
                break;
            }
        }
    }
}

inline void checkBirthday() {
    //草 是一月八号我没记错吧
    //印象中好像你生日和身份证不符啊
    RtcDateTime t = rtc.GetDateTime();
    if (t.Month() == 1 && t.Day() == 8) {
        birthday();
    }
}