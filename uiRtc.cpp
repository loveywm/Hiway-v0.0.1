#include "hiwaylib.h"


#include <QDebug>


/************************************************************************/
/*    关于RTC的相关时间处理函数                                                                  */
/************************************************************************/
static int rtcDaysPerMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int     uiRtcYMD2Days(int nYear, int nMonth, int nDay);
void    uiRtcDays2YMD(int nDays, int* pnYear, int* pnMonth, int* pnDay);
void    uiRtcSeconds2YMDHMS(DWORD dwSeconds, int* pnYear, int* pnMonth, int* pnDay, int* pnHour, int* pnMinute, int* pnSecond);
int     uiRtcGetWeekDay(int nYear, int nMonth, int nDay);
int     uiRtcGetDaysForMonth(int nYear, int nMonth);
DWORD   uiRtcGetSeconds(int nYear, int nMonth, int nDay, int nHour, int nMinute, int nSecond);
DWORD   uiRtcGetSeconds(void);
void    uiRtcSetSeconds(DWORD dwSeconds);
void    uiRtcSynchronize();
void    uiRtcSetDate(DWORD dwSeconds);
void    uiRtcSetTime(DWORD dwSeconds);
QString uiRtcGetDate(DWORD dwSeconds, BOOL bWithYear);
char*   uiRtcSeconds2LogStringForDownload(DWORD dwSeconds);
QString uiRtcGetTime(DWORD dwSeconds, BOOL bShowSecond);
int     uiRtcDiffSecond(int nSecCur, int nSecPrev);
BOOL    uiRtcIsToday(DWORD dwSeconds);
char*   uiRtcSeconds2LogString(DWORD dwSeconds);
char*   uiRtcSeconds2LogStringForCamera(DWORD dwSeconds);
char*   uiRtcSeconds2Summertime(DWORD dwSeconds);


//////////////////////////////////////////////////////////////////////////
//年月日转天
int uiRtcYMD2Days(int nYear, int nMonth, int nDay)
{
        int i;
        int nDays = 0;

        if (nYear > 0)
                nDays = nYear * 365 + ((nYear - 1) / 4 + 1);

        for ( i = 1; i < nMonth; i++ )
                nDays += rtcDaysPerMonth[i-1];

        if ( nYear % 4 == 0 )
        {
                if (nMonth > 2)
                        nDays += 1;
        }
        nDays += nDay;
        return nDays;
}

//////////////////////////////////////////////////////////////////////////
void uiRtcDays2YMD(int nDays, int* pnYear, int* pnMonth, int* pnDay)
{
        int nDaysTemp;
        *pnYear = 0;
        *pnMonth = 1;
        while (1)
        {
                nDaysTemp = 365;
                if (*pnYear % 4 == 0)
                        nDaysTemp++;

                if (nDays <= nDaysTemp)
                        break;

                nDays -= nDaysTemp;
                (*pnYear)++;
        }
        while (1)
        {
                nDaysTemp = rtcDaysPerMonth[*pnMonth - 1];
                if (*pnMonth == 2 && *pnYear % 4 == 0)
                        nDaysTemp++;

                if (nDays <= nDaysTemp)
                        break;

                nDays -= nDaysTemp;
                (*pnMonth)++;
        }
        *pnDay = nDays;
}

//////////////////////////////////////////////////////////////////////////
void uiRtcSeconds2YMDHMS(DWORD dwSeconds, int* pnYear, int* pnMonth, int* pnDay, int* pnHour, int* pnMinute, int* pnSecond)
{
        DWORD dwSeconds2 = dwSeconds % (3600 * 24);
        *pnHour = dwSeconds2 / 3600;
        dwSeconds2 %= 3600;
        *pnMinute = dwSeconds2 / 60;
        *pnSecond = dwSeconds2 % 60;

        uiRtcDays2YMD(dwSeconds / 3600 / 24 + 1, pnYear, pnMonth, pnDay);
        *pnYear += 2000;
}

//////////////////////////////////////////////////////////////////////////
int uiRtcGetWeekDay(int nYear, int nMonth, int nDay)
{
        return (uiRtcYMD2Days(nYear, nMonth, nDay) + 5) % 7 + 1;
}

