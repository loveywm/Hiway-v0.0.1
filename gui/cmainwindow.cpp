#include "cmainwindow.h"
#include "ui_cmainwindow.h"
#include <QPixmap>
#include <QDebug>
#include <QTimer>
#include <QTime>
#include <QDate>
#include <QLabel>

#include "../hiwaylib.h"
#include "Define.h"
#include "menu.h"


/////////////////////////////////////////////////
void uiProcMain(BOOL bFirst);
CMainWindow *g_MainWindow = NULL;
extern unsigned int nTouchX, nTouchY, nTouchPress;
void uiProcBuildMenu(void);

/////////////////////////////////////////////////
void uiProcKeyboardManager(void)
{
    int nKey;
    nKey = GetKey();
    if(nKey == UIKEY_NONE)
    {
        return;
    }
    if(nKey == UIKEY_2)//right
    {
        qDebug() << "nKey == UIKEY_2";
    }
    else if (nKey == UIKEY_MENU)
    {
        CMenu m(g_MainWindow);
        m.show();
        m.MenuProc(UISTR_MENU_MAINMENU);
    }

/*
   uiGetTs();
   if ((nTouchX >= Ts_MainWindowNum_Min_X) && (nTouchX <= Ts_MainWindowNum_Max_X) && (nTouchY >= Ts_MainWindowNum_Min_Y) && (nTouchY <= Ts_MainWindowNum_Max_Y))
   {
           qDebug("nTouchX1==%d",nTouchX);
           qDebug("nTouchY1==%d",nTouchY);
           qDebug("uiProcKeyboardManager");
           return;
   }
   qDebug("nTouchX2==%d",nTouchX);
   qDebug("nTouchY2==%d",nTouchY);
*/
}
void uiProcKeyboardManager_pc(void)
{
    int nKey;
    //nKey = GetKey();
    nKey = g_keyvalue;
    if(nKey == UIKEY_NONE)
    {
        return;
    }
    if(nKey == UIKEY_2)//right
    {
        qDebug() << "nKey == UIKEY_2";
    }
    else if (nKey == UIKEY_MENU)
    {
        CMenu m(g_MainWindow);
        m.show();
        m.MenuProc(UISTR_MENU_MAINMENU);
    }

/*
   uiGetTs();
   if ((nTouchX >= Ts_MainWindowNum_Min_X) && (nTouchX <= Ts_MainWindowNum_Max_X) && (nTouchY >= Ts_MainWindowNum_Min_Y) && (nTouchY <= Ts_MainWindowNum_Max_Y))
   {
           qDebug("nTouchX1==%d",nTouchX);
           qDebug("nTouchY1==%d",nTouchY);
           qDebug("uiProcKeyboardManager");
           return;
   }
   qDebug("nTouchX2==%d",nTouchX);
   qDebug("nTouchY2==%d",nTouchY);
*/
}


////////////////////////////////////////////////
#define UIPROC_WRAPPER(_f_)	{POST_EVENTS(); (_f_);}
////////////////////////////////////////////////
void uiProcMain(BOOL bFirst)
{
    qDebug() << "i am in uiProcMain!";
    if(g_MainWindow == NULL)
    {
        qDebug() << "g_MainWindow = NULL";
        return;
    }

    uiProcBuildMenu();


    //QApplication::processEvents();
    g_MainWindow->DrawClock(TRUE);
    g_MainWindow->show();
    QApplication::processEvents();
    //sleep(2);
    while(1)
    {
        //uiProcKeyboardManager();
        //g_MainWindow->show();
        //sleep(1);
        //CMenu m(g_MainWindow);
        //m.show();
        //m.MenuProc(UISTR_MENU_MAINMENU);
        UIPROC_WRAPPER(uiProcKeyboardManager_pc());
        //UIPROC_WRAPPER(VerifyLoop());



        //QApplication::processEvents();
        //g_MainWindow->DrawClock(TRUE);

    }


}





///////////////////////////////////////////////////////
CMainWindow::CMainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CMainWindow)
{
    ui->setupUi(this);
    GUI_DLG_IMPL(TRUE);
    //QApplication::processEvents();

    //ui->lblMenu.
    qDebug() << "CMainWindow init!";

    ui->lblBackground->setPixmap(QPixmap(":/images/res/backgroup.png"));
    //ui->lblMenu->setPixmap(QPixmap(":/images/res/menu.png"));
    //ui->lblNum->setPixmap(QPixmap(":/images/res/num.png"));

    //设置palTime的调色板
    QPalette palTime = ui->lblTime->palette();
    palTime.setColor(QPalette::All,QPalette::WindowText,QColor(255,255,214));
    ui->lblTime->setPalette(palTime);
    //ui->lblTime->setFont(SB_FONT_15());
    //ui->lblDate->setFont(SB_FONT_13());

    //ui->lblTime->setAlignment(Qt::Alignment);
    //ui->lblDate->setAlignment(Qt::Alignment);

    //Rtc_Set_time(2013,11,21,4,14,56,02);



    g_MainWindow = this;

    QTimer::singleShot(50,this,SLOT(OnTimer()));


}

CMainWindow::~CMainWindow()
{
    delete ui;
}

