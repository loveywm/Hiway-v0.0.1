#ifndef UILCD_H
#define UILCD_H



#include "gui/Define.h"

typedef enum
{
        UILANG_EN,
        UILANG_SC,
        UILANG_TC,
        UILANG_KR,
        UILANG_JP,
        UILANG_CNT
} T_UI_LANG;

typedef enum
{
        UI_MSG_ERROR,
        UI_MSG_OK,
        UI_MSG_QUESTION
} T_UI_MSG_TYPE;

#define UI_MSGTIMEOUT	1500

typedef enum
{
        UI_WAIT_KEY_EVENT,
} T_UI_MSG_WAITMODE;

#define LCD_SIZE_X	320
#define LCD_SIZE_Y	240
#define LCD_BPP		32

#define LCDPROG_PERCENT(_v_, _t_)	(100*(_v_)/(_t_))
extern QRgb				g_rgbForeColor1;
//////////////////////////////////////////////////////////////////////////
void uiLcdProgressDlgShow(int nTitle);
void uiLcdProgressDlgExit();
void uiLcdProgressStart(int nTitle);
void uiLcdProgress(int nPercent);
void uiLcdProgress1(int nPercent);
void uiLcdProgressEnd();

//////////////////////////////////////////////////////////////////////////
//int uiLcdMessageBox(int nMessageType, int nMessage, DWORD dwTimeout = 0xFFFFFFFF);
int uiLcdMessageBox(int nMessageType, char *szMessage, DWORD dwTimeout = 0xFFFFFFFF);
int uiLcdMessageBox2(int nMessageType, char *szMessage, DWORD dwTimeout /*= 0xFFFFFFFF*/);
void uiLcdMessageOut(int nMessageType, void *pLabel, int nMessage);
void uiLcdMessageBoxByResult(BOOL bResult, int nSuccessMessage, int nFailMessage);
void uiLcdSetLabelText0(QLabel *pLabel, QString str, QColor color,QColor edge_color = QColor(),QString strName = QString(""));
void uiLcdDrawText0(QPainter *painter, int x, int y, int w, int h, int align, QString str, QColor color, QColor edge_color = QColor());
void uiLcdSetLabelText2(QLabel *pLabel, QString str, QColor color,QColor edge_color /*= FOREGROUND_COLOR1*/ ,QString strName /*= QString("")*/);







#endif // UILCD_H