//////////////////////////////////////////////////////////////////////////
int uiRtcGetDaysForMonth(int nYear, int nMonth)
{
        int nret;
        nret = rtcDaysPerMonth[nMonth - 1];
        if (nMonth == 2 && nYear % 4 == 0)
                nret++;
        return nret;
}

//////////////////////////////////////////////////////////////////////////
DWORD uiRtcGetSeconds(int nYear, int nMonth, int nDay, int nHour, int nMinute, int nSecond)
{
        DWORD dwSeconds;
        nYear -= 2000;
        dwSeconds = (DWORD)(uiRtcYMD2Days(nYear, nMonth, nDay) - 1) * 24 * 3600;
        dwSeconds += nHour * 3600;
        dwSeconds += nMinute * 60;
        dwSeconds += nSecond;
        return dwSeconds;
}


//////////////////////////////////////////////////////////////////////////
DWORD uiRtcGetSeconds(void)
{
        int nYear, nMonth, nDay, nWeekday, nHour, nMinute, nSecond;
        Rtc_Get_time(&nYear, &nMonth, &nDay, &nWeekday, &nHour, &nMinute, &nSecond);
        return uiRtcGetSeconds(nYear, nMonth, nDay, nHour, nMinute, nSecond);
}

//////////////////////////////////////////////////////////////////////////
void uiRtcSetSeconds(DWORD dwSeconds)
{
        int nYear, nMonth, nDay, nWeekday, nHour, nMinute, nSecond;
/*
        if ((dwSeconds >= dbSetupTotal.setSystem.dwDaylightChangeTime) &&
                (dwSeconds <= dbSetupTotal.setSystem.dwDaylightRestoreTime))
                dwSeconds -= 3600 * dbSetupTotal.setSystem.nDaylightOffset;
*/
        uiRtcSeconds2YMDHMS(dwSeconds, &nYear, &nMonth, &nDay, &nHour, &nMinute, &nSecond);
        //注意这个year
        nYear -= 2000;//nYear -= 1900;
        nWeekday = uiRtcGetWeekDay(nYear, nMonth, nDay);
        Rtc_Set_time(nYear, nMonth, nDay, nWeekday, nHour, nMinute, nSecond);
        //Rtc1Set(nYear, nMonth, nDay, nWeekday, nHour, nMinute, nSecond);
        //g_MainWindow->DrawClock(TRUE);
}

//////////////////////////////////////////////////////////////////////////
void uiRtcSynchronize()
{
        int nYear, nMonth, nDay, nWeekday, nHour, nMinute, nSecond;

        Rtc_Get_time(&nYear, &nMonth, &nDay, &nWeekday, &nHour, &nMinute, &nSecond);
        if (nYear < 0 || nYear > 99 ||
                nMonth < 1 || nMonth > 12 ||
                nDay < 1 || nDay > uiRtcGetDaysForMonth(nYear, nMonth) ||
                nHour < 0 || nHour > 23 ||
                nMinute < 0 || nMinute > 59 ||
                nSecond < 0 || nSecond > 59)
        {
                nYear = 0;
                nMonth = 1;
                nDay = 1;
                nHour = 0;
                nMinute = 0;
                nSecond = 0;
                Rtc_Set_time(nYear, nMonth, nDay, uiRtcGetWeekDay(nYear, nMonth, nDay), nHour, nMinute, nSecond);
        }
//	printf("%04d-%02d-%02d %02d:%02d:%02d\n", nYear, nMonth, nDay, nHour, nMinute, nSecond);
        Rtc_Set_time(nYear, nMonth, nDay, nWeekday, nHour, nMinute, nSecond);
        //g_MainWindow->DrawClock(TRUE);
}

//////////////////////////////////////////////////////////////////////////
void uiRtcSetDate(DWORD dwSeconds)
{
        int nYear1, nMonth1, nDay1, nHour1, nMinute1, nSecond1;
        int nYear2, nMonth2, nDay2, nHour2, nMinute2, nSecond2;

        uiRtcSeconds2YMDHMS(uiRtcGetSeconds(), &nYear1, &nMonth1, &nDay1, &nHour1, &nMinute1, &nSecond1);
        uiRtcSeconds2YMDHMS(dwSeconds, &nYear2, &nMonth2, &nDay2, &nHour2, &nMinute2, &nSecond2);

        nHour2 = nHour1; nMinute2 = nMinute1; nSecond2 = nSecond1;
        uiRtcSetSeconds(uiRtcGetSeconds(nYear2, nMonth2, nDay2, nHour2, nMinute2, nSecond2));
}

