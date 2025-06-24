#ifndef __USER_DISKIO_H
#define __USER_DISKIO_H

#include "ff_gen_drv.h"

DSTATUS USER_initialize(BYTE);
DSTATUS USER_status(BYTE);
DRESULT USER_read(BYTE, BYTE *, LBA_t, UINT);
DRESULT USER_write(BYTE, const BYTE *, LBA_t, UINT);
DRESULT USER_ioctl(BYTE, BYTE, void *);

#endif
