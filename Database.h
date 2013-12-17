#ifndef DATABASE_H
#define DATABASE_H

#include <QtCore/QString>
//#include "../global.h"
typedef int				HFILE;
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


#define FLASH_SECTOR_SIZE		0x4000
#define MAKE_SECTOR_SIZE(x)		(((x) + FLASH_SECTOR_SIZE - 1) / FLASH_SECTOR_SIZE * FLASH_SECTOR_SIZE)

//////////////////////////////////////////////////////////////////////////
#define ENROLLDATA_MOUNTPOINT	"."
#define USB_MOUNTPOINT			"/mnt/ext1"
#define SDCARD_MOUNTPOINT		"/mnt/ext2"

//////////////////////////////////////////////////////////////////////////
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


#define FLASH_MP3_BACKUP_DIRNAME            "/sb3000t/mp3"
#define FLASH_MP3_CURRENT_DIRNAME           (ENROLLDATA_MOUNTPOINT "/mp3")
#define FLASH_SCREENSAVER_BACKUP_DIRNAME    "/sb3000t/image"
#define FLASH_SCREENSAVER_CURRENT_DIRNAME   (ENROLLDATA_MOUNTPOINT "/screensaver")
#define FLASH_SCREENSAVER_MP3_FILENAME      "screensaver.mp3"
#define FLASH_SCREENSAVER_IMAGE_COUNT       6

#define PARTITION_DOWNLOADER	"/dev/mtd0"
#define PARTITION_KERNEL		"/dev/mtd1"
#define PARTITION_ROOTFS		"/dev/mtd2"
#define PARTITION_USER			"/dev/mtd3"

#define PATH_USER_PHOTO			"/user-photo"
#define PATH_PHOTO_LOG			"/photo-log"
#define PATH_USER_VOICE			"/user-voice"

#define GUI_RESOURCE_PATH		":/images/res/"

#define DB_ENROLLDATA_FILENAME	"ENROLLDB"
#define DB_SLOGDATA_FILENAME	"SLOG"
#define DB_GLOGDATA_FILENAME	"GLOG"


#define FLASH_CHECKSUM_SIGN		0x20100115
#define LNSC_FIRST_DATE			"2011.08.29"
//#define	LNSC_SERIAL				"SB3300-0003"//修改链接命令和上传验证信息
#define	LNSC_SERIAL				"SB3300-0004"//修复获取用户信息bug，20130130
#define LNSC_TRADEMARK			"COMET"	/*In SB3500ASETDlg.cpp, this string must be changed*/
#define LNSC_PRODUCTNAME		"E60P"
#define LNSC_PRODUCTTYPE		"TR"
#define LNSC_ENGINEVERSION		"SmackFinger3.0"
#if (CardType==1)  //ID卡
//#define LNSC_FIRMWAREVERSION	"SB3300-5K v1.35.1539.00"    //注意不要超过28bit,版本功能号第9,10位必须为1.  zwh 2010.10.14    xf 091106  E60=V1.0 E60B=V6.0
//#define LNSC_FIRMWAREVERSION	"SB3300-5K v1.35.1539.01"//2013.04.18修复兼容bug
//#define LNSC_FIRMWAREVERSION	"SB3300-5K v1.35.1540.00"
//#define LNSC_FIRMWAREVERSION	"SB3300-5K v1.35.1541.00"//升级到网络传输加密算法
//A表示考勤类型，SX表示375平台，
//#define LNSC_FIRMWAREVERSION	"Asx-v2.0.0.130428"//从这次版本开始使用新的版本管理方式
//#define LNSC_FIRMWAREVERSION	"Asx-v2.1.0.130428"//修复id卡注册上传死机问题
//#define LNSC_FIRMWAREVERSION	"Asx-v2.1.0.130506"//增加卡的注册
//#define LNSC_FIRMWAREVERSION	"Asx-v2.1.0.130507"//增加设置mac地址命令
#define LNSC_FIRMWAREVERSION	"Asx-v2.1.0.130510"//增加姓名下载

//只使用ID卡片的开发版本记录
//#define LNSC_FIRMWAREVERSION	"Asx-v2.9.0.130509"//只ID读卡的功能

#elif (CardType==2)  //IC卡
//#define LNSC_FIRMWAREVERSION	"SB3300-5K v1.35.1536.01"    //注意不要超过28bit,版本功能号第9,10位必须为1.  zwh 2010.10.14    xf 091106  E60=V1.0 E60B=V6.0
#define LNSC_FIRMWAREVERSION	"Asx-v2.8.0.130510" //只IC读卡的功能
#endif

#define LNSC_HARDWAREVERSION	"v1.3"           //xf 091106

#define TEXTCODEC				"utf8"

#define MAGIC_DOWNLOADER		0xEA000077
#define MAGIC_ZIMAGE			0xE1A00000
#define MAGIC_ROOTFS			0x28CD3D45
#define MAGIC_SPLASH			0x544F4F42
#define MAGIC_UNICODE			0xFEFF
#define MAGIC_UNICODEBIG		0xFFFE
#define MAGIC_UTF8				0xBFBBEF
#define MAGIC_SMSG				0x534D5347
#define MAGIC_ENROLLDB			0x52454744
#define MAGIC_SLOG				0x534C4F47
#define MAGIC_GLOG				0x474C4F47

#define O_UNICODE				0x10000000
#define O_UNICODEBIG			0x20000000
#define O_UTF8					0x40000000
#define O_CUSTOMMASK			~(O_UNICODE | O_UNICODEBIG | O_UTF8)

