#include "Database.h"
#include "global.h"
#include <QDebug>

//#include "precomp.h"
#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtCore/QTextCodec>
#include <QtCore/QStringList>
#include <QtCore/QMap>


#define xprintf qDebug

speed_t __UART_BAUDRATE_MAP[] = {B9600, B19200, B38400, B57600, B115200};
//int __DOOR_STATUS[4] = {T_LOCK_UNCOND_CLOSE, T_LOCK_UNCOND_OPEN, T_LOCK_AUTO_RECOVER, T_LOCK_DOOR_OPEN};

enum
{
        FLASHREAD_NONE,
        FLASHREAD_FP,
        FLASHREAD_USERINFO,
        FLASHREAD_SLOG,
        FLASHREAD_GLOG
};

enum
{
        SETUPREAD_SUCCESS,
        SETUPREAD_NOEXIST,
        SETUPREAD_CSUMERROR,
};

static int __DB_BACKUPREAD_LICENSE_STAT = SETUPREAD_SUCCESS;
static int __DB_BACKUPREAD_SETUP_STAT = SETUPREAD_SUCCESS;

static int __flashread_type = FLASHREAD_NONE;
static BOOL __DB_FIST_LOAD = TRUE;

static BOOL DbTzVerify_High(int nTimeSectionID, int nWeekday, int nHour, int nMinute);
//////////////////////////////////////////////////////////////////////////

BOOL _Db_ReadFpDataFromFlash(int fd, void* pDst, int from, int to, BYTE byEmpty, int* pIndexDBChanged, int nBaseAddr/* = 0*/)
{
/*        int i;
        int nSizeof = sizeof(FPINFO);
        int pos;
        BYTE *buf = (BYTE*)pDst;
        int result;
        int nPercent, nPrevPercent = 0;

        *pIndexDBChanged = 0;
        if (from < 0 || from >= (int)gFpMaximum || to < 1 || to > (int)gFpMaximum || from >= to)
                return FALSE;

        uiLcdProgressStart(UISTR_FINGERPRINT_LOAD);

        for (i=from; i<to; i++)
        {
                if (gpIndexData[i])
                {
                        pos = i * nSizeof;
                        result = pread(fd, buf, (size_t)nSizeof, (off_t)(nBaseAddr + pos));

                        if (result == 0) //EOF
                                break;
                        else if (result == -1) //Fail
                        {
                                memset(buf, byEmpty, nSizeof);
                                *pIndexDBChanged = 1;
                                gpIndexData[i] = 0;
                        }
                }

                nPercent = LCDPROG_PERCENT(i-from, to-from) * (__DB_FIST_LOAD ? 0.15 : 1);
                if (nPercent != nPrevPercent)
                {
                        if (__DB_FIST_LOAD)
                                uiLcdProgress1(nPercent);
                        else
                                uiLcdProgress(nPercent);
                        nPrevPercent = nPercent;
                }

                buf += nSizeof;
        }

        uiLcdProgressEnd();

        return TRUE;
 */
}

BOOL _Db_FlashRead(int fd, void* pDst, int from, int to, int nSizeof, BYTE byEmpty, char */*szTitle*/, int *pResult/* = NULL*/, int nBaseAddr/* = 0*/)
{
        int i;
        int pos;
        BYTE *buf = (BYTE*)pDst;
        int result = 0;
        int nPercentBase = 0;
        int nPercent, nPrevPercent = 0;

        //uiLcdProgressStart(UISTR_FILEREAD);
        /*
        if (__DB_FIST_LOAD)
        {
                if(__flashread_type == FLASHREAD_USERINFO)
                        nPercentBase = 15;//userinfo
                else if(__flashread_type == FLASHREAD_SLOG)
                        nPercentBase = 20;//mlog
                else if(__flashread_type == FLASHREAD_GLOG)
                        nPercentBase = 25;//glog
        }
        */
        for (i=from; i<to; i++)
        {
                pos = i * nSizeof;
                result = pread(fd, buf, (size_t)nSizeof, (off_t)(nBaseAddr + pos));

                if (result == 0) //EOF
                {
                        i++;
                        break;
                }
                else if (result == -1) //ERROR
                        memset(buf, byEmpty, nSizeof);
                /*
                nPercent = nPercentBase + LCDPROG_PERCENT(i-from, to-from) * (__DB_FIST_LOAD ? 0.05 : 0);
                if (nPercent != nPrevPercent)
                {
                        if (__DB_FIST_LOAD)
                                uiLcdProgress1(nPercent);
                        else
                                uiLcdProgress(nPercent);
                        nPrevPercent = nPercent;
                }
                */
                buf += nSizeof;
        }

        //uiLcdProgressEnd();

        if (pResult)
                *pResult = i - from;
        return (i == to) || (result == 0);
}


BOOL _Db_FlashWrite(int fd, void* pSrc, int from, int to, int nSizeof, char */*szTitle*/, int nBaseAddr/* = 0*/)
{
/*        int i;
        int pos;
        BYTE *buf = (BYTE*)pSrc;
        int result = 0;

        uiLcdProgressStart(UISTR_FILEWRITE);

        for (i=from; i<to; i++)
        {
                pos = i * nSizeof;
                result = pwrite(fd, buf, (size_t)nSizeof, (off_t)(nBaseAddr + pos));

                if (result != nSizeof)
                        break;

                uiLcdProgress(LCDPROG_PERCENT(i-from, to-from));

                buf += nSizeof;
        }

        uiLcdProgressEnd();

        return (result > 0);
        */
}

//////////////////////////////////////////////////////////////////////////
BOOL _Db_FWWriteToFlash1(HFILE hFile, void* pSrc, int nSize)
{
/*        int		nOrgSize = nSize;
        BOOL	bRet = TRUE;

        if (nSize != MAKE_SECTOR_SIZE(nSize))
                return FALSE;

// 	if (CRC16Checksum(pSrc, nSize) != 0)
// 	{
// 		return FALSE;
// 	}

        uiLcdProgressStart(UISTR_FLASHWRITE);

        while (nSize > 0)
        {
                int nRet;

                nRet = write(hFile, pSrc, FLASH_SECTOR_SIZE);
                if (nRet != FLASH_SECTOR_SIZE)
                {
                        bRet = FALSE;
                        goto _lEXIT;
                }
                sync();

                uiLcdProgress(LCDPROG_PERCENT(nOrgSize-nSize, nOrgSize));

                pSrc = (char*)pSrc + FLASH_SECTOR_SIZE;
                nSize -= FLASH_SECTOR_SIZE;
        }

_lEXIT:
        uiLcdProgressEnd();
        return bRet;*/
}

//////////////////////////////////////////////////////////////////////////
BOOL _Db_FWWriteToFlash(unsigned  char* pRomImage, int nFileSize)
{
/*        BOOL bRet = TRUE;
        DWORD dwMagic;
        BYTE *pImages[3] = {NULL, NULL, NULL};
        int  nImageSize[3] = {0, 0, 0};
        const char *szFiles[3] = {PARTITION_DOWNLOADER, PARTITION_KERNEL, PARTITION_ROOTFS};

        dwMagic = *(DWORD*)pRomImage;

        if( (*(pRomImage+0)==0x77)&&(*(pRomImage+1)==0x00)&&
        (*(pRomImage+2)==0x00)&&(*(pRomImage+3)==0xea) )
        {
            dwMagic =MAGIC_DOWNLOADER;
        }
        if (dwMagic == MAGIC_DOWNLOADER)
        {
                if (nFileSize == DOWNLOADER_IMAGE_SIZE)
                {
                        if (nFileSize > DOWNLOADER_IMAGE_SIZE)
                                return FALSE;

                        pImages[0] = pRomImage; nImageSize[0] = nFileSize;
                }
                else if (nFileSize > g_params.nDownloaderSize + g_params.nKernelSize)
                {
                        if (nFileSize > ROM_IMAGE_SIZE)
                                return FALSE;

                        T_PARAMETER_INFO *param = (T_PARAMETER_INFO*)&pRomImage[DOWNLOADER_IMAGE_SIZE];
                        param->dwFlashMagic = NAND_FLASH_MAGIC; //Systemarea's ECC is confirmed
                        param->nMachineID = g_params.nMachineID;
                        param->nBaudrate = g_params.nBaudrate;
                        memcpy(param->byMACaddr, g_params.byMACaddr, 8);
                        param->ipAddress = g_params.ipAddress;
                        param->ipSubnetMask = g_params.ipSubnetMask;
                        param->ipDefaultGateway = g_params.ipDefaultGateway;
                        param->dwCommPassword = g_params.dwCommPassword;
                        param->wPortNum = g_params.wPortNum;
                        param->wChecksum = 0;
                        param->wChecksum = CRC16Checksum(param, sizeof(T_PARAMETER_INFO));
                        pImages[0] = &pRomImage[0]; nImageSize[0] = g_params.nDownloaderSize;
                        pImages[1] = &pRomImage[g_params.nDownloaderSize]; nImageSize[1] = g_params.nKernelSize;
                        pImages[2] = &pRomImage[g_params.nDownloaderSize + g_params.nKernelSize]; nImageSize[2] = nFileSize - nImageSize[0] - nImageSize[1];
                }
        }
        else if (dwMagic == MAGIC_ZIMAGE)
        {
                if (nFileSize > KERNEL_IMAGE_SIZE)
                        return FALSE;

                pImages[1] = pRomImage; nImageSize[1] = nFileSize;
        }
        else if (dwMagic == MAGIC_ROOTFS)
        {
                if (nFileSize > ROOTFS_IMAGE_SIZE)
                        return FALSE;

                pImages[2] = pRomImage;
                nImageSize[2] = nFileSize;
        }

        for (int i=0; i<3; i++)
        {
                if (!pImages[i])
                        continue;

                HFILE hDev = open(szFiles[i], O_RDWR);
                if (hDev == INVALID_HANDLE_VALUE)
                {
                        bRet = FALSE;
                        goto _lExit;
                }
                uiLcdProgressDlgShow(UISTR_FILEWRITE); g_bProgress = TRUE;
                bRet = _Db_FWWriteToFlash1(hDev, pImages[i], MAKE_SECTOR_SIZE(nImageSize[i]));
                uiLcdProgressDlgExit(); g_bProgress = FALSE;
                FD_CLOSE(hDev);
        }

_lExit:
        uiLcdProgressDlgExit(); g_bProgress = FALSE;

        return bRet;*/
}


