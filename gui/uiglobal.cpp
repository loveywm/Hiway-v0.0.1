//#include "uiglobal.h"
#include <QPainter>
#include <QtGui/QLineEdit>
#include <QtGui/QComboBox>
#include <QDebug>


//#include <time.h>
#include <sys/time.h>
#include "Define.h"

extern DWORD  g_uiTimeLastAction;

//////////////////////////////////////////////////////////////////////////
void uiLcdSetLabelText(QLabel *pLabel, QString str, QColor color,QColor edge_color /*= FOREGROUND_COLOR1*/ ,QString strName /*= QString("")*/)
{
    if (!pLabel)
        return;
    const int x = 1;
    const int y = 1;
    int w = pLabel->width();
    int h = pLabel->height();
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
        //painter.setFont(SB_FONT_12());
        painter.drawText(x+painter.fontMetrics().width(str)+10,y,w,h,align,strName);
    }
    pLabel->setPixmap(pmap);
}

void uiLcdDrawText(QPainter *painter, int x, int y, int w, int h, int align, QString str, QColor color, QColor edge_color /*= FOREGROUND_COLOR1*/)
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

////////////////////////////下面几个是时间函数，主要获取间隔时间/////////////////////////////////////////
int GetMainTickCount(void)
{
    static int __start_time = 0; //second
    struct timeval tv;

    gettimeofday(&tv, NULL);

    if (__start_time == 0)
        __start_time = tv.tv_sec;

    return ((tv.tv_sec - __start_time) * 1000 + tv.tv_usec / 1000);//秒数*1000+微秒/1000就全部转换为毫秒
}

void uiTimeSetLastActionTime(void)
{
    g_uiTimeLastAction = GetMainTickCount();
}

DWORD uiTimeGetIdleTime(void)
{
    return GetMainTickCount() - g_uiTimeLastAction;
}

BOOL uiTimeIsTimeout(DWORD dwTimeout)
{
    BOOL bRet;
    //bRet = (uiPowerGetStatus() != -1);
    bRet = (uiTimeGetIdleTime() >= dwTimeout);
    //qDebug() <<"bRet==" << bRet;
    return bRet;
}

//////////////////////////////////////////////////////////

void SET_DLG_ITEM_COLOR(QWidget *w,int colorFlag /*= 0*/)
{
    int i;

    QPalette pal_title = w->palette();
    GUI_DLG_SET_FORE_COLOR(&pal_title, TITLECOLOR);

    QLabel* pTilte = w->findChild<QLabel*>("lblTitleText");
    QList<QLabel*> labelList = w->findChildren<QLabel*>();
    QList<QLineEdit*> editList = w->findChildren<QLineEdit*>();
    QList<QComboBox*> comboList = w->findChildren<QComboBox*>();

    QPalette pal = w->palette();
    if(colorFlag == 0)
            GUI_DLG_SET_FORE_COLOR(&pal, FOREGROUND_COLOR0);
    if(colorFlag == 1)
            GUI_DLG_SET_FORE_COLOR(&pal, FOREGROUND_COLOR1);

    for (i=0; i<labelList.size(); i++)
            labelList[i]->setPalette(pal);
    for (i=0; i<editList.size(); i++)
            editList[i]->setPalette(pal);
    for (i=0; i<comboList.size(); i++)
            comboList[i]->setPalette(pal);

    if(pTilte != 0)
    {
            pTilte->setPalette(pal_title);
            //pTilte->setFont(SB_FONT_2());
    }

}