//////////////////////////////////////////////////////////////////////////
#define SB3000_TIMEZONE_LEVEL	1	//1:SB3500A, 2:ARM150x
#define SB3000_USERVERIFY_LEVEL	1	//1:SB3500A, 2:ARM150x

//////////////////////////////////////////////////////////////////////////
#define DWORD_ALIGN(_x_)		(((_x_) + 3) / 4 * 4)
#define DOWNLOADER_IMAGE_SIZE	(640  * 1024)
#define KERNEL_IMAGE_SIZE		(g_params.nKernelSize)
#define ROOTFS_IMAGE_SIZE		(g_params.nRootfsSize)
#define ROM_IMAGE_SIZE			(g_params.nDownloaderSize + g_params.nKernelSize + g_params.nRootfsSize)
#define OFFSET_PARAM_INFO		(640 * 1024)
#define OFFSET_SPLASH			(656 * 1024)

//////////////////////////////////////////////////////////////////////////
#define MAX_USER_COUNT			5000   //5000-10000
#define MAX_SLOG_COUNT			5000

//#define MAX_USER_COUNT			2000   //loveywm 2012.09.11
//#define MAX_SLOG_COUNT			2000   //loveywm 2012.09.11
#define MAX_GLOG_COUNT			100000
#define MAX_ENROLL_BACKUP_NUM	10
#define MAX_ENROLL_MANAGERS		10

#define IDNUMBER_LENGTH		8   //zwh 2010.10.26
#define USERNAME_LENGTH		12
#define DEFAULT_PASSWORD	0x888888
#define SMANAGER_PWD_LEN	6
#define PWD_LENTH			6

#define PRIV_USER		1
#define PRIV_MGR		6
#define PRIV_SMGR		7
#define PRIV_INDEX(_v_)	(((_v_) & 0x03) - 1)

#define TZNAME_LENGTH				16
#define ACCESS_TIME_SET_COUNT		50
#define ACCESS_USER_GROUP_COUNT		5
#define LOG_TZONE_COUNT				10
#define MULTI_IDENT_SET_COUNT		10

//only for highlevel timezone function
#define TIMEZONE_COUNT				32
#define TIMEGROUP_COUNT				32
#define TIMECOUNT_PER_TG			10
#define ACCESS_TIME_SET_COUNT_HIGH	32

#define BELL_INFO_COUNT				10
#define MSG_INFO_COUNT				10
#define MSG_LEN						60
#define EVENT_LENGTH				64

#define ILLEGAL_VERIFY_TIMEOUT		(3 * 60 * 1000)
#define LOGOUT_ALARM_TIMEOUT		(10* 1000)

#define KEY_BK 2

#define TCPIP_SERVER 0
#define TCPIP_CLIENT 1

typedef enum
{
        CMOSTYPE_PG0305,
        CMOSTYPE_HV7131R,
}T_CMOSTYPE;

typedef enum
{
        BACKUP_START,
        BACKUP_FINGER = BACKUP_START,
        BACKUP_FINGER0 = BACKUP_FINGER,
        BACKUP_FINGER1,
        BACKUP_FINGER2,
        BACKUP_FINGER3,
        BACKUP_FINGER4,
        BACKUP_FINGER5,
        BACKUP_FINGER6,
        BACKUP_FINGER7,
        BACKUP_FINGER8,
        BACKUP_FINGER9,
        BACKUP_PASSWORD,
        BACKUP_CARD,
        BACKUP_END = BACKUP_CARD,
        BACKUP_ALL = 15,
}T_BACKUP_NUMBER;

typedef enum
{//	Action								// Result
        SLOG_START,
        SLOG_TURNON = SLOG_START,			// 0:Manual, 1:Auto
        SLOG_TURNOFF,						// 0:Manual, 1:Auto
        SLOG_ILLEGALVERIFY_ALARM,			// 0
        SLOG_TAMPER_ALARM,					// 0
        SLOG_ENTERMENU,						// Privilege
        SLOG_SETTINGCHANGED,				// Changed Item(= UISTR_MENU_XXX)
        SLOG_BACKUPENROLL_FP,				// 0:Fail, 1:Success
        SLOG_SETPASSWORD,					// 0:Fail, 1:Success
        SLOG_ENROLL_CARD,					// 0:Fail, 1:Success
        SLOG_DELETE_USER,					// 0:Fail, 1:Success
        SLOG_DELETE_FP,						// 0:Fail, 1:Success
        SLOG_DELETE_PASSWORD,				// 0:Fail, 1:Success
        SLOG_DELETE_CARD,					// 0:Fail, 1:Success
        SLOG_DELETE_ALL,					// 0:Fail, 1:Success
        SLOG_CREATE_MFCARD,					// Reserved
        SLOG_ENROLL_MFCARD,					// Reserved
        SLOG_REGISTER_MFCARD,				// Reserved
        SLOG_DELETE_MF_REGIST,				// Reserved
        SLOG_CLEAR_MF,						// Reserved
        SLOG_ENROLLDATA2CARD,				// Reserved
        SLOG_CARD2MACHINE,					// Reserved
        SLOG_SETTIME,						// 0:Fail, 1:Date changed, 2:Time changed
        SLOG_RESTORE,						// 0:Fail, 1:Success
        SLOG_DELETE_ALL_LOG,				// 0x00:GLOG fail, 0x01:GLOG success, 0x80:SLOG fail, 0x81:SLOG success
        SLOG_REMOVE_MANAGERPRIV,			// 0:Fail, 1:Success
        SLOG_TIMEGROUP_SET,					// 0:Fail, 1:Success
        SLOG_USERTZ_SET,					// 0:Fail, 1:Success
        SLOG_TIMEZONE_SET,					// 0:Fail, 1:Success
        SLOG_LOCKGROUP_SET,					// 0:Fail, 1:Success
        SLOG_DOOROPEN,						// 0
        SLOG_ENROLL_USER,					// 0:Fail, 1:Success
        SLOG_NOCLOSE_ALARM,					// 0
        SLOG_ILGOPEN_ALARM,					// 0
        SLOG_DURESS_ALARM,					// 0

        SLOG_SET_ID,
        SLOG_SET_IP,
        SLOG_SET_MASK,
        SLOG_SET_GATEWAY,
        SLOG_SET_COMMPWD,
        SLOG_SET_DHCP,
        SLOG_SET_IPBACK,
        SLOG_SET_DNS,
        SLOG_SET_PORTBACK,

        SLOG_END = SLOG_SET_PORTBACK
}T_SLOG_TYPE; //When you add new SLOG or remove any, please refer to COM.cpp's _convSlog array !

