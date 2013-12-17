#ifndef GLOBAL_H
#define GLOBAL_H

//////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>

#include <asm/errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <linux/route.h>
#include <sys/time.h>
#include <sys/mount.h>
#include <sys/vfs.h>
#include <sys/sysinfo.h>
#include <unistd.h>
#include <fcntl.h>
#include <dlfcn.h>
#include <termios.h>
#include <pthread.h>
#include <errno.h>
#include <linux/videodev.h>
#include <sys/reboot.h>
#include <netdb.h>
#include<linux/input.h>//按键输出

#include <QtCore/QString>
#include <QtGui/QApplication>
#include <QtGui/QRgb>
#include <QtGui/QPainter>
#include <QtGui/QLabel>
#include <QtGui/QColor>

//#include "../include/s3c2410addr.h"
//#include "../include/rtc.h"
//#include "../include/ownrtc.h"
//#include "../include/portctl.h"
//#include "../include/buzzer.h"
//#include "../include/keyboard.h"
//#include "../include/monochrome.h"
//#include "../include/wdog.h"

#include "hiwaylib.h"
#include "Database.h"
//////////////////////////////////////////////////////////////////////////
typedef int				HFILE;

typedef char				CHAR;
typedef short				SHORT;
typedef int				INT;

typedef unsigned char			BYTE, u8, uchar;
typedef unsigned char			BOOL;
typedef unsigned short			WORD, UINT16,u16;
typedef unsigned int			DWORD, UINT32, u32;
typedef long				LONG;
typedef unsigned long long		UINT64, u64;

typedef unsigned short			WPARAM;
typedef unsigned long			LPARAM;

//////////////////////////////////////////////////////////////////////////
#ifndef NULL
#define NULL					(0)
#endif /*NULL*/
#ifndef TRUE
#define TRUE					(1)
#endif /*TRUE*/
#ifndef FALSE
#define FALSE					(0)
#endif /*FALSE*/
#ifndef INVALID_HANDLE_VALUE
#define INVALID_HANDLE_VALUE	(-1)
#endif /*INVALID_HANDLE_VALUE*/


#define FUCK   1

//////////////////////////////////////////////////////////////////////////
#define MAX(_a_, _b_)			((_a_) > (_b_) ? (_a_) : (_b_))
#define MIN(_a_, _b_)			((_a_) < (_b_) ? (_a_) : (_b_))
#define MAKEWORD(a, b)			((WORD)(((BYTE)(a)) | ((WORD)((BYTE)(b))) << 8))
#define MAKELONG(a, b)			((LONG)(((WORD)(a)) | ((DWORD)((WORD)(b))) << 16))
#define LOWORD(l)				((WORD)(l))
#define HIWORD(l)				((WORD)(((DWORD)(l) >> 16) & 0xFFFF))
#define LOBYTE(w)				((BYTE)(w))
#define HIBYTE(w)				((BYTE)(((WORD)(w) >> 8) & 0xFF))
#define PACKED					__attribute__((packed))
#define STR2ASCII(_str_)		((_str_).toAscii().data())

#define UI_IP_MAKE(a,b,c,d) (((a)<<24) | ((b)<<16) | ((c)<<8) | (d))
#define UI_IP_UNMAKE(ip, a,b,c,d) { (a)=((ip)>>24)&0xFF; (b)=((ip)>>16)&0xFF; (c)=((ip)>>8)&0xFF; (d)=(ip)&0xFF; }

#define POST_EVENTS()			{QApplication::processEvents(); /*ioctl(g_hTftLcd, FBIOBLANK, FBINFO_ROTATE);*/}
#define ITEM_CNT(_x_)			(sizeof((_x_)) / sizeof((_x_)[0]))
#define WAIT_EVENT(_e_)			{while((_e_)) { POST_EVENTS(); }}

