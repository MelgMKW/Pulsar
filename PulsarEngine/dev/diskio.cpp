/*-----------------------------------------------------------------------*/
/* Low level disk I/O module SKELETON for FatFs     (C)ChaN, 2019        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control modules to the FatFs module with a defined API.       */
/*-----------------------------------------------------------------------*/

#include <dev/ff.hpp>         /* Obtains integer types */
#include <dev/diskio.hpp>     /* Declarations of disk functions */
#include <dev/sdi.hpp>

/*-----------------------------------------------------------------------*/
/* Get Drive Status                                                      */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status(
    BYTE /* pdrv: Physical drive nmuber to identify the drive */
)
{
    return 0;
}



/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize(
    BYTE /* pdrv: Physical drive nmuber to identify the drive */
)
{
    return 0;
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read(
    BYTE /* pdrv */,    /* Physical drive nmuber to identify the drive */
    BYTE* buff,         /* Data buffer to store read data */
    LBA_t sector,       /* Start sector in LBA */
    UINT count          /* Number of sectors to read */
)
{
    return ((Pulsar::FATIO*)Pulsar::IO::sInstance)->Sdi_read(sector, count, buff) ? RES_OK : RES_ERROR;
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

#if FF_FS_READONLY == 0

DRESULT disk_write(
    BYTE /* pdrv */,    /* Physical drive nmuber to identify the drive */
    const BYTE* buff,   /* Data to be written */
    LBA_t sector,       /* Start sector in LBA */
    UINT count          /* Number of sectors to write */
)
{
    return ((Pulsar::FATIO*)Pulsar::IO::sInstance)->Sdi_write(sector, count, buff) ? RES_OK : RES_ERROR;
}

#endif


/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

DRESULT disk_ioctl(
    BYTE /* pdrv */,    /* Physical drive nmuber (0..) */
    BYTE cmd,           /* Control code */
    void* buff          /* Buffer to send/receive control data */
)
{
    switch(cmd) {
        case CTRL_SYNC:
            return RES_OK;
        case GET_SECTOR_SIZE:
            *(WORD*)buff = ((Pulsar::FATIO*)Pulsar::IO::sInstance)->Sdi_sectorSize();
            return RES_OK;
        case CTRL_TRIM:
            {
                /*
                const LBA_t* args = (const LBA_t*)buff;
                LBA_t firstSector = args[0];
                LBA_t sectorCount = args[1] - args[0] + 1;
                */
                return RES_OK;
            }
        default:
            return RES_PARERR;
    }
}