typedef enum
{//	Event Type                        // Content
        EVENT_START,                      //
        EVENT_SLOG = EVENT_START,         // SLog Structure
        EVENT_GLOG,                       // Glog Structure
        EVENT_PRESS_FP,                   // No Param
        EVENT_VERIFY_SUCCESS,             // [0]=Verifymode, [1]=ID
        EVENT_VERIFY_FAIL,                // [0]=Verifymode
        EVENT_ALARM_ON,                   // [0]=AlarmType, [1]=ID
        EVENT_ALARM_OFF,                  // [0]=AlarmType, [1]=AlarmReleaseType, [2]=ID
        EVENT_HEART,                      // [0]=event_heart
        EVENT_ENROLL_GET_NAME,			//注册时获取姓名
        EVENT_ENROLL_GET_FINGER_DATA,		//注册返回指纹模板
        EVENT_VERIFY_GET_DATA,			//认证时获取相应数据
        EVENT_TIMESYN,
        EVENT_ENROLL_GET_FINGER_IMAGE,
        EVENT_GLOG_LONG,
        EVENT_END = EVENT_GLOG_LONG
}T_EVENT_TYPE;

typedef enum
{//	Release Type							// Param
        ALARMRELEASE_START,						//
        ALARMRELEASE_AUTO = ALARMRELEASE_START,	// No
        ALARMRELEASE_USER,						// User ID
        ALARMRELEASE_MANAGER,					// Manager ID. If super manager(id=0), this is 0
        ALARMRELEASE_OCX,						// No
        ALARMRELEASE_END = ALARMRELEASE_MANAGER	//
}T_ALARMRELEASE_TYPE;

typedef enum
{
        BAUDRATE_START,
        BAUDRATE_9600 = BAUDRATE_START,
        BAUDRATE_19200,
        BAUDRATE_38400,
        BAUDRATE_57600,
        BAUDRATE_115200,
        BAUDRATE_END = BAUDRATE_115200
}T_BAUDRATE;

typedef enum
{
        NETSPEED_10MBPS,
        NETSPEED_100MBPS,
}T_NETSPEED;

typedef enum
{
        THEME_1,
        THEME_2,
        THEME_3
}T_THEME;

typedef enum
{
        WIEGAND_26,
        WIEGAND_34,
        WIEGAND_CUSTOM
}T_WIEGANDFORMAT;

typedef enum
{
        DOORSENSOR_TYPE_START,
        DOORSENSOR_TYPE_NONE = DOORSENSOR_TYPE_START,
        DOORSENSOR_TYPE_OPEN,
        DOORSENSOR_TYPE_CLOSE,
        DOORSENSOR_TYPE_END = DOORSENSOR_TYPE_CLOSE
}T_DOORSENSOR_TYPE;

typedef enum
{
        TR_START,
        TR_DUTYNO = TR_START,
    TR_DUTYON,
        TR_DUTYOFF,
        TR_END = TR_DUTYOFF,
        TR_OVERTIMEON,
        TR_OVERTIMEOFF,
        TR_GOOUTON,
        TR_GOOUTOFF,
        TR_IN,
        TR_OUT,
        /*TR_END = TR_OUT,*/
        FUNC_LOGVIEW,
        FUNC_BELL,
        FUNC_ALARM,
        FUNC_SYSINFO
}T_TR_STATUS;

typedef enum
{
        SMSG_START,
        SMSG_ALL = SMSG_START,
        SMSG_USER,
        SMSG_GROUP,
        SMSG_END = SMSG_GROUP
}T_SMSG_TYPE;

typedef enum
{
        VM_START,
        VM_NONE = VM_START,
        VM_ANY = VM_START,
        VM_FP = 1,
        VM_IDPW = 2,
        VM_RF = 3,
        VM_IDFP = 4,
        VM_RFFP = 33,
        VM_RFPW = 34,
        VM_FPPW = 35,
        VM_FPRFPW = 36,
        VM_END = VM_FPRFPW
}T_VERIFY_MODE;

