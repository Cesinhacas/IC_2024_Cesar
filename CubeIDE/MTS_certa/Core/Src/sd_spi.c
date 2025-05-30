#include "sd_spi.h"
#include "spi.h"

#define CMD0   0
#define CMD8   8
#define CMD17  17
#define CMD24  24
#define CMD55  55
#define CMD58  58
#define ACMD41 41

#define SD_CS_GPIO_Port GPIOA      // Altere conforme seu pino CS
#define SD_CS_Pin GPIO_PIN_4       // Altere conforme seu pino CS

#define SD_CS_LOW()   HAL_GPIO_WritePin(SD_CS_GPIO_Port, SD_CS_Pin, GPIO_PIN_RESET)
#define SD_CS_HIGH()  HAL_GPIO_WritePin(SD_CS_GPIO_Port, SD_CS_Pin, GPIO_PIN_SET)

extern SPI_HandleTypeDef hspi3; // Use a instância correta do SPI

static void SD_SendDummyClock(void) {
    uint8_t dummy = 0xFF;
    for (int i = 0; i < 10; i++)
        HAL_SPI_Transmit(&hspi3, &dummy, 1, HAL_MAX_DELAY);
}

static uint8_t SD_TransmitByte(uint8_t data) {
    uint8_t received;
    HAL_SPI_TransmitReceive(&hspi3, &data, &received, 1, HAL_MAX_DELAY);
    return received;
}

static uint8_t SD_ReceiveByte(void) {
    return SD_TransmitByte(0xFF);
}

static uint8_t SD_WaitReady(void) {
    uint8_t res;
    uint32_t timeout = HAL_GetTick();
    do {
        res = SD_ReceiveByte();
        if (res == 0xFF) return 1;
    } while ((HAL_GetTick() - timeout) < 500);
    return 0;
}

static void SD_Select(void) {
    SD_CS_LOW();
    SD_ReceiveByte();
}

static void SD_Deselect(void) {
    SD_CS_HIGH();
    SD_ReceiveByte();
}

static uint8_t SD_SendCommand(uint8_t cmd, uint32_t arg, uint8_t crc) {
    uint8_t buf[6];
    buf[0] = 0x40 | cmd;
    buf[1] = (arg >> 24) & 0xFF;
    buf[2] = (arg >> 16) & 0xFF;
    buf[3] = (arg >> 8) & 0xFF;
    buf[4] = arg & 0xFF;
    buf[5] = crc;

    SD_Deselect();
    SD_Select();

    if (!SD_WaitReady()) {
        SD_Deselect();
        return 0xFF;
    }

    for (int i = 0; i < 6; i++)
        SD_TransmitByte(buf[i]);

    // Aguarda resposta (bit 7 == 0)
    for (int i = 0; i < 10; i++) {
        uint8_t res = SD_ReceiveByte();
        if ((res & 0x80) == 0)
            return res;
    }

    return 0xFF;
}

uint8_t SD_Init(void) {
    SD_CS_HIGH();
    SD_SendDummyClock(); // 80 clocks

    uint8_t res = SD_SendCommand(CMD0, 0, 0x95);
    if (res != 0x01) return SD_ERROR;

    res = SD_SendCommand(CMD8, 0x1AA, 0x87);
    if (res != 0x01) return SD_ERROR;

    // Espera inicialização
    do {
        SD_SendCommand(CMD55, 0, 0x01);
        res = SD_SendCommand(ACMD41, 0x40000000, 0x01);
    } while (res != 0x00);

    res = SD_SendCommand(CMD58, 0, 0x01);
    SD_Deselect();
    return (res == 0x00) ? SD_OK : SD_ERROR;
}

uint8_t SD_ReadBlock(uint32_t blockAddr, uint8_t* buff) {
    uint8_t token;

    if (SD_SendCommand(CMD17, blockAddr, 0x01) != 0x00)
        return SD_ERROR;

    // Espera token 0xFE (início do bloco)
    for (int i = 0; i < 10000; i++) {
        token = SD_ReceiveByte();
        if (token == 0xFE) break;
    }
    if (token != 0xFE) return SD_ERROR;

    for (int i = 0; i < 512; i++)
        buff[i] = SD_ReceiveByte();

    SD_ReceiveByte(); // Discard CRC
    SD_ReceiveByte();

    SD_Deselect();
    return SD_OK;
}

uint8_t SD_WriteBlock(uint32_t blockAddr, const uint8_t* buff) {
    if (SD_SendCommand(CMD24, blockAddr, 0x01) != 0x00)
        return SD_ERROR;

    SD_TransmitByte(0xFE); // Start token

    for (int i = 0; i < 512; i++)
        SD_TransmitByte(buff[i]);

    SD_TransmitByte(0xFF); // Dummy CRC
    SD_TransmitByte(0xFF);

    uint8_t resp = SD_ReceiveByte();
    if ((resp & 0x1F) != 0x05) {
        SD_Deselect();
        return SD_ERROR;
    }

    while (!SD_ReceiveByte()); // Espera escrever

    SD_Deselect();
    return SD_OK;
}
