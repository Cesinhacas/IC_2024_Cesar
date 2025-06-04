#include "sd_spi.h"
#include <avr/io.h>
#include <util/delay.h>

// SPI Pins
#define DDR_SPI     DDRB
#define PORT_SPI    PORTB
#define DD_MOSI     PB3
#define DD_MISO     PB4
#define DD_SCK      PB5
#define DD_SS       PB2

// Cartão SD
#define SD_CS_LOW()     (PORTB &= ~(1 << DD_SS))
#define SD_CS_HIGH()    (PORTB |=  (1 << DD_SS))

// Comandos SD
#define CMD0  (0x40 + 0)    // GO_IDLE_STATE
#define CMD17 (0x40 + 17)   // READ_SINGLE_BLOCK
#define CMD24 (0x40 + 24)   // WRITE_BLOCK

// SPI: envia e recebe 1 byte
static uint8_t spi_transfer(uint8_t data) {
    SPDR = data;
    while (!(SPSR & (1 << SPIF)));
    return SPDR;
}

// Espera até receber 0xFF (idle)
static void sd_wait_ready(void) {
    for (uint16_t i = 0; i < 50000; i++) {
        if (spi_transfer(0xFF) == 0xFF) return;
        _delay_us(10);
    }
}

// Envia comando para o SD
static uint8_t sd_send_cmd(uint8_t cmd, uint32_t arg) {
    uint8_t res, crc;

    sd_wait_ready();
    SD_CS_LOW();

    spi_transfer(cmd);
    spi_transfer(arg >> 24);
    spi_transfer(arg >> 16);
    spi_transfer(arg >> 8);
    spi_transfer(arg);

    // CRC válido apenas para CMD0
    crc = (cmd == CMD0) ? 0x95 : 0xFF;
    spi_transfer(crc);

    // Espera resposta
    for (uint8_t i = 0; i < 10; i++) {
        res = spi_transfer(0xFF);
        if ((res & 0x80) == 0) break;
    }

    return res;
}

uint8_t SD_Init(void) {
    // Configura SPI como mestre
    DDR_SPI |= (1 << DD_MOSI) | (1 << DD_SCK) | (1 << DD_SS);
    DDR_SPI &= ~(1 << DD_MISO);
    PORT_SPI |= (1 << DD_SS); // SD CS em HIGH

    // SPI: habilita, mestre, clk/128 (~125kHz)
    SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR1) | (1 << SPR0);

    // Envia 80 clocks com CS alto
    SD_CS_HIGH();
    for (uint8_t i = 0; i < 10; i++) spi_transfer(0xFF);

    // CMD0 ? modo idle
    if (sd_send_cmd(CMD0, 0) != 0x01) {
        SD_CS_HIGH();
        return SD_ERROR;
    }

    // Aguarda sair do estado idle (envia 0xFF até 0x00)
    for (uint16_t i = 0; i < 5000; i++) {
        spi_transfer(0xFF);
        if (sd_send_cmd(0x41, 0) == 0x00) break;  // CMD1 ou ACMD41 (dependendo do cartão)
    }

    SD_CS_HIGH();
    spi_transfer(0xFF);

    return SD_OK;
}

uint8_t SD_ReadBlock(uint32_t blockAddr, uint8_t* buff) {
    if (sd_send_cmd(CMD17, blockAddr) != 0x00) {
        SD_CS_HIGH();
        return SD_ERROR;
    }

    // Espera pelo token 0xFE
    for (uint16_t i = 0; i < 10000; i++) {
        uint8_t token = spi_transfer(0xFF);
        if (token == 0xFE) break;
        _delay_us(10);
    }

    // Lê 512 bytes
    for (uint16_t i = 0; i < 512; i++) {
        buff[i] = spi_transfer(0xFF);
    }

    // Descarta CRC
    spi_transfer(0xFF);
    spi_transfer(0xFF);

    SD_CS_HIGH();
    spi_transfer(0xFF);
    return SD_OK;
}

uint8_t SD_WriteBlock(uint32_t blockAddr, const uint8_t* buff) {
    if (sd_send_cmd(CMD24, blockAddr) != 0x00) {
        SD_CS_HIGH();
        return SD_ERROR;
    }

    spi_transfer(0xFF);
    spi_transfer(0xFE); // Token de início

    // Envia 512 bytes
    for (uint16_t i = 0; i < 512; i++) {
        spi_transfer(buff[i]);
    }

    // Envia CRC falso
    spi_transfer(0xFF);
    spi_transfer(0xFF);

    // Verifica resposta
    uint8_t resp = spi_transfer(0xFF);
    if ((resp & 0x1F) != 0x05) {
        SD_CS_HIGH();
        return SD_ERROR;
    }

    // Aguarda fim do busy
    while (spi_transfer(0xFF) == 0x00);

    SD_CS_HIGH();
    spi_transfer(0xFF);
    return SD_OK;
}