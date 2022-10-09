#pragma once
#include "stm32f1xx_hal.h"

#define FMC_FLASH_BASE 0x08000000  // FLASH的起始地址
#define FMC_FLASH_END 0x08010000   // FLASH的结束地址,此处为64KB

#define FMC_FLASH_SIZE 64  // 定义Flash大小，单位KB

#if FMC_FLASH_SIZE < 256
#define FMC_SECTOR_SIZE 1024  // 字节
#define MOD_SECTOR_SIZE 0X3FF
#define PAGE_COUNT_BY16 512
#else
#define FMC_SECTOR_SIZE 2048
#define MOD_SECTOR_SIZE 0X7FF
#define PAGE_COUNT_BY16 1024
#endif

// 不检查的写入
void flashWriteNoCheck(uint32_t address, uint8_t* buffer, uint16_t lenth) {
    uint16_t i;
    for (i = 0; i < lenth; i += 4) {
        while (HAL_OK != HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, address + i, *(uint32_t*)(buffer + i)))
            ;
    }
}

//分页擦除数据
void FLASH_PageErase(uint32_t PageAddress) {
    /* Clean the error context */

#if defined(FLASH_BANK2_END)
    if (PageAddress > FLASH_BANK1_END) {
        /* Proceed to erase the page */
        SET_BIT(FLASH->CR2, FLASH_CR2_PER);
        WRITE_REG(FLASH->AR2, PageAddress);
        SET_BIT(FLASH->CR2, FLASH_CR2_STRT);
    } else {
#endif /* FLASH_BANK2_END */
        /* Proceed to erase the page */
        SET_BIT(FLASH->CR, FLASH_CR_PER);
        WRITE_REG(FLASH->AR, PageAddress);
        SET_BIT(FLASH->CR, FLASH_CR_STRT);
#if defined(FLASH_BANK2_END)
    }
#endif /* FLASH_BANK2_END */
}

//先检查地址再写入
void flashWriteBuff(const uint32_t address, uint8_t* buffer, uint32_t length) {
    uint16_t i;
    uint8_t  FlashBuff[FMC_SECTOR_SIZE];
    uint32_t StartAddress = address - address % FMC_SECTOR_SIZE;
    uint16_t Offset       = address - StartAddress;
    uint8_t* pBuf         = buffer;
    uint32_t remaindNum   = length;

    HAL_StatusTypeDef status = HAL_ERROR;

    // 地址检查
    if ((address < FMC_FLASH_BASE) || (address + length >= FMC_FLASH_END) || (length <= 0)) {
        return;
    }

    HAL_FLASH_Unlock();  // 解锁

    do {
        // 读出一页数据
        for (i = 0; i < FMC_SECTOR_SIZE; i += 4) {
            *(uint32_t*)(FlashBuff + i) = *(uint32_t*)(StartAddress + i);
        }

        // 修改要改入的数据
        for (i = 0; (i + Offset) < FMC_SECTOR_SIZE && i < remaindNum; i++) {
            *(FlashBuff + Offset + i) = *(pBuf + i);
        }

        // 擦除一ROW数据
        FLASH_PageErase(StartAddress);

        // HAL库 FLASH_PageErase有BUFF,要加上下面三句代码
        while (status != HAL_OK) {
            status = FLASH_WaitForLastOperation(FLASH_TIMEOUT_VALUE);
        }
        CLEAR_BIT(FLASH->CR, FLASH_CR_PER);

        // 写入数据
        flashWriteNoCheck(StartAddress, FlashBuff, FMC_SECTOR_SIZE);

        // 为下一页做准备
        StartAddress += FMC_SECTOR_SIZE;
        remaindNum -= i;
        pBuf += i;
        Offset = 0;

    } while (remaindNum > 0);

    HAL_FLASH_Lock();  // 上锁
}

// 从FLASH中读指定长度数据
void flashReadBuff(const uint32_t address, uint8_t* buffer, uint16_t length) {
    uint16_t i;
    uint8_t  Offset       = 0;
    uint32_t StartAddress = address;
    uint16_t data;

    // 地址检测
    if (address + length > FMC_FLASH_END) {
        return;
    }

    // 如果没有对16齐
    if (address & 1) {
        Offset       = 1;
        StartAddress = address - 1;
    }

    // flash的操作要求16对齐 最小读写操作16个比特
    if (Offset) {
        data      = *(uint16_t*)(StartAddress);
        buffer[0] = data >> 8;
        StartAddress += 2;
    }

    for (i = 0; i < (length - Offset); i += 2) {
        data               = *(uint16_t*)(StartAddress + i);
        buffer[i + Offset] = (data & 0xFF);
        if ((i + Offset) < (length - 1)) {
            buffer[i + Offset + 1] = (data >> 8);
        }
    }
}