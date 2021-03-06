
#include <QApplication>
#include <QTranslator>
#include <QDebug>
#include <QtCore/QTextCodec>

#include "../gui/cmainframe.h"
#include "../gui/menu.h"
#include "../gui/cmainwindow.h"
#include "../gui/Define.h"
#include "../gui/customstyle.h"
#include "global.h"

extern CMainWindow *g_MainWindow;


//#include "Define.h"

BOOL HIWAY_LOAD(void);
void uiProcMain(BOOL bFirst);

int main(int argc, char *argv[])
{
    BOOL bFirst = TRUE;
    QApplication app(argc, argv);

    //app.setFont(SB_FONT_12());
    //app.setFont(SB_FONT_13(), "QLineEdit");

    //app.setStyle(new CustomStyle);
    QTextCodec::setCodecForTr(QTextCodec::codecForName(TEXTCODEC));


    QTranslator translator;
    translator.load("./hiway.qm");
    app.installTranslator(&translator);

    if(!HIWAY_LOAD())
    {
        qDebug() << "HIWAY_LOAD Failed!!!";
        return FALSE;
    }

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
        qDebug() << "HIWAY_LOAD::HIWAY_INIT0 error!";
    }

    //读取totle setup 系统运行使用的数据
    //BOOL bRet = DbSetupTotalRead();


    //加载用户数据，考勤数据等
    //if (!Db_LoadAllData(bRet))
    //{
        //qDebug() << "HIWAY_LOAD::Db_LoadAllData(bRet) error!";
        //return FALSE;
    //}




    return TRUE;
}
