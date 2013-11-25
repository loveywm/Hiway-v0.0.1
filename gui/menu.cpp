#include "menu.h"
#include "Define.h"
#include <QDebug>
//#include "xxx.h"
#include <QIcon>
#include <QPainterPath>
#include "../global.h"
#include "ui_cmainframe.h"

#define SELECTED_ITEM_FILENAME "selected-item.png"
#define RESOURCE_PATH	":/images/res/"
#define MENUITEM_ICONSTYLE_SIZE         68
#define MENUITEM_COLS       3
#define MENU_ICON_TOPMARGIN		10

typedef enum//菜单的几种类型枚举
{
    // 0,1,2,... = parent & title, UISTR_SPACE - top menu
    UIMENU_POPUP = -1,//有二级标题
    UIMENU_HASVALUE = -2,//有下拉设置值
    UIMENU_CUSTOM = -3,
    UIMENU_CUSTOM_HASCHILD = -4,
    UIMENU_NOACTION = -5,
    UIMENU_TITLE = -6//标题
} T_UI_MENUITEM_TYPE;

typedef enum
{
    UIMENU_ICON,
    UIMENU_REPORT,
    UIMENU_REPORT_NOICON,
    UIMENU_CUSTOMDRAW
} T_UI_MENUITEM_LISTSTYLE;


typedef struct//标题数据结构
{
    int nMenuStr;//标题命名
    int nType;//标题类型“T_UI_MENUITEM_TYPE”
    const char* szIconFile;//连接标题图标
    int nHelpStr;//备用
} T_UI_MENUITEM;

//日后添加标题都在这两添加
T_UI_MENUITEM g_uiMenuItemsSrc[] =
{
    {UISTR_MENU_MAINMENU, UIMENU_TITLE, (const char*)UIMENU_ICON, -1},
    //{UISTR_MENU_USERMANAGE, UIMENU_POPUP, "FP.png", -1},
    {UISTR_MENU_USERMANAGE, UIMENU_POPUP, "USERMANAGE.png", -1},
    {UISTR_MENU_DATAVIEW, UIMENU_POPUP, "DATAVIEW.png", -1},
    {UISTR_MENU_USBMANAGE, UIMENU_POPUP, "USBMANAGE.png", -1},
    {UISTR_MENU_SYSTEMSETTING, UIMENU_POPUP, "SYSTEMSETTING.png", -1},
    {UISTR_MENU_SYSINFOVIEW, UIMENU_POPUP, "SYSINFOVIEW.png", -1},


    {-1, UIMENU_TITLE, NULL, -1}
};

//声明存放标题数组
T_UI_MENUITEM g_uiMenuItems[ITEM_CNT(g_uiMenuItemsSrc)];

int g_uiMenuItemTitle = UISTR_MENU_MAINMENU;
int g_uiMenuItemIndex = 1;//标题项目索引
int g_uiMenuTopIndex = 1;//标题项目顶端位置标志

extern DWORD	g_uiTimeLastAction;//记录前一次操作的时间


//函数作用就是将g_uiMenuItemsSrc数组复制到g_uiMenuItems中，可以排除其中不用的标题索引
void uiProcBuildMenu(void)//构建主题菜单，需要第一步初始化
{
    int i, j=0;
    for (i=0; i<(int)ITEM_CNT(g_uiMenuItemsSrc); i++)
    {
        g_uiMenuItems[j] = g_uiMenuItemsSrc[i];
        j++;
    }
}

//获取标题索引下面索引到下个标题索引之间的索引位置
//from=开始，to=下一个标题之前索引
BOOL uiProcMenuGetCurrentRange(int *from, int *to)
{
    int start, end;
    BOOL bRet = FALSE;
    start = 0;
    while (1)//获取开始标题
    {
        if (g_uiMenuItems[start].nMenuStr == -1)
            goto _lExit;
        if ((g_uiMenuItems[start].nMenuStr == g_uiMenuItemTitle) && (g_uiMenuItems[start].nType == UIMENU_TITLE))
            break;
        start++;
    }
    start++;//开始是从title+1开始
    end = start;//end从start开始
    while (1)//获取下一个标题
    {
        if (g_uiMenuItems[end].nMenuStr == -1)
            break;
        if (g_uiMenuItems[end].nType == UIMENU_TITLE)
            break;
        end++;
    }
    *from = start;
    *to = end - 1;//结束是“后一个标题”-1

    bRet = TRUE;
_lExit:
    return bRet;
}

//获取传入nItemStr的title索引，并返回索引
int uiProcMenuTitleIndex(int nItemStr)
{
    int i = 0;
    //遍历索引数组
    while (g_uiMenuItems[i].nMenuStr != -1)//跳出条件，索引数组最后一个是-1
    {
        //满足下面两个条件就返回索引
        if ((g_uiMenuItems[i].nMenuStr == nItemStr) && (g_uiMenuItems[i].nType == UIMENU_TITLE))
            return i;
        i++;
    }
    return -1;
}
//menu的初始化设置
void MenuSettingStart(BOOL bFirst = FALSE)
{

}
void MenuSettingEnd(int nStrTitle)
{

}


