#pragma once

//在Flash中保留255字节空间
#define configAddr 0x0800ff00

//定义保存的信息
struct deviceConfig {
    //亮度
    uint8_t light;
    //闹钟一天的第几秒
    uint32_t alarm;
    //关机时间
    uint32_t t1;
    //开机时间
    uint32_t t2;
};
deviceConfig config;

//在devices/flash.h中
extern void flashReadBuff(const uint32_t address, uint8_t* buffer, uint16_t length);
//在devices/flash.h中
extern void flashWriteBuff(const uint32_t address, uint8_t* buffer, uint32_t length);

//读取配置
inline void readDeviceConfig() {
    flashReadBuff(configAddr, (uint8_t*)&config, sizeof(config));
}

//保存配置
inline void saveDeviceConfig() {
    flashWriteBuff(configAddr, (uint8_t*)&config, sizeof(config));
}