#define MAX_SOUND_COUNT		50
typedef enum
{
        SOUND_START,
        SOUND_DIGIT0 = SOUND_START,
        SOUND_DIGIT1,
        SOUND_DIGIT2,
        SOUND_DIGIT3,
        SOUND_DIGIT4,
        SOUND_DIGIT5,
        SOUND_DIGIT6,
        SOUND_DIGIT7,
        SOUND_DIGIT8,
        SOUND_DIGIT9,
        SOUND_TURNON,
        SOUND_TURNOFF,
        SOUND_PRESSFINGER_1,
        SOUND_PRESSFINGER_2,
        SOUND_PRESSFINGER_3,
        SOUND_TAKEOFF_FP,
        SOUND_PRESSFP_RETRY,
        SOUND_FPENROLL_SUCCESS,
        SOUND_FPENROLL_FAIL,
        SOUND_FPDOUBLED,
        SOUND_INPUT_PWD,
        SOUND_PWD_ERROR,
        SOUND_INPUT_CARD,
        SOUND_CARDDOUBLED_RETRY,
        SOUND_CARDENROLL_SUCCESS,
        SOUND_TALK_YOURNAME,
        SOUND_VOICERECORD_SUCCESS,
        SOUND_VOICERECORD_RETRY,
        SOUND_PREPARE_FOR_PHOTO,
        SOUND_PHOTO_SUCCESS,
        SOUND_CAMERA_TONE,
        SOUND_KEYTONES,
        SOUND_MENUSELECT,
        SOUND_ENTERMENU,
        SOUND_VERIFY_SUCCESS,
        SOUND_VERIFY_FAIL,
        SOUND_ERROR,
        SOUND_QUESTION,
        SOUND_OK,
        SOUND_BELL1,
        SOUND_BELL2,
        SOUND_BELL3,
        SOUND_BELL4,
        SOUND_BELL5,
        SOUND_END = SOUND_BELL5,
        APLUS_OK,
        APLUS_REVERIFY,
}T_SOUND_TYPE;

typedef enum
{
        ANTIPASS_START,
        ANTIPASS_NO = ANTIPASS_START,
        ANTIPASS_MASTER,
        ANTIPASS_SLAVE,
        ANTIPASS_END = ANTIPASS_SLAVE
}T_ANTIPASS_TYPE;

typedef enum
{
        ANTIPASSOUT_NONE = 0,
        ANTIPASSOUT_IN = 1,
        ANTIPASSOUT_OUT = 3
}T_ANTIPASSOUT_TYPE;

//////////////////////////////////////////////////////////////////////////

typedef struct _ENROLLDB_HDR
{
        DWORD dwUIIndexSize;
        DWORD dwFPIndexSize;
        DWORD dwUserInfoSize;
        DWORD dwFPSize;
} T_ENROLLDB_HDR;

typedef struct {
        DWORD	mENROLL		: 24;		// (2bit(used_bit, duress_bit) per FP*10, PWD, CARD)
        DWORD	byUseGroupTZ: 1;		// use group's timezone
        DWORD	byUseGroupVM: 1;		// use group's verify mode
        DWORD	byPhotoExist: 1;		// 1 && sdcard exist => photo exist
        DWORD	byVoiceExist: 1;		// 1 && sdcard exist => voice exist
        DWORD	byMgr		: 3;		// privilege, 001:User, 110:Manager, 111:SManager
        DWORD	bEnable		: 1;		// enable/disable flag
} ALL_FLAG;

typedef union {
        DWORD		dwALL;
        ALL_FLAG	members;
} DATA_FLAG;

typedef struct _user_info
{
        UINT64	ID;			//8
        DATA_FLAG FLAG;		//4
        DWORD	FP;			//4		1 ~ MaxEnrollCount
        DWORD	PWD;		//4
        DWORD	CARD;		//4
        BYTE	UserTZ[3];	//3
        BYTE	TIMEGROUP;	//1, 1 ~ 5
        BYTE	VERIFYMODE;	//1
        BYTE	PART;		//1
        BYTE	RES[2];		//2
        WORD	NAME[USERNAME_LENGTH]; //24
} USER_INFO;			//Total = 56

typedef struct _user_time
{
        DWORD	dwSeconds;	//4
        UINT64	nID;	//8
        //BYTE    vaild; //AA
} USER_TIME;			//Total = 12


#define UI_EXIST_ENROLL(_ui_, _n_)		(((_ui_)->FLAG.members.mENROLL & (1 << ((_n_) << 1))) >> ((_n_) << 1))
#define UI_SET_ENROLL(_ui_, _n_, _v_)	((_ui_)->FLAG.members.mENROLL = ((_ui_)->FLAG.members.mENROLL & ~(1 << ((_n_) << 1))) | (((_v_)?1:0) << ((_n_) << 1)))
#define UI_EXIST_DURESS(_ui_, _n_)		(((_ui_)->FLAG.members.mENROLL & (1 << (((_n_) << 1) + 1))) >> (((_n_) << 1) + 1))
#define UI_SET_DURESS(_ui_,_n_,_v_)		((_ui_)->FLAG.members.mENROLL = ((_ui_)->FLAG.members.mENROLL & ~(1 << (((_n_) << 1) + 1))) | (((_v_)?1:0) << (((_n_) << 1) + 1)))
#define UI_GROUPTZ_STATUS(_ui_)			((_ui_)->FLAG.members.byUseGroupTZ)
#define UI_GROUPVM_STATUS(_ui_)			((_ui_)->FLAG.members.byUseGroupVM)
#define UI_PHOTO_STATUS(_ui_)			((_ui_)->FLAG.members.byPhotoExist)
#define UI_VOICE_STATUS(_ui_)			((_ui_)->FLAG.members.byVoiceExist)
#define UI_MANAGER_STATUS(_ui_)			((_ui_)->FLAG.members.byMgr)
#define UI_ENABLE_STATUS(_ui_)			((_ui_)->FLAG.members.bEnable)
#define UI_ALL_DATA(_ui_)				((_ui_)->FLAG.dwALL)

//////////////////////////////////////////////////////////////////////////
typedef struct SLOG_INFO
{
        DWORD	dwSeconds;	//4
        UINT64	nManagerID;	//8
        UINT64	nUserID;	//8
        BYTE	byAction;	//1
        BYTE	byResult;	//1
        WORD	res;		//2
} MLOG_INFO;			//Total = 24

