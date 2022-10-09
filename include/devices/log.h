#pragma once
#include <stdio.h>
//限制缓冲区的大小
#ifndef LOG_BUF_SIZE
#define LOG_BUF_SIZE 256
#endif
//指定缓冲区的位置
#ifndef LOG_BUF_ADDR
#define LOG_BUF_ADDR "0x20000400"
#endif
#define LOG_BUF_SECTION_INFO ".ARM.__AT_" LOG_BUF_ADDR ""

uint8_t  _log_buf_[LOG_BUF_SIZE] __attribute__((section(LOG_BUF_SECTION_INFO)));
uint16_t _log_idx_ = 0;

//重写这个函数来控制printf的输出目标到缓冲区
int fputc(char ch, FILE* f) {
    _log_buf_[_log_idx_++] = ch;
    if (_log_idx_ >= LOG_BUF_SIZE) {
        _log_idx_ = 0;
    }
    return ch;
}

extern int printf();