#define FD_CLOSE(_fd_)	{if ((_fd_) != INVALID_HANDLE_VALUE) close((_fd_)); (_fd_) = INVALID_HANDLE_VALUE;}
#define FREE(_p_)		{if ((_p_) != NULL) free((_p_)); (_p_) = NULL;}
#define DELETE(_p_)		{if ((_p_) != NULL) delete((_p_)); (_p_) = NULL;}

#define WM_USER					(QEvent::User)
#define WM_T9INPUT				((QEvent::Type)(WM_USER + 1))

#define FP_GET_NEXTPOS(_f_)		LOWORD(((FPINFO*)(_f_))->lParam)
#define FP_SET_NEXTPOS(_f_,_v_)	(((FPINFO*)(_f_))->lParam = MAKELONG((_v_), HIWORD(((FPINFO*)(_f_))->lParam)))
#define FP_GET_UIPOS(_f_)		HIWORD(((FPINFO*)(_f_))->lParam)
#define FP_SET_UIPOS(_f_,_v_)	(((FPINFO*)(_f_))->lParam = MAKELONG(LOWORD(((FPINFO*)(_f_))->lParam), (_v_)))

#define WM_USER					(QEvent::User)
#define WM_T9INPUT				((QEvent::Type)(WM_USER + 1))

#define TIMER_RTCCLOCK			0x1001
#define TIMER_LED_ON			0x1002
#define TIMER_MANAGERREQUEST	0x1003
#define TIMER_DATETIME_SETUP	0x1004
#define TIMER_ALARM				0x1005
#define TIMER_SYSMONITOR		0x1006
#define TIMER_SMSG				0x1007
#define TIMER_ACCACHE_FLUSH		0x1008
#define TIMER_DURESS_ALARM		0x1009
#define TIMER_SOSKEY_RELEASE	0x100A
#define TIMER_KEYPAD_BACKGROUND	0x100B
#define TIMER_LOCK_RESTORE		0x100C
#define TIMER_LOGOUT_ALARM		0x100D

#define SETUP_TIMER(_timerid_, _timeout_, _param_, _callback_)	{if (g_MainWindow) g_MainWindow->SetTimer((_timerid_), (_timeout_), (_param_), (_callback_));}
#define STOP_TIMER(_timerid_)	{if (g_MainWindow) g_MainWindow->StopTimer((_timerid_));}

#define PERF_CHECK(_X_)		//_X_

#define G2U(s) ( QTextCodec::codecForName("GBK")->toUnicode(s) )
#define U2G(s) ( QTextCodec::codecForName("GBK")->fromUnicode(s) )
#define TEXTCODEC "utf8"

/////////////////////////////////////////////////////////////
extern int GetMainTickCount(void);

//////////////////////////////////////////////////////////////////////////
//Device Handles
extern HFILE    g_hTs;
extern HFILE    g_hRtc;
extern HFILE    g_hKeyBoard;

extern BOOL     g_uiBuildMenu;
extern DWORD    g_uiTimeLastAction;
//extern USER_INFO g_UserInfoTemp;
extern int      g_keyvalue;

extern DBLICENSE                dbLicense;
extern DBSETUP_TOTAL            dbSetupTotal;
extern USER_INFO*		gpUserInfoEnrollData;

//extern BYTE gFpData[1404];
extern USER_INFO gUserInfoTemp;

//extern DBLICENSE dbLicense;
//extern DBSETUP_TOTAL dbSetupTotal;
extern DBSETUP_TOTAL dbSetupTotalTemp;
extern DBSETUP_SYSTEM dbSetupSystemNew;
extern DBSETUP_TIMEZONE dbSetupTimezoneNew;
extern T_PARAMETER_INFO g_params;
//extern BYTE				gpSplash[65536];

//extern USER_INFO*		gpUserInfoEnrollData;
extern USER_TIME*		gpUserTimeData;
//extern st_HeadString*		gpUserIdHeadData;

//extern P_FPINFO			gpFingerEnrollData;

extern WORD*			gpUIIndexData;
extern BYTE*			gpIndexData;
extern BYTE*			gpAntipassData;

////////////////////////////////////////
#endif // GLOBAL_H
