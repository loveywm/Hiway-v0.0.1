#include "menu.h"
#include "Define.h"
#include <QDebug>
//#include "xxx.h"
#include <QIcon>
#include <QPainterPath>
#include "../global.h"
#include "ui_cmainframe.h"

QRect g_uiMenuCurrentArea;
#define SELECTED_ITEM_FILENAME "selected-item.png"
#define RESOURCE_PATH	":/images/res/"
#define MENUITEM_ICONSTYLE_SIZE         68
#define MENUITEM_COLS                   3
#define MENU_ICON_TOPMARGIN		10
#define MENUITEM_ROWS                   5

#define SCROLL_BG_FILENAME		"scroll-bg.png"
#define SCROLL_ITEM_FILENAME            "scroll-item.png"

#define MENU_PEN_COLOR			QColor(255,255,214)//FOREGROUND_COLOR
#define MENU_ITEM_SELET_COLOR           QColor(255,255,0)

#define MENU_ICON_TOPMARGIN		10
#define MENU_REPORT_LEFTMARGIN          5
#define MENU_ICON_DRAW_NUMBER           TRUE

static int __MENU_ICON_COL_CNT = 3;
static int __MENU_ICON_ITEM_SIZE = 68;

static const char * const __RIGHT_ARROW[] =
{
        "4 7 2 1",
        "   c None",
        "*  c #064CA4",
        "*   ",
        "**  ",
        "*** ",
        "****",
        "*** ",
        "**  ",
        "*   "
};



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
    {UISTR_MENU_MAINMENU,       UIMENU_TITLE,       (const char*)UIMENU_ICON,   -1},
    //{UISTR_MENU_USERMANAGE,   UIMENU_POPUP,       "FP.png",                   -1},
    {UISTR_MENU_USERMANAGE,     UIMENU_POPUP,       "USERMANAGE.png",           -1},
    {UISTR_MENU_DATAVIEW,       UIMENU_POPUP,       "DATAVIEW.png",             -1},
    {UISTR_MENU_USBMANAGE,      UIMENU_POPUP,       "USBMANAGE.png",            -1},
    {UISTR_MENU_SYSTEMSETTING,  UIMENU_POPUP,       "SYSTEMSETTING.png",        -1},
    {UISTR_MENU_SYSINFOVIEW,    UIMENU_POPUP,       "SYSINFOVIEW.png",          -1},

    {UISTR_MENU_USERMANAGE,     UIMENU_TITLE,       (const char*)UIMENU_ICON,   -1},
    {UISTR_MENU_ENROLLNEW,      UIMENU_CUSTOM,      "ENROLLNEW.png",            -1},
    {UISTR_MENU_ENROLLEDIT,     UIMENU_CUSTOM,      "ENROLLEDIT.png",           -1},
    {UISTR_MENU_ENROLLDEL,      UIMENU_CUSTOM,      "ENROLLDEL.png",            -1},


    {UISTR_MENU_SYSINFOVIEW,    UIMENU_TITLE,       (const char*)UIMENU_REPORT, -1},
    {UISTR_MENU_USERENROLLCOUNT,UIMENU_HASVALUE,    "USED_USERS.png",           -1},
    {UISTR_MENU_FPENROLLCOUNT,  UIMENU_HASVALUE,    "USED_FP.png",              -1},
    //{UISTR_MENU_PWDENROLLCOUNT, UIMENU_HASVALUE,    "USED_PWD.png",             -1},
    //{UISTR_MENU_CARDENROLLCOUNT,UIMENU_HASVALUE,    "USED_CARD.png",            -1},
    //{UISTR_MENU_GLOGCOUNT,      UIMENU_HASVALUE,    "USED_GLOG.png",            -1},
    //{UISTR_MENU_MLOGCOUNT,      UIMENU_HASVALUE,    "USED_MLOG.png",            -1},
    //{UISTR_MENU_USEDMEMORY,     UIMENU_HASVALUE,    "USED_MEMORY.png",          -1},
    //{UISTR_MENU_FREESPACES,   UIMENU_POPUP,       "FREESPACES.png",           -1},
    {UISTR_MENU_DEVICEINFO,     UIMENU_POPUP,       "DEVICEINFO.png",           -1},


    {-1,                        UIMENU_TITLE,       NULL,                       -1}
};