typedef struct GLOG_INFO
{
        DWORD	dwSeconds;	//4
        UINT64	nID;		//8
        BYTE	byAction;	//1, VerifyMode
        BYTE	byTrStatus;	//1
        BOOL	bAntipassOut;//1
        BYTE	res[1];		//1
} ALOG_INFO;			//Total = 16

typedef struct GLOG_INFO_index
{
        DWORD	dwSeconds;	//4
        UINT64	nID;		//8
        BYTE	byAction;	//1, VerifyMode
        BYTE	byTrStatus;	//1
        BOOL	bAntipassOut;//1
        BYTE	res[1];		//1
        DWORD	dwIndex;	//4//hym//1
} ALOG_INFO_INDEX;			//Total = 16
//////////////////////////////////////////////////////////////////////////
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
        INT		nMaxEnrollCount;		//4
        INT		nBackupNumber;			//4
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

        INT		nSlogMaxCount;			//4
        DWORD	dwFlashSizeSlog;		//4
        INT		nGlogMaxCount;			//4
        DWORD	dwFlashSizeGlog;

        BOOL      bOnLineEnroll;
} DBLICENSE;						//Total = 140

typedef struct _wiegand_type{
        unsigned char byOEM_len;	// length of OEM code
        unsigned char byFC_len;		// length of the machine no field
        unsigned char byCC_len;		// length of the ID field
        unsigned char byRes;		// reserved
        unsigned int  dwTpw;		// pulse width (micro second)
        unsigned int  dwTpi;		// pulse interval (micro second)
} WIEGAND_TYPE;

typedef struct _dbsetup_nomenu
{
        char	szCompanyNamy[32];		//32
        int		nReadMLogPos;			//4
        int		nReadALogPos;			//4
        DWORD	dwMechanical;			//4
        DWORD	dwExpose;				//4
        BOOL	bDisableDevice;			//1
        BYTE	byDoorStatus;			//1, 0:Off, 1:On, 2:Auto
        BOOL	bSummertimeUpdated;		//1
        BYTE	res[1];					//1
        WIEGAND_TYPE wiegand_type;		//12
} DBSETUP_NOMENU;					//Total = 64

typedef struct _dbsetup_system
{
        int		nTimeFormat;			//4
        int		nDateFormat;			//4
        int		nLanguage;				//4
        int		nVolume;				//4
        BOOL	bVoiceOut;				//1
        BOOL	bKeyTones;				//1
        BYTE	res[2];					//2
        int		nDaylightOffset;		//4
        DWORD	dwDaylightChangeTime;	//4
        DWORD	dwDaylightRestoreTime;	//4
        BYTE	byF1Status;				//1
        BYTE	byF2Status;				//1
        BYTE	byF3Status;				//1
        BYTE	byF4Status;				//1
        BYTE	byF5Status;				//1
        BYTE	byF6Status;				//1
        BYTE	byF7Status;				//1
        BYTE	byF8Status;				//1
        int		nIdletimeForPoweroff;	//4
        int		nIdletimeForSleep;		//4
        int		nIdletimeForLcdswitch;	//4
        DWORD	dwAutoPoweroffTime;		//4
        DWORD	dwAutoPoweronTime;		//4
        DWORD	dwAutoSleepTime;		//4
        BOOL	bPowerkeyLock;			//1
        BOOL	bRS232Use;				//1
        BOOL	bRS485Use;				//1
        BOOL	bUSBSlaveUse;			//1
        int		nMachineID;				//4
        int		nBaudrate;				//4
        DWORD	ipAddress;				//4
        DWORD	ipSubnetMask;			//4
        DWORD	ipDefaultGateway;		//4
        DWORD	ipPCBackground;			//4
        DWORD	dwCommPassword;			//4
        int		nMLogWarning;			//4
        int		nGLogWarning;			//4
        int		nReverifyTime;			//4
        int		nLockTime;				//4
        int		nDoorOpenTime;			//4
        int		nDoorSensorStatus;		//4
        int		nIllegalVerifyWarning;	//4
        int		nManagersNumber;		//4
        int		nVerifyMode;			//4
        DWORD	dwSManagerPwd;			//4
        BOOL	bDHCPUse;				//1
        BOOL	byAntipassStatus;		//1
        BOOL	bPwdAlarmUse;			//1
        BOOL	bSOSKeyUse;				//1
        int		nAlarmDelay;			//4
        int		nLockGroupMain;			//4
        DWORD	dwBindingID;			//4
        BOOL	bEthernetUse;			//1
        BYTE	byNetworkSpeed;			//1
        BYTE	byTheme;				//1
        BYTE	byWiegandFormat;		//1
        BYTE	byDefaultGVM;			//1
        BOOL	bCameraShow;			//1
        BOOL	bPhotoShow;				//1
        BOOL	bFPShow;				//1
        BOOL	bCameraSave;			//1
        BYTE	byCameraRateForFP;		//1
        BYTE	byCameraRateForCard;	//1
        BYTE	byCameraRateForPWD;		//1
        int     nBackgroupIconFile;
        WORD    wPortNumBack;
        CHAR	szHostByName[32];
        //CHAR	szHostByName_1[32];
        //CHAR	szHostByName_2[32];
        //int		nRealSpaceTime;
        //CHAR	nHttpMachineID[20];
        CHAR	szHttpRomFileName[256];
        int		nRealSpaceTime;
        DWORD	dwDataSaveTime;
        DWORD		DNSserverIp;
} DBSETUP_SYSTEM;					//Total = 164

typedef struct _db_timesection_a
{
        BYTE	bStartHour;				//1
        BYTE	bStartMinute;			//1
        BYTE	bEndHour;				//1, In the case of bell, bell-type
        BYTE	bEndMinute;				//1, In the case of bell, bell-length
}DB_TIMESECTION_A;					//Total = 4;

