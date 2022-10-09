#include "iv18clock.h"
#include <Arduino.h>

/*
额外的建议:尽量使用delayWithDisplay(uint16_t x10ms)替代delay(uint32_t ms)
*/

void setup() {
    //设置引脚
    initPin();
    //关闭绿色指使灯
    digitalWrite(P_LED, HIGH);
    //启动RTC
    initRTC();
    //启动电源
    powerOn();
    //启动显示
    enableDisplay();
    //读取保存的配置
    readDeviceConfig();
    //使用配置,第一次启动亮度不能太低
    if (config.light < 25) {
        config.light = 25;
    }
    setLight(config.light);
    //(如果需要)同步时间
    syncTime();
    //响一下表示开机
    beep(1000, 300);
    //设置为时钟模式
    MODE = MODE_CLOCK;

}

//大约1000s, 不到20分钟
void loop100000() {
    checkBirthday();
}
//大约100s
void loop10000() {}
//大约10s
void loop1000() {}
//大约1s
void loop100() {}
//大约0.1s
void loop10() {}

int loop_cnt = 0;

void loop() {
    checkPowerSchedule();
    checkAlarm();
    switchMode();
    flush();
    loop_cnt++;
    if (!(loop_cnt % 10)) {
        loop10();
    }
    if (!(loop_cnt % 100)) {
        loop100();
    }
    if (!(loop_cnt % 1000)) {
        loop1000();
    }
    if (!(loop_cnt % 10000)) {
        loop10000();
    }
    if (!(loop_cnt % 100000)) {
        loop100000();
    }
}