CMenu::CMenu(QWidget *parent /* = NULL */)
    : CMainFrame(parent)
{
    m_bTerminateFlag = FALSE;
    g_uiTimeLastAction = GetMainTickCount();
    uiProcBuildMenu();

}
//进入标题主界面程序会第一执行下面函数
void CMenu::MenuProc(int nPopupMenuTitle /* = -1 */)
{
    int nkey;
    qDebug() << "nkey=="<<nkey;
    _lstart:
    if(nPopupMenuTitle == -1)//默认值
    {
        MenuSettingStart(TRUE);
        nPopupMenuTitle = UISTR_MENU_MAINMENU;//取其作为默认值
    }
    g_uiMenuItemTitle = nPopupMenuTitle;//设置title位置
    g_uiMenuItemIndex = uiProcMenuTitleIndex(nPopupMenuTitle) + 1;//取title下面第一个Index
    g_uiMenuTopIndex = g_uiMenuItemIndex;//设置title下面第一个为top索引
    qDebug() << "nPopupMenuTitle=="<<nPopupMenuTitle;
    qDebug() << "g_uiMenuItemTitle=="<<g_uiMenuItemTitle;
    qDebug() << "uiProcMenuTitleIndex(nPopupMenuTitle)+1=="<<uiProcMenuTitleIndex(nPopupMenuTitle);
    qDebug() << "g_uiMenuItemIndex=="<<g_uiMenuItemIndex;
    qDebug() << "g_uiMenuTopIndex=="<<g_uiMenuTopIndex;

    OnRedraw();

    while (!m_bTerminateFlag && uiTimeIsTimeout(5000) == FALSE)
    {

        QApplication::processEvents();
        //qDebug() << "m_bTerminateFlag=="<<m_bTerminateFlag;
        //g_uiBuildMenu = 1;
        if(g_uiBuildMenu && nPopupMenuTitle == UISTR_MENU_MAINMENU)
        {
            g_uiBuildMenu = FALSE;
            //qDebug() << "xxx";
            uiProcBuildMenu();
            goto _lstart;
        }
    }

    MenuSettingEnd(nPopupMenuTitle);
    //GUI_DLG_SET_THEME();


}

void CMenu::OnRedraw()
{
    int nTitleIndex = uiProcMenuTitleIndex(g_uiMenuItemTitle);

    if(g_uiMenuItemTitle == UISTR_MENU_SYSINFOVIEW)
    {
/*        setTitle(QString(RESOURCE_PATH) + QString(g_uiMenuItems[g_uiMenuItemIndex].szIconFile),
                UISTR(UISTR_SYMBOL_BRACKET_ON) +
                UISTR(g_uiMenuItemTitle) +
                UISTR(UISTR_SYMBOL_BRACKET_OFF));
        uiLcdSetLabelText(ui.lblTitleText1, UISTR(UISTR_UNIT_TOTAL), TITLECOLOR);
        ui.lblTitleText1->show();
*/   }
     else
     {
        //this->lblTitleText1->hide();
        setTitle(QString(RESOURCE_PATH) + QString(g_uiMenuItems[g_uiMenuItemIndex].szIconFile),
                /*UISTR(UISTR_SYMBOL_BRACKET_ON) +*/ QString("[")
                + UISTR(g_uiMenuItemTitle)
                /*UISTR(UISTR_SYMBOL_BRACKET_OFF)*/+ QString("]") + QString("-") +
                UISTR(g_uiMenuItems[g_uiMenuItemIndex].nMenuStr));
      }
      if ((int)(g_uiMenuItems[nTitleIndex].szIconFile) == UIMENU_ICON)//
      {
          //预留显示信息
          uiLcdSetLabelText(ui->lblStatusText, QString("I love ywm!")/*UISTR("Click it")*/, FOREGROUND_COLOR0);

      }
      else
      {
          //同上
          uiLcdSetLabelText(ui->lblStatusText, QString("I love world!")/*UISTR(UISTR_MENU_USERMANAGE)*/, FOREGROUND_COLOR1);
      }
      update();
}

