#ifndef __SD_SPI_H__
#define __SD_SPI_H__

#include "stm32f7xx_hal.h"

#define SD_OK     0
#define SD_ERROR  1

uint8_t SD_Init(void);
uint8_t SD_ReadBlock(uint32_t blockAddr, uint8_t* buff);
uint8_t SD_WriteBlock(uint32_t blockAddr, const uint8_t* buff);

#endif