void CMainWindow::OnTimer()
{
    static DWORD __wdog_prev_time = 0;
    int i;
    //DWORD dwCurrentTime = uiTimeGetTickCount();
    DWORD dwCurrentTime = GetMainTickCount();

    if (dwCurrentTime - __wdog_prev_time > 1000)
    {
            //wdog_app_alive();
            __wdog_prev_time = dwCurrentTime;
            //if (g_bDeviceBusy)
            DrawClock();
    }

    //__timerLedControl();

/*    if (!g_bDeviceBusy)
    {
            for (i = 0; i < MAX_TIMER_COUNT; i++)
            {
                    if (!g_TimerList[i].dwTimerID)
                            continue;
                    if (dwCurrentTime - g_TimerList[i].dwProcessedTime >= (DWORD)g_TimerList[i].nElapse)
                    {
                            g_TimerList[i].dwProcessedTime = dwCurrentTime;
                            uiProcOnTimer(this, g_TimerList[i].dwTimerID, g_TimerList[i].dwParam);
                    }
            }
    }
 */
    QTimer::singleShot(50, this, SLOT(OnTimer()));

}

void CMainWindow::DrawClock(BOOL bFirst /*bFirst = FALSE*/)
{
   //QPixmap pmap = m_ClockPixmap;
   //QPainter painter(&pmap);
   int nYear, nMonth, nDay, nWeekday, nHour, nMinute, nSecond;

   QDate date = QDate::currentDate();
   QTime time = QTime::currentTime();
   nYear = date.year();
   nMonth = date.month();
   nDay = date.day();
   //nWeekday = date.weekNumber();
   nHour = time.hour();
   nMinute = time.minute();
   nSecond = time.second();

   //embedded
   //Rtc_Get_time(&nYear,&nMonth,&nDay,&nWeekday,&nHour,&nMinute,&nSecond);

   //char szBuffer[12];
   //uiRtcGet(&nYear, &nMonth, &nDay, &nWeekday, &nHour, &nMinute, &nSecond);
   //g_uiProcStatus.dwCurrentSecond = uiRtcGetSeconds(nYear, nMonth, nDay, nHour, nMinute, nSecond);

/*   if( nBackgroupIconFile != dbSetupTotal.setSystem.nBackgroupIconFile )
   {
            switch(dbSetupTotal.setSystem.nBackgroupIconFile + UISTR_BK_START)
            {
                    case UISTR_BK_1:
                                    ui.lblBackground->setPixmap(QPixmap(GUI_RESOURCE_PATH"backgroup1.png"));
                                    break;
                    case UISTR_BK_2:
                                    ui.lblBackground->setPixmap(QPixmap(GUI_RESOURCE_PATH"backgroup2.png"));
                                    break;
                    case UISTR_BK_3:
                                    ui.lblBackground->setPixmap(QPixmap(GUI_RESOURCE_PATH"backgroup3.png"));
                                    break;
                    case UISTR_BK_4:
                                    ui.lblBackground->setPixmap(QPixmap(GUI_RESOURCE_PATH"backgroup4.png"));
                                    break;
                    case UISTR_BK_5:
                                    ui.lblBackground->setPixmap(QPixmap(GUI_RESOURCE_PATH"backgroup5.png"));
                                    break;
                    case UISTR_BK_6:
                                    ui.lblBackground->setPixmap(QPixmap(GUI_RESOURCE_PATH"backgroup6.png"));
                                    break;
                    default:
                                ui.lblBackground->setPixmap(QPixmap(GUI_RESOURCE_PATH"backgroup1.png"));
                                break;
            }
            nBackgroupIconFile = dbSetupTotal.setSystem.nBackgroupIconFile;
    }
*/
    //sprintf(szBuffer, ":%02d", nSecond);
    //uiLcdSetLabelText(ui.lblAMPM, szBuffer, QColor(255, 255, 200), QColor(255, 255, 255));

    //if (bFirst || !nSecond)
    {
        char szBuf[15];
        //char
        //int __weekday_list[] = {UISTR_WEEKDAY_SUN, UISTR_WEEKDAY_MON, UISTR_WEEKDAY_TUE, UISTR_WEEKDAY_WED, UISTR_WEEKDAY_THU, UISTR_WEEKDAY_FRI, UISTR_WEEKDAY_SAT};
        //DWORD dwSeconds;
        //dwSeconds = uiRtcGetSeconds();
        //uiRtcGetDate(dwSeconds);
        //uiLcdSetLabelText(ui.lblMonth, uiRtcGetDate(dwSeconds), QColor(255, 255, 200), QColor(255, 255, 255));

        sprintf(szBuf, "%04d-%02d-%02d",nYear,nMonth,nDay);
        uiLcdSetLabelText(ui->lblDate, szBuf, QColor(255, 255, 0), QColor(255, 255, 255));

        sprintf(szBuf, "%02d:%02d:%02d", nHour, nMinute,nSecond);
        //sprintf(szBuf, "%02d:%02d",nHour,nMinute);
        uiLcdSetLabelText(ui->lblTime, szBuf, QColor(255, 255, 0), QColor(255, 255, 255));
        //uiLcdSetLabelText(ui.lblWeekday, UISTR(__weekday_list[nWeekday - 1]), QColor(255, 255, 214), QColor(255, 255, 255));
    }


}

void CMainWindow::keyPressEvent(QKeyEvent *e)
{
    //g_keyvalue = 0;
    switch (e->key())
    {
       case Qt::Key_W : qDebug() << "Up!";break;
       case Qt::Key_S : qDebug() << "Down";  g_keyvalue = UIKEY_DOWN;break;
       case Qt::Key_A : qDebug() << "Left"; break;
       case Qt::Key_D : qDebug() << "Right"; break;
       case Qt::Key_M : qDebug() << "Menu"; g_keyvalue = UIKEY_MENU;break;
    }
}
