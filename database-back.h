#ifndef DATABASE_H
#define DATABASE_H

//#include "../global.h"
typedef char				CHAR;
typedef short				SHORT;
typedef int				INT;

typedef unsigned char			BYTE, u8, uchar;
typedef unsigned char			BOOL;
typedef unsigned short			WORD, UINT16,u16;
typedef unsigned int			DWORD, UINT32, u32;
//typedef long				LONG;
typedef unsigned long long		UINT64, u64;

#define TRUE					(1)
#define FALSE					(0)
#define NULL					(0)

//////////////////////////////////////////////////////////////////////////
#define FLASH_SECTOR_SIZE		0x4000
#define MAKE_SECTOR_SIZE(x)		(((x) + FLASH_SECTOR_SIZE - 1) / FLASH_SECTOR_SIZE * FLASH_SECTOR_SIZE)


#define ENROLLDATA_MOUNTPOINT           "."
#define USB_MOUNTPOINT			"/mnt/ext1"
#define SDCARD_MOUNTPOINT		"/mnt/ext2"

#define FLASH_LICENSE_SIZE		( FLASH_SECTOR_SIZE )
#define FLASH_LICENSE_FILENAME          (ENROLLDATA_MOUNTPOINT "/LICENSE.set")
#define FLASH_LICENSE_BACKUP            (ENROLLDATA_MOUNTPOINT "/LICENSE-bak.set")
#define FLASH_SETUP_SIZE		(FLASH_SECTOR_SIZE)
#define FLASH_SETUP_FILENAME            (ENROLLDATA_MOUNTPOINT "/SETUP.set")
#define FLASH_SETUP_BACKUP		(ENROLLDATA_MOUNTPOINT "/SETUP-bak.set")
#define FLASH_UI_INDEX_SIZE		( FLASH_SECTOR_SIZE * 2 )
#define FLASH_UI_INDEX_FILENAME         (ENROLLDATA_MOUNTPOINT "/UI_INDEX.dat")
//#define FLASH_FP_INDEX_SIZE		( FLASH_SECTOR_SIZE )
#define FLASH_FP_INDEX_FILENAME         (ENROLLDATA_MOUNTPOINT "/FP_INDEX.dat")
#define FLASH_ANTIPASS_SIZE		( FLASH_SECTOR_SIZE )
#define FLASH_ANTIPASS_FILENAME         (ENROLLDATA_MOUNTPOINT "/ANTIPASS.dat")

#define FLASH_USERINFO_FILENAME         (ENROLLDATA_MOUNTPOINT "/USERINFO.dat")
#define FLASH_FP_FILENAME		(ENROLLDATA_MOUNTPOINT "/FP.dat")
#define FLASH_SLOG_FILENAME		(ENROLLDATA_MOUNTPOINT "/SLOG.dat")
#define FLASH_GLOG_FILENAME		(ENROLLDATA_MOUNTPOINT "/GLOG.dat")
#define FLASH_PART_FILENAME		(ENROLLDATA_MOUNTPOINT "/part.txt")
#define FLASH_USERTIME_FILENAME         (ENROLLDATA_MOUNTPOINT "/USERTIME.dat")
#define FLASH_IDHEADLIST_FILENAME	(ENROLLDATA_MOUNTPOINT "/IdHeadList.dat")
#define FLASH_FPUPLOAD_FILENAME         (ENROLLDATA_MOUNTPOINT "/fpupload.dat")

#define MAX_USER_COUNT			5000   //5000-10000
#define MAX_SLOG_COUNT			5000
#define MAX_GLOG_COUNT			100000

#define FLASH_CHECKSUM_SIGN		0x20131212//0x20100115

#define     USERNAME_LENGTH     12

typedef struct {
        DWORD	mENROLL		:24;		// (2bit(used_bit, duress_bit) per FP*10, PWD, CARD)
        DWORD	byUseGroupTZ    :1;		// use group's timezone
        DWORD	byUseGroupVM    :1;		// use group's verify mode
        DWORD	byPhotoExist    :1;		// 1 && sdcard exist => photo exist
        DWORD	byVoiceExist    :1;		// 1 && sdcard exist => voice exist
        DWORD	byMgr		:3;		// privilege, 001:User, 110:Manager, 111:SManager
        DWORD	bEnable		:1;		// enable/disable flag
} ALL_FLAG;

