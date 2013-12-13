#include "Database.h"
#include "global.h"
#include <QDebug>

enum
{
    SETUPREAD_SUCCESS,
    SETUPREAD_NOEXIST,
    SETUPREAD_CSUMERROR,
};

static int __DB_BACKUPREAD_LICENSE_STAT = SETUPREAD_SUCCESS;
static int __DB_BACKUPREAD_SETUP_STAT = SETUPREAD_SUCCESS;
static BOOL __DB_FIST_LOAD = TRUE;
static BOOL SetupTotaldataDefault_flag=0;

int DbBackupLicenseRead(BYTE *pby)
{
        int i;
        int fd;
        DWORD* pdw = (DWORD*)pby;
        DWORD dwCheckSum = FLASH_CHECKSUM_SIGN;

        fd = open(FLASH_LICENSE_BACKUP, O_RDONLY);
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
        }

        if (dwCheckSum != *(DWORD*)pby || SetupTotaldataDefault_flag) //To Default, in case of License & LicenseBackup damaged or first booting !
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

// 		if (dbLicense.nMaxEnrollCount != (int)gFpMaximum)
// 			dwCheckSum++;
        }



// 	printf("dbLicense.bUseEthernet        = %d\r\n", dbLicense.bUseEthernet);
// 	printf("dbLicense.bUseUSB             = %d\r\n", dbLicense.bUseUSB);
// 	printf("dbLicense.bUseCard            = %d\r\n", dbLicense.bUseCard);
// 	printf("dbLicense.bUsePOE             = %d\r\n", dbLicense.bUsePOE);
// 	printf("dbLicense.bUseWebServer       = %d\r\n", dbLicense.bUseWebServer);
// 	printf("dbLicense.bUseRS232           = %d\r\n", dbLicense.bUseRS232);
// 	printf("dbLicense.bUseMP3             = %d\r\n", dbLicense.bUseMP3);
// 	printf("dbLicense.bUseWiegand         = %d\r\n", dbLicense.bUseWiegand);
// 	printf("dbLicense.bUseAlarmFunction   = %d\r\n", dbLicense.bUseAlarmFunction);
// 	printf("dbLicense.bLockControl        = %d\r\n", dbLicense.bLockControl);
// 	printf("dbLicense.nMaxEnrollCount     = %d\r\n", dbLicense.nMaxEnrollCount);
// 	printf("dbLicense.pFlashStartUserInfo = %p\r\n", dbLicense.pFlashStartUserInfo);
// 	printf("dbLicense.pFlashStartFP       = %p\r\n", dbLicense.pFlashStartFP);
// 	printf("dbLicense.dwFlashSizeFP       = %p\r\n", dbLicense.dwFlashSizeFP);
// 	printf("dbLicense.pFlashStartSLOG     = %p\r\n", dbLicense.pFlashStartSlog);
// 	printf("dbLicense.dwFlashSizeSLOG     = %p\r\n", dbLicense.dwFlashSizeSlog);
// 	printf("dbLicense.nSlogMaxCount       = %d\r\n", dbLicense.nSlogMaxCount);
// 	printf("dbLicense.pFlashStartGLOG     = %p\r\n", dbLicense.pFlashStartGlog);
// 	printf("dbLicense.dwFlashSizeGLOG     = %p\r\n", dbLicense.dwFlashSizeGlog);
// 	printf("dbLicense.nGlogMaxCount       = %d\r\n", dbLicense.nGlogMaxCount);

_lExit:
        FREE(pby);
        FREE(pbyBackup);
        FD_CLOSE(fd);
        return bRet;
}


//备份setup读取
int DbBackupSetupRead(BYTE *pby)
{
        int i;
        int fd;
        DWORD* pdw = (DWORD*)pby;
        DWORD dwCheckSum = FLASH_CHECKSUM_SIGN;

        fd = open(FLASH_SETUP_BACKUP, O_RDONLY);
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

//对setup数据的读取
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
        qDebug() << "(dwCheckSum == *(DWORD*)pby) && (nBackupStatus != SETUPREAD_SUCCESS)";
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
        qDebug() << "(dwCheckSum != *(DWORD*)pby) && (nBackupStatus == SETUPREAD_SUCCESS)";
    }
    //都正常运行
    else if((dwCheckSum == *(DWORD*)pby) && (nBackupStatus == SETUPREAD_SUCCESS))
    {
        if (memcmp(pby, pbyBackup, FLASH_SETUP_SIZE))
            DbBackupSetupWrite(pby);
        qDebug() << "(dwCheckSum == *(DWORD*)pby) && (nBackupStatus == SETUPREAD_SUCCESS)";
    }
    else
    {
        qDebug() << "(dwCheckSum != *(DWORD*)pby) && (nBackupStatus != SETUPREAD_SUCCESS)";
    }
    //默认情况下设置的参数
    if (!bRet || (dwCheckSum != *(DWORD*)pby) || SetupTotaldataDefault_flag)//To Default
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

        qDebug() << "SetupTotaldataDefault_flag";

    }
    else
    {
        memcpy(&dbSetupTotal, pby, sizeof(DBSETUP_TOTAL));
        qDebug() << "SetupTotaldataDefault_flag1111111111111";
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

        //gpUserInfoEnrollData = (USER_INFO*)malloc(sizeof(USER_INFO) * dbLicense.nMaxEnrollCount);
        gpUserInfoEnrollData = (USER_INFO*)malloc(sizeof(USER_INFO) * 100);
        if (gpUserInfoEnrollData == NULL)
        {
                bRet = FALSE;
                goto _lExit;
        }

        //memset(gpUserInfoEnrollData, 0, sizeof(USER_INFO) * dbLicense.nMaxEnrollCount);
        memset(gpUserInfoEnrollData, 0, sizeof(USER_INFO) * 100);
        //bRet = _Db_FlashRead(fd, gpUserInfoEnrollData, 0, dbLicense.nMaxEnrollCount, sizeof(USER_INFO), 0, NULL);

_lExit:
        FD_CLOSE(fd);
        return bRet;
}
/************************************************************************/
/*                                                                      */
/************************************************************************/
//////////////////////////////////////////////////////////////////////////
BOOL Db_LoadAllData(BOOL bSetupReadStatus)
{
    BOOL bRet = TRUE, bRet2;

        //bRet2 = DbUIIndexLoad();bRet = bRet && bRet2; /*printf("UIIndexLoad: %d\r\n", bRet2);*/
        //bRet2 = DbFPIndexLoad();bRet = bRet && bRet2; /*printf("UIIndexLoad: %d\r\n", bRet2);*/ //if (!bSetupReadStatus) DbFPIndexDeleteAll();
        //bRet2 = DbAntipassLoad();bRet= bRet && bRet2; /*printf("AntipassLoad:%d\r\n", bRet2);*/

        //__flashread_type = FLASHREAD_FP;
        //bRet2 = DbFpLoad();		bRet = bRet && bRet2; /*printf("FPLoad: %d\r\n", bRet2);*/
    //__flashread_type = FLASHREAD_USERINFO;
    bRet2 = DbUserInfoLoad();
    bRet=bRet && bRet2;
    printf("UserInfoLoad: %d\r\n", bRet2);

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
