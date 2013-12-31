
#include "global.h"
#include "gui/messagebox.h"
//#include "gui/ProgressDlg.h"
#include "gui/cmainwindow.h"
#include <QtGui/QPainter>
#include "uiLcd.h"
#include <QDebug>

/*
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<{
static CProgressDlg* __PROG_DLG = NULL;
static QLabel* __BACKGROUND = NULL;
extern CMainWindow *g_MainWindow;

void uiLcdProgressDlgShow(int nTitle)
{
        xprintf("30\r\n");
        if (__PROG_DLG)
                uiLcdProgressEnd();
        __PROG_DLG = new CProgressDlg(NULL);
        __PROG_DLG->SetTitle(UISTR(nTitle));
        __PROG_DLG->show();
        POST_EVENTS();
        xprintf("31\r\n");
}

void uiLcdProgressDlgExit()
{
        if (__PROG_DLG)
        {
                __PROG_DLG->close();
                DELETE(__PROG_DLG);
                __PROG_DLG = NULL;
        }
}

void uiLcdProgressStart(int nTitle)
{
        g_bDeviceBusy = TRUE;

        if (!g_bProgress)
                return;
        __PROG_DLG->SetText(UISTR(nTitle)); POST_EVENTS();
}

void uiLcdProgress(int nPercent)
{
        static DWORD __prev_time = 0;
        DWORD dwCurrentTime = uiTimeGetTickCount();

        if (dwCurrentTime - __prev_time < 100)
                return;
        __prev_time = dwCurrentTime;
        if (!g_bProgress)
        {
                POST_EVENTS();
                return;
        }
        __PROG_DLG->SetProgressPercent(nPercent); POST_EVENTS();
}

void uiLcdProgress1(int nPercent)
{
        HFILE hFile;
        char szPercent[4];

        sprintf(szPercent, "%d", nPercent);
        hFile = open("/proc/boot-splash", O_RDWR);
        if (hFile == INVALID_HANDLE_VALUE)
                return;
        write(hFile, szPercent, strlen(szPercent));
        FD_CLOSE(hFile);
}

void uiLcdProgressEnd()
{
        if (!g_bProgress)
        {
                g_bDeviceBusy = FALSE;
                return;
        }
        __PROG_DLG->SetProgressPercent(100); POST_EVENTS();
        g_bDeviceBusy = FALSE;
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>}
*/
extern CMainWindow *g_MainWindow;
static QLabel* __BACKGROUND = NULL;
static const char* __MSG_ICONFILE[] = {"icon-abort.png", "icon-ok.png", "icon-question.png"};
//////////////////////////////////////////////////////////////////////////
//int uiLcdMessageBox(int nMessageType, int nMessage, DWORD dwTimeout /*= 0xFFFFFFFF*/)
//{
   /*     if (!g_MainWindow)
        {
                if (!__BACKGROUND)
                {
                        QPixmap pmap;

                        if (g_params.wSplashSize)
                                pmap.loadFromData((const uchar*)&gpSplash[sizeof(T_SPLASH_HDR)], (uint)((T_SPLASH_HDR*)gpSplash)->pBackgroundImage);
                        else
                                pmap.load(GUI_RESOURCE_PATH "background.png");

                        __BACKGROUND = new QLabel;
                        __BACKGROUND->setGeometry(0, 0, LCD_SIZE_X, LCD_SIZE_Y);
                        __BACKGROUND->setPixmap(pmap);
                }
                __BACKGROUND->show();
                uiLcdProgress1(100);
        }*//*
        int nRet = 0;
        CMessageBox msgBox(NULL);

//	uiTimeSetLastActionTime();
        msgBox.SetIcon(QString(GUI_RESOURCE_PATH) + QString(__MSG_ICONFILE[nMessageType]));
        msgBox.SetText(QString(UISTR(nMessage)));
        //msgBox.SetText(nMessage);
        msgBox.show();

        switch (nMessageType)
        {
        case UI_MSG_ERROR:
                uiTimeSetLastActionTime();
                uiSoundOut(SOUND_ERROR, UI_BUZZER_ERROR);
                break;
        case UI_MSG_OK:
                uiTimeSetLastActionTime();
                uiSoundOut(SOUND_OK, UI_BUZZER_OK);
                break;
        case UI_MSG_QUESTION:
                uiSoundOut(SOUND_QUESTION, UI_BUZZER_NONE);
                break;
        }

        msgBox.SetType(nMessageType);
        nRet = msgBox.MsgBoxProc(dwTimeout);
        return nRet;*/

