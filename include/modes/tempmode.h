#pragma once

#include "devices.h"
int _cnt = 0;
/*
    1. C
    2. F
    3. K
*/
int  t_mode = 1;
void tempMode() {
    _cnt++;
    if (checkKey(P_KEY_NEXT)) {
        delayWithDisplay(20);
        t_mode++;
        if (t_mode > 3) {
            t_mode = 1;
        }
    }
    if (_cnt == 100) {
        if (t_mode == 1) {
            showInt(int(getT_C() * 10));
        }
        if (t_mode == 2) {
            showInt(int(getT_F() * 10));
        }
        if (t_mode == 3) {
            showInt(int(getT_K() * 10));
        }
        pushLeft(2);
        orChar(4, '.');
        if (t_mode == 1) {
            setChar(1, 'C');
        }
        if (t_mode == 2) {
            setChar(1, 'F');
        }
        if (t_mode == 3) {
            setChar(1, 'K');
        }
        pushLeft();
        _cnt = 0;
    }
}