//声明存放标题数组
T_UI_MENUITEM g_uiMenuItems[ITEM_CNT(g_uiMenuItemsSrc)];

int g_uiMenuItemTitle = UISTR_MENU_MAINMENU;
int g_uiMenuItemIndex = 1;//标题项目索引
int g_uiMenuTopIndex = 1;//标题项目顶端位置标志
int g_uiPopupTitle = -1;//

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
//获取title下面子菜单的数目
int uiProcMenuGetItemCount(int nTitle)
{
    int nIndex = uiProcMenuTitleIndex(nTitle);
    if (nIndex >= (int)ITEM_CNT(g_uiMenuItems))
        return 0;
    if (g_uiMenuItems[nIndex++].nType != UIMENU_TITLE)//从0开始，需要提前+1
        return 0;

    int nCount= 0;
    while (g_uiMenuItems[nIndex].nType != UIMENU_TITLE)
    {
        nCount++;
        nIndex++;
    }

    return nCount;
}
//获取Item下面子菜单的对应显示值
QString uiProcMenuGetItemValue(int nItemStr)
{
    DWORD dwValue = 0;
    QString str;
    int a, b, c, d;
    char strTemp[16];

    switch (nItemStr)
    {
        case UISTR_MENU_USERENROLLCOUNT:
            str = QString("%1 / %3%4").arg(1000).arg(5000).arg("ywm");
            break;
        case UISTR_MENU_FPENROLLCOUNT:
            str = QString("%1 / %3%4").arg(200).arg(5000).arg("xxx");
            break;
        default:
            break;
    }

    if (!str.length())
        str = QString("%1").arg(dwValue);

    return str;
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
    //this->MenuProc(UISTR_MENU_MAINMENU);

}
//进入标题主界面程序会第一执行下面函数
void CMenu::MenuProc(int nPopupMenuTitle /* = -1 */)
{
    int nKey;
    //qDebug() << "nkey=="<<nkey;
 _lstart:
    if(nPopupMenuTitle == -1)//默认值
    {
        MenuSettingStart(TRUE);
        nPopupMenuTitle = UISTR_MENU_MAINMENU;//取其作为默认值
    }
    g_uiMenuItemTitle = nPopupMenuTitle;//设置title位置
    g_uiMenuItemIndex = uiProcMenuTitleIndex(nPopupMenuTitle) + 1;//取title下面第一个Index
    g_uiMenuTopIndex = g_uiMenuItemIndex;//设置title下面第一个为top索引
    //qDebug() << "nPopupMenuTitle=="<<nPopupMenuTitle;
    //qDebug() << "g_uiMenuItemTitle=="<<g_uiMenuItemTitle;
    //qDebug() << "uiProcMenuTitleIndex(nPopupMenuTitle)+1=="<<uiProcMenuTitleIndex(nPopupMenuTitle);
    //qDebug() << "g_uiMenuItemIndex=="<<g_uiMenuItemIndex;
    //qDebug() << "g_uiMenuTopIndex=="<<g_uiMenuTopIndex;

    OnRedraw();

    while (!m_bTerminateFlag && uiTimeIsTimeout(60000) == FALSE)
    {

        //QApplication::processEvents();
        POST_EVENTS();


        if(g_uiBuildMenu && nPopupMenuTitle == UISTR_MENU_MAINMENU)
        {
            g_uiBuildMenu = FALSE;
            //qDebug() << "xxx";
            uiProcBuildMenu();
            goto _lstart;
        }

        nKey = GetKey();
        switch(nKey)
        {
        case UIKEY_OK://13
            qDebug() << "keycode==ok"<<13;
            OnKeyPressOk(nPopupMenuTitle);
            //this->hide();
            break;
        case 19:
            qDebug() << "keycode==menu"<<19;
            //this->show();
            break;
        case UIKEY_UP://14
            qDebug() << "keycode==up"<<14;
            OnKeyPressArrow(nKey,nPopupMenuTitle);
            break;
        case UIKEY_DOWN://15
            qDebug() << "keycode==down"<<15;
            OnKeyPressArrow(nKey,nPopupMenuTitle);
            break;
        case UIKEY_1://UIKEY_ESC
            qDebug() << "keycode==esc"<<1;
            goto _ExitWithoutSave;
            break;
        case 2:
            qDebug() << "keycode==right"<<2;
            break;
        default:
            break;
        }
    }
    if(uiTimeIsTimeout(60000))
    {
        goto _ExitWithoutSave;
    }

    MenuSettingEnd(nPopupMenuTitle);
    GUI_DLG_SET_THEME();
    //update();

_ExitWithoutSave:

    return;
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

    //qDebug() << "paintEvent";

    int title, from, to;
    title = uiProcMenuTitleIndex(g_uiMenuItemTitle);

    //qDebug() << "title=="<<title;
    //qDebug() << "from=="<<from;
    //qDebug() << "to=="<<to;

    if (uiProcMenuGetCurrentRange(&from, &to))
    {
            //qDebug() << "from1=="<<from;
            //qDebug() << "to1=="<<to;
            switch ((int)(g_uiMenuItems[title].szIconFile))
            {
                case UIMENU_ICON:
                    //qDebug() << "UIMENU_ICON";
                    drawIconStyle(&painter, g_uiMenuItemIndex, from, to);
                    break;
                case UIMENU_REPORT:
                    //qDebug() << "UIMENU_REPORT";
                    drawReportStyle(&painter, g_uiMenuItemIndex, from, to, TRUE);
                    break;
                case UIMENU_REPORT_NOICON:
                    qDebug() << "UIMENU_REPORT_NOICON";
                    drawReportStyle(&painter, g_uiMenuItemIndex, from, to, FALSE);
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

//绘制szIconFile类型为UIMENU_ICON的标题
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

            //qDebug() << "i==" << i;
            //qDebug() << "nCurrentIndex==" << nCurrentIndex;

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
                //qDebug() << "love1";
            }
            else
            {
                painter->setPen(QPen(QColor(74,74,74),1,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
                painter->setBrush(QColor(20,20,20));
                painter->drawRoundRect(x, y, w, h, 20, 15);
                //qDebug() << "love2";
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

//绘制szIconFile类型为UIMENU_REPORT,UIMENU_REPORT_NOICON,的标题
void CMenu::drawReportStyle(QPainter *painter, int nCurrentIndex, int from, int to, bool bDrawIcon)
{
    painter->save();

    int i;
    int nBottomIndex;
    int x, y, w, h, w_spacer;
    T_UI_MENUITEM *item;

    w_spacer = 5;
    x = w_spacer; y = m_nFrameY + 10;
    w = m_nFrameWidth - 15; h = (m_nFrameHeight - 10) / MENUITEM_ROWS;

    nBottomIndex = MIN(g_uiMenuTopIndex + MENUITEM_ROWS - 1, to);
    //qDebug() << "drawReportStyle::nBottomIndex==" << nBottomIndex;

    for (i = g_uiMenuTopIndex; i <= nBottomIndex; i++)
    {
            x = w_spacer;

            item = &g_uiMenuItems[i];

            if (nCurrentIndex == i)
            {
                    QPixmap pmap_sel(QString(RESOURCE_PATH) + QString(SELECTED_ITEM_FILENAME));
                    QPainterPath roundPath = CustomStyle::roundRectPath(QRect(x, y, w, h));
                    painter->setClipPath(roundPath);
                    painter->drawPixmap(x, y, w, h, pmap_sel, 0, 0, pmap_sel.width(), pmap_sel.height());
                    painter->setClipPath(roundPath, Qt::NoClip);
                    g_uiMenuCurrentArea = QRect(x, y, w, h);
            }

            if (bDrawIcon)
            {
                    QPixmap pmap(QString(RESOURCE_PATH) + QString(item->szIconFile));
                    painter->drawPixmap(x + ((30 - pmap.width()) >> 1), y + ((h - pmap.height()) >> 1), pmap);
                    x += 30;
            }
            if(nCurrentIndex == i)
            {
                    painter->setFont(SB_FONT_12());
                    uiLcdDrawText(painter, x + MENU_REPORT_LEFTMARGIN, y, w-x, h, Qt::AlignTop | Qt::AlignLeft, UISTR(item->nMenuStr), MENU_ITEM_SELET_COLOR);
                    if(item->nType == UIMENU_HASVALUE)
                        uiLcdDrawText(painter, x, y, w-x, h, Qt::AlignBottom | Qt::AlignRight, uiProcMenuGetItemValue(item->nMenuStr), MENU_ITEM_SELET_COLOR);
                    painter->setFont(SB_FONT_13());
            }
            else
            {
                    uiLcdDrawText(painter, x + MENU_REPORT_LEFTMARGIN, y, w-x, h, Qt::AlignTop | Qt::AlignLeft, UISTR(item->nMenuStr), MENU_PEN_COLOR);
                    if(item->nType == UIMENU_HASVALUE)
                        uiLcdDrawText(painter, x, y, w-x, h, Qt::AlignBottom | Qt::AlignRight, uiProcMenuGetItemValue(item->nMenuStr), MENU_PEN_COLOR);
            }

            if (item->nType == UIMENU_POPUP || item->nType == UIMENU_CUSTOM_HASCHILD)
            {
                    QImage pmap_more(__RIGHT_ARROW);
                    if(nCurrentIndex == i)
                            pmap_more.setColor(1,qRgb(255,255,0));
                    else
                            pmap_more.setColor(1,qRgb(255,255,255));
                    painter->drawImage(w-pmap_more.width(), y+(h-pmap_more.height())/2, pmap_more);
            }
            y += h;
    }
    if (TRUE)
    {
            QPixmap pmap_scrollBg(QString(RESOURCE_PATH) + QString(SCROLL_BG_FILENAME));
            QPixmap pmap_scrollItem(QString(RESOURCE_PATH) + QString(SCROLL_ITEM_FILENAME));

            h = (m_nFrameHeight - 10) / (to - from + 1);

            painter->drawPixmap(m_nFrameWidth - 7, m_nFrameY + 10, 6, m_nFrameHeight - 10,
                                                    pmap_scrollBg, 0, 0, 6, pmap_scrollBg.height());
            painter->drawPixmap(m_nFrameWidth - 7, m_nFrameY + 10  + h*(nCurrentIndex - from), 6, h,
                                                    pmap_scrollItem, 0, 0, 6, pmap_scrollItem.height());
    }
    painter->restore();
}

//按键按下操作，传入ntitle参数
void CMenu::OnKeyPressOk(int nTitle)
{
    int nCurrentTitle, nCurrentIndex, nTopIndex;
    int __prev_col_cnt, __prev_item_size;

    nCurrentTitle = g_uiMenuItemTitle;
    nCurrentIndex = g_uiMenuItemIndex;
    nTopIndex = g_uiMenuTopIndex;
    qDebug() << "OnKeyPressOk::nCurrentTitle=="<<nCurrentTitle;
    qDebug() << "OnKeyPressOk::nCurrentIndex=="<<nCurrentIndex;
    qDebug() << "OnKeyPressOk::nTopIndex=="<<nTopIndex;
/*
    if ((g_uiMenuItems[nCurrentIndex].nMenuStr == UISTR_MENU_USBMANAGE) ||
            (g_uiMenuItems[nCurrentIndex].nMenuStr == UISTR_MENU_SYSTEMSETTING))
    {
            if (g_uiProcStatus.byMgr != PRIV_SMGR && Db_GetManagerCount(PRIV_SMGR))
            {
                    uiLcdMessageBox(UI_MSG_ERROR, UISTR_VERIFY_ILLEGAL, UI_MSGTIMEOUT);
                    return;
            }
    }

    if ((g_uiMenuItems[nCurrentIndex].nMenuStr == UISTR_MENU_COMMSETTING_BAUDRATE))
    {
            if (!dbSetupSystemNew.bRS232Use && !dbSetupSystemNew.bRS485Use)
                    return;
    }

    if ((g_uiMenuItems[nCurrentIndex].nMenuStr == UISTR_MENU_COMMSETTING_IPADDRESS) ||
            (g_uiMenuItems[nCurrentIndex].nMenuStr == UISTR_MENU_COMMSETTING_MASKADDRESS) ||
            (g_uiMenuItems[nCurrentIndex].nMenuStr == UISTR_MENU_COMMSETTING_GWADDRESS) ||
            (g_uiMenuItems[nCurrentIndex].nMenuStr == UISTR_MENU_COMMSETTING_COMMPWD) ||
            (g_uiMenuItems[nCurrentIndex].nMenuStr == UISTR_MENU_COMMSETTING_DHCPUSE) ||
    (g_uiMenuItems[nCurrentIndex].nMenuStr == UISTR_MENU_COMMSETTING_PORTBACKGROUND) ||
            (g_uiMenuItems[nCurrentIndex].nMenuStr == UISTR_MENU_COMMSETTING_PCBACKGROUND))
    {
            if (!dbSetupSystemNew.bEthernetUse)
                    return;
    }

    if ((dbSetupSystemNew.nLockGroupMain) &&
            (g_uiMenuItems[nCurrentIndex].nMenuStr == UISTR_MENU_ACSETTING_LOCKGROUP_SET))
            return;
*/
    switch (g_uiMenuItems[nCurrentIndex].nType)
    {
    case UIMENU_POPUP:
            __prev_col_cnt = __MENU_ICON_COL_CNT;
            __prev_item_size = __MENU_ICON_ITEM_SIZE;

            if (g_uiMenuItems[nCurrentIndex].nMenuStr == UISTR_MENU_SYSTEMSETTING)
            {
                __MENU_ICON_COL_CNT = 3;
                __MENU_ICON_ITEM_SIZE = 68;
            }
/*            if (g_uiMenuItems[nCurrentIndex].nMenuStr == UISTR_MENU_ENROLLNEW)
            {
                    BOOL bResult;
                    g_uiPopupTitle = g_uiMenuItems[nCurrentIndex].nMenuStr;
                    bzero(&gUserInfoTemp, sizeof(USER_INFO));
                    DbUserInfoFlagManagerSet(&gUserInfoTemp, PRIV_USER);
                    bResult = (BOOL)DIALOGBOXEX(CInputUserIDName, CInputUserIDName::ID_ALL);
                    goto _lPopupExit;
            }
            if (g_uiMenuItems[nCurrentIndex].nMenuStr == UISTR_MENU_ENROLLDELETE)
            {
                    if (!Db_GetUserCount())
                    {
                            uiLcdMessageBox(UI_MSG_ERROR, UISTR_ENROLLDELETE_NODATA, UI_MSGTIMEOUT);
                            break;
                    }
                    g_uiPopupTitle = g_uiMenuItems[nCurrentIndex].nMenuStr;
                    bzero(&gUserInfoTemp, sizeof(USER_INFO));
                    gUserInfoTemp.ID = DIALOGBOX_RET(CInputUserID);
                    goto _lPopupExit;
            }
            if ((g_uiMenuItems[nCurrentIndex].nMenuStr == UISTR_MENU_ACSETTING_USERTIMEZONE) ||
                    (g_uiMenuItems[nCurrentIndex].nMenuStr == UISTR_MENU_ACSETTING_DURESS_MANAGE))
            {
                    if (!Db_GetUserCount())
                    {
                            uiLcdMessageBox(UI_MSG_ERROR, UISTR_ENROLLDELETE_NODATA, UI_MSGTIMEOUT);
                            break;
                    }
                    g_uiPopupTitle = g_uiMenuItems[nCurrentIndex].nMenuStr;
                    g_uiMenuIDForUerTZ = (UINT64)DIALOGBOX_RET(CInputUserID);
                    goto _lPopupExit;
            }
            uiSoundOut(SOUND_MENUSELECT, UI_BUZZER_NONE);
*/
            MenuProc(g_uiMenuItems[nCurrentIndex].nMenuStr);

_lPopupExit:
            g_uiMenuItemTitle = nCurrentTitle;
            g_uiMenuItemIndex = nCurrentIndex;
            g_uiMenuTopIndex = nTopIndex;
            __MENU_ICON_COL_CNT = __prev_col_cnt;
            __MENU_ICON_ITEM_SIZE = __prev_item_size;
            g_uiPopupTitle = -1;
            OnRedraw();
            qDebug() << "OnKeyPressOk::UIMENU_POPUP";
            break;
    case UIMENU_HASVALUE:
            //uiProcMenuHasValue(ui.lblBackgroundFrame, g_uiMenuItems[nCurrentIndex].nMenuStr);
            //GUI_DLG_SET_THEME();
            //OnRedraw();
            break;
    case UIMENU_CUSTOM:
    case UIMENU_CUSTOM_HASCHILD:
            //uiProcMenuCustom(this, g_uiMenuItems[nCurrentIndex].nMenuStr);
            //if (g_uiMenuItems[nCurrentIndex].nMenuStr == UISTR_MENU_ADVANCEDSETTING_DEFAULT)
            //{
                    //GUI_DLG_SET_THEME();
            //}
            //OnRedraw();
            break;
    }


}
//按键上下翻动界面处理函数，传入按键值和title的索引
void CMenu::OnKeyPressArrow(int nKey, int nTitle)
{
    int nItemCnt, nItemCnt1;
    int nFirstIndex;
    BOOL bReport;
    nItemCnt = uiProcMenuGetItemCount(nTitle);//获取ntitle下的子数目
    qDebug() << "nItemCnt111=="<<nItemCnt;
    nFirstIndex = uiProcMenuTitleIndex(nTitle) + 1;//获取ntitle的第一个index
    qDebug() << "nFirstIndex111=="<<nFirstIndex;

    //nfirstindex前后判断
    bReport = ((int)g_uiMenuItems[nFirstIndex-1].szIconFile == UIMENU_REPORT) ||
            ((int)g_uiMenuItems[nFirstIndex-1].szIconFile == UIMENU_REPORT_NOICON);

    switch (nKey)
    {
    case UIKEY_UP:
            /*if ((g_uiMenuItems[nFirstIndex-1].nMenuStr == UISTR_MENU_ENROLLNEW) ||
                    (g_uiMenuItems[nFirstIndex-1].nMenuStr == UISTR_MENU_ENROLLDELETE))
            {
                    nItemCnt1 = (nItemCnt + ENROLLMENU_ROWCOUNT - 1) / ENROLLMENU_ROWCOUNT * ENROLLMENU_ROWCOUNT;
                    if ((nItemCnt1 > ENROLLMENU_ROWCOUNT) && ((g_uiMenuItemIndex - nFirstIndex) % ENROLLMENU_ROWCOUNT > (nItemCnt - 1) % ENROLLMENU_ROWCOUNT))
                            nItemCnt1 -= ENROLLMENU_ROWCOUNT;
                    g_uiMenuItemIndex = nFirstIndex + (g_uiMenuItemIndex - nFirstIndex + nItemCnt1 - ENROLLMENU_ROWCOUNT) % nItemCnt1;
            }
            else*/
            g_uiMenuItemIndex = nFirstIndex + (g_uiMenuItemIndex - nFirstIndex + nItemCnt - 1) % nItemCnt;
            qDebug() << "g_uiMenuItemIndex111=="<<g_uiMenuItemIndex;
            break;
    case UIKEY_DOWN:
            /*if ((g_uiMenuItems[nFirstIndex-1].nMenuStr == UISTR_MENU_ENROLLNEW) ||
                    (g_uiMenuItems[nFirstIndex-1].nMenuStr == UISTR_MENU_ENROLLDELETE))
            {
                    nItemCnt1 = (nItemCnt + ENROLLMENU_ROWCOUNT - 1) / ENROLLMENU_ROWCOUNT * ENROLLMENU_ROWCOUNT;
                    if ((nItemCnt1 > ENROLLMENU_ROWCOUNT) && ((g_uiMenuItemIndex - nFirstIndex) % ENROLLMENU_ROWCOUNT > (nItemCnt - 1) % ENROLLMENU_ROWCOUNT))
                            nItemCnt1 -= ENROLLMENU_ROWCOUNT;
                    g_uiMenuItemIndex = nFirstIndex + (g_uiMenuItemIndex - nFirstIndex + nItemCnt1 + ENROLLMENU_ROWCOUNT) % nItemCnt1;
            }
            else*/
            g_uiMenuItemIndex = nFirstIndex + (g_uiMenuItemIndex - nFirstIndex + nItemCnt + 1) % nItemCnt;
            qDebug() << "g_uiMenuItemIndex222=="<<g_uiMenuItemIndex;
            break;
    }
    qDebug() << "bReport111=="<<bReport;
    if (bReport)
    {
            if (g_uiMenuItemIndex < g_uiMenuTopIndex)
                    g_uiMenuTopIndex = g_uiMenuItemIndex;
            if (g_uiMenuItemIndex + 1 > g_uiMenuTopIndex + MENUITEM_ROWS)
                    g_uiMenuTopIndex = g_uiMenuItemIndex - MENUITEM_ROWS + 1;
    }

    OnRedraw();//退出前绘制标题
}