void CMenu::paintEvent(QPaintEvent *e)
{
    CMainFrame::paintEvent(e);
    QPixmap pmap = m_pmapFrame;
    QPainter painter(&pmap);

    qDebug() << "paintEvent";

    int title, from, to;
    title = uiProcMenuTitleIndex(g_uiMenuItemTitle);

    qDebug() << "title=="<<title;
    qDebug() << "from=="<<from;
    qDebug() << "to=="<<to;

    if (uiProcMenuGetCurrentRange(&from, &to))
    {
            qDebug() << "from1=="<<from;
            qDebug() << "to1=="<<to;
            switch ((int)(g_uiMenuItems[title].szIconFile))
            {
                case UIMENU_ICON:
                    qDebug() << "UIMENU_ICON";
                    drawIconStyle(&painter, g_uiMenuItemIndex, from, to);
                    break;
                case UIMENU_REPORT:
                    qDebug() << "UIMENU_REPORT";
                    //drawReportStyle(&painter, g_uiMenuItemIndex, from, to, TRUE);
                    break;
                case UIMENU_REPORT_NOICON:
                    qDebug() << "UIMENU_REPORT_NOICON";
                    //drawReportStyle(&painter, g_uiMenuItemIndex, from, to, FALSE);
                    break;
                case UIMENU_CUSTOMDRAW:
                {
                    //funcMenuCustomDraw fp = (funcMenuCustomDraw)g_uiMenuItems[title].nHelpStr;
                    //if ((int)fp == -1)
                        //break;
                    //fp(this, &painter, g_uiMenuItems, from, to);
                    qDebug() << "UIMENU_CUSTOMDRAW";
                }
                break;
            }

    }
    ui->lblBackgroundFrame->setPixmap(pmap);
    //this->lblBackgroundFrame->setPixmap(pmap);
}

void CMenu::drawIconStyle(QPainter *painter, int nCurrentIndex, int from, int to)
{
        painter->save();
        painter->setRenderHint(QPainter::Antialiasing);

        int i;
        int x, y, w, h, w_spacer, h_spacer;
        T_UI_MENUITEM *item;

        w = MENUITEM_ICONSTYLE_SIZE; h = MENUITEM_ICONSTYLE_SIZE;
        w_spacer = (painter->window().width() - w * MENUITEM_COLS) / (MENUITEM_COLS + 1);
        h_spacer = 15;
        x = m_nFrameX + w_spacer;
        y = MENU_ICON_TOPMARGIN + m_nFrameY - h - h_spacer;
        //y = m_nFrameY + h_spacer;
/*
        qDebug() << "w==" << w;
        qDebug() << "h==" << h;
        qDebug() << "h_spacer==" << h_spacer;
        qDebug() << "w_spacer==" << w_spacer;
        qDebug() << "x==" << x;
        qDebug() << "y==" << y;
        qDebug() << "painter->window().width()==" << painter->window().width();
        qDebug() << "w * MENUITEM_COLS==" << w * MENUITEM_COLS;
        qDebug() << "MENUITEM_COLS==" << MENUITEM_COLS;
*/

        for (i=from; i<=to; i++)
        {
            if ((i - from) % MENUITEM_COLS == 0)
            {
                //qDebug() << "(i - from) % MENUITEM_COLS==" << (i - from) % MENUITEM_COLS;
                x = m_nFrameX + w_spacer;
                y += h + h_spacer;
            }

            qDebug() << "i==" << i;
            qDebug() << "nCurrentIndex==" << nCurrentIndex;

            item = &g_uiMenuItems[i];
            //qDebug() << "nMenuStr==" << g_uiMenuItems[i].nMenuStr;
            //qDebug() << "szIconFile==" << g_uiMenuItems[i].szIconFile;
            //qDebug() << "nType==" << g_uiMenuItems[i].nType;

            if (nCurrentIndex == i)
            {
                QPixmap pmap_sel(QString(RESOURCE_PATH) + QString(SELECTED_ITEM_FILENAME));
                QPainterPath roundPath = CustomStyle::roundRectPath(QRect(x, y, w, h));
                painter->setClipPath(roundPath);
                painter->drawPixmap(x, y, w, h, pmap_sel, 0, 0, pmap_sel.width(), pmap_sel.height());
                painter->setClipPath(roundPath, Qt::NoClip);
                qDebug() << "love1";
            }
            else
            {
                painter->setPen(QPen(QColor(74,74,74),1,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
                painter->setBrush(QColor(20,20,20));
                painter->drawRoundRect(x, y, w, h, 20, 15);
                qDebug() << "love2";
            }

            QIcon ico(QString(RESOURCE_PATH) + QString(item->szIconFile));
            //qDebug() << "xxx" << QString(RESOURCE_PATH) + QString(item->szIconFile);
            ico.paint(painter, x, y, MENUITEM_ICONSTYLE_SIZE, MENUITEM_ICONSTYLE_SIZE, Qt::AlignCenter, QIcon::Normal);

            QString str = UISTR(item->nMenuStr);
            if (painter->fontMetrics().width(str) >= w)
            {
                while (str.length() > 1 && painter->fontMetrics().width(str) >= w - painter->fontMetrics().width("..."))
                    str.resize(str.length() - 1);
                str.append("...");
            }

            x = x + w + w_spacer;
        }

        painter->restore();
        //while(1){sleep(5);}
}



