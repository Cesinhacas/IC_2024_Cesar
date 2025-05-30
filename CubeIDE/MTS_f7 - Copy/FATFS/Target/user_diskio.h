#ifndef __USER_DISKIO_H
#define __USER_DISKIO_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ff_gen_drv.h"   // Para tipos como DSTATUS, DRESULT
#include "sd_spi.h"       // Seu driver de cartão SD via SPI
#include "ffconf.h"       // Para FF_FS_READONLY
#include "integer.h"      // Para tipos como DWORD, BYTE, etc.

typedef DWORD LBA_t;

extern Diskio_drvTypeDef USER_Driver;


// Identificador do drive físico (0 = SD)
#define DEV_MMC 0

// Prototipação das funções exigidas pelo FatFs
DSTATUS disk_status(BYTE pdrv);
DSTATUS disk_initialize(BYTE pdrv);
DRESULT disk_read(BYTE pdrv, BYTE* buff, LBA_t sector, UINT count);
DRESULT disk_write(BYTE pdrv, const BYTE* buff, LBA_t sector, UINT count);
DRESULT disk_ioctl(BYTE pdrv, BYTE cmd, void* buff);

#ifdef __cplusplus
}
#endif

#endif /* __USER_DISKIO_H */