//////////////////////////////////////////////////////////////////////////
void uiRtcSetTime(DWORD dwSeconds)
{
        int nYear1, nMonth1, nDay1, nHour1, nMinute1, nSecond1;
        int nYear2, nMonth2, nDay2, nHour2, nMinute2, nSecond2;

        uiRtcSeconds2YMDHMS(uiRtcGetSeconds(), &nYear1, &nMonth1, &nDay1, &nHour1, &nMinute1, &nSecond1);
        uiRtcSeconds2YMDHMS(dwSeconds, &nYear2, &nMonth2, &nDay2, &nHour2, &nMinute2, &nSecond2);

        nYear2 = nYear1; nMonth2 = nMonth1; nDay2 = nDay1;
        uiRtcSetSeconds(uiRtcGetSeconds(nYear2, nMonth2, nDay2, nHour2, nMinute2, nSecond2));
}

//////////////////////////////////////////////////////////////////////////
QString uiRtcGetDate(DWORD dwSeconds, BOOL bWithYear)
{
        char strDate[16];
        char *strDateWithoutYear = &strDate[3];
        int nYear, nMonth, nDay, nHour, nMinute, nSecond;

        if (dwSeconds == -1UL)
                dwSeconds = uiRtcGetSeconds();

        uiRtcSeconds2YMDHMS(dwSeconds, &nYear, &nMonth, &nDay, &nHour, &nMinute, &nSecond);
        nYear -= 2000;
/*
        switch (dbSetupTotal.setSystem.nDateFormat + UISTR_DATEFMT_START)
        {
        case UISTR_DATEFMT_1:
                sprintf(strDate, "%02d-%02d-%02d", nYear, nMonth, nDay);
                break;
        case UISTR_DATEFMT_2:
                sprintf(strDate, "%02d/%02d/%02d", nYear, nMonth, nDay);
                break;
        case UISTR_DATEFMT_3:
                sprintf(strDate, "%02d.%02d.%02d", nYear, nMonth, nDay);
                break;
        case UISTR_DATEFMT_4:
                sprintf(strDate, "%02d-%02d-%02d", nMonth, nDay, nYear);
                break;
        case UISTR_DATEFMT_5:
                sprintf(strDate, "%02d/%02d/%02d", nMonth, nDay, nYear);
                break;
        case UISTR_DATEFMT_6:
                sprintf(strDate, "%02d.%02d.%02d", nMonth, nDay, nYear);
                break;
        case UISTR_DATEFMT_7:
                sprintf(strDate, "%02d-%02d-%02d", nDay, nMonth, nYear);
                break;
        case UISTR_DATEFMT_8:
                sprintf(strDate, "%02d/%02d/%02d", nDay, nMonth, nYear);
                break;
        case UISTR_DATEFMT_9:
                sprintf(strDate, "%02d.%02d.%02d", nDay, nMonth, nYear);
                break;
        case UISTR_DATEFMT_10:
                sprintf(strDate, "%04d%02d%02d", 2000 + nYear, nMonth, nDay);
                strDateWithoutYear = &strDate[4];
                break;
        }
*/
        if (bWithYear)
                return QString(strDate);
        else
                return QString(strDateWithoutYear);
}

//////////////////////////////////////////////////////////////////////////
char* uiRtcSeconds2LogStringForDownload(DWORD dwSeconds)
{
        static char strDate[32];
        int nYear, nMonth, nDay, nHour, nMinute, nSecond;


        uiRtcSeconds2YMDHMS(dwSeconds, &nYear, &nMonth, &nDay, &nHour, &nMinute, &nSecond);

        sprintf(strDate,  "%04d/%02d/%02d  %02d:%02d:%02d", nYear, nMonth, nDay, nHour, nMinute, nSecond);

        return strDate;

}

//////////////////////////////////////////////////////////////////////////
QString uiRtcGetTime(DWORD dwSeconds, BOOL bShowSecond)
{
        char strTime[16];
        int nYear, nMonth, nDay, nHour, nMinute, nSecond;

        if (dwSeconds == -1UL)
                dwSeconds = uiRtcGetSeconds();
        uiRtcSeconds2YMDHMS(dwSeconds, &nYear, &nMonth, &nDay, &nHour, &nMinute, &nSecond);
// 	switch (dbSetupSystemNew)
// 	{
//
// 	}
        if (bShowSecond)
                sprintf(strTime, "%02d:%02d:%02d", nHour, nMinute, nSecond);
        else
                sprintf(strTime, "%02d:%02d", nHour, nMinute);
        return QString(strTime);
}