//////////////////////////////////////////////////////////////////////////
BOOL _Db_SaveOne(int fd, int nPos, int nSizeOf, char* pcBuf)
{
        int result;

        result = pwrite(fd, pcBuf + nPos * nSizeOf, nSizeOf, (off_t)(nPos * nSizeOf));

        return (result == nSizeOf);
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
//////////////////////////////////////////////////////////////////////////




//备份setup读取
int DbBackupSetupRead(BYTE *pby)
{
        int i;
        int fd;
        DWORD* pdw = (DWORD*)pby;
        DWORD dwCheckSum = FLASH_CHECKSUM_SIGN;

        fd = open(FLASH_SETUP_BACKUP, O_RDONLY,777);
        if (fd == INVALID_HANDLE_VALUE)
                return SETUPREAD_NOEXIST;

        memset(pby, 0, FLASH_SETUP_SIZE);
        i = read(fd, pby, FLASH_SETUP_SIZE);
        FD_CLOSE(fd);

        for (i=0; i<(FLASH_SETUP_SIZE - 4)/4; i++)
        {
                pdw++;
                dwCheckSum += *pdw;
        }

        if (dwCheckSum != *(DWORD*)pby)
                return SETUPREAD_CSUMERROR;

        return SETUPREAD_SUCCESS;
}
//备份setup写入
int DbBackupSetupWrite(BYTE *pby)
{
        int fd;
        BOOL bRet;

        fd = open(FLASH_SETUP_BACKUP,O_WRONLY|O_CREAT,777);
        if (fd == INVALID_HANDLE_VALUE)
                return FALSE;

        bRet = (write(fd,pby,FLASH_SETUP_SIZE) == FLASH_SETUP_SIZE);
        FD_CLOSE(fd);
        return bRet;
}


//////////////////////////////////////////////////////////////////////////
static BYTE g_byMACaddr_default[8] = {0x01, 0x13, 0x8F, 0x28, 0x47, 0xF2, 0x00, 0x0};
static BOOL SetupTotaldata2Default_flag=0;

//////////////////////////////////////////////////////////////////////////
BOOL DbParamInfoSave(void)
{
/*        BYTE *pBuffer = (BYTE*)malloc(FLASH_SECTOR_SIZE);
        int mtd_fd = INVALID_HANDLE_VALUE;

        if (!pBuffer)
                return FALSE;

        g_params.wChecksum = 0;
        g_params.wChecksum = CRC16Checksum(&g_params, sizeof(g_params));
        memcpy(pBuffer, &g_params, sizeof(g_params));

        mtd_fd = open(PARTITION_DOWNLOADER, O_RDWR);
        if (mtd_fd != INVALID_HANDLE_VALUE)
        {
                pwrite(mtd_fd, pBuffer, FLASH_SECTOR_SIZE, OFFSET_PARAM_INFO);
                sync();
                FD_CLOSE(mtd_fd);
        }

        FREE(pBuffer);

        return TRUE;*/
}

//////////////////////////////////////////////////////////////////////////
BOOL DbParamInfoLoad(void)
{
/*        BOOL bRet = TRUE;
        BYTE *pBuffer = (BYTE*)malloc(FLASH_SECTOR_SIZE);
        T_PARAMETER_INFO *PARAM_INFO = (T_PARAMETER_INFO*)pBuffer;
        int mtd_fd = INVALID_HANDLE_VALUE;

        if (!pBuffer)
                return FALSE;

        mtd_fd = open(PARTITION_DOWNLOADER, O_RDWR);
        if (mtd_fd != INVALID_HANDLE_VALUE)
        {
                pread(mtd_fd, pBuffer, FLASH_SECTOR_SIZE, OFFSET_PARAM_INFO);
                FD_CLOSE(mtd_fd);
        }

        if (CRC16Checksum(PARAM_INFO, sizeof(T_PARAMETER_INFO)) == 0 &&
                MAKELONG(PARAM_INFO->res2, PARAM_INFO->res1) == NAND_FLASH_MAGIC)
        {
                memcpy(&g_params, pBuffer, sizeof(T_PARAMETER_INFO));
        }
        else //to Default
        {
                g_params.dwFlashMagic = NAND_FLASH_MAGIC;
                //
                g_params.nMachineID = 1;
                        g_params.nBaudrate = BAUDRATE_38400;
                //g_params.nBaudrate = BAUDRATE_115200;
                memcpy(g_params.byMACaddr, g_byMACaddr_default, sizeof(g_params.byMACaddr));
                g_params.ipAddress = UI_IP_MAKE(192, 168, 10, 62);
                g_params.ipSubnetMask = UI_IP_MAKE(255, 255, 255, 0);
                g_params.ipDefaultGateway = UI_IP_MAKE(192, 168,10, 1);
                g_params.dwCommPassword = 0;
                g_params.wPortNum = 5005;
                g_params.res1 = HIWORD(NAND_FLASH_MAGIC);
                //
                g_params.nDownloaderSize = 1*1024*1024;
                g_params.nKernelSize = 2*1024*1024;
                g_params.nRootfsSize = 13*1024*1024;
                g_params.nConsoleUse = 0;
                //
                g_params.wSplashSize = 0xFFFF;
                g_params.wSplashChecksum = 0;
                //
                g_params.res2 = LOWORD(NAND_FLASH_MAGIC);
                g_params.wChecksum = 0;

                bRet = DbParamInfoSave();
        }

        FREE(pBuffer);

        if (g_params.nConsoleUse)
                g_bPoweroffFlag = FALSE;

        if (g_params.wSplashSize)
        {
                mtd_fd = open(PARTITION_DOWNLOADER, O_RDWR);
                if (mtd_fd != INVALID_HANDLE_VALUE)
                {
                        if (pread(mtd_fd, gpSplash, g_params.wSplashSize, OFFSET_SPLASH) != g_params.wSplashSize)
                                memset(gpSplash, 0, sizeof(gpSplash));
                        FD_CLOSE(mtd_fd);
                }
        }

        return bRet;*/
}

int DbBackupLicenseRead(BYTE *pby)
{
        int i;
        int fd;
        DWORD* pdw = (DWORD*)pby;
        DWORD dwCheckSum = FLASH_CHECKSUM_SIGN;

        fd = open(FLASH_LICENSE_BACKUP, O_RDONLY,777);
        if (fd == INVALID_HANDLE_VALUE)
                return SETUPREAD_NOEXIST;

        memset(pby, 0, FLASH_LICENSE_SIZE);
        i = read(fd, pby, FLASH_LICENSE_SIZE);
        FD_CLOSE(fd);

        for (i=0; i<(FLASH_LICENSE_SIZE - 4)/4; i++)
        {
                pdw++;
                dwCheckSum += *pdw;
        }

        if (dwCheckSum != *(DWORD*)pby)
                return SETUPREAD_CSUMERROR;

        return SETUPREAD_SUCCESS;
}
BOOL DbBackupLicenseWrite(BYTE *pby)
{
        int fd;
        BOOL bRet;

        fd = open(FLASH_LICENSE_BACKUP, O_WRONLY | O_CREAT,777);
        if (fd == INVALID_HANDLE_VALUE)
                return FALSE;

        bRet = (write(fd, pby, FLASH_LICENSE_SIZE) == FLASH_LICENSE_SIZE);
        FD_CLOSE(fd);
        return bRet;
}
void DbLicenseCalc(void)
{
        dbLicense.dwFlashSizeUserInfo = MAKE_SECTOR_SIZE(sizeof(USER_INFO) * dbLicense.nMaxEnrollCount);

        //dbLicense.dwFlashSizeFP = MAKE_SECTOR_SIZE(sizeof(FPINFO) * dbLicense.nMaxEnrollCount);

        //dbLicense.nSlogMaxCount = MAX_SLOG_COUNT + 1;
        //dbLicense.dwFlashSizeSlog = MAKE_SECTOR_SIZE(sizeof(MLOG_INFO) * dbLicense.nSlogMaxCount);

        //dbLicense.nGlogMaxCount = MAX_GLOG_COUNT + 1;
        //dbLicense.dwFlashSizeGlog = MAKE_SECTOR_SIZE(sizeof(ALOG_INFO) * dbLicense.nGlogMaxCount);
}
BOOL DbLicenseWrite(void)
{
        int i;
        int fd;
        BYTE* pby;
        DWORD* pdw;
        DWORD dwCheckSum = FLASH_CHECKSUM_SIGN;
        BOOL bRet = TRUE;

        fd = open(FLASH_LICENSE_FILENAME, O_WRONLY | O_CREAT,777);
        if (fd == INVALID_HANDLE_VALUE)
                return FALSE;

        pby = (BYTE*)malloc(FLASH_LICENSE_SIZE);
        pdw = (DWORD*)pby;
        if (pby == NULL)
        {
                bRet = FALSE;
                goto _lExit;
        }

        DbLicenseCalc();

        memset(pby, 0, FLASH_LICENSE_SIZE);
        memcpy(pby, &dbLicense, sizeof(DBLICENSE));

        for (i=0; i<(FLASH_LICENSE_SIZE - 4)/4; i++)
        {
                pdw++;
                dwCheckSum += *pdw;
        }

        *(DWORD*)pby = dwCheckSum;

        bRet = (write(fd, pby, FLASH_LICENSE_SIZE) == FLASH_LICENSE_SIZE);

        if (!__DB_FIST_LOAD)
                bRet = bRet && DbBackupLicenseWrite(pby);


        if (TRUE)
        {
                //memcpy(&g_params.byMACaddr[0], &dbLicense.byMACaddr[0], 6);
                //DbParamInfoSave();
        }
_lExit:
        if (pby)
                FREE(pby);

        FD_CLOSE(fd);

        return bRet;
}

BOOL DbLicenseRead(void)
{
        int i;
        int fd;
        BYTE* pby;
        BYTE* pbyBackup;
        DWORD* pdw;
        DWORD dwCheckSum = FLASH_CHECKSUM_SIGN;
        BOOL bRet = TRUE;
        int nBackupStatus;

        fd = open(FLASH_LICENSE_FILENAME, O_RDWR | O_CREAT,777);
        if (fd == INVALID_HANDLE_VALUE)
                return FALSE;

        pby = (BYTE*)malloc(FLASH_LICENSE_SIZE);
        pdw = (DWORD*)pby;
        pbyBackup = (BYTE*)malloc(FLASH_LICENSE_SIZE);
        if (pby == NULL || pbyBackup == NULL)
        {
                bRet = FALSE;
                goto _lExit;
        }

        memset(pby, 0, FLASH_LICENSE_SIZE);
        i = read(fd, pby, FLASH_LICENSE_SIZE);
        FD_CLOSE(fd);

        for (i=0; i<(FLASH_LICENSE_SIZE - 4)/4; i++)
        {
                pdw++;
                dwCheckSum += *pdw;
        }

        __DB_BACKUPREAD_LICENSE_STAT = nBackupStatus = DbBackupLicenseRead(pbyBackup);

        if ((dwCheckSum == *(DWORD*)pby) && (nBackupStatus != SETUPREAD_SUCCESS))
        {
                DbBackupLicenseWrite(pby);
#if FUCK
                qDebug() << "DbLicenseRead::DbBackupLicenseWrite(pby);";
#endif
        }
        else if ((dwCheckSum != *(DWORD*)pby) && (nBackupStatus == SETUPREAD_SUCCESS))
        {
                memcpy(pby, pbyBackup, FLASH_LICENSE_SIZE);
                memcpy(&dbLicense, pbyBackup, sizeof(DBLICENSE));
                dbLicense.dwCheckSum = 0;
                DbLicenseWrite();
                pdw = (DWORD*)pby;
                for (i=0; i<(FLASH_LICENSE_SIZE - 4)/4; i++)
                {
                        pdw++;
                        dwCheckSum += *pdw;
                }
        }
        else if ((dwCheckSum == *(DWORD*)pby) && (nBackupStatus == SETUPREAD_SUCCESS))
        {
                if (memcmp(pby, pbyBackup, FLASH_LICENSE_SIZE))
                        DbBackupLicenseWrite(pby);
#if FUCK
                qDebug() << "DbLicenseRead::(dwCheckSum == *(DWORD*)pby) && (nBackupStatus == SETUPREAD_SUCCESS)";
#endif
        }

        if (dwCheckSum != *(DWORD*)pby || SetupTotaldata2Default_flag) //To Default, in case of License & LicenseBackup damaged or first booting !
        {
//_lDefault:
                dbLicense.dwCheckSum = 0;
                //dbLicense.dwBuildNumber = FLASH_CHECKSUM_SIGN;
                dbLicense.dwSystemCheck = 0;
                //strcpy(dbLicense.szFirstDate, LNSC_FIRST_DATE);
                //strcpy(dbLicense.szSerialNumber, LNSC_SERIAL);
                //strcpy(dbLicense.szTradeMark, LNSC_TRADEMARK);
                //strcpy(dbLicense.szProductName, LNSC_PRODUCTNAME);
                //strcpy(dbLicense.szProductType, LNSC_PRODUCTTYPE);
                //strcpy(dbLicense.szEngineVersion, LNSC_ENGINEVERSION);
                ///strcpy(dbLicense.szFirmwareVersion, LNSC_FIRMWAREVERSION);
                dbLicense.nMaxEnrollCount = 5000;

                //dbLicense.nBackupNumber = MAX_ENROLL_BACKUP_NUM;
                dbLicense.bUseEthernet = TRUE;
                dbLicense.bUseUSB = TRUE;
                dbLicense.bUseCard = TRUE;
                dbLicense.bUsePOE = FALSE;
                dbLicense.bUseWebServer = TRUE;
                //dbLicense.bUseWebServer = FALSE;
                dbLicense.bUseRS232 = TRUE;
                dbLicense.bUseMP3 = FALSE;
                dbLicense.bUseWiegand = TRUE;
                dbLicense.bUseAlarmFunction = TRUE;
                dbLicense.bUseACFunction = FALSE;
                dbLicense.bLockControl = TRUE;
                dbLicense.bUseCamera = FALSE;
                //dbLicense.nCMOS = CMOSTYPE_PG0305;
                //memcpy(&dbLicense.byMACaddr[0], &g_params.byMACaddr[0], 6);
                //dbLicense.byTcpipMode = TCPIP_CLIENT;
                dbLicense.bOnLineEnroll = FALSE;
                //dbLicense.bOnLineEnroll = TRUE;

                DbLicenseWrite();

                bzero(pby, FLASH_LICENSE_SIZE);
                memcpy(pby, &dbLicense, sizeof(dbLicense));
                pdw = (DWORD*)pby;
                for (i=0; i<(FLASH_LICENSE_SIZE - 4)/4; i++)
                {
                        pdw++;
                        dwCheckSum += *pdw;
                }
                *(DWORD*)pby = dwCheckSum;
                DbBackupLicenseWrite(pby);

                bRet = FALSE;
        }
        else
        {
                memcpy(&dbLicense, pby, sizeof(DBLICENSE));
#if FUCK
                qDebug() << "DbLicenseRead::memcpy(&dbLicense, pby, sizeof(DBLICENSE))";
#endif
        }

_lExit:
        FREE(pby);
        FREE(pbyBackup);
        FD_CLOSE(fd);
        return bRet;
}



//////////////////////////////////////////////////////////////////////////
BOOL DbSetupTotalRead(BOOL bBackupCheck /*= TRUE*/)
{
    int i, k;
    int fd;
    BYTE* pby;
    BYTE* pbyBackup;
    DWORD* pdw;
    DWORD dwCheckSum = FLASH_CHECKSUM_SIGN;
    BOOL bRet = TRUE;
    char *szCurrentName = NULL;
    int nBackupStatus;


    bRet = DbLicenseRead();


    //读取原始数据，便于程序使用
    fd = open(FLASH_SETUP_FILENAME,O_RDWR|O_CREAT,777);
    if (fd == INVALID_HANDLE_VALUE)
            return FALSE;
    pby = (BYTE*)malloc(FLASH_SETUP_SIZE);//分配
    pdw = (DWORD*)pby;//转换下
    pbyBackup = (BYTE*)malloc(FLASH_SETUP_SIZE);//备份
    if(pby == NULL || pbyBackup == NULL)
    {
        bRet = FALSE;
        goto _lExit;
    }

    memset(pby, 0, FLASH_SETUP_SIZE);
    i = read(fd,pby,FLASH_SETUP_SIZE);//将存储的读出来放入
    FD_CLOSE(fd);
    for (i=0;i<(FLASH_SETUP_SIZE - 4)/4;i++)//四字节读取检测
    {
        pdw++;
        dwCheckSum += *pdw;
    }

    //读取备份
    __DB_BACKUPREAD_SETUP_STAT = nBackupStatus = DbBackupSetupRead(pbyBackup);

    //如果检测正确但备份有问题，那么重新写入备份
    if((dwCheckSum == *(DWORD*)pby) && (nBackupStatus != SETUPREAD_SUCCESS))
    {
        DbBackupSetupWrite(pby);
        qDebug() << "DbSetupTotalRead::(dwCheckSum == *(DWORD*)pby) && (nBackupStatus != SETUPREAD_SUCCESS)";
    }
    //如果检测错误，备份正确,那将备份写入运行的
    else if ((dwCheckSum != *(DWORD*)pby) && (nBackupStatus == SETUPREAD_SUCCESS))
    {
        if (bBackupCheck)//默认是1
        {
            memcpy(pby,pbyBackup,FLASH_SETUP_SIZE);
            memcpy(&dbSetupTotal,pbyBackup,sizeof(DBSETUP_TOTAL));
            dbSetupTotal.dwCheckSum = 0;
            DbSetupTotalWrite();
            pdw = (DWORD*)pby;
            for (i=0; i<(FLASH_SETUP_SIZE - 4)/4; i++)
            {
                pdw++;
                dwCheckSum += *pdw;
            }
         }
        qDebug() << "DbSetupTotalRead::(dwCheckSum != *(DWORD*)pby) && (nBackupStatus == SETUPREAD_SUCCESS)";
    }
    //都正常运行
    else if((dwCheckSum == *(DWORD*)pby) && (nBackupStatus == SETUPREAD_SUCCESS))
    {
        if (memcmp(pby, pbyBackup, FLASH_SETUP_SIZE))
            DbBackupSetupWrite(pby);
        qDebug() << "(DbSetupTotalRead::dwCheckSum == *(DWORD*)pby) && (nBackupStatus == SETUPREAD_SUCCESS)";
    }
    else
    {
        qDebug() << "DbSetupTotalRead::(dwCheckSum != *(DWORD*)pby) && (nBackupStatus != SETUPREAD_SUCCESS)";
    }
    //默认情况下设置的参数
    if (!bRet || (dwCheckSum != *(DWORD*)pby) || SetupTotaldata2Default_flag)//To Default
    {
        dbSetupTotal.dwCheckSum = 0;

        dbSetupTotal.setSystem.nTimeFormat = 1;
        dbSetupTotal.setSystem.nDateFormat = 1;


        DbSetupTotalWrite();//写入
        bzero(pby,FLASH_SETUP_SIZE);
        memcpy(pby,&dbSetupTotal,sizeof(dbSetupTotal));
        pdw = (DWORD*)pby;
        for (i=0; i<(FLASH_SETUP_SIZE - 4)/4; i++)
        {
            pdw++;
            dwCheckSum += *pdw;
        }
        *(DWORD*)pby = dwCheckSum;
        DbBackupSetupWrite(pby);
        bRet = FALSE;

        qDebug() << "DbSetupTotalRead::SetupTotaldataDefault_flag";

    }
    else
    {
        memcpy(&dbSetupTotal, pby, sizeof(DBSETUP_TOTAL));
        qDebug() << "DbSetupTotalRead::SetupTotaldataDefault_flag1111111111111";
    }

_lExit:
    if(pby)
      FREE(pby);
    FD_CLOSE(fd);
    return bRet;
}

//对setup数据的写入
BOOL DbSetupTotalWrite(BOOL bChangeTheme /*= TRUE*/)
{
    int i;
    int fd;
    BYTE* pby;
    DWORD* pdw;
    DWORD dwCheckSum = FLASH_CHECKSUM_SIGN;
    BOOL bRet = TRUE;

    fd = open(FLASH_SETUP_FILENAME,O_RDWR|O_CREAT,777);
    if (fd == INVALID_HANDLE_VALUE)
        return FALSE;
    pby = (BYTE*)malloc(FLASH_SETUP_SIZE);
    pdw = (DWORD*)pby;
    if (pby == NULL)
    {
        bRet = FALSE;
        goto _lExit;
    }
    memset(pby, 0, FLASH_SETUP_SIZE);
    memcpy(pby,&dbSetupTotal,sizeof(DBSETUP_TOTAL));//读取
    for (i=0; i<(FLASH_SETUP_SIZE - 4)/4; i++)
    {
        pdw++;
        dwCheckSum += *pdw;
    }
    *(DWORD*)pby = dwCheckSum;
    if(write(fd,pby,FLASH_SETUP_SIZE) != FLASH_SETUP_SIZE)//写入
        bRet = FALSE;
    if(!__DB_FIST_LOAD)
        bRet = bRet && DbBackupSetupWrite(pby);
_lExit:
    if(pby)
        FREE(pby);
    FD_CLOSE(fd);
    return bRet;
}


void DbSetupTotalSave(void)

{
        int i;
        int fd;
        BYTE* pby;
        DWORD* pdw;
        DWORD dwCheckSum = FLASH_CHECKSUM_SIGN;
        BOOL bRet = TRUE;

        fd = open(FLASH_SETUP_FILENAME, O_RDWR | O_CREAT,777);
        if (fd == INVALID_HANDLE_VALUE)
                return ;

        pby = (BYTE*)malloc(FLASH_SETUP_SIZE); pdw = (DWORD*)pby;
        if (pby == NULL)
        {
                bRet = FALSE;
                goto _lExit;
        }

        memset(pby, 0, FLASH_SETUP_SIZE);
        memcpy(pby, &dbSetupTotal, sizeof(DBSETUP_TOTAL));

        for (i=0; i<(FLASH_SETUP_SIZE - 4)/4; i++)
        {
                pdw++;
                dwCheckSum += *pdw;
        }

        *(DWORD*)pby = dwCheckSum;

        if (write(fd, pby, FLASH_SETUP_SIZE) != FLASH_SETUP_SIZE)
                bRet = FALSE;
_lExit:
        if (pby)
                FREE(pby);

        FD_CLOSE(fd);
}

void DbSetupTotal2Default(void)
{
        int fd;
        BOOL bRet = TRUE;
        BYTE* pby;

        fd = open(FLASH_SETUP_FILENAME, O_WRONLY | O_CREAT,777);
        if (fd == INVALID_HANDLE_VALUE)
                return;

        pby = (BYTE*)malloc(FLASH_SETUP_SIZE);
        if (pby == NULL)
        {
                bRet = FALSE;
                goto _lExit;
        }

        dbSetupTotal.dwCheckSum ++;
        memcpy(pby, &dbSetupTotal, sizeof(DBSETUP_TOTAL));
        write(fd, pby, FLASH_SETUP_SIZE);

        SetupTotaldata2Default_flag=1;
        DbSetupTotalRead(FALSE);
        SetupTotaldata2Default_flag=0;


_lExit:
        if (pby)
                FREE(pby);

        FD_CLOSE(fd);
        if (bRet == FALSE)
        {
                printf("DbSetupTotal2Default Fail !\n");
        }
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
//////////////////////////////////////////////////////////////////////////
BOOL DbFpLoad(void)
{
 /*       int nIndexDBChanged;
        int fd;
        BOOL bRet = TRUE;

        fd = open(FLASH_FP_FILENAME, O_RDWR | O_CREAT);
        if (fd == INVALID_HANDLE_VALUE)
                return FALSE;

        gpFingerEnrollData = SB_FP_FPDBALLOC();
        if ( gpFingerEnrollData == NULL )
        {
                bRet = FALSE;
                goto _lExit;
        }

        _Db_ReadFpDataFromFlash(fd, gpFingerEnrollData, 0, dbLicense.nMaxEnrollCount, 0, &nIndexDBChanged);

        if(nIndexDBChanged)
                bRet = DbFPIndexSave();

_lExit:
        FD_CLOSE(fd);
        return bRet;*/
}

//////////////////////////////////////////////////////////////////////////
BOOL DbFpSave(void)
{
/*        int fd;
        BOOL bRet = TRUE;

        fd = open(FLASH_FP_FILENAME, O_RDWR | O_CREAT);
        if (fd == INVALID_HANDLE_VALUE)
                return FALSE;

        if ( gpFingerEnrollData == NULL )
        {
                bRet = FALSE;
                goto _lExit;
        }

        bRet = _Db_FlashWrite(fd, gpFingerEnrollData, 0, dbLicense.nMaxEnrollCount, sizeof(FPINFO), NULL);

_lExit:
        FD_CLOSE(fd);
        return bRet;*/
}

//////////////////////////////////////////////////////////////////////////
BOOL DbFpSaveOne(int nPos)
{
 /*       int fd;
        BOOL bRet = TRUE;

        fd = open(FLASH_FP_FILENAME, O_RDWR | O_CREAT);
        if (fd == INVALID_HANDLE_VALUE)
                return FALSE;

        bRet = _Db_SaveOne(fd, nPos, sizeof(FPINFO), (char*)gpFingerEnrollData);

        FD_CLOSE(fd);
        return bRet;*/
}

//////////////////////////////////////////////////////////////////////////
BOOL DbFpDelete(USER_INFO* pUserInfo, int nFP)
{
 /*       DWORD dwIndexFP, dwPrevIndexFP;
        int i;
        FPINFO* pFpInfo = NULL;

        i = 0;
        dwPrevIndexFP = -1UL;
        dwIndexFP = pUserInfo->FP - 1;

        while (dwIndexFP != -1UL)
        {
                pFpInfo = &gpFingerEnrollData[dwIndexFP];
                if (pFpInfo->wParam == nFP)
                {
                        if (dwPrevIndexFP == -1UL)
                                pUserInfo->FP = FP_GET_NEXTPOS(pFpInfo);
                        else
                                FP_SET_NEXTPOS(&gpFingerEnrollData[dwPrevIndexFP], FP_GET_NEXTPOS(pFpInfo));

                        memset(pFpInfo, 0, sizeof(FPINFO)); DbFpSaveOne((int)dwIndexFP);
                        gpIndexData[dwIndexFP] = 0; DbFPIndexSave();
                        return TRUE;
                }

                dwPrevIndexFP = dwIndexFP;
                dwIndexFP = FP_GET_NEXTPOS(pFpInfo) - 1;

                i++;
                if (i >= dbLicense.nBackupNumber)
                        break;
        }

        return FALSE;*/
}

//////////////////////////////////////////////////////////////////////////
BOOL DbFpDeleteAll(void)
{
        //return DELETE_FILE(FLASH_FP_FILENAME);
}

//////////////////////////////////////////////////////////////////////////
int DbFpGetPosition(int nUIPos, int nFP)
{
 /*       if (nUIPos >= dbLicense.nMaxEnrollCount)
                return -1;

        DWORD dwIndexFP;
        int i;
        FPINFO* pFpInfo = NULL;
        USER_INFO* pUserInfo = &gpUserInfoEnrollData[nUIPos];

        i = 0;
        dwIndexFP = pUserInfo->FP - 1;
        while (dwIndexFP != -1UL)
        {
                pFpInfo = &gpFingerEnrollData[dwIndexFP];
                if (pFpInfo->wParam == nFP)
                        return (int)dwIndexFP;

                dwIndexFP = FP_GET_NEXTPOS(pFpInfo) - 1;

                i++;
                if (i >= dbLicense.nBackupNumber)
                        break;
        }

        return -1;*/
}

//////////////////////////////////////////////////////////////////////////
void* DbFpGetPointer(int nUIPos, int nFP)
{
 /*       int nPos = DbFpGetPosition(nUIPos, nFP);
        if (nPos < 0)
                return NULL;

        return &gpFingerEnrollData[nPos];*/
}

//////////////////////////////////////////////////////////////////////////
BOOL DbFpSetPointer(int nUIPos, int nFP, void* pFpInfo, BOOL bNoMatch, BOOL bFlashWrite /*= TRUE*/)
{
/*        if (nUIPos >= dbLicense.nMaxEnrollCount)
                return FALSE;

        BOOL bRet = TRUE;
        BYTE INDEX_BACKUP;
        FPINFO* FP_BACKUP = (FPINFO*)malloc(sizeof(FPINFO));
        USER_INFO* pUserInfo = &gpUserInfoEnrollData[nUIPos];
        int nPos;
        FPINFO* pFpDatabase;
        BOOL bOverwrite = TRUE;

        if (!FP_BACKUP)
        {
                bRet = FALSE;
                goto _lExit;
        }

        nPos = DbFpGetPosition(nUIPos, nFP);

        if (nPos < 0)
        {
                if(DbFpGetCount() + 1 > dbLicense.nMaxEnrollCount)
                {
                        bRet = FALSE;
                        goto _lExit;
                }

                bOverwrite = FALSE;
                nPos = DbFpGetUnusedPosition();
        }
////
        if (nPos != dbLicense.nMaxEnrollCount)
        {
                xprintf("10\r\n");
                pFpDatabase = &gpFingerEnrollData[nPos];
                memcpy(FP_BACKUP, pFpDatabase, sizeof(FPINFO));
                INDEX_BACKUP = gpIndexData[nPos];

                memset(pFpDatabase, 0, sizeof(FPINFO));
                gpIndexData[nPos] = 0;
xprintf("11\r\n");
xprintf("bNoMatch ==%d\r\n",bNoMatch );
                if (!bNoMatch && SB_FP_IDENTIFYFPDATA((FPINFO*)pFpInfo, NULL) >= 0)
                {
                        xprintf("12\r\n");
                        memcpy(pFpDatabase, FP_BACKUP, sizeof(FPINFO));
                        gpIndexData[nPos] = INDEX_BACKUP;
                        bRet = FALSE;
                        goto _lExit;
                }
///
xprintf("ywm1\r\n");
                memcpy(pFpDatabase, pFpInfo, sizeof(FPINFO));
                pFpDatabase->lParam = FP_BACKUP->lParam;
                if (!bOverwrite)
                {
                        xprintf("13\r\n");
                        FP_SET_UIPOS(pFpDatabase, nUIPos);
                        FP_SET_NEXTPOS(pFpDatabase, pUserInfo->FP);
                        pUserInfo->FP = nPos + 1;
                }
                xprintf("14\r\n");
                pFpDatabase->wParam = nFP;
                gpIndexData[nPos] = 1;
xprintf("15\r\n");
                if (bFlashWrite)
                        bRet = DbFpSaveOne(nPos) && DbFPIndexSave();
                xprintf("16\r\n");
        }
xprintf("17\r\n");
_lExit:
        FREE(FP_BACKUP);

        return bRet;*/
}

//////////////////////////////////////////////////////////////////////////
int DbFpGetCount(void)
{
 /*       int i;
        int nRet = 0;

        for (i = 0; i < dbLicense.nMaxEnrollCount; i++)
        {
                if (gpIndexData[i] == 1)
                         nRet++;
        }

        return nRet;*/
}

//////////////////////////////////////////////////////////////////////////
int DbFpGetFingerCountPerUser(USER_INFO* pUserInfo)
{
        int i;
        int nRet = 0;

        if (!pUserInfo)
                return 0;

        for (i=BACKUP_FINGER0; i<=BACKUP_FINGER9; i++)
        {
                if (DbUserInfoFlagEnrollStatusGet(pUserInfo, i))
                        nRet++;
        }
        return nRet;
}

//////////////////////////////////////////////////////////////////////////
int DbFpGetUnusedPosition(void)
{
  /*      int i;

        for (i=0; i<dbLicense.nMaxEnrollCount; i++)
        {
                if (gpIndexData[i] == 0)
                         break;
        }

        return i;*/
}

//////////////////////////////////////////////////////////////////////////
int DbFpGetUnusedFingernumber(UINT64 nID, int nStart)
{
        int i;
        USER_INFO *pUserInfo = (USER_INFO*)DbUserInfoGetPointer(nID);
        if (!pUserInfo)
                return 0;
        for (i=nStart; i<=BACKUP_FINGER9; i++)
        {
                if (!DbUserInfoFlagEnrollStatusGet(pUserInfo, i))
                        return i;
        }
        for (i=0; i<nStart; i++)
                if (!DbUserInfoFlagEnrollStatusGet(pUserInfo, i))
                        return i;

        return dbLicense.nBackupNumber;
}

//////////////////////////////////////////////////////////////////////////
int DbFpGetUsedFingernumber(UINT64 nID, int nStart)
{
        int i;
        USER_INFO *pUserInfo = (USER_INFO*)DbUserInfoGetPointer(nID);
        if (!pUserInfo)
                return -1;

        for (i=nStart; i<=BACKUP_FINGER9; i++)
        {
                if (DbUserInfoFlagEnrollStatusGet(pUserInfo, i))
                        return i;
        }
        for (i=0; i<nStart; i++)
        {
                if (DbUserInfoFlagEnrollStatusGet(pUserInfo, i))
                        return i;
        }

        return -1;
}


BOOL DbUserTimeLoad(void)
{
   /*     int fd;
        BOOL bRet = TRUE;
        int size;

        fd = open(FLASH_USERTIME_FILENAME, O_RDWR | O_CREAT);
        if (fd == INVALID_HANDLE_VALUE)
                return FALSE;

        gpUserTimeData = (USER_TIME*)malloc(sizeof(USER_TIME) * dbLicense.nMaxEnrollCount);
        if (gpUserTimeData == NULL)
        {
                bRet = FALSE;
                goto _lExit;
        }
        size=sizeof(USER_TIME) * dbLicense.nMaxEnrollCount;
        memset(gpUserTimeData, 0, size);
        bRet = (read(fd, gpUserTimeData, size) == size);
        if (!bRet)
        {
                memset(gpUserTimeData, 0, size);
                bRet = (pwrite(fd, gpUserTimeData, size, 0) == size);
        }

        //bRet = _Db_FlashRead(fd, gpUserTimeData, 0, dbLicense.nMaxEnrollCount, sizeof(USER_TIME), 0, NULL);

_lExit:
        FD_CLOSE(fd);
        return bRet;*/
}


//////////////////////////////////////////////////////////////////////////
BOOL DbUserTimeSave(void)
{
        int fd;
        BOOL bRet = TRUE;

        fd = open(FLASH_USERTIME_FILENAME, O_RDWR | O_CREAT,777);
        if (fd == INVALID_HANDLE_VALUE)
                return FALSE;

        if (gpUserTimeData == NULL)
        {
                bRet = FALSE;
                goto _lExit;
        }

        bRet = _Db_FlashWrite(fd, gpUserTimeData, 0, dbLicense.nMaxEnrollCount, sizeof(USER_TIME), NULL);

_lExit:
        FD_CLOSE(fd);
        return bRet;
}

//////////////////////////////////////////////////////////////////////////
BOOL DbUserTimeSaveOne(int nPos)
{
        int fd;
        BOOL bRet = TRUE;

        fd = open(FLASH_USERTIME_FILENAME, O_RDWR | O_CREAT,777);
        if (fd == INVALID_HANDLE_VALUE)
                return FALSE;

        bRet = _Db_SaveOne(fd, nPos, sizeof(USER_TIME), (char*)gpUserTimeData);

        FD_CLOSE(fd);
        return bRet;
}



//////////////////////////////////////////////////////////////////////////
BOOL DbUserTimeDelete(UINT64 nID)
{
        int i;

        for (i=0; i<dbLicense.nMaxEnrollCount; i++)
        {
                if(nID == gpUserTimeData[i].nID)
                {
           gpUserTimeData[i].nID=0;
                   gpUserTimeData[i].dwSeconds=0;
                   DbUserTimeSaveOne(i);
           return 1;
                }
        }
        return 0;
}

//////////////////////////////////////////////////////////////////////////
BOOL DbUserTimeDeleteAll(void)
{
        memset(gpUserTimeData, 0, sizeof(USER_TIME) * dbLicense.nMaxEnrollCount);
        DbUserTimeSave();
        return  1;//	DELETE_FILE(FLASH_USERTIME_FILENAME);
}

//////////////////////////////////////////////////////////////////////////
DWORD DbUserTimeDataRead(UINT64 nID)
{
        int i;

        for (i=0; i<dbLicense.nMaxEnrollCount; i++)
        {
                if(nID == gpUserTimeData[i].nID)
                {
                   return (gpUserTimeData[i].dwSeconds);
                }
        }
        return 0;
}

//////////////////////////////////////////////////////////////////////////
BOOL DbUserTimeDataWrite(UINT64 nID)
{
 /*       int i;
        DWORD todaySeconds=uiRtcGetSeconds();

        for (i=0; i<dbLicense.nMaxEnrollCount; i++)
        {
                if(gpUserTimeData[i].nID==nID)
                {
           gpUserTimeData[i].nID=nID;
                   gpUserTimeData[i].dwSeconds=todaySeconds;
                   DbUserTimeSaveOne(i);
                   return 1;
                }
        }
        return 0;*/
}

//////////////////////////////////////////////////////////////////////////
BOOL DbUserTimeDataNew(UINT64 nID)
{
  /*      int i;
        DWORD todaySeconds=uiRtcGetSeconds();

        for (i=0; i<dbLicense.nMaxEnrollCount; i++)
        {
                if(gpUserTimeData[i].nID==0 && gpUserTimeData[i].dwSeconds==0)
                {
           gpUserTimeData[i].nID=nID;
                   gpUserTimeData[i].dwSeconds=todaySeconds;
                   DbUserTimeSaveOne(i);
                   return 1;
                }
        }
        return 0;*/
}

//////////////////////////////////////////////////////////////////////////
BOOL DbUserTimeOut(DWORD Seconds)
{
  /*      int i;
        DWORD todaySeconds;

        if(Seconds==0)
                return 0;
        todaySeconds=uiRtcGetSeconds();
        for (i=0; i<dbLicense.nMaxEnrollCount; i++)
        {
                if(gpUserTimeData[i].nID && gpUserTimeData[i].dwSeconds)
                {
                        if(gpUserTimeData[i].dwSeconds+Seconds < todaySeconds)
                        {
                                DbUserInfoDelete(gpUserTimeData[i].nID,0xFFFF);
                                // uiLogSlogAdd(g_uiProcStatus.nIDCurrentMgr, (BYTE)SLOG_DELETE_USER, nID, bResult);
                                gpUserTimeData[i].nID=0;
                                gpUserTimeData[i].dwSeconds=0;
                                DbUserTimeSaveOne(i);
                        }
                }
        }
        return 1;*/
}

int  UserTimePos=0;
//////////////////////////////////////////////////////////////////////////
BOOL DbUserTimeOutOne(DWORD Seconds)
{
 /*       int i;
        DWORD todaySeconds;

    if(Seconds==0)
                return 0;
        if(UserTimePos>=dbLicense.nMaxEnrollCount)
        {
            UserTimePos=0;
        }
        else
                UserTimePos++;

        i=UserTimePos;
        if(gpUserTimeData[i].nID && gpUserTimeData[i].dwSeconds)
        {
           todaySeconds=uiRtcGetSeconds();
           if(gpUserTimeData[i].dwSeconds+Seconds<todaySeconds)
                {
                   DbUserInfoDelete(gpUserTimeData[i].nID,0xFFFF);
                  // uiLogSlogAdd(g_uiProcStatus.nIDCurrentMgr, (BYTE)SLOG_DELETE_USER, nID, bResult);
                   gpUserTimeData[i].nID=0;
                   gpUserTimeData[i].dwSeconds=0;
                   DbUserTimeSaveOne(i);
                }
        }
        return 1;*/
}


BOOL DbFpUploadDataLoad(void)
{
 /*       int fd;
        BOOL bRet = TRUE;
        int size;

        fd = open(FLASH_FPUPLOAD_FILENAME, O_RDWR | O_CREAT);
        if (fd == INVALID_HANDLE_VALUE)
                return FALSE;

        gpFpUploadData = (st_FpUploadData*)malloc(sizeof(st_FpUploadData) * dbLicense.nMaxEnrollCount);
        if (gpFpUploadData == NULL)
        {
                bRet = FALSE;
                goto _lExit;
        }
        size=sizeof(st_FpUploadData) * dbLicense.nMaxEnrollCount;
        memset(gpFpUploadData, 0, size);
        bRet = (read(fd, gpFpUploadData, size) == size);
        if (!bRet)
        {
                memset(gpFpUploadData, 0, size);
                bRet = (pwrite(fd, gpFpUploadData, size, 0) == size);
        }

        //bRet = _Db_FlashRead(fd, gpUserTimeData, 0, dbLicense.nMaxEnrollCount, sizeof(USER_TIME), 0, NULL);

_lExit:
        FD_CLOSE(fd);
        return bRet;*/
}
//////////////////////////////////////////////////////////////////////////
BOOL DbFpUploadDataSaveOne(int Pos)
{
 /*       int fd;
        BOOL bRet = TRUE;

        fd = open(FLASH_FPUPLOAD_FILENAME, O_RDWR | O_CREAT);
        if (fd == INVALID_HANDLE_VALUE)
                return FALSE;
        bRet = _Db_SaveOne(fd, Pos, sizeof(st_FpUploadData), (char*)gpFpUploadData);

        FD_CLOSE(fd);
        return bRet;*/
}

//////////////////////////////////////////////////////////////////////////
BOOL DbFpUploadDataSave(UINT64 nID, int nFP,BOOL bClear)
{
 /*       int i;
        BOOL bRet = TRUE;


        for (i=0; i<dbLicense.nMaxEnrollCount; i++)
        {
                if(gpFpUploadData[i].nID==nID)
                {
                   if(bClear)
                        {
                      gpFpUploadData[i].nFP=(~(1 << nFP))&gpFpUploadData[i].nFP;
                          if(gpFpUploadData[i].nFP==0)
                          {
                                 gpFpUploadData[i].nID=0;
                                 gpFpUploadData[i].Avail=FALSE;
                          }
                          else
                            gpFpUploadData[i].Avail=TRUE;
                        }
                   else
                        {
                          gpFpUploadData[i].nID=nID;
                      gpFpUploadData[i].nFP=(1 << nFP)|gpFpUploadData[i].nFP;
                      gpFpUploadData[i].Avail=TRUE;
                        }
                   DbFpUploadDataSaveOne(i);
                   break;
                }
        }
        if(i==dbLicense.nMaxEnrollCount && bClear==0)
        {
                for (i=0; i<dbLicense.nMaxEnrollCount; i++)
                {
                        if(gpFpUploadData[i].nID==0&&gpFpUploadData[i].nFP==0 && gpFpUploadData[i].Avail==0)
                        {
                                gpFpUploadData[i].nID=nID;
                                gpFpUploadData[i].nFP=(1 << nFP)|gpFpUploadData[i].nFP;
                                gpFpUploadData[i].Avail=TRUE;
                                DbFpUploadDataSaveOne(i);
                            break;
                        }
                }
        }
        return bRet;*/
}

//////////////////////////////////////////////////////////////////////////
BOOL DbFpUploadDataGet(UINT64 *nId,int *nFp)
{
 /*       int i;

        for (i=0; i<dbLicense.nMaxEnrollCount; i++)
        {
                if(gpFpUploadData[i].nID && gpFpUploadData[i].nFP && gpFpUploadData[i].Avail)
                {
                   *nId=gpFpUploadData[i].nID;
               *nFp=gpFpUploadData[i].nFP;
                  return TRUE;
                }
        }
        return FALSE;*/
}
//////////////////////////////////////////////////////////////////////////
BOOL DbFpUploadDataClear(UINT64 nId)
{
 /*       int i;

        for (i=0; i<dbLicense.nMaxEnrollCount; i++)
        {
                if(gpFpUploadData[i].nID==nId)
                {
                   gpFpUploadData[i].nID=0;
               gpFpUploadData[i].nFP=0;
                   gpFpUploadData[i].Avail=FALSE;
                   return TRUE;
                }
        }
        return FALSE;*/
}





BOOL DbUserIdHeadListLoad(void)
{
   /*     int fd;
        BOOL bRet = TRUE;
        int size;

        fd = open(FLASH_IDHEADLIST_FILENAME, O_RDWR | O_CREAT);
        if (fd == INVALID_HANDLE_VALUE)
                return FALSE;

        gpUserIdHeadData = (st_HeadString*)malloc(sizeof(st_HeadString) * MaxIdHeadListCount);
        if (gpUserIdHeadData == NULL)
        {
                bRet = FALSE;
                goto _lExit;
        }
        size=sizeof(st_HeadString) * MaxIdHeadListCount;
        memset(gpUserIdHeadData, 0, size);
        bRet = (read(fd, gpUserIdHeadData, size) == size);
        if (!bRet)
        {
                memset(gpUserIdHeadData, 0, size);
                bRet = (pwrite(fd, gpUserIdHeadData, size, 0) == size);
        }

           if(gpUserIdHeadData!=NULL)
                         return true;
        //bRet = _Db_FlashRead(fd, gpUserTimeData, 0, dbLicense.nMaxEnrollCount, sizeof(USER_TIME), 0, NULL);

_lExit:
        FD_CLOSE(fd);
        return bRet;*/
}


//////////////////////////////////////////////////////////////////////////
BOOL DbUserIdHeadListSave(void)
{
  /*      int fd;
        BOOL bRet = TRUE;

        fd = open(FLASH_IDHEADLIST_FILENAME, O_RDWR | O_CREAT);
        if (fd == INVALID_HANDLE_VALUE)
                return FALSE;

        if (gpUserIdHeadData == NULL)
        {
                bRet = FALSE;
                goto _lExit;
        }

        bRet = _Db_FlashWrite(fd, gpUserIdHeadData, 0, MaxIdHeadListCount, sizeof(st_HeadString), NULL);

_lExit:
        FD_CLOSE(fd);
        return bRet;*/
}

//////////////////////////////////////////////////////////////////////////
BOOL DbUserIdHeadListDeleteAll(void)
{
        //memset(gpUserIdHeadData, 0, sizeof(st_HeadString) * MaxIdHeadListCount);
        //DbUserIdHeadListSave();
        //return 	1;//DELETE_FILE(FLASH_IDHEADLIST_FILENAME);
}

int GetDbUserIdHeadListCountAll()
{
  /*      int i,count;

    count=0;
        for(i=0;i<MaxIdHeadListCount;i++)
        {
                if ((gpUserIdHeadData[i].Letter[0] >= 'A' && gpUserIdHeadData[i].Letter[0] <= 'Z')||
                        (gpUserIdHeadData[i].Letter[0] >= 'a' && gpUserIdHeadData[i].Letter[0] <= 'z'))
        {
          count++;
        }
        }
    return count;*/
}


/************************************************************************/
/*                                                                      */
/************************************************************************/
//////////////////////////////////////////////////////////////////////////
BOOL DbUserInfoLoad(void)
{
        int fd;
        BOOL bRet = TRUE;

        fd = open(FLASH_USERINFO_FILENAME,O_RDWR | O_CREAT,777);
        if (fd == INVALID_HANDLE_VALUE)
                return FALSE;

        gpUserInfoEnrollData = (USER_INFO*)malloc(sizeof(USER_INFO) * dbLicense.nMaxEnrollCount);
        //gpUserInfoEnrollData = (USER_INFO*)malloc(sizeof(USER_INFO) * 100);
        if (gpUserInfoEnrollData == NULL)
        {
                bRet = FALSE;
                goto _lExit;
        }

        memset(gpUserInfoEnrollData, 0, sizeof(USER_INFO) * dbLicense.nMaxEnrollCount);
        //memset(gpUserInfoEnrollData, 0, sizeof(USER_INFO) * 100);
        bRet = _Db_FlashRead(fd, gpUserInfoEnrollData, 0, dbLicense.nMaxEnrollCount, sizeof(USER_INFO), 0, NULL);

_lExit:
        FD_CLOSE(fd);
        return bRet;
}



//////////////////////////////////////////////////////////////////////////
BOOL DbUserInfoSave(void)
{
        int fd;
        BOOL bRet = TRUE;

        fd = open(FLASH_USERINFO_FILENAME, O_RDWR | O_CREAT,777);
        if (fd == INVALID_HANDLE_VALUE)
                return FALSE;

        if (gpUserInfoEnrollData == NULL)
        {
                bRet = FALSE;
                goto _lExit;
        }

        bRet = _Db_FlashWrite(fd, gpUserInfoEnrollData, 0, dbLicense.nMaxEnrollCount, sizeof(USER_INFO), NULL);

_lExit:
        FD_CLOSE(fd);
        return bRet;
}

//////////////////////////////////////////////////////////////////////////
BOOL DbUserInfoSaveOne(int nPos)
{
        int fd;
        BOOL bRet = TRUE;

        fd = open(FLASH_USERINFO_FILENAME, O_RDWR | O_CREAT,777);
        if (fd == INVALID_HANDLE_VALUE)
                return FALSE;

        bRet = _Db_SaveOne(fd, nPos, sizeof(USER_INFO), (char*)gpUserInfoEnrollData);

        FD_CLOSE(fd);
        return bRet;
}

//////////////////////////////////////////////////////////////////////////
BOOL DbUserInfoDelete(UINT64 nID, int nBackup)
{
        int i;
        int nPos;
        BOOL bRet = TRUE;
        BOOL bEnrollInfoExist = FALSE;
        USER_INFO* pUserInfo;

        nPos = DbUserInfoGetPosition(nID);
        if (nPos == dbLicense.nMaxEnrollCount)
        {
                bRet = FALSE;
                goto _lExit;
        }

        pUserInfo = &gpUserInfoEnrollData[nPos];

        for (i=BACKUP_START; i<=BACKUP_END; i++)
        {
                if (nBackup & (0x01 << i))
                {
                        if ((i >= BACKUP_FINGER0) && (i <= BACKUP_FINGER9))
                                DbFpDelete(pUserInfo, i);
                        else if (i == BACKUP_PASSWORD)
                                pUserInfo->PWD = 0;
                        else if (i == BACKUP_CARD)
                                pUserInfo->CARD = 0;
                        DbUserInfoFlagEnrollStatusSet(pUserInfo, i, 0);
                        DbUserInfoFlagDuressStatusSet(pUserInfo, i, 0);
                        DbFpUploadDataSave(nID, i,1);
                }
        }

        for (i=BACKUP_START; i<=BACKUP_END; i++)
        {
                if (DbUserInfoFlagEnrollStatusGet(pUserInfo, i))
                {
                        bEnrollInfoExist = TRUE;
                        break;
                }
        }

//	if (!pUserInfo->FP && !pUserInfo->PWD && !pUserInfo->CARD)
        if (!bEnrollInfoExist)
        {
                unlink(DbUserInfoGetVoiceFilename(pUserInfo->ID));
                unlink(DbUserInfoGetPhotoFilename(pUserInfo->ID));

                int nPos1 = DbUserInfoGetNearestPosition(nID, NULL);
                int nLeft = dbLicense.nMaxEnrollCount - nPos1 - 1;

                if (nPos1 >= 0)
                {
                        memcpy(&gpUIIndexData[nPos1], &gpUIIndexData[nPos1 + 1], sizeof(WORD) * nLeft);
                        gpUIIndexData[dbLicense.nMaxEnrollCount - 1] = 0xffff;
                        DbUIIndexSave();
                }
                DbAntipassSet(pUserInfo->ID, TRUE, -1UL, TRUE);
                pUserInfo->ID = 0;
        }

        DbUserInfoSaveOne(nPos);

_lExit:
        return bRet;
}

//////////////////////////////////////////////////////////////////////////
BOOL DbUserInfoDeleteAll(void)
{
        memset(gpUserInfoEnrollData, 0, sizeof(USER_INFO) * dbLicense.nMaxEnrollCount);
        //return 	DELETE_FILE(FLASH_USERINFO_FILENAME);
}

//////////////////////////////////////////////////////////////////////////
int DbUserInfoGetPosition(UINT64 nID)
{
        int nPos;

        nPos = DbUserInfoGetNearestPosition(nID, NULL);
        if (nPos < 0)
                return dbLicense.nMaxEnrollCount;
        nPos = gpUIIndexData[nPos];
        if (nPos == 0xFFFF)
                return dbLicense.nMaxEnrollCount;
        return nPos;
}

//////////////////////////////////////////////////////////////////////////
void* DbUserInfoGetPointer(UINT64 nID)
{
        int nPos = DbUserInfoGetPosition(nID);
        if (nPos == dbLicense.nMaxEnrollCount)
                return NULL;
        return &gpUserInfoEnrollData[nPos];
}

//////////////////////////////////////////////////////////////////////////
void* DbUserInfoGetPointer(UINT64 nID, int nBackup)
{
        int nPos = DbUserInfoGetPosition(nID);
        if (nPos == dbLicense.nMaxEnrollCount)
                return NULL;
        if ((nBackup >= BACKUP_FINGER0) && (nBackup <= BACKUP_FINGER9))
                return DbFpGetPointer(nPos, nBackup);
        else if (nBackup == BACKUP_PASSWORD)
        {
                if (gpUserInfoEnrollData[nPos].PWD)
                        return &gpUserInfoEnrollData[nPos].PWD;
        }
        else if (nBackup == BACKUP_CARD)
        {
                if (gpUserInfoEnrollData[nPos].CARD)
                        return &gpUserInfoEnrollData[nPos].CARD;
        }

        return NULL;
}

//////////////////////////////////////////////////////////////////////////
BOOL DbUserInfoEnroll(USER_INFO *pUserInfoNew, int nBackup, void* pData, BOOL bFlashWrite /*= TRUE*/, BOOL bNoMatch /*= TRUE*/)
{
        BOOL bRet = TRUE;
        int nPos;
        USER_INFO BACKUP;
        USER_INFO *pUserInfo = NULL;
        BOOL bOverwrite = TRUE;
#if FUCK
        qDebug()<< "pUserInfoNew->ID=="<<pUserInfoNew->ID;
        qDebug()<< "pUserInfoNew->PWD=="<<pUserInfoNew->PWD;
        qDebug()<< "nBackup=="<<nBackup;
        qDebug()<< "bFlashWrite=="<<bFlashWrite;
        qDebug()<< "bNoMatch=="<<bNoMatch;
#endif
        nPos = DbUserInfoGetPosition(pUserInfoNew->ID);
        qDebug()<< "nPos=="<<nPos;
        if (nPos == dbLicense.nMaxEnrollCount)
        {
                qDebug()<<"1";
                if (DbUserInfoGetCount(nBackup) + 1 > dbLicense.nMaxEnrollCount)
                {
                        bRet = FALSE;
                        goto _lExit;
                }
                nPos = DbUserInfoGetUnusedPosition();
                bOverwrite = FALSE;
        }
        if (nPos == dbLicense.nMaxEnrollCount)
        {
                bRet = FALSE;
                goto _lExit;
        }
        pUserInfo = &gpUserInfoEnrollData[nPos];
        memcpy(&BACKUP, pUserInfo, sizeof(USER_INFO));
        qDebug()<< "bOverwrite=="<<bOverwrite;
        qDebug()<< "pUserInfo->ID=="<<pUserInfo->ID;
        if (!bOverwrite || nBackup == BACKUP_ALL)
                memcpy(pUserInfo, pUserInfoNew, sizeof(USER_INFO));
        if (bOverwrite)
        {
                pUserInfo->FP = BACKUP.FP;
        }
        else
        {
                pUserInfo->FP = 0;
                pUserInfo->TIMEGROUP = 1;
                DbUserInfoFlagGTZStatusSet(pUserInfo, TRUE);
                pUserInfo->UserTZ[0] = dbSetupTotal.setTimezone.tzGroup[pUserInfo->TIMEGROUP - 1].bGroupA;
                pUserInfo->UserTZ[1] = dbSetupTotal.setTimezone.tzGroup[pUserInfo->TIMEGROUP - 1].bGroupB;
                pUserInfo->UserTZ[2] = dbSetupTotal.setTimezone.tzGroup[pUserInfo->TIMEGROUP - 1].bGroupC;
                DbUserInfoFlagGVMStatusSet(pUserInfo, TRUE);
                pUserInfo->VERIFYMODE = VM_NONE;
                pUserInfo->RES[0] = pUserInfo->RES[1] = 0;
                DbAntipassSet(pUserInfo->ID, TRUE, -1UL, TRUE);
        }


        if (nBackup >= BACKUP_FINGER0 && nBackup <= BACKUP_FINGER9)
        {
        xprintf("2\r\n");
                if (!DbFpSetPointer(nPos, nBackup, pData, bNoMatch, bFlashWrite))// 死在这里
                {
                        bRet = FALSE;

                        goto _lFail;
                }

        }
        else if (nBackup == BACKUP_PASSWORD && *(DWORD*)pData)
        {
xprintf("3\r\n");
                pUserInfo->PWD = *(DWORD*)pData;
        }
        else if (nBackup == BACKUP_CARD && *(DWORD*)pData)
        {
xprintf("4\r\n");
                pUserInfo->CARD = 0;							//090731 modify by RSI
                if (!bNoMatch && DbUserInfoCardVerify(*(DWORD*)pData) < dbLicense.nMaxEnrollCount)
                {
                        bRet = FALSE;
                        goto _lFail;
                }
                pUserInfo->CARD = *(DWORD*)pData;
        }
        else if (nBackup == BACKUP_ALL) //when change only user info
        {
xprintf("5\r\n");
                if (pUserInfo->PWD)
                        nBackup = BACKUP_PASSWORD;
        }
        else
        {
xprintf("6\r\n");
                bRet = FALSE;
                goto _lFail;
        }
        if (!bOverwrite && nBackup == BACKUP_ALL)
        {
                bRet = FALSE;
                goto _lFail;
        }

        if (nBackup >= BACKUP_START && nBackup <= BACKUP_END)
        {
xprintf("7\r\n");
                DbUserInfoFlagEnrollStatusSet(pUserInfo, nBackup, 1);
        }
        DbUserInfoEnable(nPos, TRUE);
xprintf("8\r\n");
        if (bFlashWrite)
                DbUserInfoSaveOne(nPos);
xprintf("9\r\n");
        if (TRUE)
        {
        xprintf("10\r\n");
                int NearestPos;
                int nPos1 = DbUserInfoGetNearestPosition(pUserInfo->ID, &NearestPos);
                qDebug()<< "nPos1=="<<nPos1;
                if (nPos1 < 0)
                {
                        xprintf("11\r\n");
                        for (int k=dbLicense.nMaxEnrollCount-1; k>NearestPos; k--)
                                gpUIIndexData[k] = gpUIIndexData[k-1];
                        gpUIIndexData[NearestPos] = nPos;
                }

                if (bFlashWrite)
                        DbUIIndexSave();

        }

        memcpy(pUserInfoNew, pUserInfo, sizeof(USER_INFO));
        xprintf("123456789\r\n");

_lExit:
        xprintf("987654321\r\n");
        return bRet;

_lFail:
        memcpy(pUserInfo, &BACKUP, sizeof(USER_INFO));
        xprintf("54321\r\n");
        return bRet;
}

//////////////////////////////////////////////////////////////////////////
BOOL DbUserInfoHasVoice(USER_INFO *pUserInfo)
{
        //if (!DbUserInfoFlagVoiceStatusGet(pUserInfo))
                //return FALSE;

        ///char *szFilename = MAKE_FULLPATH(SDCARD_MOUNTPOINT PATH_USER_VOICE, UserId_BCDtoSTR(pUserInfo->ID), NULL);
        //sprintf(&szFilename[strlen(szFilename)], "voice.wav");
        //return FILE_EXIST(szFilename);
}

//////////////////////////////////////////////////////////////////////////
BOOL DbUserInfoHasVoice(UINT64 nID)
{
        USER_INFO *pUserInfo = (USER_INFO*)DbUserInfoGetPointer(nID);
        //return (SDCARD_MOUNT() && DbUserInfoHasVoice(pUserInfo));
}

//////////////////////////////////////////////////////////////////////////
char* DbUserInfoGetVoiceFilename(UINT64 nID)
{
        //char *szFilename = MAKE_FULLPATH(SDCARD_MOUNTPOINT PATH_USER_VOICE, UserId_BCDtoSTR(nID), NULL);
        //sprintf(&szFilename[strlen(szFilename)], "voice.wav");
        //return szFilename;
}

//////////////////////////////////////////////////////////////////////////
BOOL DbUserInfoSetVoice(UINT64 nID, BOOL bStatus)
{
        int nPos = DbUserInfoGetPosition(nID);
        if (nPos < dbLicense.nMaxEnrollCount && DbUserInfoFlagVoiceStatusSet(&gpUserInfoEnrollData[nPos], bStatus))
                return DbUserInfoSaveOne(nPos);
        else
                return FALSE;
}

//////////////////////////////////////////////////////////////////////////
BOOL DbUserInfoHasPhoto(USER_INFO *pUserInfo)
{
        //if (!DbUserInfoFlagPhotoStatusGet(pUserInfo))
                return FALSE;
        ///return FILE_EXIST(MAKE_FULLPATH(SDCARD_MOUNTPOINT PATH_USER_PHOTO, UserId_BCDtoSTR(pUserInfo->ID), "jpg"));
}

//////////////////////////////////////////////////////////////////////////
BOOL DbUserInfoHasPhoto(UINT64 nID)
{
        USER_INFO *pUserInfo = (USER_INFO*)DbUserInfoGetPointer(nID);
        //return (SDCARD_MOUNT() && DbUserInfoHasPhoto(pUserInfo));
}

char* DbUserInfoGetPhotoFilename(UINT64 nID)
{
        //return MAKE_FULLPATH(SDCARD_MOUNTPOINT PATH_USER_PHOTO, UserId_BCDtoSTR(nID), "jpg");
}

//////////////////////////////////////////////////////////////////////////
BOOL DbUserInfoSetPhoto(UINT64 nID, BOOL bStatus)
{
        int nPos = DbUserInfoGetPosition(nID);
        if (nPos < dbLicense.nMaxEnrollCount && DbUserInfoFlagPhotoStatusSet(&gpUserInfoEnrollData[nPos], bStatus))
                return DbUserInfoSaveOne(nPos);
        else
                return FALSE;
}

//////////////////////////////////////////////////////////////////////////
BOOL DbUserInfoGetTimezone(USER_INFO *pUserInfo, int *pnTZ1, int *pnTZ2, int *pnTZ3)
{
        int nGroup = pUserInfo->TIMEGROUP - 1;

        *pnTZ1 = *pnTZ2 = *pnTZ3 = 0;

        if (!pUserInfo)
                return FALSE;

        if (DbUserInfoFlagGTZStatusGet(pUserInfo))
        {
                *pnTZ1 = dbSetupTotal.setTimezone.tzGroup[nGroup].bGroupA;
                *pnTZ2 = dbSetupTotal.setTimezone.tzGroup[nGroup].bGroupB;
                *pnTZ3 = dbSetupTotal.setTimezone.tzGroup[nGroup].bGroupC;
        }
        else
        {
                *pnTZ1 = pUserInfo->UserTZ[0];
                *pnTZ2 = pUserInfo->UserTZ[1];
                *pnTZ3 = pUserInfo->UserTZ[2];
        }
        return TRUE;
}

//////////////////////////////////////////////////////////////////////////
int DbUserInfoGetCount(void)
{
        int i;
        int nCount = 0;

        for (i=0; i<dbLicense.nMaxEnrollCount; i++)
        {
                if (gpUserInfoEnrollData[i].ID)
                        nCount++;
        }
        return nCount;
}

//////////////////////////////////////////////////////////////////////////
int DbUserInfoGetCount(int nBackup)
{
        int i;
        int nCount = 0;
        switch (nBackup)
        {
        case BACKUP_FINGER:
                nCount = DbFpGetCount();
                break;
        case BACKUP_PASSWORD:
                for (i=0; i<dbLicense.nMaxEnrollCount; i++)
                {
//			if (gpUserInfoEnrollData[i].PWD)
                        if (DbUserInfoFlagEnrollStatusGet(&gpUserInfoEnrollData[i], BACKUP_PASSWORD))
                                nCount++;
                }
                break;
        case BACKUP_CARD:
                for (i=0; i<dbLicense.nMaxEnrollCount; i++)
                {
//			if (gpUserInfoEnrollData[i].CARD)
                        if (DbUserInfoFlagEnrollStatusGet(&gpUserInfoEnrollData[i], BACKUP_CARD))
                                nCount++;
                }
                break;
        }

        return nCount;
}

//////////////////////////////////////////////////////////////////////////
int DbUserInfoGetFreeCount(int nBackup)
{
        return dbLicense.nMaxEnrollCount - DbUserInfoGetCount(nBackup);
}

//////////////////////////////////////////////////////////////////////////
BOOL DbUserInfoIsUsedID(UINT64 nID)
{
        int i;

        if (!nID)
                return TRUE;

        for (i=0; i<dbLicense.nMaxEnrollCount; i++)
        {
                if (gpUserInfoEnrollData[i].ID == nID)
                        return TRUE;
        }

        return FALSE;
}

//////////////////////////////////////////////////////////////////////////
int DbUserInfoGetUnusedPosition(void)
{
        int i;

        for (i=0; i<dbLicense.nMaxEnrollCount; i++)
        {
                if (gpUserInfoEnrollData[i].ID == 0)
                        break;
        }

        return i;
}

//////////////////////////////////////////////////////////////////////////
int DbUserInfoGetManagerCount(BYTE byMgr)
{
        int i;
        int nCount = 0;

        for (i=0; i<dbLicense.nMaxEnrollCount; i++)
        {
                if (gpUserInfoEnrollData[i].ID && DbUserInfoFlagManagerGet(&gpUserInfoEnrollData[i]) == byMgr)
                        nCount++;
        }

        return nCount;
}

//////////////////////////////////////////////////////////////////////////
BOOL DbUserInfoManagerFull(BYTE byMgr)
{
        return (DbUserInfoGetManagerCount(byMgr) == dbSetupTotal.setSystem.nManagersNumber);
}

//////////////////////////////////////////////////////////////////////////
BYTE DbUserInfoGetPrivilege(UINT64 nID)
{
        int nPos;
        nPos = DbUserInfoGetPosition(nID);
        return DbUserInfoFlagManagerGet(&gpUserInfoEnrollData[nPos]);
}

//////////////////////////////////////////////////////////////////////////
BOOL DbUserInfoSetPrivilege(UINT64 nID, BYTE byPrivilege)
{
        int nPos;
        nPos = DbUserInfoGetPosition(nID);

    if( nPos >= dbLicense.nMaxEnrollCount )
                return FALSE;

        return (DbUserInfoFlagManagerSet(&gpUserInfoEnrollData[nPos], byPrivilege) && DbUserInfoSaveOne(nPos));
}

//////////////////////////////////////////////////////////////////////////
BOOL DbUserInfoRemovePrivilege()
{
        int i;

        for (i=0; i<dbLicense.nMaxEnrollCount; i++)
        {
                if (gpUserInfoEnrollData[i].ID && DbUserInfoFlagManagerGet(&gpUserInfoEnrollData[i]) != PRIV_USER)
                {
                        DbUserInfoFlagManagerSet(&gpUserInfoEnrollData[i], PRIV_USER);
                        DbUserInfoSaveOne(i);
                }
        }

        return TRUE;
}


//////////////////////////////////////////////////////////////////////////
BOOL DbUserInfoGetDuress(UINT64 nID, int nBackup)
{
        int nPos = DbUserInfoGetPosition(nID);
        if (nPos == dbLicense.nMaxEnrollCount)
                return FALSE;

        USER_INFO *pUserInfo = (USER_INFO*)DbUserInfoGetPointer(nID);
        if (!pUserInfo || nBackup < BACKUP_START || nBackup > BACKUP_END)
                return FALSE;
        return DbUserInfoFlagDuressStatusGet(pUserInfo, nBackup);
}

//////////////////////////////////////////////////////////////////////////
int DbUserInfoGetDuressCount(UINT64 nID)
{
        int i;
        int nRet = 0;
        USER_INFO *pUserInfo = (USER_INFO*)DbUserInfoGetPointer(nID);

        for (i=BACKUP_FINGER; i<BACKUP_END; i++)
        {
                if (DbUserInfoFlagDuressStatusGet(pUserInfo, i))
                        nRet++;
        }
        return nRet;
}

//////////////////////////////////////////////////////////////////////////
BOOL DbUserInfoSetDuress(UINT64 nID, int nBackup, int nStatus)
{
        int nPos = DbUserInfoGetPosition(nID);
        if (nPos == dbLicense.nMaxEnrollCount)
                return FALSE;

        USER_INFO *pUserInfo = (USER_INFO*)DbUserInfoGetPointer(nID);
        if (!pUserInfo)
                return FALSE;
        if ((nBackup < BACKUP_START || nBackup > BACKUP_END) && (nBackup != BACKUP_ALL))
                return FALSE;

        if (nBackup == BACKUP_ALL)
        {
                for (int i=BACKUP_START; i<=BACKUP_END; i++)
                        DbUserInfoFlagDuressStatusSet(pUserInfo, i, nStatus);
        }
        else
                DbUserInfoFlagDuressStatusSet(pUserInfo, nBackup, nStatus);
        return DbUserInfoSaveOne(nPos);
}

//////////////////////////////////////////////////////////////////////////
BOOL DbUserInfoEnable(int nPos, BOOL bEnable)
{
        DbUserInfoFlagDisableStatusSet(&gpUserInfoEnrollData[nPos], FALSE);
        if (!bEnable)
                DbUserInfoFlagDisableStatusSet(&gpUserInfoEnrollData[nPos], TRUE);
        return TRUE;
}

//////////////////////////////////////////////////////////////////////////
BOOL DbUserInfoIsAble(int nPos)
{
        if (nPos >= dbLicense.nMaxEnrollCount)
                return FALSE;

        if (DbUserInfoFlagDisableStatusGet(&gpUserInfoEnrollData[nPos]))
                return FALSE;

        return TRUE;
}

//////////////////////////////////////////////////////////////////////////
BOOL DbUserInfoFlagEnrollStatusGet(USER_INFO *pUserInfo, int nBackup)
{
        if (!pUserInfo || nBackup < BACKUP_START || nBackup > BACKUP_END)
                return FALSE;
        return UI_EXIST_ENROLL(pUserInfo, nBackup);
}

BOOL DbUserInfoFlagEnrollStatusSet(USER_INFO *pUserInfo, int nBackup, BOOL bStatus)
{
        if (!pUserInfo || nBackup < BACKUP_START || nBackup > BACKUP_END)
                return FALSE;
        UI_SET_ENROLL(pUserInfo, nBackup, bStatus);
        return TRUE;
}

BOOL DbUserInfoFlagDuressStatusGet(USER_INFO *pUserInfo, int nBackup)
{
        if (!pUserInfo || nBackup < BACKUP_START || nBackup > BACKUP_END)
                return FALSE;
        return UI_EXIST_DURESS(pUserInfo, nBackup);
}

BOOL DbUserInfoFlagDuressStatusSet(USER_INFO *pUserInfo, int nBackup, BOOL bStatus)
{
        if (!pUserInfo || nBackup < BACKUP_START || nBackup > BACKUP_END)
                return FALSE;
        UI_SET_DURESS(pUserInfo, nBackup, bStatus);
        return TRUE;
}

BOOL DbUserInfoFlagGTZStatusGet(USER_INFO *pUserInfo)
{
        if (!pUserInfo)
                return FALSE;
        return UI_GROUPTZ_STATUS(pUserInfo);
}

BOOL DbUserInfoFlagGTZStatusSet(USER_INFO *pUserInfo, BOOL bStatus)
{
        if (!pUserInfo)
                return FALSE;
        UI_GROUPTZ_STATUS(pUserInfo) = bStatus;
        return TRUE;
}

BOOL DbUserInfoFlagGVMStatusGet(USER_INFO *pUserInfo)
{
        if (!pUserInfo)
                return FALSE;
        return UI_GROUPVM_STATUS(pUserInfo);
}

BOOL DbUserInfoFlagGVMStatusSet(USER_INFO *pUserInfo, BOOL bStatus)
{
        if (!pUserInfo)
                return FALSE;
        UI_GROUPVM_STATUS(pUserInfo) = bStatus;
        return TRUE;
}

BOOL DbUserInfoFlagPhotoStatusGet(USER_INFO *pUserInfo)
{
        if (!pUserInfo)
                return FALSE;
        return UI_PHOTO_STATUS(pUserInfo);
}

BOOL DbUserInfoFlagPhotoStatusSet(USER_INFO *pUserInfo, BOOL bStatus)
{
        if (!pUserInfo)
                return FALSE;
        UI_PHOTO_STATUS(pUserInfo) = bStatus;
        return TRUE;
}

BOOL DbUserInfoFlagVoiceStatusGet(USER_INFO *pUserInfo)
{
        if (!pUserInfo)
                return FALSE;
        return UI_VOICE_STATUS(pUserInfo);
}

BOOL DbUserInfoFlagVoiceStatusSet(USER_INFO *pUserInfo, BOOL bStatus)
{
        if (!pUserInfo)
                return FALSE;
        UI_VOICE_STATUS(pUserInfo) = bStatus;
        return TRUE;
}

int DbUserInfoFlagManagerGet(USER_INFO *pUserInfo)
{
        if (!pUserInfo)
                return 0xFF;
        return UI_MANAGER_STATUS(pUserInfo);
}

BOOL DbUserInfoFlagManagerSet(USER_INFO *pUserInfo, int nPriv)
{
        if (!pUserInfo || (nPriv != PRIV_USER && nPriv != PRIV_MGR && nPriv != PRIV_SMGR))
                return FALSE;

        if (nPriv != PRIV_USER)
        {
                int nPrivBackup = UI_MANAGER_STATUS(pUserInfo);
                UI_MANAGER_STATUS(pUserInfo) = PRIV_USER;
                if (Db_GetManagerCount((BYTE)nPriv) + 1 > dbSetupTotal.setSystem.nManagersNumber)
                {
                        UI_MANAGER_STATUS(pUserInfo) = nPrivBackup;
                        return FALSE;
                }
                UI_MANAGER_STATUS(pUserInfo) = nPrivBackup;
        }

        UI_MANAGER_STATUS(pUserInfo) = nPriv;
        return TRUE;
}

BOOL DbUserInfoFlagDisableStatusGet(USER_INFO *pUserInfo)
{
        if (!pUserInfo)
                return FALSE;
        return UI_ENABLE_STATUS(pUserInfo);
}

BOOL DbUserInfoFlagDisableStatusSet(USER_INFO *pUserInfo, BOOL bStatus)
{
        if (!pUserInfo)
                return FALSE;
        UI_ENABLE_STATUS(pUserInfo) = bStatus;
        return TRUE;
}


//////////////////////////////////////////////////////////////////////////
static BOOL DbTzVerify_A(int nTimeSectionID, int nWeekday, int nHour, int nMinute)
{
        int From, To, Val;

        if(nTimeSectionID < 0 || nTimeSectionID >= ACCESS_TIME_SET_COUNT)
                return FALSE;

        From =  dbSetupTotal.setTimezone.tzAccess[nTimeSectionID].RANGE[nWeekday].bStartHour*60 +
                        dbSetupTotal.setTimezone.tzAccess[nTimeSectionID].RANGE[nWeekday].bStartMinute;
        To   =	dbSetupTotal.setTimezone.tzAccess[nTimeSectionID].RANGE[nWeekday].bEndHour*60 +
                        dbSetupTotal.setTimezone.tzAccess[nTimeSectionID].RANGE[nWeekday].bEndMinute;
        Val  =	nHour*60 + nMinute;

        if(Val<From || To<Val)
                return FALSE;

        return TRUE;
}

//warning
/*
static BOOL DbTzVerify_High(int nTimeSectionID, int nWeekday, int nHour, int nMinute)
{
        int i;
        int nTG, nTIME;
        int From, To, Val;
        DB_TIMESECTION_A *tm;

        if(nTimeSectionID < 0 || nTimeSectionID >= ACCESS_TIME_SET_COUNT_HIGH)
                return FALSE;

        Val = nHour*60 + nMinute;
        nTG = (int)dbSetupTotal.setTimezone.tzHighAccess[nTimeSectionID][nWeekday];
        if (nTG < 0 || nTG >= TIMEGROUP_COUNT)
                return FALSE;

        for (i=0; i<TIMECOUNT_PER_TG; i++)
        {
                nTIME = (int)dbSetupTotal.setTimezone.tzHighTG[nTG][i];
                if (nTIME < 0 || nTIME >= TIMEZONE_COUNT)
                        continue;

                tm = &dbSetupTotal.setTimezone.tzHighTIME[nTIME];
                From = tm->bStartHour*60 + tm->bStartMinute;
                To = tm->bEndHour*60 + tm->bEndMinute;
                if (Val >= From && Val <= To)
                        return TRUE;
        }

        return FALSE;
}
*/
BOOL DbUserInfoTzVerify(USER_INFO* pUserInfo)
{
        int nYear, nMonth, nDay, nWeekday, nHour, nMinute, nSecond;
        int nTZ1, nTZ2, nTZ3;

        DbUserInfoGetTimezone(pUserInfo, &nTZ1, &nTZ2, &nTZ3);

        //uiRtcGet(&nYear, &nMonth, &nDay, &nWeekday, &nHour, &nMinute, &nSecond);
//	nWeekday = (nWeekday + 5) % 7;
        nWeekday -= 1;

#if (SB3000_TIMEZONE_LEVEL == 1)
        return DbTzVerify_A(nTZ1 - 1, nWeekday, nHour, nMinute) ||
                   DbTzVerify_A(nTZ2 - 1, nWeekday, nHour, nMinute) ||
                   DbTzVerify_A(nTZ3 - 1, nWeekday, nHour, nMinute);
#elif (SB3000_TIMEZONE_LEVEL == 2)
        return DbTzVerify_High(nTZ1 - 1, nWeekday, nHour, nMinute) ||
                   DbTzVerify_High(nTZ2 - 1, nWeekday, nHour, nMinute) ||
                   DbTzVerify_High(nTZ3 - 1, nWeekday, nHour, nMinute);
#endif
}

//////////////////////////////////////////////////////////////////////////
int DbUserInfoPwdVerify(UINT64 nID, DWORD dwPassword)
{
        int i;

        for (i=0; i<dbLicense.nMaxEnrollCount; i++)
        {
                if (gpUserInfoEnrollData[i].ID == nID && gpUserInfoEnrollData[i].PWD == dwPassword)
                        break;
        }
        return i;
}

//////////////////////////////////////////////////////////////////////////
int DbUserInfoCardVerify(DWORD dwCardNumber)
{
        int i;

        for (i=0; i<dbLicense.nMaxEnrollCount; i++)
        {
                if (gpUserInfoEnrollData[i].ID && gpUserInfoEnrollData[i].CARD == dwCardNumber)
                        break;
        }
        return i;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
static int __SLOG_POS = 0;
//////////////////////////////////////////////////////////////////////////
BOOL DbSLogLoad(void)
{
        int fd;
        int nFileSize;
        BOOL bRet = TRUE;
        MLOG_INFO *pLogBuffer = NULL;

        fd = open(FLASH_SLOG_FILENAME, O_RDWR | O_CREAT,777);
        if (fd == INVALID_HANDLE_VALUE)
                return FALSE;

        ioctl(fd, FIONREAD, &nFileSize);
        if (nFileSize < (int)sizeof(MLOG_INFO) * dbLicense.nSlogMaxCount)
        {
                __SLOG_POS = nFileSize / sizeof(MLOG_INFO);
                if (__SLOG_POS > 0)
                        __SLOG_POS--;
                goto _lExit;
        }
        pLogBuffer = (MLOG_INFO*)malloc( sizeof(MLOG_INFO) * dbLicense.nSlogMaxCount );
        if ( pLogBuffer == NULL )
        {
                bRet = FALSE;
                goto _lExit;
        }

        memset(pLogBuffer, 0, sizeof(MLOG_INFO) * dbLicense.nSlogMaxCount);
        bRet = _Db_FlashRead(fd, pLogBuffer, 0, dbLicense.nSlogMaxCount, sizeof(MLOG_INFO), 0, NULL);
        if (bRet)
        {
                int i;
                for (i=0; i<dbLicense.nSlogMaxCount; i++)
                {
                        if (!pLogBuffer[i].dwSeconds)
                        {
                                __SLOG_POS = i;
                                break;
                        }
                }
                if (i == dbLicense.nSlogMaxCount)
                        bRet = FALSE;
        }

_lExit:
        FREE(pLogBuffer);
        FD_CLOSE(fd);
        return bRet;
}

//////////////////////////////////////////////////////////////////////////
BOOL DbSLogSaveOne(int /*nPos*/)
{
// 	int fd;
// 	BOOL bRet = TRUE;
//
// 	fd = open(FLASH_SLOG_FILENAME, O_RDWR | O_CREAT);
// 	if (fd == INVALID_HANDLE_VALUE)
// 		return FALSE;
//
// 	bRet = _Db_SaveOne(fd, nPos, sizeof(MLOG_INFO), (char*)gpMLogs);
//
// 	FD_CLOSE(fd);
//	return bRet;
        return TRUE;
}

//////////////////////////////////////////////////////////////////////////
BOOL DbSLogAdd(MLOG_INFO *pLogData)
{
        int fd;
        BOOL bRet = TRUE;
        MLOG_INFO LOGTEMP[2];
        int nSize = sizeof(LOGTEMP);

        memset(LOGTEMP, 0, nSize);
        memcpy(&LOGTEMP[0], pLogData, sizeof(MLOG_INFO));

        fd = open(FLASH_SLOG_FILENAME, O_RDWR | O_CREAT,777);
        if (fd == INVALID_HANDLE_VALUE)
                return FALSE;

        if (__SLOG_POS == dbLicense.nSlogMaxCount - 1)
        {
                if (pwrite(fd, &LOGTEMP[0], sizeof(MLOG_INFO), (off_t)__SLOG_POS * sizeof(MLOG_INFO)) != sizeof(MLOG_INFO) ||
                        pwrite(fd, &LOGTEMP[1], sizeof(MLOG_INFO), (off_t)0 * sizeof(MLOG_INFO)) != sizeof(MLOG_INFO))
                {
                        bRet = FALSE;
                        goto _lExit;
                }
        }
        else
        {
                if (pwrite(fd, LOGTEMP, nSize, (off_t)__SLOG_POS * sizeof(MLOG_INFO)) != nSize)
                {
                        bRet = FALSE;
                        goto _lExit;
                }
        }

        __SLOG_POS = (__SLOG_POS + 1) % dbLicense.nSlogMaxCount;

        if (__SLOG_POS == dbSetupTotal.setNoMenu.nReadMLogPos)
        {
                dbSetupTotal.setNoMenu.nReadMLogPos = (dbSetupTotal.setNoMenu.nReadMLogPos + 1) % dbLicense.nSlogMaxCount;
                DbSetupTotalWrite();
        }

_lExit:
        FD_CLOSE(fd);
        return bRet;
}

//////////////////////////////////////////////////////////////////////////
BOOL DbSLogDeleteAll(void)
{
        //DELETE_FILE(FLASH_SLOG_FILENAME);
        __SLOG_POS = 0;
        dbSetupTotal.setNoMenu.nReadMLogPos = 0;
        DbSetupTotalWrite();
        return TRUE;
}

//////////////////////////////////////////////////////////////////////////
int DbSLogCount(void)
{
        return (__SLOG_POS + dbLicense.nSlogMaxCount - dbSetupTotal.setNoMenu.nReadMLogPos) % dbLicense.nSlogMaxCount;
}

//////////////////////////////////////////////////////////////////////////
int	DbSLogCountAll(void)
{
        int fd;
        int nFileSize;
        int nCount;

        fd = open(FLASH_SLOG_FILENAME, O_RDWR | O_CREAT,777);
        if (fd == INVALID_HANDLE_VALUE)
                return 0;

        ioctl(fd, FIONREAD, &nFileSize);
        FD_CLOSE(fd);
        nCount = nFileSize / sizeof(MLOG_INFO);
        if (nCount > 0)
                nCount -= 1;
        return nCount;
}

//////////////////////////////////////////////////////////////////////////
int	DbSLogGet(MLOG_INFO *pLogBuffer, int from, int count)
{
        int fd;
        int nResult, nResult1;
//	int nFileSize;
        BOOL bRet = TRUE;
        BOOL bRotate = (DbSLogCountAll() + 1 == dbLicense.nSlogMaxCount);

        if (bRotate)
                from = (from + __SLOG_POS + 1) % dbLicense.nSlogMaxCount;

        fd = open(FLASH_SLOG_FILENAME, O_RDWR | O_CREAT,777);
        if (fd == INVALID_HANDLE_VALUE)
                return 0;

// 	ioctl(fd, FIONREAD, &nFileSize);
// 	if (nFileSize == sizeof(ALOG_INFO) * dbLicense.nSlogMaxCount)
// 	{
// 		from = (__SLOG_POS + 1 + from) % dbLicense.nSlogMaxCount;
// 	}

        memset(pLogBuffer, 0, sizeof(MLOG_INFO) * count);
        bRet = _Db_FlashRead(fd, pLogBuffer, from, from + count, sizeof(MLOG_INFO), 0, NULL, &nResult);
        if (bRet && from + count > dbLicense.nSlogMaxCount)
        {
//		pLogBuffer += dbLicense.nSlogMaxCount - from;
                pLogBuffer += nResult;
                bRet = _Db_FlashRead(fd, pLogBuffer, 0, from + count - dbLicense.nSlogMaxCount, sizeof(MLOG_INFO), 0, NULL, &nResult1);
                nResult += nResult1;
        }

//_lExit:
        FD_CLOSE(fd);
        return (bRet ? nResult : 0);
}

//////////////////////////////////////////////////////////////////////////
int DbSLogPos()
{
        return __SLOG_POS;
}

//////////////////////////////////////////////////////////////////////////
BOOL DbSLogSetReadPos(int nPos)
{
        BOOL bRotate = (DbSLogCountAll() + 1 == dbLicense.nSlogMaxCount);

        if (bRotate)
                dbSetupTotal.setNoMenu.nReadMLogPos = (__SLOG_POS + 1 + nPos) % dbLicense.nSlogMaxCount;
        else
        {
                if (nPos > __SLOG_POS)
                        nPos = __SLOG_POS;
                dbSetupTotal.setNoMenu.nReadMLogPos = nPos;
        }
        return DbSetupTotalWrite();
}

//////////////////////////////////////////////////////////////////////////
int DbSLogGetReadPos()
{
        int nRet;
        BOOL bRotate = (DbSLogCountAll() + 1 == dbLicense.nSlogMaxCount);

        if (bRotate)
                nRet = (dbSetupTotal.setNoMenu.nReadMLogPos + dbLicense.nSlogMaxCount - __SLOG_POS - 1) % dbLicense.nSlogMaxCount;
        else
                nRet = dbSetupTotal.setNoMenu.nReadMLogPos;

        return nRet;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
static int __GLOG_POS = 0;
//////////////////////////////////////////////////////////////////////////
BOOL DbGLogLoad(void)
{
 /*       int i;
        int fd;
// 	int nFileSize;
        BOOL bRet = TRUE;
        ALOG_INFO *pLogBuffer;
                int from, to, step;
                                DWORD dwAntipassLastDate ;
                DWORD dwSecond;

        fd = open(FLASH_GLOG_FILENAME, O_RDWR | O_CREAT);
        if (fd == INVALID_HANDLE_VALUE)
                return FALSE;

// 	ioctl(fd, FIONREAD, &nFileSize);
// 	if (nFileSize < sizeof(ALOG_INFO) * dbLicense.nGlogMaxCount)
// 	{
// 		__GLOG_POS = nFileSize / sizeof(ALOG_INFO);
// 		if (__GLOG_POS > 0)
// 			__GLOG_POS--;
// 		goto _lExit;
// 	}
        pLogBuffer = (ALOG_INFO*)malloc( sizeof(ALOG_INFO) * dbLicense.nGlogMaxCount );
        if ( pLogBuffer == NULL )
        {
                bRet = FALSE;
                goto _lExit;
        }

        g_dwVerifyCountFP = g_dwVerifyCountCD = g_dwVerifyCountPW = 0;
        memset(pLogBuffer, 0, sizeof(ALOG_INFO) * dbLicense.nGlogMaxCount);
        bRet = _Db_FlashRead(fd, pLogBuffer, 0, dbLicense.nGlogMaxCount, sizeof(ALOG_INFO), 0, NULL);
        if (bRet)
        {
                for (i=0; i<dbLicense.nGlogMaxCount; i++)
                {
                        if (pLogBuffer[i].dwSeconds==0)
                        {
                                __GLOG_POS = i;
                                break;
                        }
                }
                if (i == dbLicense.nGlogMaxCount)
                        bRet = FALSE;
        }
        if (bRet)
        {

                 dwAntipassLastDate = DbAntipassGetLastDate();
                 dwSecond = uiRtcGetSeconds();


                if (dwAntipassLastDate == -1UL)
                        dwAntipassLastDate = 0;

                for (step=0; step<2; step++)
                {
                        if (step == 0)
                        {
                                from = __GLOG_POS;
                                to   = dbLicense.nGlogMaxCount - 1;
                        }
                        else
                        {
                                from = 0;
                                to   = __GLOG_POS - 1;
                        }
                        for (i=from; i<=to; i++)
                        {
                                if (!pLogBuffer[i].dwSeconds)
                                        continue;
                                if (pLogBuffer[i].dwSeconds > dwAntipassLastDate)
                                        DbAntipassSet(pLogBuffer[i].nID, pLogBuffer[i].bAntipassOut, dwSecond);
                                if (pLogBuffer[i].bAntipassOut)
                                        continue;
                                switch (pLogBuffer[i].byAction)
                                {
                                case VM_FP:
                                        g_dwVerifyCountFP++;
                                        break;
                                case VM_RFFP:
                                        g_dwVerifyCountFP++;
                                        g_dwVerifyCountCD++;
                                        break;
                                case VM_RF:
                                        g_dwVerifyCountCD++;
                                        break;
                                case VM_IDFP:
                                        g_dwVerifyCountFP++;
                                        break;
                                case VM_IDPW:
                                        g_dwVerifyCountPW++;
                                        break;
                                }
                        }

                        DbAntipassSave();
                }
        }
_lExit:
        FREE(pLogBuffer);
        FD_CLOSE(fd);
        return bRet;*/
}

//////////////////////////////////////////////////////////////////////////
BOOL DbGLogAdd(ALOG_INFO *pLogData)
{
        int fd;
        BOOL bRet = TRUE;
        ALOG_INFO LOGTEMP[2];
        int nSize = sizeof(LOGTEMP);

        memset(LOGTEMP, 0, nSize);
        memcpy(&LOGTEMP[0], pLogData, sizeof(ALOG_INFO));

        fd = open(FLASH_GLOG_FILENAME, O_RDWR | O_CREAT,777);
        if (fd == INVALID_HANDLE_VALUE)
                return FALSE;

        if (__GLOG_POS == dbLicense.nGlogMaxCount - 1)
        {
                if (pwrite(fd, &LOGTEMP[0], sizeof(ALOG_INFO), (off_t)__GLOG_POS * sizeof(ALOG_INFO)) != sizeof(ALOG_INFO) ||
                        pwrite(fd, &LOGTEMP[1], sizeof(ALOG_INFO), (off_t)0 * sizeof(ALOG_INFO)) != sizeof(ALOG_INFO))
                {
                        bRet = FALSE;
                        goto _lExit;
                }
        }
        else
        {
                if (pwrite(fd, LOGTEMP, nSize, (off_t)__GLOG_POS * sizeof(ALOG_INFO)) != nSize)
                {
                        bRet = FALSE;
                        goto _lExit;
                }
        }

        __GLOG_POS = (__GLOG_POS + 1) % dbLicense.nGlogMaxCount;

        if (__GLOG_POS == dbSetupTotal.setNoMenu.nReadALogPos)
        {
                dbSetupTotal.setNoMenu.nReadALogPos = (dbSetupTotal.setNoMenu.nReadALogPos + 1) % dbLicense.nGlogMaxCount;
                DbSetupTotalWrite();
        }
        DbAntipassSet(pLogData->nID, pLogData->bAntipassOut);

_lExit:
        FD_CLOSE(fd);
        return bRet;
}

//////////////////////////////////////////////////////////////////////////
BOOL DbGLogDeleteAll(void)
{
        //RMDIR(SDCARD_MOUNTPOINT PATH_PHOTO_LOG);
        //DELETE_FILE(FLASH_GLOG_FILENAME);
        __GLOG_POS = 0;
        dbSetupTotal.setNoMenu.nReadALogPos = 0;
        DbSetupTotalWrite();
        DbAntipassDeleteAll();
        return TRUE;
}

//////////////////////////////////////////////////////////////////////////
int DbGLogCount(void)
{
        return (__GLOG_POS + dbLicense.nGlogMaxCount - dbSetupTotal.setNoMenu.nReadALogPos) % dbLicense.nGlogMaxCount;
}

//////////////////////////////////////////////////////////////////////////
int	DbGLogCountAll(void)
{
        int fd;
        int nFileSize;
        int nCount;

        fd = open(FLASH_GLOG_FILENAME, O_RDWR | O_CREAT,777);
        if (fd == INVALID_HANDLE_VALUE)
                return 0;

        ioctl(fd, FIONREAD, &nFileSize);
        FD_CLOSE(fd);
        nCount = nFileSize / sizeof(ALOG_INFO);
        if (nCount > 0)
                nCount -= 1;
        return nCount;
}

//////////////////////////////////////////////////////////////////////////
int	DbGLogGet(ALOG_INFO *pLogBuffer, int from, int count)
{
        int fd;
        int nResult, nResult1;
//	int nFileSize;
        BOOL bRet = TRUE;
        BOOL bRotate = (DbGLogCountAll() + 1 == dbLicense.nGlogMaxCount);

        if (bRotate)
                from = (from + __GLOG_POS + 1) % dbLicense.nGlogMaxCount;

        fd = open(FLASH_GLOG_FILENAME, O_RDWR | O_CREAT,777);
        if (fd == INVALID_HANDLE_VALUE)
                return 0;

// 	ioctl(fd, FIONREAD, &nFileSize);
// 	if (nFileSize == sizeof(ALOG_INFO) * dbLicense.nGlogMaxCount)
// 	{
// 		from = (__GLOG_POS + 1 + from) % dbLicense.nGlogMaxCount;
// 	}

        memset(pLogBuffer, 0, sizeof(ALOG_INFO) * count);
        bRet = _Db_FlashRead(fd, pLogBuffer, from, from + count, sizeof(ALOG_INFO), 0, NULL, &nResult);
        if (bRet && from + count > dbLicense.nGlogMaxCount)
        {
//		pLogBuffer += dbLicense.nGlogMaxCount - from;
                pLogBuffer += nResult;
                bRet = _Db_FlashRead(fd, pLogBuffer, 0, from + count - dbLicense.nGlogMaxCount, sizeof(ALOG_INFO), 0, NULL, &nResult1);
                nResult += nResult1;
        }

//_lExit:
        FD_CLOSE(fd);
        return (bRet ? nResult : 0);
}

//////////////////////////////////////////////////////////////////////////
int	DbSLogGetByTime(MLOG_INFO *pLogBuffer,int from,int to, int fromsecond, int tosecond)
{
        int fd;
        int nCount;
        int i;
        MLOG_INFO logtemp;
        int pos;
        int result = 0;
        MLOG_INFO *buf =pLogBuffer;


        fd = open(FLASH_SLOG_FILENAME, O_RDWR | O_CREAT,777);
        if (fd == INVALID_HANDLE_VALUE)
                return 0;

        memset(pLogBuffer, 0, sizeof(MLOG_INFO) * (to-from));
    nCount=0;
    for(i=from;i<to;i++)
    {
                pos = i * sizeof(MLOG_INFO);
                result = pread(fd, &logtemp, (size_t)sizeof(MLOG_INFO), (off_t)pos);

                if (result == 0) //EOF
                {
                        break;
                }
                else if (result == -1) //ERROR
                        memset(&logtemp, 0, sizeof(MLOG_INFO));
                if(logtemp.dwSeconds>=fromsecond && logtemp.dwSeconds<=tosecond)
                {
               memcpy(buf,&logtemp,sizeof(MLOG_INFO));
                   buf += sizeof(MLOG_INFO);
                   nCount++;
                }
    }

        FD_CLOSE(fd);
        return (nCount);
}

//////////////////////////////////////////////////////////////////////////
int	DbGLogGetByTime(ALOG_INFO *pLogBuffer,int from,int to, u32 fromsecond, u32 tosecond)
{
        int fd;
        //int nResult, nResult1;
        int nCount;
        //BOOL bRet = TRUE;
        //BOOL bRotate = (DbGLogCountAll() + 1 == dbLicense.nGlogMaxCount);
        int i;
        ALOG_INFO logtemp;
        int pos;
        int result = 0;
        ALOG_INFO *buf = pLogBuffer;

        //if (bRotate)
        //	from = (from + __GLOG_POS + 1) % dbLicense.nGlogMaxCount;

        fd = open(FLASH_GLOG_FILENAME, O_RDWR | O_CREAT,777);
        if (fd == INVALID_HANDLE_VALUE)
                return 0;

        //xprintf("DbGLogGetByTime.DbGLogGetByTime\r\n");

        //if(pLogBuffer)
           //memset(pLogBuffer, 0, sizeof(ALOG_INFO) * (to-from));
    nCount=0;
    for(i=from;i<to;i++)
    {
                pos = i * sizeof(ALOG_INFO);
                result = pread(fd, &logtemp, (size_t)sizeof(ALOG_INFO), (off_t)pos);

                if (result == 0) //EOF
                {
                        xprintf("DbGLogGetByTime.result = pread\r\n");
                        break;
                }
                else if (result == -1) //ERROR
                        memset(&logtemp, 0, sizeof(ALOG_INFO));
                xprintf("logtemp.dwSeconds=%d \r\n", logtemp.dwSeconds);
                if(logtemp.dwSeconds>=fromsecond && logtemp.dwSeconds<=tosecond)
                {
                        //if(buf)
                        //{
                                xprintf("nID=%d dwSeconds=%d byAction=%d \r\n", logtemp.nID,logtemp.dwSeconds,logtemp.byAction);
                                memcpy(buf,&logtemp,sizeof(ALOG_INFO));
                                buf ++;
                        //}
                        nCount++;
                }
    }

//_lExit:
        FD_CLOSE(fd);
        return (nCount);
}

extern int pos_allSearch;

//////////////////////////////////////////////////////////////////////////
int	DbGLogGetByTimeAllSearch(ALOG_INFO *pLogBuffer,DWORD from,DWORD to, int fromsecond, int tosecond,int allcount)
{
        int fd;
        int nCount;
    DWORD i;
        ALOG_INFO logtemp;
        int pos;
        int result = 0;
        ALOG_INFO *buf =pLogBuffer;

        fd = open(FLASH_GLOG_FILENAME, O_RDWR | O_CREAT,777);
        if (fd == INVALID_HANDLE_VALUE)
                return 0;


        if(pLogBuffer)
           memset(pLogBuffer, 0, sizeof(ALOG_INFO) * (allcount));
    nCount=0;
     to = DbGLogCountAll();
         //xprintf("to   DbGLogCountAll=%d\r\n",to);
    for(i=from;i<to;i++)
    {
                pos = i * sizeof(ALOG_INFO);
                result = pread(fd, &logtemp, (size_t)sizeof(ALOG_INFO), (off_t)pos);

                if (result == 0) //EOF
                {
                        break;
                }
                else if (result == -1) //ERROR
                        memset(&logtemp, 0, sizeof(ALOG_INFO));
                //if(logtemp.dwSeconds>fromsecond && logtemp.dwSeconds<tosecond)
                  if(logtemp.dwSeconds>fromsecond&&logtemp.dwSeconds<tosecond)
                {
                   if(buf)
                   {
                         memcpy(buf,&logtemp,sizeof(ALOG_INFO));
                       buf ++;
                 }
                   nCount++;
                   if(nCount>=allcount)
                        break;
                }
         // pos_allSearch++;
    }
        //xprintf("ggg    pos_allSearch=%d\r\n",pos_allSearch);
        //xprintf("ggg  nCount=%d\r\n",nCount);
        FD_CLOSE(fd);
        return (nCount);
}

//////////////////////////////////////////////////////////////////////////
int	DbSLogPosGetByTime(int from,int to, int fromsecond, int tosecond)
{
        int fd;
    int i;
        MLOG_INFO logtemp;
        int pos;
        int result = 0;

        fd = open(FLASH_SLOG_FILENAME, O_RDWR | O_CREAT,777);
        if (fd == INVALID_HANDLE_VALUE)
                return 0;
    for(i=from;i<to;i++)
    {
                pos = i * sizeof(MLOG_INFO);
                result = pread(fd, &logtemp, (size_t)sizeof(MLOG_INFO), (off_t)pos);

                if (result == 0) //EOF
                {
                        break;
                }
                else if (result == -1) //ERROR
                        memset(&logtemp, 0, sizeof(MLOG_INFO));
                if(logtemp.dwSeconds>=fromsecond && logtemp.dwSeconds<=tosecond)
                {
                   break;
                }
    }

//_lExit:
        FD_CLOSE(fd);
        return (i);
}



//////////////////////////////////////////////////////////////////////////
int	DbGLogPosGetByTime(int from,int to, u32 fromsecond, u32 tosecond)
{
        int fd;
    int i;
        ALOG_INFO logtemp;
        int pos;
        int result = 0;
        fd = open(FLASH_GLOG_FILENAME, O_RDWR | O_CREAT,777);
        if (fd == INVALID_HANDLE_VALUE)
                return 0;
    for(i=from;i<to;i++)
    {
                pos = i * sizeof(ALOG_INFO);
                result = pread(fd, &logtemp, (size_t)sizeof(ALOG_INFO), (off_t)pos);

                if (result == 0) //EOF
                {
                        break;
                }
                else

                        if (result == -1) //ERROR
                        memset(&logtemp, 0, sizeof(ALOG_INFO));
                if(logtemp.dwSeconds>=fromsecond && logtemp.dwSeconds<=tosecond)
                {

                   break;
                }
    }

//_lExit:
        FD_CLOSE(fd);
        return (i);
}

//////////////////////////////////////////////////////////////////////////
int	DbGLogCountGetByTime(int from,int to, u32 fromsecond, u32 tosecond)
{
        int fd;
    int i;
        ALOG_INFO logtemp;
        int pos;
        int result = 0;

        //   	int nYear,  nMonth,  nDay, nHour, nMinute,  nSecond;

        fd = open(FLASH_GLOG_FILENAME, O_RDWR | O_CREAT,777);
        if (fd == INVALID_HANDLE_VALUE)
                return 0;
    for(i=from;i<to;i++)
    {
                pos = i * sizeof(ALOG_INFO);
                result = pread(fd, &logtemp, (size_t)sizeof(ALOG_INFO), (off_t)pos);

                if (result == 0) //EOF
                {
                        break;
                }
                else if (result == -1) //ERROR
                        memset(&logtemp, 0, sizeof(ALOG_INFO));
                if(logtemp.dwSeconds>tosecond||logtemp.dwSeconds<fromsecond)
                {

/*
             xprintf("3 DbGLogCountGetByTime  logtemp.dwSeconds=%d,logtemp.nID=%d,logtemp.byAction=%d\r\n",logtemp.dwSeconds,logtemp.nID,logtemp.byAction);
                uiRtcSeconds2YMDHMS(logtemp.dwSeconds,&nYear, &nMonth, &nDay, &nHour, &nMinute, &nSecond);
                xprintf("3 DbGLogCountGetByTime nYear=%d,nMonth=%d,nDay=%d,nHour=%d,nMinute=%d,nSecond=%d\r\n",nYear,  nMonth,  nDay, nHour, nMinute,  nSecond);
             i++;
                                                        pos = i * sizeof(ALOG_INFO);
                result = pread(fd, &logtemp, (size_t)sizeof(ALOG_INFO), (off_t)pos);
                                                   xprintf("4 DbGLogCountGetByTime  logtemp.dwSeconds=%d,logtemp.nID=%d,logtemp.byAction=%d\r\n",logtemp.dwSeconds,logtemp.nID,logtemp.byAction);
                uiRtcSeconds2YMDHMS(logtemp.dwSeconds,&nYear, &nMonth, &nDay, &nHour, &nMinute, &nSecond);
                xprintf("4 DbGLogCountGetByTime nYear=%d,nMonth=%d,nDay=%d,nHour=%d,nMinute=%d,nSecond=%d\r\n",nYear,  nMonth,  nDay, nHour, nMinute,  nSecond);

*/

                   break;
                }
    }

//_lExit:
        FD_CLOSE(fd);
        return (i);
}

//////////////////////////////////////////////////////////////////////////
DWORD	DbGLogCountGetByTimeAllSearch( u32 fromsecond, u32 tosecond)
{
        int fd;
      DWORD i;
        ALOG_INFO logtemp;
        int pos;
        int result = 0;
        DWORD count,SearchCount;
        //   	int nYear,  nMonth,  nDay, nHour, nMinute,  nSecond;
        count = DbGLogCountAll();
        SearchCount=0;
        fd = open(FLASH_GLOG_FILENAME, O_RDWR | O_CREAT,777);
        if (fd == INVALID_HANDLE_VALUE)
                return 0;
    for(i=0;i<count;i++)
    {
                pos = i * sizeof(ALOG_INFO);
                result = pread(fd, &logtemp, (size_t)sizeof(ALOG_INFO), (off_t)pos);

                if (result == 0) //EOF
                {
                        break;
                }
                else if (result == -1) //ERROR
                        memset(&logtemp, 0, sizeof(ALOG_INFO));
                if(logtemp.dwSeconds>fromsecond&&logtemp.dwSeconds<tosecond)
                {
                      SearchCount++;
                }
    }
        FD_CLOSE(fd);
        return (SearchCount);
}
/*
//////////////////////////////////////////////////////////////////////////
BOOL  DbGLogCopyDataToRamForAllSearch( ALOG_INFO *pLogBuffer,int fromsecond, int tosecond)
{
        int fd;
      DWORD i;
        ALOG_INFO logtemp;
        int pos;
        int result = 0;
        DWORD count,SearchCount;
        //   	int nYear,  nMonth,  nDay, nHour, nMinute,  nSecond;
        count = DbGLogCountAll();
        SearchCount=0;
        fd = open(FLASH_GLOG_FILENAME, O_RDWR | O_CREAT);
        if (fd == INVALID_HANDLE_VALUE)
                return 0;
    for(i=0;i<count;i++)
    {
                pos = i * sizeof(ALOG_INFO);
                result = pread(fd, &logtemp, (size_t)sizeof(ALOG_INFO), (off_t)pos);

                if (result == 0) //EOF
                {
                        break;
                }
                else if (result == -1) //ERROR
                        memset(&logtemp, 0, sizeof(ALOG_INFO));
                if(logtemp.dwSeconds>fromsecond&&logtemp.dwSeconds<tosecond)
                {
                      pLogBuffer[i].bAntipassOut=logtemp.bAntipassOut;
                        pLogBuffer[i].byAction=logtemp.byAction;
                        pLogBuffer[i].byTrStatus=logtemp.byTrStatus;
                        pLogBuffer[i].dwSeconds=logtemp.dwSeconds;
                        pLogBuffer[i].nID=logtemp.nID;
                        pLogBuffer[i].res=logtemp.res;
                }
    }
        FD_CLOSE(fd);
        return (SearchCount);
}
*/
//////////////////////////////////////////////////////////////////////////
BOOL DbGlogIsReverify(UINT64 nID)
{
        int i, from;
        int nLogCount = DbGLogCount();
        DWORD dwSecondsNow, dwSecondsLast;
        ALOG_INFO TEMP[100];

        if (!dbSetupTotal.setSystem.nReverifyTime || dbSetupTotal.setSystem.byAntipassStatus != ANTIPASS_NO)
                return FALSE;

        //dwSecondsNow = uiRtcGetSeconds();

        from = (__GLOG_POS + dbLicense.nGlogMaxCount - 100) % dbLicense.nGlogMaxCount;
        while (nLogCount > 0)
        {
                memset(TEMP, 0, sizeof(TEMP));
                DbGLogGet(TEMP, from, 100);
                for (i=99; i>=0; i--)
                {
                        if (!TEMP[i].dwSeconds)
                                continue;
                        dwSecondsLast = TEMP[i].dwSeconds;
                        if (dwSecondsNow > dwSecondsLast + dbSetupTotal.setSystem.nReverifyTime * 60)
                                return FALSE;
                        if (!TEMP[i].bAntipassOut && TEMP[i].nID == nID)
                                return TRUE;
                }
                nLogCount -= 100;
                from = (from + dbLicense.nGlogMaxCount - 100) % dbLicense.nGlogMaxCount;
        }

// 	if (dwSecondsNow > dwSecondsLast + dbSetupTotal.setSystem.nReverifyTime * 60)
// 		return FALSE;

        return FALSE;
}


//////////////////////////////////////////////////////////////////////////
BOOL DbGlogIsReverify2(UINT64 nID)
{
        int i, from;
        int nLogCount = DbGLogPos(); //DbGLogCount();
        DWORD dwSecondsNow, dwSecondsLast;
        ALOG_INFO TEMP[100];

        if (!dbSetupTotal.setSystem.nReverifyTime || dbSetupTotal.setSystem.byAntipassStatus != ANTIPASS_NO)
                return FALSE;

        //dwSecondsNow = uiRtcGetSeconds();

        from = (__GLOG_POS + dbLicense.nGlogMaxCount - 100) % dbLicense.nGlogMaxCount;
        while (nLogCount > 0)
        {
                memset(TEMP, 0, sizeof(TEMP));
                DbGLogGet(TEMP, from, 100);
                for (i=99; i>=0; i--)
                {
                        if (!TEMP[i].dwSeconds)
                                continue;
                        dwSecondsLast = TEMP[i].dwSeconds;
                        if (dwSecondsNow > dwSecondsLast + dbSetupTotal.setSystem.nReverifyTime * 60)
                                return FALSE;
                        if (!TEMP[i].bAntipassOut && TEMP[i].nID == nID)
                                return TRUE;
                }
                nLogCount -= 100;
                from = (from + dbLicense.nGlogMaxCount - 100) % dbLicense.nGlogMaxCount;
        }

// 	if (dwSecondsNow > dwSecondsLast + dbSetupTotal.setSystem.nReverifyTime * 60)
// 		return FALSE;

        return FALSE;
}

//////////////////////////////////////////////////////////////////////////
int DbGLogPos()
{
        return __GLOG_POS;
}

//////////////////////////////////////////////////////////////////////////
BOOL DbGLogSetReadPos(int nPos)
{
        BOOL bRotate = (DbGLogCountAll() + 1 == dbLicense.nGlogMaxCount);

        if (bRotate)
                dbSetupTotal.setNoMenu.nReadALogPos = (__GLOG_POS + 1 + nPos) % dbLicense.nGlogMaxCount;
        else
        {
                if (nPos > __GLOG_POS)
                        nPos = __GLOG_POS;
                dbSetupTotal.setNoMenu.nReadALogPos = nPos;
        }
        return DbSetupTotalWrite();

}

//////////////////////////////////////////////////////////////////////////
int DbGLogGetReadPos()
{
        int nRet;
        BOOL bRotate = (DbGLogCountAll() + 1 == dbLicense.nGlogMaxCount);

        if (bRotate)
                nRet = (dbSetupTotal.setNoMenu.nReadALogPos + dbLicense.nGlogMaxCount - __GLOG_POS - 1) % dbLicense.nGlogMaxCount;
        else
                nRet = dbSetupTotal.setNoMenu.nReadALogPos;

        return nRet;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
//////////////////////////////////////////////////////////////////////////
BOOL DbUIIndexLoad(void)
{
        int fd;
        BOOL bRet = TRUE;

        fd = open(FLASH_UI_INDEX_FILENAME, O_RDWR | O_CREAT,777);
        if (fd == INVALID_HANDLE_VALUE)
                return FALSE;

        gpUIIndexData = (WORD*)malloc(FLASH_UI_INDEX_SIZE);
        if (gpUIIndexData == NULL)
        {
                bRet = FALSE;
                goto _lExit;
        }

        memset(gpUIIndexData, 0, FLASH_UI_INDEX_SIZE);
        bRet = (read(fd, gpUIIndexData, FLASH_UI_INDEX_SIZE) == FLASH_UI_INDEX_SIZE);
        if (!bRet)
        {
                memset(gpUIIndexData, 0xFF, FLASH_UI_INDEX_SIZE);
                bRet = (pwrite(fd, gpUIIndexData, FLASH_UI_INDEX_SIZE, 0) == FLASH_UI_INDEX_SIZE);
        }

_lExit:
        FD_CLOSE(fd);
        return bRet;
}

//////////////////////////////////////////////////////////////////////////
BOOL DbUIIndexSave(void)
{
        int fd;
        BOOL bRet = TRUE;

        fd = open(FLASH_UI_INDEX_FILENAME, O_RDWR | O_CREAT,777);
        if (fd == INVALID_HANDLE_VALUE)
                return FALSE;

        bRet = (write(fd, gpUIIndexData, FLASH_UI_INDEX_SIZE) == FLASH_UI_INDEX_SIZE);
        FD_CLOSE(fd);
        return bRet;
}

//////////////////////////////////////////////////////////////////////////
BOOL DbUIIndexDeleteAll(void)
{
        if (!gpUIIndexData)
                return FALSE;
        memset(gpUIIndexData, 0xFF, FLASH_UI_INDEX_SIZE);
        return DbUIIndexSave();
}

//////////////////////////////////////////////////////////////////////////
int DbUIIndexGetPosition(int nUserInfoPos)
{
        int i;

        for (i=0; i<dbLicense.nMaxEnrollCount; i++)
        {
                if (gpUIIndexData[i] == (WORD)nUserInfoPos)
                        break;
        }

        return i;
}

//////////////////////////////////////////////////////////////////////////
int DbUserInfoGetNearestPosition(UINT64 nID, int *pNearestPos)
{
        int i;
        int nUserInfoPos;
        int nRet = -1;
        int nNearestPos = -1;

        for (i=0; i<dbLicense.nMaxEnrollCount; i++)
        {
                nUserInfoPos = gpUIIndexData[i];
                if (nUserInfoPos == 0xFFFF)
                {
                        nNearestPos = i;
                        nRet = -1;
                        goto _lExit;
                }
                if (gpUserInfoEnrollData[nUserInfoPos].ID == nID)
                {
                        nRet = i;
                        goto _lExit;
                }
        /*
                if (gpUserInfoEnrollData[nUserInfoPos].ID > nID)
                {
                        nNearestPos = i;
                        nRet = -1;
                        goto _lExit;
                }   */
        }

_lExit:
        if (pNearestPos) *pNearestPos = nNearestPos;
        return nRet;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
//////////////////////////////////////////////////////////////////////////
BOOL DbFPIndexLoad(void)
{
        int fd;
        BOOL bRet = TRUE;

        fd = open(FLASH_FP_INDEX_FILENAME, O_RDWR | O_CREAT,777);
        if (fd == INVALID_HANDLE_VALUE)
                return FALSE;

        //gpIndexData = SB_FP_INDEXDBALLOC();
        if ( gpIndexData == NULL )
        {
                bRet = FALSE;
                goto _lExit;
        }

        bRet = (read(fd, gpIndexData, dbLicense.nMaxEnrollCount) == dbLicense.nMaxEnrollCount);
        if (bRet == FALSE)
        {
                memset(gpIndexData, 0, dbLicense.nMaxEnrollCount);
                bRet = (pwrite(fd, gpIndexData, dbLicense.nMaxEnrollCount, 0) == dbLicense.nMaxEnrollCount);
        }

_lExit:
        FD_CLOSE(fd);
        return bRet;
}

//////////////////////////////////////////////////////////////////////////
BOOL DbFPIndexSave(void)
{
        int fd;
        BOOL bRet = TRUE;

        fd = open(FLASH_FP_INDEX_FILENAME, O_RDWR | O_CREAT,777);
        if (fd == INVALID_HANDLE_VALUE)
                return FALSE;

        bRet = (write(fd, gpIndexData, dbLicense.nMaxEnrollCount) == dbLicense.nMaxEnrollCount);

        FD_CLOSE(fd);
        return bRet;
}

//////////////////////////////////////////////////////////////////////////
BOOL DbFPIndexDeleteAll(void)
{
        if(!gpIndexData) return FALSE;
        memset ( gpIndexData, 0, sizeof(BYTE) * dbLicense.nMaxEnrollCount );
        return DbFPIndexSave();
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
QMap<UINT64, BYTE> __ANTIPASS_MAP;
//////////////////////////////////////////////////////////////////////////
BOOL DbAntipassLoad(void)
{
        __ANTIPASS_MAP.clear();
        return TRUE;
/*
// 	int fd;
        BOOL bRet = TRUE;

// 	fd = open(FLASH_ANTIPASS_FILENAME, O_RDWR | O_CREAT);
// 	if (fd == INVALID_HANDLE_VALUE)
// 		return FALSE;

        gpAntipassData = (BYTE*)malloc(FLASH_ANTIPASS_SIZE);
        if (gpAntipassData == NULL)
        {
                bRet = FALSE;
                goto _lExit;
        }

        memset(gpAntipassData, 0, FLASH_ANTIPASS_SIZE);
// 	bRet = (read(fd, gpAntipassData, FLASH_ANTIPASS_SIZE) == FLASH_ANTIPASS_SIZE);
// 	if (!bRet)
// 	{
// 		memset(gpAntipassData, 0, FLASH_ANTIPASS_SIZE);
// 		bRet = (pwrite(fd, gpAntipassData, FLASH_ANTIPASS_SIZE, 0) == FLASH_ANTIPASS_SIZE);
// 	}

_lExit:
// 	FD_CLOSE(fd);
        return bRet;
*/
}

//////////////////////////////////////////////////////////////////////////
BOOL DbAntipassSave(void)
{
/*	int fd;
        BOOL bRet = TRUE;

        fd = open(FLASH_ANTIPASS_FILENAME, O_RDWR | O_CREAT);
        if (fd == INVALID_HANDLE_VALUE)
                return FALSE;

        bRet = (write(fd, gpAntipassData, FLASH_ANTIPASS_SIZE) == FLASH_ANTIPASS_SIZE);
        FD_CLOSE(fd);
        return bRet;*/
        return TRUE;
}

//////////////////////////////////////////////////////////////////////////
BOOL DbAntipassDeleteAll(void)
{
        __ANTIPASS_MAP.clear();
        return TRUE;
/*	if (!gpAntipassData)
                return FALSE;
        memset(gpAntipassData, 0, FLASH_ANTIPASS_SIZE);
        return DbAntipassSave();*/
}

//////////////////////////////////////////////////////////////////////////
BOOL DbAntipassSet(UINT64 nID, BOOL bStatus, DWORD /*dwTime*/, BOOL /*bSave*/)
{
        __ANTIPASS_MAP.insert(nID, bStatus ? ANTIPASSOUT_OUT : ANTIPASSOUT_IN);
        return TRUE;
/*	BOOL bRet = TRUE;
        WORD wID = (WORD)nID;
        DWORD *pHdr = (DWORD*)gpAntipassData;
        BYTE *pData = gpAntipassData + 4;

        if (dwTime == -1UL)
                dwTime = uiRtcGetSeconds();
        *pHdr = dwTime;
        if (bStatus)
                pData[wID >> 2] |= (ANTIPASSOUT_OUT << ((wID & 3) * 2));
        else
        {
                pData[wID >> 2] &= ~(ANTIPASSOUT_OUT << ((wID & 3) * 2));
                pData[wID >> 2] |=  (ANTIPASSOUT_IN << ((wID & 3) * 2));
        }

        if (bSave)
                bRet = DbAntipassSave();

        return TRUE;*/
}

//////////////////////////////////////////////////////////////////////////
BYTE DbAntipassGet(UINT64 nID)
{
        if (__ANTIPASS_MAP.contains(nID))
                return __ANTIPASS_MAP[nID];
        return ANTIPASSOUT_NONE;
/*	BYTE bRet;
        WORD wID = (WORD)nID;
        DWORD *pHdr = (DWORD*)gpAntipassData;
        BYTE *pData = gpAntipassData + 4;

        bRet = (pData[wID >> 2] & (1 << ((wID & 3) * 2))) >> ((wID & 3) * 2);
        return bRet;*/
}

//////////////////////////////////////////////////////////////////////////
DWORD DbAntipassGetLastDate(void)
{
        return 0;
//	return *(DWORD*)gpAntipassData;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
static QStringList __parts;
BOOL DbPartLoad(void)
{
        QFile f;
        QString szPart;

        __parts.clear();
        __parts.append("");

        f.setFileName(FLASH_PART_FILENAME);
        if (!f.open(QIODevice::ReadOnly))
                goto _lExit;

        if (TRUE)
        {
                QTextStream input(&f);
                input.setCodec(QTextCodec::codecForName(TEXTCODEC));

                while (!input.atEnd())
                {
                        szPart = input.readLine();
                        if (szPart.length())
                                __parts.append(szPart);
                }
        }

_lExit:
        return TRUE;
}

BOOL DbPartReload(void)
{
        BOOL bRet = TRUE;
        QFile f;
        QString szPart;

        f.setFileName(FLASH_PART_FILENAME);

        if (f.exists(FLASH_PART_FILENAME))
        {
                if (!f.open(QIODevice::ReadOnly))
                {
                        bRet = FALSE;
                        goto _lExit;
                }
                QTextStream input(&f);
                input.setCodec(QTextCodec::codecForName(TEXTCODEC));

                while (!input.atEnd())
                {
                        szPart = input.readLine();
                        if (szPart.length() && !__parts.contains(szPart))
                                __parts.append(szPart);
                }
                f.close();
        }
        else
        {
                __parts.clear();
                __parts.append("");
                goto _lExit;
        }

        if (TRUE)
        {
                if (!f.open(QIODevice::WriteOnly | QIODevice::Truncate))
                {
                        bRet = FALSE;
                        goto _lExit;
                }
                QTextStream output(&f);
                output.setCodec(QTextCodec::codecForName(TEXTCODEC));

                for (int i=1; i<__parts.count(); i++)
                {
                        output << __parts[i] << "\r\n";
                }
                f.close();
        }

_lExit:
        return bRet;
}

BOOL DbPartSave(void)
{
        return TRUE;
}

int DbPartCount(void)
{
        return __parts.size();
}

QString	DbPartGet(int nIndex)
{
        if (nIndex >= __parts.size())
                return QString("");
        return __parts[nIndex];
}

BOOL DbPartSet(int /*nIndex*/, const QString & /*szValue*/)
{
        return TRUE;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
//////////////////////////////////////////////////////////////////////////
BOOL Db_IsUnusedID (UINT64 nID)
{
        return (DbUserInfoIsUsedID(nID) == FALSE);
}

//////////////////////////////////////////////////////////////////////////
UINT64 Db_GetUsedID(UINT64 nIDFrom)
{
        int nPos;
        int NearestPos;
        int nUserInfoPos;
        UINT64 nRet = nIDFrom;

_lSearch:
        nPos = DbUserInfoGetNearestPosition(nIDFrom, &NearestPos);
        if (nPos < 0)
                nPos = NearestPos;

        if (nPos < 0 || gpUIIndexData[nPos] == 0xFFFF)
        {
                nRet = 0;
        }
        else
        {
                nUserInfoPos = gpUIIndexData[nPos];
                nRet = gpUserInfoEnrollData[nUserInfoPos].ID;
        }
        if (nIDFrom && nRet == 0)
        {
                nIDFrom = 0;
                goto _lSearch;
        }

        return nRet;
}

//////////////////////////////////////////////////////////////////////////
UINT64 Db_GetUnusedID(UINT64 nIDFrom)
{
        int nPos;
        int NearestPos;
        int nUserInfoPos1, nUserInfoPos2;

        if(nIDFrom < 1)
            nIDFrom = 1;

        nPos = DbUserInfoGetNearestPosition(nIDFrom, &NearestPos);
        if (nPos < 0)
                return nIDFrom;

        while (nPos && gpUIIndexData[nPos] == 0xFFFF)
                nPos--;
        if (gpUIIndexData[nPos] == 0xFFFF)
                return 1;

        nUserInfoPos1 = 0;
        while (nPos < dbLicense.nMaxEnrollCount)
        {
                nUserInfoPos1 = gpUIIndexData[nPos];
                nUserInfoPos2 = gpUIIndexData[nPos + 1];
                if (nUserInfoPos2 == 0xFFFF)
                {
                        return gpUserInfoEnrollData[nUserInfoPos1].ID + 1;
                }
                if (gpUserInfoEnrollData[nUserInfoPos2].ID - gpUserInfoEnrollData[nUserInfoPos1].ID > 1)
                {
                    break;
                }
                    //break;
                nPos++;
        }

        qDebug() << "nUserInfoPos1 ==" << nUserInfoPos1;
        return gpUserInfoEnrollData[nUserInfoPos1].ID + 1;
}

//////////////////////////////////////////////////////////////////////////
UINT64 Db_GetCandidateID(BOOL bNew, UINT64 nIDCandidate)
{
        if (bNew)
        {
                UINT64 nID;
                nID = Db_GetUnusedID(nIDCandidate);
                if (nID > 999999999)
                        nID = Db_GetUnusedID(1);
                return nID;
        }
        else
                return Db_GetUsedID(nIDCandidate);
}

//////////////////////////////////////////////////////////////////////////
int Db_GetUserCount(void)
{
        return DbUserInfoGetCount();
}

//////////////////////////////////////////////////////////////////////////
int Db_GetUserVoiceCount(void)
{
        int i;
        int count = 0;

        //if (!SDCARD_MOUNT())
                //return 0;

        for (i=0; i<dbLicense.nMaxEnrollCount; i++)
        {
                if (DbUserInfoHasVoice(&gpUserInfoEnrollData[i]))
                        count++;
        }
        return count;
}

//////////////////////////////////////////////////////////////////////////
int Db_GetUserPhotoCount(void)
{
        int i;
        int count = 0;

        //if (!SDCARD_MOUNT())
                //return 0;

        for (i=0; i<dbLicense.nMaxEnrollCount; i++)
        {
                if (DbUserInfoHasPhoto(&gpUserInfoEnrollData[i]))
                        count++;
        }
        return count;
}

//////////////////////////////////////////////////////////////////////////
int Db_GetManagerCount(BYTE byMgr)
{
        return DbUserInfoGetManagerCount(byMgr);
}

//////////////////////////////////////////////////////////////////////////
int Db_GetManagerCountTotal(void)
{
        return Db_GetManagerCount(PRIV_MGR) + Db_GetManagerCount(PRIV_SMGR);
}

//////////////////////////////////////////////////////////////////////////
int Db_GetManagerCountMax(void)
{
        return MAX(Db_GetManagerCount(PRIV_MGR), Db_GetManagerCount(PRIV_SMGR));
}

//////////////////////////////////////////////////////////////////////////
int Db_GetEnrolledIDMask(UINT64 nID)
{
        int nRet = 0;
        USER_INFO* pUserInfo = (USER_INFO*)DbUserInfoGetPointer(nID);

        if (pUserInfo)
        {
                for (int i=BACKUP_START; i<=BACKUP_END; i++)
                {
                        if (DbUserInfoFlagEnrollStatusGet(pUserInfo, i))
                                nRet += (1 << i);
                }
        }
//_lExit:
        return nRet;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
//////////////////////////////////////////////////////////////////////////
BOOL Db_LoadAllData(BOOL bSetupReadStatus)
{
    BOOL bRet = TRUE, bRet2;

    bRet2 = DbUIIndexLoad();
    bRet = bRet && bRet2;
    qDebug("Db_LoadAllData::DbUIIndexLoad:%d\r\n", bRet2);

        //bRet2 = DbFPIndexLoad();bRet = bRet && bRet2; /*printf("UIIndexLoad: %d\r\n", bRet2);*/ //if (!bSetupReadStatus) DbFPIndexDeleteAll();
        //bRet2 = DbAntipassLoad();bRet= bRet && bRet2; /*printf("AntipassLoad:%d\r\n", bRet2);*/

        //__flashread_type = FLASHREAD_FP;
        //bRet2 = DbFpLoad();		bRet = bRet && bRet2; /*printf("FPLoad: %d\r\n", bRet2);*/
    //__flashread_type = FLASHREAD_USERINFO;
    bRet2 = DbUserInfoLoad();
    bRet=bRet && bRet2;
    qDebug("Db_LoadAllData::UserInfoLoad:%d\r\n", bRet2);

/*	__flashread_type = FLASHREAD_USERINFO;
        bRet2 = DbUserTimeLoad(); bRet=bRet && bRet2; //printf("UserInfoLoad: %d\r\n", bRet2);

        __flashread_type = FLASHREAD_USERINFO;
        bRet2 = DbFpUploadDataLoad(); bRet=bRet && bRet2; //printf("UserInfoLoad: %d\r\n", bRet2);
        bRet2 = DbUserIdHeadListLoad(); bRet=bRet && bRet2;

        __flashread_type = FLASHREAD_SLOG;
        bRet2 = DbSLogLoad();	bRet = bRet && bRet2; //printf("SLog: %d\r\n", bRet2);

        __flashread_type = FLASHREAD_GLOG;
        bRet2 = DbGLogLoad();	bRet = bRet && bRet2; //printf("GLog: %d\r\n", bRet2);
        if (!__DB_FIST_LOAD)
        {
                uiLcdProgressEnd();
                g_bProgress = FALSE;
        }
        if (__DB_FIST_LOAD)
        {
                __DB_FIST_LOAD = FALSE;
                uiLcdProgress1(30);
                DelayMiliSecond(50);
                uiLcdProgress1(100);
        }

        bRet2 = DbPartLoad();	bRet = bRet && bRet2; //printf("Part: %d\r\n", bRet2);

        uiLcdProgressDlgExit();
*/
    if (!bSetupReadStatus && (__DB_BACKUPREAD_LICENSE_STAT == SETUPREAD_CSUMERROR || __DB_BACKUPREAD_SETUP_STAT == SETUPREAD_CSUMERROR))
        //uiLcdMessageBox(UI_MSG_ERROR, (char*)"System setting was damaged, so all of them will be reset!", 10000);
         qDebug() << "System setting was damaged, so all of them will be reset!";
    return bRet;
}


BOOL Db_DeleteAllEnrollData()
{
 /*       BOOL bRet = TRUE, bRet2;

        bRet2 = RMDIR(SDCARD_MOUNTPOINT PATH_USER_PHOTO); //bRet = bRet && bRet2;
        bRet2 = RMDIR(SDCARD_MOUNTPOINT PATH_USER_VOICE); //bRet = bRet && bRet2;

        bRet2 = DbAntipassDeleteAll();	bRet = bRet && bRet2;
        bRet2 = DbFpDeleteAll();		bRet = bRet && bRet2;
        bRet2 = DbFPIndexDeleteAll();	bRet = bRet && bRet2;
        bRet2 = DbUIIndexDeleteAll();	bRet = bRet && bRet2;
        bRet2 = DbUserInfoDeleteAll();	bRet = bRet && bRet2;
        bRet2 = DbUserTimeDeleteAll();	bRet = bRet && bRet2;
//	bRet2 = DbUserIdHeadListDeleteAll();	bRet = bRet && bRet2;

        //part free

        return bRet;*/
}

BOOL Db_DeleteAllLogData()
{
        BOOL bRet = TRUE, bRet2;

        bRet2 = DbSLogDeleteAll(); bRet = bRet && bRet2;
        bRet2 = DbGLogDeleteAll(); bRet = bRet && bRet2;

        return bRet;
}

void Db_FreeAllData(void)
{
/*//	FlashWriteWithBackupPolling(TRUE);

        if (gpAntipassData)			{ FREE(gpAntipassData); gpAntipassData = NULL; }
        if (gpIndexData)			{ SB_FP_INDEXDBFREE(); gpIndexData = NULL; }
        //if (gpFingerEnrollData)		{ SB_FP_FPDBFREE(); gpFingerEnrollData = NULL; }
        if (gpUIIndexData)			{ FREE(gpUIIndexData); gpUIIndexData = NULL; }
        if (gpUserInfoEnrollData)	{ FREE(gpUserInfoEnrollData); gpUserInfoEnrollData = NULL; }
*/}

COM_USER_INFO	allUserFlag[MAX_USER_COUNT];

int	GetAllUserID(void)
{
        int i, nCount = 0;

        for (i = 0; i<dbLicense.nMaxEnrollCount; i++)
        {
                if (gpUserInfoEnrollData[i].ID) {
                        allUserFlag[nCount].dwID = (DWORD)gpUserInfoEnrollData[i].ID;
                        allUserFlag[nCount].flag = gpUserInfoEnrollData[i].FLAG;
                        nCount++;
                }
        }
        return nCount;
}
////1.34
BOOL DbSetupTotalWriteOnly( void)
{
        int i;
        int fd;
        BYTE* pby;
        DWORD* pdw;
        DWORD dwCheckSum = FLASH_CHECKSUM_SIGN;
        BOOL bNetworkSetting = FALSE;
        BOOL bRet = TRUE;

        fd = open(FLASH_SETUP_FILENAME, O_RDWR | O_CREAT,777);
        if (fd == INVALID_HANDLE_VALUE)
                return FALSE;

        pby = (BYTE*)malloc(FLASH_SETUP_SIZE); pdw = (DWORD*)pby;
        if (pby == NULL)
        {
                bRet = FALSE;
                goto _lExit;
        }

        memset(pby, 0, FLASH_SETUP_SIZE);
        memcpy(pby, &dbSetupTotal, sizeof(DBSETUP_TOTAL));

        for (i=0; i<(FLASH_SETUP_SIZE - 4)/4; i++)
        {
                pdw++;
                dwCheckSum += *pdw;
        }

        *(DWORD*)pby = dwCheckSum;

        if (write(fd, pby, FLASH_SETUP_SIZE) != FLASH_SETUP_SIZE)
                bRet = FALSE;

        if (!__DB_FIST_LOAD)
                bRet = bRet && DbBackupSetupWrite(pby);

_lExit:
        if (pby)
                FREE(pby);

        FD_CLOSE(fd);
        return bRet;
}
////1.34

////1.34
//////////////////////////////////////////////////////////////////////////
BOOL DbGLogSetReadPosOnly(int nPos)
{
        BOOL bRotate = (DbGLogCountAll() + 1 == dbLicense.nGlogMaxCount);

        if (bRotate)
                dbSetupTotal.setNoMenu.nReadALogPos = (__GLOG_POS + 1 + nPos) % dbLicense.nGlogMaxCount;
        else
        {
                if (nPos > __GLOG_POS)
                        nPos = __GLOG_POS;
                dbSetupTotal.setNoMenu.nReadALogPos = nPos;
        }
        return DbSetupTotalWriteOnly();
}
////1.34
////1.34
BOOL DbSLogSetReadPosOnly(int nPos)
{
        BOOL bRotate = (DbSLogCountAll() + 1 == dbLicense.nSlogMaxCount);

        if (bRotate)
                dbSetupTotal.setNoMenu.nReadMLogPos = (__SLOG_POS + 1 + nPos) % dbLicense.nSlogMaxCount;
        else
        {
                if (nPos > __SLOG_POS)
                        nPos = __SLOG_POS;
                dbSetupTotal.setNoMenu.nReadMLogPos = nPos;
        }
        return DbSetupTotalWriteOnly();
}

DWORD	DbGLogCountGetByTimeAllSearch_and_byid( u32 fromsecond, u32 tosecond,u64 id)
{
        int fd;
      DWORD i;
        ALOG_INFO logtemp;
        int pos;
        int result = 0;
        DWORD count,SearchCount;
        //   	int nYear,  nMonth,  nDay, nHour, nMinute,  nSecond;
        count = DbGLogCountAll();
        SearchCount=0;
        fd = open(FLASH_GLOG_FILENAME, O_RDWR | O_CREAT,777);
        if (fd == INVALID_HANDLE_VALUE)
                return 0;
    for(i=0;i<count;i++)
    {
                pos = i * sizeof(ALOG_INFO);
                result = pread(fd, &logtemp, (size_t)sizeof(ALOG_INFO), (off_t)pos);

                if (result == 0) //EOF
                {
                        break;
                }
                else if (result == -1) //ERROR
                        memset(&logtemp, 0, sizeof(ALOG_INFO));
                if(logtemp.dwSeconds>fromsecond && logtemp.dwSeconds<tosecond && (logtemp.nID == id))
                {
                      SearchCount++;
                }
    }
        FD_CLOSE(fd);
        return (SearchCount);
}

int	DbGLogGetByTime_and_byID(ALOG_INFO *pLogBuffer,int from,int to, u32 fromsecond, u32 tosecond,u64 id)
{
   /*     int fd;
        //int nResult, nResult1;
        int nCount;
        //BOOL bRet = TRUE;
        //BOOL bRotate = (DbGLogCountAll() + 1 == dbLicense.nGlogMaxCount);
        int i;
        ALOG_INFO logtemp;
        int pos;
        int result = 0;
        ALOG_INFO *buf =pLogBuffer;

        //if (bRotate)
        //	from = (from + __GLOG_POS + 1) % dbLicense.nGlogMaxCount;

        fd = open(FLASH_GLOG_FILENAME, O_RDWR | O_CREAT);
        if (fd == INVALID_HANDLE_VALUE)
                return 0;

        //xprintf("DbGLogGetByTime\r\n");

        //if(pLogBuffer)
           //memset(pLogBuffer, 0, sizeof(ALOG_INFO) * (to-from));
    nCount=0;
    for(i=from;i<to;i++)
    {
                pos = i * sizeof(ALOG_INFO);
                result = pread(fd, &logtemp, (size_t)sizeof(ALOG_INFO), (off_t)pos);

                if (result == 0) //EOF
                {
                        xprintf("DbGLogGetByTime.result = pread\r\n");
                        break;
                }
                else if (result == -1) //ERROR
                        memset(&logtemp, 0, sizeof(ALOG_INFO));
                xprintf("logtemp.nID=%d \r\n", logtemp.nID);
                xprintf("fromsecond=%d \r\n", fromsecond);
                xprintf("logtemp.dwSeconds=%d \r\n", logtemp.dwSeconds);
                xprintf("tosecond=%d \r\n", tosecond);

                if((logtemp.dwSeconds>=fromsecond) && (logtemp.dwSeconds<=tosecond) && (logtemp.nID == id))//改动地方
                {
                        //if(buf)
                        //{
                                xprintf("nID=%d dwSeconds=%d byAction=%d \r\n", logtemp.nID,logtemp.dwSeconds,logtemp.byAction);
                                memcpy(buf,&logtemp,sizeof(ALOG_INFO));
                                buf ++;
                        //}
                        nCount++;
                }
    }

//_lExit:
        FD_CLOSE(fd);
        return (nCount);*/
}

int DbGLogGetByindex(ALOG_INFO *pLogBuffer,int from,int to)
{
 /*       int fd;
        //int nResult, nResult1;
        int nCount;
        //BOOL bRet = TRUE;
        //BOOL bRotate = (DbGLogCountAll() + 1 == dbLicense.nGlogMaxCount);
        int i;
        ALOG_INFO logtemp;
        int pos;
        int result = 0;
        ALOG_INFO *buf =pLogBuffer;

        //if (bRotate)
        //	from = (from + __GLOG_POS + 1) % dbLicense.nGlogMaxCount;

        fd = open(FLASH_GLOG_FILENAME, O_RDWR | O_CREAT);
        if (fd == INVALID_HANDLE_VALUE)
                return 0;

        //xprintf("DbGLogGetByindex\r\n");

        if(pLogBuffer)
           memset(pLogBuffer, 0, sizeof(ALOG_INFO) * (to-from));
        nCount=0;
        for(i=from;i<to;i++)
        {
                pos = i * sizeof(ALOG_INFO);
                result = pread(fd, &logtemp, (size_t)sizeof(ALOG_INFO), (off_t)pos);

                if (result == 0) //EOF
                {
                        xprintf("DbGLogGetByTime.result = pread\r\n");
                        break;
                }
                else if (result == -1) //ERROR
                        memset(&logtemp, 0, sizeof(ALOG_INFO));
                xprintf("logtemp.dwSeconds=%d \r\n", logtemp.dwSeconds);
                //if(logtemp.dwSeconds>=fromsecond && logtemp.dwSeconds<=tosecond && logtemp.nID == id)//改动地方
                //{
                if(buf)
                {
                         xprintf("nID=%d dwSeconds=%d byAction=%d \r\n", logtemp.nID,logtemp.dwSeconds,logtemp.byAction);
                         memcpy(buf,&logtemp,sizeof(ALOG_INFO));
                         buf ++;
                }
                  nCount++;
                //}
        }

//_lExit:
        FD_CLOSE(fd);
        return (nCount);*/
}


