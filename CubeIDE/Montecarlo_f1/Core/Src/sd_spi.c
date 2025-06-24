// sd_spi.c
#include "sd_spi.h"
#include "stm32f1xx_hal.h"
#include <string.h>

#define CMD0    0   // GO_IDLE_STATE
#define CMD1    1   // SEND_OP_COND (MMC)
#define CMD8    8   // SEND_IF_COND
#define CMD9    9   // SEND_CSD
#define CMD10   10  // SEND_CID
#define CMD12   12  // STOP_TRANSMISSION
#define CMD17   17  // READ_SINGLE_BLOCK
#define CMD18   18  // READ_MULTIPLE_BLOCK
#define CMD24   24  // WRITE_BLOCK
#define CMD25   25  // WRITE_MULTIPLE_BLOCK
#define CMD55   55  // APP_CMD
#define CMD58   58  // READ_OCR
#define ACMD41  41  // SD_SEND_OP_COND (SDC)

#define SD_DUMMY_BYTE 0xFF
#define SD_TOKEN_START_BLOCK 0xFE

static SPI_HandleTypeDef *hspi_sd;
static GPIO_TypeDef *cs_port;
static uint16_t cs_pin;
static uint8_t card_type = 0;

static void SD_Select(void) {
    HAL_GPIO_WritePin(cs_port, cs_pin, GPIO_PIN_RESET);
}

static void SD_Deselect(void) {
    HAL_GPIO_WritePin(cs_port, cs_pin, GPIO_PIN_SET);
    uint8_t dummy = SD_DUMMY_BYTE;
    HAL_SPI_Transmit(hspi_sd, &dummy, 1, HAL_MAX_DELAY); // clock after deselect
}

static uint8_t SD_SPI_TxRx(uint8_t data) {
    uint8_t rx;
    HAL_SPI_TransmitReceive(hspi_sd, &data, &rx, 1, HAL_MAX_DELAY);
    return rx;
}

static int SD_WaitReady(uint32_t timeout) {
    uint8_t r;
    uint32_t tick = HAL_GetTick();
    do {
        r = SD_SPI_TxRx(SD_DUMMY_BYTE);
        if (r == 0xFF) return 1;
    } while ((HAL_GetTick() - tick) < timeout);
    return 0;
}

static uint8_t SD_SendCmd(uint8_t cmd, uint32_t arg) {
    uint8_t buf[6];
    uint8_t crc = 0x01;

    if (cmd == CMD0) crc = 0x95;
    if (cmd == CMD8) crc = 0x87;

    buf[0] = 0x40 | cmd;
    buf[1] = (arg >> 24) & 0xFF;
    buf[2] = (arg >> 16) & 0xFF;
    buf[3] = (arg >> 8) & 0xFF;
    buf[4] = arg & 0xFF;
    buf[5] = crc;

    SD_Deselect();
    SD_Select();

    if (!SD_WaitReady(500)) {
        SD_Deselect();
        return 0xFF;
    }

    for (uint8_t i = 0; i < 6; i++) {
        SD_SPI_TxRx(buf[i]);
    }

    uint8_t r;
    for (uint8_t i = 0; i < 10; i++) {
        r = SD_SPI_TxRx(SD_DUMMY_BYTE);
        if (!(r & 0x80)) break;
    }

    return r;
}

int SD_SPI_Init(SPI_HandleTypeDef *hspi, GPIO_TypeDef *port, uint16_t pin) {
    hspi_sd = hspi;
    cs_port = port;
    cs_pin = pin;

    SD_Deselect();
    for (uint8_t i = 0; i < 10; i++) {
        SD_SPI_TxRx(SD_DUMMY_BYTE); // 80 clocks
    }

    uint8_t r = SD_SendCmd(CMD0, 0);
    if (r != 0x01) return -1;

    r = SD_SendCmd(CMD8, 0x1AA);
    if (r == 0x01) {
        uint8_t buf[4];
        for (uint8_t i = 0; i < 4; i++) buf[i] = SD_SPI_TxRx(SD_DUMMY_BYTE);
        if (buf[2] != 0x01 || buf[3] != 0xAA) return -2;

        do {
            r = SD_SendCmd(CMD55, 0);
            r = SD_SendCmd(ACMD41, 0x40000000);
        } while (r != 0x00);

        r = SD_SendCmd(CMD58, 0);
        if (r != 0x00) return -3;

        SD_SPI_TxRx(SD_DUMMY_BYTE); // OCR[0]
        SD_SPI_TxRx(SD_DUMMY_BYTE); // OCR[1]
        SD_SPI_TxRx(SD_DUMMY_BYTE); // OCR[2]
        uint8_t ocr = SD_SPI_TxRx(SD_DUMMY_BYTE); // OCR[3]
        card_type = (ocr & 0x40) ? 2 : 1;
    } else {
        do {
            r = SD_SendCmd(CMD55, 0);
            r = SD_SendCmd(ACMD41, 0);
        } while (r != 0x00);
        card_type = 1;
    }

    SD_Deselect();
    return 0;
}

int SD_SPI_ReadBlocks(uint8_t *buff, uint32_t sector, uint32_t count) {
    if (!(card_type & 2)) sector *= 512;

    if (count == 1) {
        if (SD_SendCmd(CMD17, sector) != 0x00) return -1;
        if (!SD_ReadBlock(buff, 512)) return -2;
    } else {
        if (SD_SendCmd(CMD18, sector) != 0x00) return -3;
        for (uint32_t i = 0; i < count; i++) {
            if (!SD_ReadBlock(buff + i * 512, 512)) return -4;
        }
        SD_SendCmd(CMD12, 0); // STOP_TRANSMISSION
    }

    SD_Deselect();
    return 0;
}

int SD_ReadBlock(uint8_t *buff, uint32_t len) {
    uint8_t token;
    uint32_t timeout = HAL_GetTick();
    do {
        token = SD_SPI_TxRx(SD_DUMMY_BYTE);
        if (token == SD_TOKEN_START_BLOCK) break;
    } while ((HAL_GetTick() - timeout) < 200);

    if (token != SD_TOKEN_START_BLOCK) return 0;

    for (uint32_t i = 0; i < len; i++) {
        buff[i] = SD_SPI_TxRx(SD_DUMMY_BYTE);
    }

    SD_SPI_TxRx(SD_DUMMY_BYTE); // discard CRC
    SD_SPI_TxRx(SD_DUMMY_BYTE);
    return 1;
}

int SD_SPI_WriteBlocks(const uint8_t *buff, uint32_t sector, uint32_t count) {
    if (!(card_type & 2)) sector *= 512;

    if (count == 1) {
        if (SD_SendCmd(CMD24, sector) != 0x00) return -1;

        SD_SPI_TxRx(0xFE);
        for (uint32_t i = 0; i < 512; i++) {
            SD_SPI_TxRx(buff[i]);
        }
        SD_SPI_TxRx(0xFF); // dummy CRC
        SD_SPI_TxRx(0xFF);

        uint8_t response = SD_SPI_TxRx(SD_DUMMY_BYTE);
        if ((response & 0x1F) != 0x05) return -2;

        if (!SD_WaitReady(500)) return -3;
    } else {
        return -99; // multiblock write não implementado
    }

    SD_Deselect();
    return 0;
}

uint32_t SD_SPI_GetSectorCount(void) {
    // Retorna um número fictício seguro se não implementado
    return 8192; // Ex: 4MB
}
