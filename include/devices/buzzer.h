#pragma once

#include <Arduino.h>
#include "pins.h"

//使蜂鸣器发声
inline void beep(uint16_t freq, uint16_t ms) {
    digitalWrite(P_VFD_BLANK, LOW);
    analogWriteFrequency(freq);  //设置输出频率
    analogWrite(P_BUZZER, 128);  //半周期方波
    delayWithDisplay(ms / 10);   //延时,保持显示
    analogWrite(P_BUZZER, 0);    //停止蜂鸣器
    analogWriteFrequency(500);   //设置正常输出频率
}

inline void beep() {
    digitalWrite(P_VFD_BLANK, LOW);
    analogWriteFrequency(1000);  //设置输出频率
    analogWrite(P_BUZZER, 128);  //半周期方波
    delayWithDisplay(100 / 10);  //延时,保持显示
    analogWrite(P_BUZZER, 0);    //停止蜂鸣器
    analogWriteFrequency(500);   //设置正常输出频率
}
// l低音,h高音,s半音阶

#define DO_l 262
#define RE_l 294
#define MI_L 330
#define FA_l 349
#define SO_l 392
#define LA_l 440
#define SI_l 494
#define DO 523
#define RE 578
#define MI 659
#define FA 698
#define SO 784
#define LA 880
#define SI 988
#define DO_h 1046
#define RE_h 1175
#define MI_h 1318
#define FA_h 1480
#define SO_h 1568
#define LA_h 1760
#define SI_h 1976
#define DO_sl 277
#define RE_sl 311
#define FA_sl 370
#define SO_sl 415
#define LA_sl 466
#define DO_s 554
#define RE_s 622
#define FA_s 740
#define SO_s 831
#define LA_s 932
#define DO_sh 1046
#define RE_sh 1245
#define FA_sh 1480
#define SO_sh 1661
#define LA_sh 1865