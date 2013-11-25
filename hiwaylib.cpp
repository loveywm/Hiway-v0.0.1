#include "hiwaylib.h"
#include "include/rtc.h"


#include <QDebug>

/////////////////////////////////////////////////////////////////////////
//touchscreen
#define TOUCH_MIN_X   0
#define TOUCH_MIN_Y   0
#define TOUCH_MAX_X   990
#define TOUCH_MAX_Y   990
#define LCD_SIZE_X    320
#define LCD_SIZE_Y    240

typedef struct {
    signed int x;
    signed int y;
    signed int pressflag;
}TS_RET;

unsigned int nTouchX, nTouchY, nTouchPress;
struct input_event TS_DATA,TS_BUFF;
TS_RET ts_ret;
/*
struct input_event {
        struct timeval time;
        __u16 type;
        __u16 code;
        __s32 value;
};
*/


//从驱动中获取触摸的值，放入TS_DATA结构体中
void GETTS(void)
{
    memset(&TS_DATA,0,sizeof(struct input_event));
    //memset(&ts_ret,0,sizeof(TS_RET));

    if(g_hTs != INVALID_HANDLE_VALUE)
    {
        for(;;){
        read(g_hTs,&TS_DATA,sizeof(struct input_event));
        if (TS_DATA.type == EV_ABS)
        {
            if(TS_DATA.code==ABS_X)
            {
                ts_ret.x = TS_DATA.value;
                printf("ABS_X=%d\n",TS_DATA.value);
            }
            else if(TS_DATA.code==ABS_Y)
            {
                ts_ret.y = TS_DATA.value;
                printf("\t\tABS_Y=%d\n",TS_DATA.value);
            }
            else if(TS_DATA.code==ABS_PRESSURE)
            {
                ts_ret.pressflag = TS_DATA.value;
                printf("\t\t\t\tABS_P=%d\n",TS_DATA.value);
            }
        }
        if(ts_ret.pressflag == 1000)
        {
            printf("\nts_ret.x=%d\n",ts_ret.x);
            printf("ts_ret.y=%d\n",ts_ret.y);
            printf("ts_ret.pressflag=%d\n",ts_ret.pressflag);
            //return;
            read(g_hTs,&TS_BUFF,sizeof(struct input_event));
            break;
        }
        //else if(ts_ret.pressflag == 0)
        //{
            //return;
        //}
        }
    }

}
//
void uiGetTs(void)
{
   nTouchX = 0;
   nTouchY = 0;
   nTouchPress = 0;

   GETTS();

   //nTouchX = ts_ret.x;
   //nTouchY = ts_ret.y;
   nTouchPress = ts_ret.pressflag;
   nTouchX = (ts_ret.x-TOUCH_MIN_X)*LCD_SIZE_X / (TOUCH_MAX_X-TOUCH_MIN_X);
   nTouchY = (ts_ret.y-TOUCH_MIN_Y)*LCD_SIZE_Y / (TOUCH_MAX_Y-TOUCH_MIN_Y);
   //nTouchY = LCD
/*
   if(TS_DATA.type == EV_ABS)
   {
        if(TS_DATA.code==ABS_X)
        {
            qDebug("ABS_X=%d",TS_DATA.value);
            nTouchX = (TS_DATA.value-TOUCH_MIN_X)*LCD_SIZE_X / (TOUCH_MAX_X-TOUCH_MIN_X);
        }
        else if(TS_DATA.code==ABS_Y)
        {
            qDebug("ABS_Y=%d",TS_DATA.value);
            nTouchY = (TS_DATA.value-TOUCH_MIN_Y)*LCD_SIZE_Y / (TOUCH_MAX_Y-TOUCH_MIN_Y);
        }
        else if(TS_DATA.code==ABS_PRESSURE)
        {
            qDebug("ABS_P=%d",TS_DATA.value);
            nTouchPress = TS_DATA.value;
        }
   }
  */ //qDebug("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");


}
/////////////////////////////////////////////////////////////
//rtc
//获取rtc的值，存入传入指针中
void Rtc_Get_time(int* pnYear, int* pnMonth, int* pnDay, int* pnWeekday, \
                  int* pnHour, int* pnMinute, int* pnSecond)
{
    int i,retval;
    //unsigned long tmp, data;
    struct rtc_time rtc_tm;
    //int scale_type = HR24;
    //struct rtc_wkalrm rtc_alarmtm;

    if(g_hRtc == INVALID_HANDLE_VALUE)
    {
        qDebug() << "g_hRtc == INVALID_HANDLE_VALUE";
        return ;
    }
    /*read current time*/
    retval=ioctl(g_hRtc,RTC_RD_TIME,&rtc_tm);
    if(retval < 0)
    {
        qDebug("ioctl RTC_RD_TIME  faild!!!");
        return ;
    }
    /*print current time*/
/*    qDebug("Read current RTC time is: %04d-%02d-%02d %02d:%02d:%02d\n\n",
           rtc_tm.tm_year + 1900,
           rtc_tm.tm_mon + 1,
           rtc_tm.tm_mday,
           rtc_tm.tm_hour,
           rtc_tm.tm_min,
           rtc_tm.tm_sec);
*/    //printf("Read current RTC time test OK!\n");

    //*pnYear	= rtc_tm.tm_year - 100;
    *pnYear	= rtc_tm.tm_year + 1900;
    *pnMonth	= rtc_tm.tm_mon + 1;
    *pnDay	= rtc_tm.tm_mday;
    *pnWeekday	= rtc_tm.tm_wday;
    *pnHour	= rtc_tm.tm_hour;
    *pnMinute	= rtc_tm.tm_min;
    *pnSecond	= rtc_tm.tm_sec;
/*
    if ((*pnYear < 0 || *pnYear > 99) ||
            (*pnMonth < 1 || *pnMonth > 12) ||
            (*pnDay < 1 || *pnDay > 31) ||
            (*pnHour < 0 || *pnHour > 23) ||
            (*pnMinute < 0 || *pnMinute > 59) ||
            (*pnSecond < 0 || *pnSecond > 59))
    {
            *pnYear = 0; *pnMonth = 1; *pnDay = 1; *pnHour = 0; *pnMinute = 0; *pnSecond = 0;
            //RtcSet(0, 1, 1, 0, 0, 0, 0);
    }
*/
}
//set the value of rtc
void Rtc_Set_time(int nYear, int nMonth, int nDay, int nWeekday, \
            int nHour, int nMinute, int nSecond)
{
    struct rtc_time rtc;
    if (g_hRtc == INVALID_HANDLE_VALUE)
        return;
    memset(&rtc, 0, sizeof(rtc_time));
    //nYear %= 100;
    //rtc.tm_year	= nYear + 100;
    rtc.tm_year	= nYear - 1900;
    rtc.tm_mon	= nMonth - 1;
    rtc.tm_mday = nDay;
    rtc.tm_wday = nWeekday;
    rtc.tm_hour = nHour;
    rtc.tm_min	= nMinute;
    rtc.tm_sec	= nSecond;

    if (ioctl(g_hRtc, RTC_SET_TIME, &rtc))
    {
        qDebug("RTC Set Time Error !\n");
    }
    qDebug("RTC Set Time ok !\n");
}


//////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////
static BOOL InitTouchScreen(void)
{
    g_hTs = open(DEVNAME_TS,O_RDONLY);
    if(g_hTs == -1)
    {
        qDebug() << "InitTouchScreen error";
        return FALSE;
    }
    qDebug() << "InitTouchScreen ok";
    return TRUE;
}
static BOOL InitRtcClock(void)
{
    g_hRtc = open(DEVNAME_RTC,O_RDONLY);
    if(g_hRtc == -1)
    {
        qDebug() << "InitRtcClock error";
        return FALSE;
    }
    qDebug() << "InitRtcClock ok";
    return TRUE;
}



//////////////////////////////////////////////////////////////////////////
#define DEVINIT_WRAPPER(_f_, _e_)	{nRet = (_e_); bResult = (_f_); if (!bResult) goto _lExit;}
//////////////////////////////////////////////////////////////////////////
int HIWAY_INIT0(void)
{
        int nRet;
        BOOL bResult;

        DEVINIT_WRAPPER(InitTouchScreen(), DEVERR_TS);
        //DEVINIT_WRAPPER(InitRtcClock(), DEVERR_RTC);

        return DEVERR_SUCCESS;

_lExit:
        return nRet;
}