typedef union {
    DWORD	dwALL;
    ALL_FLAG	members;
}DATA_FLAG;

typedef struct _user_info
{
    UINT64	ID;		//8
    DATA_FLAG   FLAG;		//4
    DWORD	FP;		//4		1 ~ MaxEnrollCount
    DWORD	PWD;		//4
    DWORD	CARD;		//4
    BYTE	UserTZ[3];	//3
    BYTE	TIMEGROUP;	//1, 1 ~ 5
    BYTE	VERIFYMODE;	//1
    BYTE	PART;		//1
    BYTE	RES[2];		//2
    WORD	NAME[USERNAME_LENGTH]; //24
} USER_INFO;			//Total = 56

typedef struct _dbsetup_system
{
        int		nTimeFormat;			//4
        int		nDateFormat;			//4
        int		nLanguage;				//4
        int		nVolume;				//4

} DBSETUP_SYSTEM;					//Total = 164

//setup数据结构
typedef struct
{
    DWORD		dwCheckSum;	//4
    //DBSETUP_NOMENU	setNoMenu;	//64
    DBSETUP_SYSTEM	setSystem;	//156
    //DBSETUP_TIMEZONE	setTimezone;    //3108
} DBSETUP_TOTAL;			//Total = 3332

typedef struct _dblicense
{
        DWORD	dwCheckSum;				//4
        DWORD	dwBuildNumber;			//4
        DWORD   dwSystemCheck;          //4
        CHAR	szFirstDate[32];		//32
        CHAR	szSerialNumber[32];		//32
        CHAR	szTradeMark[32];		//32
        CHAR	szProductName[32];		//32
        CHAR	szProductType[32];		//32
        CHAR	szEngineVersion[32];	//32
        CHAR	szFirmwareVersion[32];	//32
        INT	nMaxEnrollCount;		//4
        INT	nBackupNumber;			//4
        BOOL	bUseEthernet;			//1
        BOOL	bUseUSB;				//1
        BOOL	bUseCard;				//1
        BOOL	bUsePOE;				//1
        BOOL	bUseWebServer;			//1
        BOOL	bUseRS232;				//1
        BOOL	bUseMP3;				//1
        BOOL	bUseWiegand;			//1
        BOOL	bUseAlarmFunction;		//1
        BOOL	bUseACFunction;			//1
        BOOL	bLockControl;			//1
        BOOL	bUseCamera;				//1
        INT		nCMOS;					//4
        BYTE	byMACaddr[8];			//8
        BYTE    byTcpipMode;            //1

        DWORD	dwFlashSizeUserInfo;	//4
        DWORD	dwFlashSizeFP;			//4

        INT	nSlogMaxCount;			//4
        DWORD	dwFlashSizeSlog;		//4
        INT	nGlogMaxCount;			//4
        DWORD	dwFlashSizeGlog;

        BOOL      bOnLineEnroll;
} DBLICENSE;						//Total = 140


BOOL    DbSetupTotalRead(BOOL bBackupCheck = TRUE);
BOOL    DbSetupTotalWrite(BOOL bChangeTheme = TRUE);
int     DbBackupSetupWrite(BYTE *pby);
int     DbBackupSetupRead(BYTE *pby);



BOOL    Db_LoadAllData(BOOL bSetupReadStatus);


//BOOL	_Db_ReadFpDataFromFlash(int fd, void* pDst, int from, int to, BYTE byEmpty, int* pIndexDBChanged, int nBaseAddr = 0);
BOOL	_Db_FlashRead(int fd, void* pDst, int from, int to, int nSizeof, BYTE byEmpty, char *szTitle, int *pResult = NULL, int nBaseAddr = 0);
//BOOL	_Db_FlashWrite(int fd, void* pSrc, int from, int to, int nSizeof, char *szTitle, int nBaseAddr = 0);
//BOOL	_Db_FWWriteToFlash1(HFILE hFile, void* pSrc, int nSize);
//BOOL	_Db_FWWriteToFlash(BYTE* pRomImage, int nFileSize);

#endif // DATABASE_H
