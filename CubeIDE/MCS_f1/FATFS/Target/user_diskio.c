#include "ff_gen_drv.h"
#include "sd_spi.h"

extern SPI_HandleTypeDef hspi1; // definido no CubeIDE
#define SD_CS_GPIO_Port GPIOB
#define SD_CS_Pin GPIO_PIN_0

DSTATUS USER_Status = STA_NOINIT;

DSTATUS USER_initialize(BYTE lun) {
    if (SD_SPI_Init(&hspi1, SD_CS_GPIO_Port, SD_CS_Pin) == 0) {
        USER_Status &= ~STA_NOINIT;
    } else {
        USER_Status |= STA_NOINIT;
    }
    return USER_Status;
}

DSTATUS USER_status(BYTE lun) {
    return USER_Status;
}

DRESULT USER_read(BYTE lun, BYTE *buff, LBA_t sector, UINT count) {
    if (USER_Status & STA_NOINIT)
        return RES_NOTRDY;

    if (SD_SPI_ReadBlocks(buff, sector, count) == 0)
        return RES_OK;
    else
        return RES_ERROR;
}

DRESULT USER_write(BYTE lun, const BYTE *buff, LBA_t sector, UINT count) {
#if FF_FS_READONLY == 0
    if (USER_Status & STA_NOINIT)
        return RES_NOTRDY;

    if (SD_SPI_WriteBlocks(buff, sector, count) == 0)
        return RES_OK;
    else
        return RES_ERROR;
#else
    return RES_WRPRT;
#endif
}

DRESULT USER_ioctl(BYTE lun, BYTE cmd, void *buff) {
    switch (cmd) {
    case CTRL_SYNC:
        return RES_OK;

    case GET_SECTOR_SIZE:
        *(WORD *)buff = 512;
        return RES_OK;

    case GET_BLOCK_SIZE:
        *(DWORD *)buff = 1;
        return RES_OK;

    case GET_SECTOR_COUNT:
        *(DWORD *)buff = SD_SPI_GetSectorCount();
        return RES_OK;

    default:
        return RES_PARERR;
    }
}