typedef struct _db_tz_normal
{
        WORD NAME[TZNAME_LENGTH];	//32
        DB_TIMESECTION_A RANGE;		//4
        DWORD STATUS;				//4
}DB_TZ_NORMAL;					//Total = 40;

typedef struct _db_tz_access
{
        DB_TIMESECTION_A RANGE[7];	//28
        DWORD STATUS;
}DB_TZACCESS;					//Total = 32

typedef struct _db_tzgroup
{
        BYTE	bGroupA;				//1
        BYTE	bGroupB;				//1
        BYTE	bGroupC;				//1
        BYTE	bGroupD;				//1(reserved)
}DB_TZGROUP_A;						//Total = 4

typedef DB_TZGROUP_A DB_TZGROUP[ACCESS_USER_GROUP_COUNT]; //4 * 5 = 20

typedef struct {
        WORD	SMSID;				// 2, message ID
        BYTE	Valid;				// 1, valid
        BYTE	Tag;				// 1, message type: 0-general, 1-user, 2-group
        WORD	Belong;				// 2, user or group ID or 0(general)
        WORD	ValidMinutes;		// 2, valid period
        DWORD	StartTime;			// 4, valid period
        char	Contents[MSG_LEN];	// 60,displayed message
} MSG_INFO;						// Total = 72

typedef struct
{
        DB_TZ_NORMAL tzTr[LOG_TZONE_COUNT];			//40
        DB_TZ_NORMAL tzBell[BELL_INFO_COUNT];		//40
        DB_TZACCESS  tzAccess[ACCESS_TIME_SET_COUNT];//1600
        DB_TZGROUP   tzGroup;						//20
        BYTE		 tzLockGroup[MULTI_IDENT_SET_COUNT];//10
        BYTE		 tzGrupVM[ACCESS_USER_GROUP_COUNT];//5
        BYTE		 tzRes;							//1
        MSG_INFO	 tzMsg[MSG_INFO_COUNT];			//720
        //only for highlevel timezone function
        DB_TIMESECTION_A	tzHighTIME[TIMEZONE_COUNT];					//128
        BYTE				tzHighTG[TIMEGROUP_COUNT][TIMECOUNT_PER_TG];//320
        BYTE				tzHighAccess[ACCESS_TIME_SET_COUNT_HIGH][7];//224
}DBSETUP_TIMEZONE;								//Total = 3108

typedef struct
{
        DWORD					dwCheckSum;	//4
        DBSETUP_NOMENU			setNoMenu;	//64
        DBSETUP_SYSTEM			setSystem;	//156
        DBSETUP_TIMEZONE		setTimezone;//3108
} DBSETUP_TOTAL;						//Total = 3332

typedef struct
{
#define NAND_FLASH_MAGIC	0x19860320
        DWORD dwFlashMagic;
        //
        int   nMachineID;
        int   nBaudrate;
        BYTE  byMACaddr[8];
        DWORD ipAddress;
        DWORD ipSubnetMask;
        DWORD ipDefaultGateway;
        DWORD dwCommPassword;
        WORD  wPortNum;
        WORD  res1; //HIWORD(NAND_FLASH_MAGIC)
        //
        int   nDownloaderSize;
        int   nKernelSize;
        int   nRootfsSize;
        int   nConsoleUse;
        //
        WORD  wSplashSize;
        WORD  wSplashChecksum;
        //
        WORD  res2; //LOWORD(NAND_FLASH_MAGIC)
        WORD  wChecksum;
} T_PARAMETER_INFO; //Downloader, Application, MakeRomImage

typedef struct
{
        unsigned char* pBackgroundImage;
        unsigned short nAnimationPosX;
        unsigned short nAnimationPosY;
        unsigned short nAnimationWidth;
        unsigned short nAnimationHeight;
        unsigned short nAnimationFrameCnt;
        unsigned short nCRC16Checksum;
        unsigned int   nAnimationSpeed;
        unsigned char* pAnimationImage;
}T_SPLASH_HDR;

//////////////////////////////////////////////////////////////////////////
BOOL DbParamInfoSave(void);
BOOL DbParamInfoLoad(void);

BOOL DbLicenseRead(void);
BOOL DbLicenseWrite(void);

BOOL DbSetupTotalRead(BOOL bBackupCheck = TRUE);
BOOL DbSetupTotalWrite(BOOL bChangeTheme = TRUE);
void DbSetupTotal2Default(void);

//////////////////////////////////////////////////////////////////////////
//
// load, save, delete, delete all,
// position
// pointer
// counting
// use, full, privilege
// enable/disable
// enrolling
// verifying
//

BOOL	DbFpLoad(void);
BOOL	DbFpSave(void);
BOOL	DbFpSaveOne(int nPos);
BOOL	DbFpDelete(USER_INFO* pUserInfo, int nFP);
BOOL	DbFpDeleteAll(void);
int		DbFpGetPosition(int nUIPos, int nFP);
void*	DbFpGetPointer(int nUIPos, int nFP);
BOOL	DbFpSetPointer(int nUIPos, int nFP, void* pFpInfo, BOOL bNoMatch, BOOL bFlashWrite = TRUE);
int		DbFpGetCount(void);
int		DbFpGetFingerCountPerUser(USER_INFO* pUserInfo);
int		DbFpGetUnusedPosition(void);
int		DbFpGetUnusedFingernumber(UINT64 nID, int nStart = 0);
int		DbFpGetUsedFingernumber(UINT64 nID, int nStart = 0);

