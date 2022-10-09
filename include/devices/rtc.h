#pragma once
#include "pins.h"
#include <Arduino.h>
#include <ThreeWire.h>
#include <RtcDS1302.h>

// RTC芯片

ThreeWire RTCwire(P_RTC_IO, P_RTC_SCLK, P_RTC_RST);

RtcDS1302<ThreeWire> rtc(RTCwire);

void syncTime() {
    //同步时间
    int ss, mm, hh;
    int dd, MM, yyyy;

    RtcDateTime rtcDateTime = rtc.GetDateTime();

    yyyy = rtcDateTime.Year();

    if (yyyy < 2022) {
        sscanf(__TIME__, "%d:%d:%d", &hh, &mm, &ss);
        char        MMs[5];
        std::string MMstr;
        sscanf(__DATE__, "%s %d %d", MMs, &dd, &yyyy);
        MMstr = MMs;
        MM    = 1;
        if (MMstr == "Jan") {
            MM = 1;
        }
        if (MMstr == "Feb") {
            MM = 2;
        }
        if (MMstr == "Mar") {
            MM = 3;
        }
        if (MMstr == "Apr") {
            MM = 4;
        }
        if (MMstr == "May") {
            MM = 5;
        }
        if (MMstr == "Jun") {
            MM = 6;
        }
        if (MMstr == "Jul") {
            MM = 7;
        }
        if (MMstr == "Aug") {
            MM = 8;
        }
        if (MMstr == "Sept") {
            MM = 9;
        }
        if (MMstr == "Oct") {
            MM = 10;
        }
        if (MMstr == "Nov") {
            MM = 11;
        }
        if (MMstr == "Dec") {
            MM = 12;
        }
        rtc.SetDateTime(RtcDateTime(yyyy, MM, dd, hh, mm + 6, ss));
    }
}

inline void setTime(uint16_t yy, uint8_t MM, uint8_t dd, uint8_t hh, uint8_t mm, uint8_t ss) {
    rtc.SetDateTime(RtcDateTime(yy, MM, dd, hh, mm, ss));
}

inline void initRTC() {
    rtc.Begin();
    rtc.SetIsRunning(1);
}

inline uint32_t getSecOfDay() {
    RtcDateTime rtcDateTime = rtc.GetDateTime();
    uint32_t    ss          = rtcDateTime.Second();
    uint32_t    mm          = rtcDateTime.Minute();
    uint32_t    hh          = rtcDateTime.Hour();
    return hh * 3600 + mm * 60 + ss;
}