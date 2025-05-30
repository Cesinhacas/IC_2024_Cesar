#ifndef SD_SPI_H
#define SD_SPI_H

#include <stdint.h>
#include <stdbool.h>

// Retornos
#define SD_OK       0
#define SD_ERROR    1
#define SD_TIMEOUT  2

// Interface pública
uint8_t SD_Init(void);
uint8_t SD_ReadBlock(uint32_t blockAddr, uint8_t* buff);
uint8_t SD_WriteBlock(uint32_t blockAddr, const uint8_t* buff);

#endif