BOOL DbUserTimeLoad(void);
BOOL DbUserTimeSave(void);
BOOL DbUserTimeSaveOne(int nPos);
BOOL DbUserTimeDelete(UINT64 nID);
BOOL DbUserTimeDeleteAll(void);
DWORD DbUserTimeDataRead(UINT64 nID);
BOOL DbUserTimeDataWrite(UINT64 nID);
BOOL DbUserTimeDataNew(UINT64 nID);
BOOL DbUserTimeOut(DWORD Seconds);
BOOL DbUserTimeOutOne(DWORD Seconds);

BOOL DbUserIdHeadListLoad(void);
BOOL DbUserIdHeadListSave(void);
BOOL DbUserIdHeadListDeleteAll(void);
int GetDbUserIdHeadListCountAll();



BOOL	DbUserInfoLoad(void);
BOOL	DbUserInfoSave(void);
BOOL	DbUserInfoSaveOne(int nPos);
BOOL	DbUserInfoDelete(UINT64 nID, int nBackup);
BOOL	DbUserInfoDeleteAll(void);
int		DbUserInfoGetPosition(UINT64 nID);
void*	DbUserInfoGetPointer(UINT64 nID);
void*	DbUserInfoGetPointer(UINT64 nID, int nBackup);
BOOL	DbUserInfoEnroll(USER_INFO *pUserInfoNew, int nBackup, void* pData, BOOL bFlashWrite = TRUE, BOOL bNoMatch = TRUE);
int		DbUserInfoGetCount(void);
BOOL	DbUserInfoHasVoice(USER_INFO *pUserInfo);
BOOL	DbUserInfoHasVoice(UINT64 nID);
char*	DbUserInfoGetVoiceFilename(UINT64 nID);
BOOL	DbUserInfoSetVoice(UINT64 nID, BOOL bStatus);
BOOL	DbUserInfoSetPhoto(UINT64 nID, BOOL bStatus);
BOOL	DbUserInfoGetTimezone(USER_INFO *pUserInfo, int *pnTZ1, int *pnTZ2, int *pnTZ3);
BOOL	DbUserInfoHasPhoto(USER_INFO *pUserInfo);
BOOL	DbUserInfoHasPhoto(UINT64 nID);
char*	DbUserInfoGetPhotoFilename(UINT64 nID);
int		DbUserInfoGetCount(int nBackup);
int		DbUserInfoGetFreeCount(int nBackup);
BOOL	DbUserInfoIsUsedID(UINT64 nID);
int		DbUserInfoGetUnusedPosition(void);
int		DbUserInfoGetManagerCount(BYTE byMgr);
BOOL	DbUserInfoManagerFull(BYTE byMgr);
BYTE	DbUserInfoGetPrivilege(UINT64 nID);
BOOL	DbUserInfoSetPrivilege(UINT64 nID, BYTE byPrivilege);
BOOL	DbUserInfoRemovePrivilege();
BOOL	DbUserInfoGetDuress(UINT64 nID, int nBackup);
int		DbUserInfoGetDuressCount(UINT64 nID);
BOOL	DbUserInfoSetDuress(UINT64 nID, int nBackup, int nStatus);
BOOL	DbUserInfoEnable(int nPos, BOOL bEnable);
BOOL	DbUserInfoIsAble(int nPos);
BOOL	DbUserInfoFlagEnrollStatusGet(USER_INFO *pUserInfo, int nBackup);
BOOL	DbUserInfoFlagEnrollStatusSet(USER_INFO *pUserInfo, int nBackup, BOOL bStatus);
BOOL	DbUserInfoFlagDuressStatusGet(USER_INFO *pUserInfo, int nBackup);
BOOL	DbUserInfoFlagDuressStatusSet(USER_INFO *pUserInfo, int nBackup, BOOL bStatus);
BOOL	DbUserInfoFlagGTZStatusGet(USER_INFO *pUserInfo);
BOOL	DbUserInfoFlagGTZStatusSet(USER_INFO *pUserInfo, BOOL bStatus);
BOOL	DbUserInfoFlagGVMStatusGet(USER_INFO *pUserInfo);
BOOL	DbUserInfoFlagGVMStatusSet(USER_INFO *pUserInfo, BOOL bStatus);
BOOL	DbUserInfoFlagPhotoStatusGet(USER_INFO *pUserInfo);
BOOL	DbUserInfoFlagPhotoStatusSet(USER_INFO *pUserInfo, BOOL bStatus);
BOOL	DbUserInfoFlagVoiceStatusGet(USER_INFO *pUserInfo);
BOOL	DbUserInfoFlagVoiceStatusSet(USER_INFO *pUserInfo, BOOL bStatus);
int		DbUserInfoFlagManagerGet(USER_INFO *pUserInfo);
BOOL	DbUserInfoFlagManagerSet(USER_INFO *pUserInfo, int nPriv);
BOOL	DbUserInfoFlagDisableStatusGet(USER_INFO *pUserInfo);
BOOL	DbUserInfoFlagDisableStatusSet(USER_INFO *pUserInfo, BOOL bStatus);
BOOL	DbUserInfoTzVerify(USER_INFO *pUserInfo);
int		DbUserInfoPwdVerify(UINT64 nID, DWORD dwPassword);
int		DbUserInfoCardVerify(DWORD dwCardNumber);
BOOL DbGlogIsReverify2(UINT64 nID);

BOOL	DbSLogLoad(void);
BOOL	DbSLogSave(void);
BOOL	DbSLogAdd(MLOG_INFO *pLogData);
BOOL	DbSLogDeleteAll(void);
int		DbSLogCount(void);
int		DbSLogCountAll(void);
int		DbSLogGet(MLOG_INFO *pLogBuffer, int from, int count);
int		DbSLogPos();
BOOL	DbSLogSetReadPos(int nPos);
int		DbSLogGetReadPos();

