
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

    //CMenu m(g_MainWindow);
    //m.show();
    //m.MenuProc(UISTR_MENU_MAINMENU);
/*while(1){
    //g_MainWindow->show();
    QApplication::processEvents();
    //g_MainWindow->
    //qDebug() << "keycode==ok"<< 1;
    BOOL keycode = 0;
    keycode = GetKey();
    switch(keycode)
    {
        case 13:
            qDebug() << "keycode==ok"<<13;
            //m.hide();
            break;
        case 19:
            qDebug() << "keycode==menu"<<19;
            //m.show();
            //m.MenuProc(UISTR_MENU_MAINMENU);
            break;
        case 14:
            qDebug() << "keycode==up"<<14;
            break;
        case 15:
            qDebug() << "keycode==down"<<15;
            break;
        case 1:
            qDebug() << "keycode==left"<<1;
            //m.hide();
            break;
        case 2:
            qDebug() << "keycode==right"<<2;
            break;
        default:
            break;

    }
}*/

    while(TRUE)
    {
        CMainWindow *w = new CMainWindow;
        if(w)
        {
            uiProcMain(bFirst);
            delete w;
        }
        bFirst = FALSE;
    }

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
