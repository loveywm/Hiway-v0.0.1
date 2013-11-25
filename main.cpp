
#include <QApplication>
#include <QTranslator>
#include <QDebug>

#include "../gui/cmainframe.h"
#include "../gui/menu.h"
#include "../gui/cmainwindow.h"
#include "global.h"

extern CMainWindow *g_MainWindow;


//#include "Define.h"

BOOL HIWAY_LOAD(void);
void uiProcMain(BOOL bFirst);

int main(int argc, char *argv[])
{
    BOOL bFirst = TRUE;
    QApplication a(argc, argv);

    QTranslator translator;
    translator.load("./hiway.qm");
    a.installTranslator(&translator);

    if(!HIWAY_LOAD())
    {
        qDebug() << "HIWAY_LOAD Failed!!!";
        return FALSE;
    }
    //CMainFrame w;
    //w.show();
    //CMainWindow w;
    //w.show();
    CMenu m;
    //m.show();
    //m.MenuProc(UISTR_MENU_MAINMENU);
    //CMenu m(g_MainWindow);
    m.show();
    m.MenuProc(UISTR_MENU_MAINMENU);


    //g_MainWindow->DrawClock(TRUE);

/*
    while(TRUE)
    {
        CMainWindow *w = new CMainWindow;
        if(w)
        {
            w->DrawClock(TRUE);
            w->show();
            //ui->show();

            //sleep(3);
            //CMenu m(g_MainWindow);
            //CMenu m;
            //m.show();
            int xxx = 1;
            while(1)
            {
                //CMenu m(g_MainWindow);
                CMenu m(g_MainWindow);
                if(xxx == 1)
                {

                    m.show();
                    m.MenuProc(UISTR_MENU_MAINMENU);
                    sleep(1);
                    xxx = 2;
                    qDebug() << "xxx =1 ";
                }

                if(xxx == 2)
                {
                    m.hide();
                    m.MenuProc(UISTR_MENU_MAINMENU);
                    sleep(1);
                    xxx = 1;
                    qDebug() << "xxx =2";
                }
                //m.show();
                //m.MenuProc(UISTR_MENU_MAINMENU);
                //sleep(2);
                //g_MainWindow->DrawClock(TRUE);
                //g_MainWindow->show();
                //m.hide();
            }
            //uiProcMain(bFirst);
            //delete w;
        }
        //bFirst = FALSE;
    }
*/
    //return FALSE;
    return a.exec();
}

BOOL HIWAY_LOAD(void)
{
    if(HIWAY_INIT0() != DEVERR_SUCCESS)
    {
        qDebug() << "HIWAY_INIT0 error!";
    }
    return TRUE;
}