//}

//////////////////////////////////////////////////////////////////////////
int uiLcdMessageBox(int nMessageType, char *szMessage, DWORD dwTimeout /*= 0xFFFFFFFF*/)
{


        switch (nMessageType)
        {
        case UI_MSG_ERROR:
                uiTimeSetLastActionTime();
                qDebug() << "UI_MSG_ERROR" ;
                //uiSoundOut(SOUND_ERROR, UI_BUZZER_ERROR);
                break;
        case UI_MSG_OK:
                uiTimeSetLastActionTime();
                qDebug() << "UI_MSG_OK" ;
                //uiSoundOut(SOUND_OK, UI_BUZZER_OK);
                break;
        case UI_MSG_QUESTION:
                qDebug() << "UI_MSG_QUESTION" ;
                //uiSoundOut(SOUND_QUESTION, UI_BUZZER_NONE);
                break;
        }

        CMessageBox msgBox(NULL);
        msgBox.SetIcon(QString(GUI_RESOURCE_PATH) + QString(__MSG_ICONFILE[nMessageType]));
        msgBox.SetText(QString(szMessage));
        msgBox.show();

        msgBox.SetType(nMessageType);
        return msgBox.MsgBoxProc(dwTimeout);
}
int uiLcdMessageBox2(int nMessageType, char *szMessage, DWORD dwTimeout /*= 0xFFFFFFFF*/)
{
  /*      CMessageBox msgBox(NULL);

        switch (nMessageType)
        {
        case UI_MSG_ERROR:
                uiTimeSetLastActionTime();
                uiSoundOut(SOUND_ERROR, UI_BUZZER_ERROR);
                break;
        case UI_MSG_OK:
                uiTimeSetLastActionTime();
                uiSoundOut(SOUND_OK, UI_BUZZER_OK);
                break;
        case UI_MSG_QUESTION:
                uiSoundOut(SOUND_QUESTION, UI_BUZZER_NONE);
                break;
        }

        msgBox.SetIcon(QString(GUI_RESOURCE_PATH) + QString(__MSG_ICONFILE[nMessageType]));
        msgBox.SetText(QString(szMessage));
        msgBox.show();

        msgBox.SetType(nMessageType);
        return msgBox.MsgBoxProc2(dwTimeout);*/
}

//////////////////////////////////////////////////////////////////////////
void uiLcdMessageOut(int nMessageType, void *pLabel, int nMessage)
{
  /*      QLabel *pLbl = (QLabel*)pLabel;

        if (!pLbl)
                return;

        switch (nMessageType)
        {
        case UI_MSG_ERROR:
                uiSoundOut(SOUND_ERROR, UI_BUZZER_ERROR);
                break;
        case UI_MSG_OK:
                uiSoundOut(SOUND_OK, UI_BUZZER_OK);
                break;
        case UI_MSG_QUESTION:
                uiSoundOut(SOUND_QUESTION, UI_BUZZER_NONE);
                break;
        }

        pLbl->setText(UISTR(nMessage));*/
}

//////////////////////////////////////////////////////////////////////////
void uiLcdMessageBoxByResult(BOOL bResult, int nSuccessMessage, int nFailMessage)
{
    /*    if (bResult)
                uiLcdMessageBox(UI_MSG_OK, nSuccessMessage, UI_MSGTIMEOUT);
        else
                uiLcdMessageBox(UI_MSG_ERROR, nFailMessage, UI_MSGTIMEOUT);*/
}