BOOL	DbGLogLoad(void);
BOOL	DbGLogAdd(ALOG_INFO *pLogData);
BOOL	DbGLogDeleteAll(void);
int		DbGLogCount(void);
int		DbGLogCountAll(void);
BOOL	DbGlogIsReverify(UINT64 nID);
int		DbGLogGet(ALOG_INFO *pLogBuffer, int from, int count);
int		DbGLogPos();
BOOL	DbGLogSetReadPos(int nPos);
int		DbGLogGetReadPos();

BOOL	DbUIIndexLoad(void);
BOOL	DbUIIndexSave(void);
BOOL	DbUIIndexDeleteAll(void);
int		DbUIIndexGetPosition(int nUserInfoPos);
int		DbUserInfoGetNearestPosition(UINT64 nID, int *pNearestPos);

BOOL	DbFPIndexLoad(void);
BOOL	DbFPIndexSave(void);
BOOL	DbFPIndexDeleteAll(void);

BOOL	DbAntipassLoad(void);
BOOL	DbAntipassSave(void);
BOOL	DbAntipassDeleteAll(void);
BOOL	DbAntipassSet(UINT64 nID, BOOL bStatus, DWORD dwTime = -1UL, BOOL bSave = FALSE);
BYTE	DbAntipassGet(UINT64 nID);
DWORD	DbAntipassGetLastDate();

BOOL	DbPartLoad(void);
BOOL	DbPartReload(void);
BOOL	DbPartSave(void);
int		DbPartCount(void);
QString	DbPartGet(int nIndex);
BOOL	DbPartSet(int nIndex, const QString & szValue);

//////////////////////////////////////////////////////////////////////////
BOOL	Db_IsUnusedID(UINT64 nID);
UINT64	Db_GetUsedID(UINT64 nIDFrom);
UINT64	Db_GetUnusedID(UINT64 nIDFrom);
UINT64	Db_GetCandidateID(BOOL bNew, UINT64 nIDCandidate);
int		Db_GetUserCount(void);
int		Db_GetUserVoiceCount(void);
int		Db_GetUserPhotoCount(void);
int		Db_GetManagerCount(BYTE byMgr);
int		Db_GetManagerCountTotal(void);
int		Db_GetManagerCountMax(void);
int		Db_GetEnrolledIDMask(UINT64 nID);

//////////////////////////////////////////////////////////////////////////
BOOL	Db_LoadAllData(BOOL bSetupReadStatus);
BOOL	Db_DeleteAllEnrollData(void);
BOOL	Db_DeleteAllLogData(void);
void	Db_FreeAllData(void);

//////////////////////////////////////////////////////////////////////////
BOOL	_Db_ReadFpDataFromFlash(int fd, void* pDst, int from, int to, BYTE byEmpty, int* pIndexDBChanged, int nBaseAddr = 0);
BOOL	_Db_FlashRead(int fd, void* pDst, int from, int to, int nSizeof, BYTE byEmpty, char *szTitle, int *pResult = NULL, int nBaseAddr = 0);
BOOL	_Db_FlashWrite(int fd, void* pSrc, int from, int to, int nSizeof, char *szTitle, int nBaseAddr = 0);
BOOL	_Db_FWWriteToFlash1(HFILE hFile, void* pSrc, int nSize);
BOOL	_Db_FWWriteToFlash(BYTE* pRomImage, int nFileSize);

/************************************************************************/
/*    For OCX communication                                             */
/************************************************************************/
typedef struct _com_user_info
{
        DWORD	dwID;					// user ID
        DATA_FLAG flag;					// all flags & options
} COM_USER_INFO;

extern	COM_USER_INFO	allUserFlag[MAX_USER_COUNT];

int		GetAllUserID(void);
int	DbGLogGetByTime(ALOG_INFO *pLogBuffer,int from,int to, u32 fromsecond, u32 tosecond);
int	DbSLogGetByTime(MLOG_INFO *pLogBuffer,int from,int to, int fromsecond, int tosecond);
int	DbGLogPosGetByTime(int from,int to, u32 fromsecond, u32 tosecond);
int	DbSLogPosGetByTime(int from,int to, int fromsecond, int tosecond);

BOOL DbFpUploadDataGet(UINT64 *nId,int *nFp);
BOOL DbFpUploadDataSave(UINT64 nID, int nFP,BOOL bClear);
BOOL DbFpUploadDataLoad(void);
BOOL DbFpUploadDataClear(UINT64 nId);

int	DbGLogCountGetByTime(int from,int to, u32 fromsecond, u32 tosecond);
void DbSetupTotalSave(void);
//BOOL DbGLogSetReadPosOnly(int nPos);
BOOL DbSLogSetReadPosOnly(int nPos);
int	DbGLogGetByTimeAllSearch(ALOG_INFO *pLogBuffer,DWORD  from,DWORD to, int fromsecond, int tosecond,int allcount);
DWORD	DbGLogCountGetByTimeAllSearch( u32 fromsecond, u32 tosecond);
DWORD	DbGLogCountGetByTimeAllSearch_and_byid( u32 fromsecond, u32 tosecond,u64 id);
int DbGLogGetByTime_and_byID(ALOG_INFO *pLogBuffer,int from,int to, u32 fromsecond, u32 tosecond,u64 id);
int DbGLogGetByindex(ALOG_INFO *pLogBuffer,int from,int to);
BOOL DbGLogSetReadPosOnly(int nPos);
BOOL DbSetupTotalWriteOnly( void);






#endif // DATABASE_H
