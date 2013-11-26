
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
    QApplication app(argc, argv);

    QTranslator translator;
    translator.load("./hiway.qm");
    app.installTranslator(&translator);

    if(!HIWAY_LOAD())
    {
        qDebug() << "HIWAY_LOAD Failed!!!";
        return FALSE;
    }
    //CMainFrame w;
    //w.show();

    //CMainWindow w;
    //w.show();

    //sleep(5);
    //g_MainWindow->DrawClock(TRUE);
    //g_MainWindow->show();
    //sleep(15);
    //a.exec();
    //qDebug() << "keycode==ok";
    CMenu m(g_MainWindow);
    m.show();
    m.MenuProc(UISTR_MENU_MAINMENU);
while(1){
    //g_MainWindow->show();
    //g_MainWindow->
    //qDebug() << "keycode==ok"<< 1;
    BOOL keycode = 0;
    keycode = GetKey();
    switch(keycode)
    {
        case 13:
            qDebug() << "keycode==ok"<<13;
            break;
        case 19:
            qDebug() << "keycode==menu"<<19;
            break;
        case 14:
            qDebug() << "keycode==up"<<14;
            break;
        case 15:
            qDebug() << "keycode==down"<<15;
            break;
        case 1:
            qDebug() << "keycode==left"<<1;
            break;
        case 2:
            qDebug() << "keycode==right"<<2;
            break;
        default:
            break;

    }
}

 /*   while(TRUE)
    {
        CMainWindow *w = new CMainWindow;
        if(w)
        {
            w->DrawClock(TRUE);
            w->show();
            //CMenu m(g_MainWindow);
            //m.show();
            //m.MenuProc(UISTR_MENU_MAINMENU);
            //m.hide();
            int xxx = 1;
            while(1)
            {
                if(xxx == 1)
                {
                    //m.show();
                    //m.MenuProc(UISTR_MENU_MAINMENU);
                    //m.update();
                    //update();
                    sleep(1);
                    xxx = 2;
                    qDebug() << "xxx =1 ";
                }
                if(xxx == 2)
                {
                    //m.hide();
                    //m.MenuProc(UISTR_MENU_MAINMENU);
                    sleep(1);
                    xxx = 1;
                    qDebug() << "xxx =2";
                }
            }
            //uiProcMain(bFirst);
            //delete w;
        }
        //bFirst = FALSE;
    }*/

    //return FALSE;
    return app.exec();
}

BOOL HIWAY_LOAD(void)
{
    if(HIWAY_INIT0() != DEVERR_SUCCESS)
    {
        qDebug() << "HIWAY_INIT0 error!";
    }
    return TRUE;
}