//////////////////////////////////////////////////////////////////////////
void uiLcdSetLabelText0(QLabel *pLabel, QString str, QColor color,QColor edge_color /*= FOREGROUND_COLOR1*/ ,QString strName /*= QString("")*/)
{
        if (!pLabel)
                return;
        const int x = 1;
        const int y = 1;
        int w = pLabel->width();
        int h = pLabel->height();
        // 	int r = FOREGROUND_COLOR1.red()/*color.red()*/;
        // 	int g = FOREGROUND_COLOR1.green()/*color.green()*/;
        // 	int b = FOREGROUND_COLOR1.blue()/*color.blue()*/;
        int r = edge_color.red()/*color.red()*/;
        int g = edge_color.green()/*color.green()*/;
        int b = edge_color.blue()/*color.blue()*/;
        int align = (int)pLabel->alignment();
        QPixmap pmap(w, h);
        pmap.fill(QColor(Qt::transparent));

        QPainter painter(&pmap);
        painter.setFont(pLabel->font());
        if(edge_color.isValid())
        {
                painter.setPen(QColor(255 - r, 255 - g, 255 - b, 64));
                painter.drawText(x-1, y-1, w, h, align, str);
                painter.setPen(QColor(255 - r, 255 - g, 255 - b, 100));
                painter.drawText(x-1, y+1, w, h, align, str);
                painter.drawText(x+1, y-1, w, h, align, str);
                painter.setPen(QColor(255 - r, 255 - g, 255 - b, 128));
                painter.drawText(x+1, y+1, w, h, align, str);
        }
        //painter.setPen(QColor(r, g, b, 255));
        painter.setPen(color);
        painter.drawText(x, y, w, h, align, str);
        if(strName.length())
        {
                //painter.setFont(SB_FONT_4());
                painter.drawText(x+painter.fontMetrics().width(str)+10,y,w,h,align,strName);
        }
        pLabel->setPixmap(pmap);
}


//////////////////////////////////////////////////////////////////////////
void uiLcdSetLabelText2(QLabel *pLabel, QString str, QColor color,QColor edge_color /*= FOREGROUND_COLOR1*/ ,QString strName /*= QString("")*/)
{
        if (!pLabel)
                return;
        const int x = 1;
        const int y = 1;
        int w = pLabel->width();
        int h = pLabel->height();
        // 	int r = FOREGROUND_COLOR1.red()/*color.red()*/;
        // 	int g = FOREGROUND_COLOR1.green()/*color.green()*/;
        // 	int b = FOREGROUND_COLOR1.blue()/*color.blue()*/;
        int r = edge_color.red()/*color.red()*/;
        int g = edge_color.green()/*color.green()*/;
        int b = edge_color.blue()/*color.blue()*/;
        int align = (int)pLabel->alignment();
        QPixmap pmap(w, h);
        pmap.fill(QColor(Qt::transparent));

        QPainter painter(&pmap);
        //painter.setFont(pLabel->font());
        //pLabel->setFont(SB_FONT_4());
        painter.setFont(pLabel->font());
        if(edge_color.isValid())
        {
                painter.setPen(QColor(255 - r, 255 - g, 255 - b, 64));
                painter.drawText(x-1, y-1, w, h, align, str);
                painter.setPen(QColor(255 - r, 255 - g, 255 - b, 100));
                painter.drawText(x-1, y+1, w, h, align, str);
                painter.drawText(x+1, y-1, w, h, align, str);
                painter.setPen(QColor(255 - r, 255 - g, 255 - b, 128));
                painter.drawText(x+1, y+1, w, h, align, str);
        }
        //painter.setPen(QColor(r, g, b, 255));
        painter.setPen(color);
        painter.drawText(x, y, w, h, align, str);
        if(strName.length())
        {
                //painter.setFont(SB_FONT_4());
                painter.drawText(x+painter.fontMetrics().width(str)+10,y,w,h,align,strName);
        }
        pLabel->setPixmap(pmap);
}

//////////////////////////////////////////////////////////////////////////
void uiLcdDrawText0(QPainter *painter, int x, int y, int w, int h, int align, QString str, QColor color, QColor edge_color /*= FOREGROUND_COLOR1*/)
{
        if (!painter)
                return;
// 	int r = FOREGROUND_COLOR1.red()/*color.red()*/;
// 	int g = FOREGROUND_COLOR1.green()/*color.green()*/;
// 	int b = FOREGROUND_COLOR1.blue()/*color.blue()*/;
        int r = edge_color.red()/*color.red()*/;
        int g = edge_color.green()/*color.green()*/;
        int b = edge_color.blue()/*color.blue()*/;

        if(edge_color.isValid())
        {
                painter->setPen(QColor(255 - r, 255 - g, 255 - b, 64));
                painter->drawText(x-1, y-1, w, h, align, str);
                painter->setPen(QColor(255 - r, 255 - g, 255 - b, 100));
                painter->drawText(x-1, y+1, w, h, align, str);
                painter->drawText(x+1, y-1, w, h, align, str);
                painter->setPen(QColor(255 - r, 255 - g, 255 - b, 128));
                painter->drawText(x+1, y+1, w, h, align, str);
        }
        painter->setPen(color);
        painter->drawText(x, y, w, h, align, str);
}
