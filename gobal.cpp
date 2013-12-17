#include "global.h"

//Device Handles
HFILE   g_hTs = INVALID_HANDLE_VALUE;
HFILE   g_hRtc = INVALID_HANDLE_VALUE;
HFILE   g_hKeyBoard = INVALID_HANDLE_VALUE;

DWORD		g_uiTimeLastAction = 0;
BOOL            g_uiBuildMenu = FALSE;
//USER_INFO       g_UserInfoTemp;
USER_INFO       gUserInfoTemp;

DBLICENSE       dbLicense;
DBSETUP_TOTAL   dbSetupTotal;
USER_INFO*	gpUserInfoEnrollData = NULL;
DBSETUP_TOTAL   dbSetupTotalTemp;																//3332
DBSETUP_SYSTEM  dbSetupSystemNew;															//156
DBSETUP_TIMEZONE dbSetupTimezoneNew;														//3108
T_PARAMETER_INFO g_params;																	//64
//BYTE			gpSplash[65536];															//65536

//USER_INFO*		gpUserInfoEnrollData = NULL;
USER_TIME*		gpUserTimeData = NULL;//4
//st_HeadString*		gpUserIdHeadData = NULL;//4
//st_FpUploadData*	gpFpUploadData = NULL;//4

//P_FPINFO		gpFingerEnrollData = NULL;													//4

WORD*			gpUIIndexData = NULL;														//4
BYTE*			gpIndexData = NULL;															//4
BYTE*			gpAntipassData = NULL;





//pc端测试需求设置的全局变量
int             g_keyvalue = 0;
