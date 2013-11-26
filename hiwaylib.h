#ifndef HIWAYLIB_H
#define HIWAYLIB_H

#include "global.h"
typedef unsigned char			BOOL;
//按键的值
typedef enum
{
        UIKEY_0,
        UIKEY_1 = 1,
        UIKEY_2 = 2,
        UIKEY_3,
        UIKEY_4,
        UIKEY_5,
        UIKEY_6,
        UIKEY_7,
        UIKEY_8,
        UIKEY_9,
        UIKEY_MENU=19,
        UIKEY_UP=14,
        UIKEY_DOWN=15,
        UIKEY_OK = 13,
        UIKEY_ESC,
        UIKEY_POWER,
        UIKEY_NONE = 0xFF
} T_UI_KEY;
//设备的枚举
typedef enum
{
    DEVERR_SUCCESS,
    DEVERR_TS,
    DEVERR_RTC,
    DEVERR_UART0,
    DEVERR_UART1,
    DEVERR_KEYBOARD,
    DEVERR_BUZZER,
    DEVERR_LCD,
    DEVERR_WIEGAND,
    DEVERR_WATCHDOG,
    DEVERR_RFMOD,
    DEVERR_SDMOD,
    DEVERR_CAMMOD,
    DEVERR_GPIO,
    DEVERR_SBUM,
    DEVERR_SENSOR,
    DEVERR_ENGINE0,
    DEVERR_ENGINE1,
    DEVERR_CAMERA
} T_DEVICE_ERROR;

#define DEVNAME_KEYBOARD  "/dev/input/event1"
#define DEVNAME_TS  "/dev/input/event0"
#define DEVNAME_RTC "/dev/rtc"
//min_x,min_y,max_x,max_y
#define Ts_MainWindowMenu_Min_X   0
#define Ts_MainWindowMenu_Min_Y   0
#define Ts_MainWindowMenu_Max_X   0 + 100
#define Ts_MainWindowMenu_Max_Y   0 + 50

#define Ts_MainWindowNum_Min_X    220
#define Ts_MainWindowNum_Min_Y    0
#define Ts_MainWindowNum_Max_X    220 + 100
#define Ts_MainWindowNum_Max_Y    0 + 50
/////////////////////////////////////////////////
int HIWAY_INIT0(void);
void uiGetTs(void);
BOOL GetKey(void/*BOOL blong*/);
void Rtc_Get_time(int* pnYear, int* pnMonth, int* pnDay, int* pnWeekday, \
                  int* pnHour, int* pnMinute, int* pnSecond);
void Rtc_Set_time(int nYear, int nMonth, int nDay, int nWeekday, \
                  int nHour, int nMinute, int nSecond);


/////////////////////////////////////////////////////




#endif // HIWAYLIB_H