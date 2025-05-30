#include "diskio.h"
#include "sd_spi.h"

#define DEV_MMC  0

DSTATUS disk_status(BYTE pdrv) {
    if (pdrv == DEV_MMC)
        return 0;
    return STA_NOINIT;
}

DSTATUS disk_initialize(BYTE pdrv) {
    if (pdrv == DEV_MMC)
        return (SD_Init() == SD_OK) ? 0 : STA_NOINIT;
    return STA_NOINIT;
}

DRESULT disk_read(BYTE pdrv, BYTE* buff, DWORD sector, UINT count) {
    if (pdrv != DEV_MMC || count == 0)
        return RES_PARERR;

    for (UINT i = 0; i < count; i++) {
        if (SD_ReadBlock((sector + i) * 512, buff + (512 * i)) != SD_OK)
            return RES_ERROR;
    }

    return RES_OK;
}

DRESULT disk_write(BYTE pdrv, const BYTE* buff, DWORD sector, UINT count) {
#if FF_FS_READONLY
    return RES_WRPRT;
#else
    if (pdrv != DEV_MMC || count == 0)
        return RES_PARERR;

    for (UINT i = 0; i < count; i++) {
        if (SD_WriteBlock((sector + i) * 512, buff + (512 * i)) != SD_OK)
            return RES_ERROR;
    }

    return RES_OK;
#endif
}

DRESULT disk_ioctl(BYTE pdrv, BYTE cmd, void* buff) {
    if (pdrv != DEV_MMC) return RES_PARERR;

    switch (cmd) {
        case CTRL_SYNC:
            return RES_OK;
        case GET_SECTOR_COUNT:
            *(DWORD*)buff = 32768;  // Exemplo: 16MB
            return RES_OK;
        case GET_SECTOR_SIZE:
            *(WORD*)buff = 512;
            return RES_OK;
        case GET_BLOCK_SIZE:
            *(DWORD*)buff = 1;
            return RES_OK;
    }

    return RES_PARERR;
}
