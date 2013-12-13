#ifndef DATABASE_H
#define DATABASE_H

//#include "../global.h"
//typedef char				CHAR;
//typedef short				SHORT;
//typedef int				INT;

typedef unsigned char			BYTE, u8, uchar;
typedef unsigned char			BOOL;
typedef unsigned short			WORD, UINT16,u16;
typedef unsigned int			DWORD, UINT32, u32;
//typedef long				LONG;
typedef unsigned long long		UINT64, u64;



#define     USERNAME_LENGTH     12

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




#endif // DATABASE_H