//////////////////////////////////////////////////////////////////////////
int uiRtcDiffSecond(int nSecCur, int nSecPrev)
{
        nSecCur = nSecCur % (3600 * 24);
        nSecPrev = nSecPrev % (3600 * 24);
        int nSecDiff = nSecCur - nSecPrev;

        if (nSecDiff < 0)
                nSecDiff += (24 * 3600);

        return nSecDiff;
}

//////////////////////////////////////////////////////////////////////////
BOOL uiRtcIsToday(DWORD dwSeconds)
{
        int nYear, nMonth, nDay, nHour, nMinute, nSecond;

        uiRtcSeconds2YMDHMS(uiRtcGetSeconds(), &nYear, &nMonth, &nDay, &nHour, &nMinute, &nSecond);
        nHour = 23;
        nMinute = 59;
        nSecond = 59;

        return (uiRtcDiffSecond(uiRtcGetSeconds(nYear, nMonth, nDay, nHour, nMinute, nSecond), dwSeconds) < 24 * 3600);
}

//////////////////////////////////////////////////////////////////////////
char* uiRtcSeconds2LogString(DWORD dwSeconds)
{
        char strDate[16];
        static char buf[16];
        int nYear, nMonth, nDay, nHour, nMinute, nSecond;

        uiRtcSeconds2YMDHMS(dwSeconds, &nYear, &nMonth, &nDay, &nHour, &nMinute, &nSecond);
/*
        switch (dbSetupTotal.setSystem.nDateFormat + UISTR_DATEFMT_START)
        {
                case UISTR_DATEFMT_1:
                case UISTR_DATEFMT_4:
                        sprintf(strDate, "%02d-%02d", nMonth, nDay);
                        break;
                case UISTR_DATEFMT_2:
                case UISTR_DATEFMT_5:
                        sprintf(strDate, "%02d/%02d", nMonth, nDay);
                        break;
                case UISTR_DATEFMT_3:
                case UISTR_DATEFMT_6:
                        sprintf(strDate, "%02d.%02d", nMonth, nDay);
                        break;
                case UISTR_DATEFMT_7:
                        sprintf(strDate, "%02d-%02d", nDay, nMonth);
                        break;
                case UISTR_DATEFMT_8:
                        sprintf(strDate, "%02d/%02d", nDay, nMonth);
                        break;
                case UISTR_DATEFMT_9:
                        sprintf(strDate, "%02d.%02d", nDay, nMonth);
                        break;
                case UISTR_DATEFMT_10:
                        sprintf(strDate, "%02d%02d", nMonth, nDay);
                        break;
        }
 */   sprintf(buf, "%s %02d:%02d", STR2ASCII(QString(strDate)), nHour, nMinute);

        return buf;
}

//////////////////////////////////////////////////////////////////////////
char* uiRtcSeconds2LogStringForCamera(DWORD dwSeconds)
{
        static char buf[32];
        int nYear, nMonth, nDay, nHour, nMinute, nSecond;

        if (dwSeconds == -1UL)
                dwSeconds = uiRtcGetSeconds();
        uiRtcSeconds2YMDHMS(dwSeconds, &nYear, &nMonth, &nDay, &nHour, &nMinute, &nSecond);
        sprintf(buf, "%02d%02d%02d-%02d%02d%02d", nYear - 2000, nMonth, nDay, nHour, nMinute, nSecond);
        return buf;
}

//////////////////////////////////////////////////////////////////////////
char* uiRtcSeconds2Summertime(DWORD dwSeconds)
{
        static char buf[16];
        int nYear, nMonth, nDay, nHour, nMinute, nSecond;

        uiRtcSeconds2YMDHMS(dwSeconds, &nYear, &nMonth, &nDay, &nHour, &nMinute, &nSecond);

        sprintf(buf, "%02d-%02d %02d:%02d", nMonth, nDay, nHour, nMinute);
        return buf;
}

/************************************************************************/
