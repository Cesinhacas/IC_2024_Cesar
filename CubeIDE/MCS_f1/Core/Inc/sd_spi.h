#ifndef __SD_SPI_H
#define __SD_SPI_H

#include "stm32f1xx_hal.h"

int SD_SPI_Init(SPI_HandleTypeDef *hspi, GPIO_TypeDef *cs_port, uint16_t cs_pin);
int SD_SPI_ReadBlocks(uint8_t *buff, uint32_t sector, uint32_t count);
int SD_SPI_WriteBlocks(const uint8_t *buff, uint32_t sector, uint32_t count);
uint32_t SD_SPI_GetSectorCount(void);
int SD_ReadBlock(uint8_t *buff, uint32_t len);

#endif
