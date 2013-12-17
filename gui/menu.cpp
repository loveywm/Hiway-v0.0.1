#include "menu.h"
#include "Define.h"
#include <QDebug>
//#include "xxx.h"
#include <QIcon>
#include <QPainterPath>
#include <QLineEdit>
#include "../global.h"
#include "ui_cmainframe.h"

#include "cenrollstep1.h"
#include "enrollpwd.h"



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

//void uiProcEnroll(USER_INFO *pUserInfo, int nStr);

/////////////////////////////////////////////////////////////
void uiProcEnroll(USER_INFO *pUserInfo, int nStr)
{
    if (nStr == UISTR_MENU_ENROLLNEWFP)
    {
            //DIALOGBOX(CEnrollFP);
    }
    else if (nStr == UISTR_MENU_ENROLLNEWPWD)
    {
        //if (DbUserInfoFlagEnrollStatusGet(&g_UserInfoTemp, BACKUP_PASSWORD) &&
            //!uiLcdMessageBox(UI_MSG_QUESTION, UISTR_ENROLLPWD_PWDEXIST, UITIME_OUT))
            //goto _lExit;
        //DWORD dwPassword = DIALOGBOX_RET(CInputPWD);
        DWORD dwPassword = 2222;//test
        if (dwPassword)
        {
            BOOL bResult;
            //bResult = uiEnrollUserInfo(&g_UserInfoTemp);
            if (bResult)
            {
                //bResult = uiPwdEnroll(&g_UserInfoTemp, PWD2STRING(dwPassword));
                //uiLogSlogAdd(g_uiProcStatus.nIDCurrentMgr, SLOG_SETPASSWORD, gUserInfoTemp.ID, bResult);
            }
            //if(bResult)
                //uiSoundOut(SOUND_OK, UI_BUZZER_OK, UITIME_VOICE);
            //else
                //uiLcdMessageBox(UI_MSG_ERROR, UISTR_ENROLLPWD_FAIL, UI_MSGTIMEOUT);
        }
    }
    //else if (nStr == UISTR_MENU_ENROLL_RFCARD)
    {

    }
    //else if (nStr == UISTR_MENU_ENROLL_VOICE)
    {

    }
    //else if (nStr == UISTR_MENU_ENROLL_PHOTO)
    {

    }

_lExit:
    return;

}
//一系列处理函数

void uiProcBoxWrapper(BOOL bEventHooked, BOOL bStart)
{
        static QWidget* pFocusWidget = NULL;

        if (!bEventHooked)
        {
                if (bStart)
                        pFocusWidget = qApp->focusWidget();
                else
                {
                        if (pFocusWidget)
                                pFocusWidget->setFocus(Qt::MouseFocusReason);
                        pFocusWidget = NULL;
                }
        }
}

void uiProcMakeString(char *szBuf, int *nValueList, int nCount, int *Lengths, int index, int i_length, char split)
{
        int i, j;
        int len;
        char FORMAT[16];

        szBuf[0] = 0;

        for (i=0; i<nCount; i++)
        {
                len = strlen(szBuf);
                sprintf(FORMAT, "%c0%dd", '%', Lengths[i]);
                sprintf(&szBuf[len], FORMAT, nValueList[i]);
                if (i == index)
                {
                        for (j = 0; j < Lengths[i] - i_length; j++)
                        {
                                szBuf[len + j] = ' ';
                        }
                }
                if (split && i < nCount - 1)
                        sprintf(&szBuf[strlen(szBuf)], "%c", split);
        }
}

int uiProcBoxTime(QWidget* parent, int x, int y, int cx, int cy, BOOL* pbRet, int nInitial, BOOL bKeyCheck = FALSE, BOOL bAutoSize = TRUE, BOOL bSecondShow = TRUE)
{
        uiProcBoxWrapper(bKeyCheck, TRUE);

#undef __CURSOR_POS
#define __CURSOR_POS (nIndex * 3)

        int addr[6] = {1,2,3,4,5,6};
        int addr_length[3] = {2, 2, 2};
        int nIndex, i_len = addr_length[0];
        int nRet = nInitial;
        //int nPrevTime = uiTimeGetTickCount() - 501;
        int nPrevTime = GetMainTickCount() - 501;
        int nKey = UIKEY_NONE;
        BOOL bStartNew = TRUE;
        QLineEdit txtTime(parent);
        char szTime[24];
//	int nCursorPos = 0;
        int nRealWidth;
        int nMin[] = {0,  0,  0 };
        int nMax[] = {23, 59, 59};
        QPalette pal = txtTime.palette();

        nIndex = 0;

        //uiRtcSeconds2YMDHMS((DWORD)nInitial, &addr[3], &addr[4], &addr[5], &addr[0], &addr[1], &addr[2]);

        pal.setBrush(QPalette::Base, QBrush(QColor(59, 129, 212)));
        pal.setColor(QPalette::All, QPalette::Text, FOREGROUND_COLOR1);
        txtTime.setPalette(pal);

        if (bAutoSize)
        {
                nRealWidth = parent->fontMetrics().width("00:00:00") + 10;
                x = x + cx - nRealWidth;
                cx = nRealWidth;
        }

        txtTime.setGeometry(x, y, cx, cy);
        txtTime.setAlignment(Qt::AlignVCenter);
        txtTime.setFocus(Qt::MouseFocusReason);
        txtTime.show();

        *pbRet = FALSE;
        while (uiTimeIsTimeout(60000) == FALSE)
        {
                POST_EVENTS();
                //DM9000_Check();
                if (GetMainTickCount() - nPrevTime > 500)
                {
                        if (addr[nIndex] > nMax[nIndex])
                        {
                                //uiSoundOut(SOUND_ERROR, UI_BUZZER_ERROR);
                                addr[nIndex] = nMax[nIndex];
                                bStartNew = TRUE;
                        }

                        if (addr[nIndex] < nMin[nIndex])
                        {
                                //uiSoundOut(SOUND_ERROR, UI_BUZZER_ERROR);
                                addr[nIndex] = nMin[nIndex];
                                bStartNew = TRUE;
                        }

                        nPrevTime = GetMainTickCount();

                        if (bStartNew)
                                i_len = addr_length[nIndex];
                        uiProcMakeString(szTime, addr, bSecondShow ? 3 : 2, addr_length, nIndex, i_len, ':');
                        txtTime.setText(szTime);

                        if (bStartNew)
                                txtTime.setSelection(__CURSOR_POS, 2);
                        else
                                txtTime.setCursorPosition(__CURSOR_POS + 2);

                        if (!bStartNew && i_len == addr_length[nIndex])
                        {
                                if(bKeyCheck)
                                        nKey = UIKEY_OK;
                                else
                                        nKey = UIKEY_DOWN;
                                goto _lKeyPressed;
                        }
                }

                //if ((nKey = uiKeyGetKey()) == UIKEY_NONE)
                        //continue;
                if ((nKey = GetKey()) == UIKEY_NONE)
                        continue;


_lKeyPressed:
                if (nKey == UIKEY_ESC)
                {
                        nRet = nInitial;
                        break;
                }

                if (nKey == UIKEY_OK)
                {
                        if(!bKeyCheck)
                        {
                                *pbRet = TRUE;
                                break;
                        }
                        else
                        {
                                nIndex = (nIndex + 1) % (bSecondShow ? 3 : 2);
                                bStartNew = TRUE;
                        }

                }

                if (bKeyCheck && (nKey == UIKEY_UP || nKey == UIKEY_DOWN))
                {
                        *pbRet = TRUE;
                        break;
                }

                if (nKey == UIKEY_DOWN)
                {
                        nIndex = (nIndex + 1) % (bSecondShow ? 3 : 2);
                        bStartNew = TRUE;
                }

                if (nKey == UIKEY_UP)
                {
                        nIndex = (nIndex + (bSecondShow ? 2 : 1)) % (bSecondShow ? 3 : 2);
                        bStartNew = TRUE;
                }

        /*	if (nKey == UIKEY_UP)
                {
                        addr[nIndex]--;
                        bStartNew = TRUE;
                }

                if (nKey == UIKEY_DOWN)
                {
                        addr[nIndex]++;
                        bStartNew = TRUE;
                }*/

                if (nKey == UIKEY_MENU) //Backspace
                {
                        if (bStartNew)
                        {
                                addr[nIndex] = nMin[nIndex];
                                i_len = 0;
                                bStartNew = FALSE;
                        }
                        else
                        {
                                addr[nIndex] = addr[nIndex] / 10;
                                if (i_len)
                                        i_len--;
                        }
                }

/*                if (uiKeyIsDigit((T_UI_KEY)nKey))
                {
                        if (bStartNew)
                        {
                                addr[nIndex] = (int)nKey;
                                bStartNew = FALSE;
                                i_len = 1;
                        }
                        else
                        {
                                addr[nIndex] = addr[nIndex] * 10 + (int)nKey;
                                i_len++;
                        }
                }
*/
                nPrevTime = GetMainTickCount() - 501;
        }

        //if (*pbRet)
                //nRet = (int)uiRtcGetSeconds(addr[3], addr[4], addr[5], addr[0], addr[1], addr[2]);
        if (bKeyCheck)
                *pbRet = nKey;

        uiProcBoxWrapper(bKeyCheck, FALSE);
        return nRet;
}





/////////////////////////////////////////////////////////////////


typedef enum//菜单的几种类型枚举
{
    // 0,1,2,... = parent & title, UISTR_SPACE - top menu
    UIMENU_POPUP = -1,//有二级标题图标
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
    const char* szIconFile;//title标题下面子栏目显示绘画方式，共四种list
    int nHelpStr;//备用
} T_UI_MENUITEM;

//日后添加标题都在这两添加
T_UI_MENUITEM g_uiMenuItemsSrc[] =
{
    {UISTR_MENU_MAINMENU,           UIMENU_TITLE,       (const char*)UIMENU_ICON,   -1},
    {UISTR_MENU_ENROLLNEWFP,        UIMENU_CUSTOM,      "ENROLLNEWFP.png",          -1},
    {UISTR_MENU_ENROLLNEWPWD,       UIMENU_CUSTOM,      "ENROLLNEWPWD.png",         -1},
    {UISTR_MENU_USERDATAVIEW,       UIMENU_POPUP,       "USERDATAVIEW.png",         -1},
    //{UISTR_MENU_SETTIME,            UIMENU_HASVALUE,    "SETTIME.png",              -1},
    {UISTR_MENU_USBMANAGER,         UIMENU_POPUP,       "USBMANAGER.png",           -1},
    {UISTR_MENU_OTHERINFO,          UIMENU_POPUP,       "OTHERINFO.png",            -1},

    {UISTR_MENU_USBMANAGER,         UIMENU_TITLE,        (const char*)UIMENU_ICON,  -1},
    {UISTR_MENU_ONEGLOGLOAD,        UIMENU_HASVALUE,     "MANAGER.png",             -1},
    {UISTR_MENU_ALLGLOGLOAD,        UIMENU_HASVALUE,     "ALLGLOGLOAD.png",         -1},
    {UISTR_MENU_ALLMANAGERGLOGLODA, UIMENU_HASVALUE,     "ALLMANAGERGLOGLODA.png",  -1},
    {UISTR_MENU_ONEUSERINFODOWN,    UIMENU_HASVALUE,     "MANAGER.png",             -1},
    {UISTR_MENU_ALLUSERINFODOWN,    UIMENU_HASVALUE,     "ALLUSERINFODOWN.png",     -1},
    {UISTR_MENU_USERINFOUP,         UIMENU_HASVALUE,     "USERINFOUP.png",          -1},

    {UISTR_MENU_OTHERINFO,          UIMENU_TITLE,        (const char*)UIMENU_ICON,  -1},
    {UISTR_MENU_USERGLOGINFO,       UIMENU_POPUP,        "MANAGER.png",             -1},
    {UISTR_MENU_DEVICEINFO,         UIMENU_POPUP,        "DEVICEINFO.png",          -1},

    {UISTR_MENU_USERGLOGINFO,       UIMENU_TITLE,        (const char*)UIMENU_REPORT,-1},
    {UISTR_MENU_USERENROLLCOUNT,    UIMENU_HASVALUE,     "USERENROLLCOUNT.png",     -1},
    {UISTR_MENU_FPENROLLCOUNT,      UIMENU_HASVALUE,     "FPENROLLCOUNT.png",       -1},
    {UISTR_MENU_PWDENROLLCOUNT,     UIMENU_HASVALUE,     "PWDENROLLCOUNT.png",      -1},
    {UISTR_MENU_GLOGCOUNT,          UIMENU_HASVALUE,     "GLOGCOUNT.png",           -1},
    {UISTR_MENU_MLOGCOUNT,          UIMENU_HASVALUE,     "MLOGCOUNT.png",           -1},
    {UISTR_MENU_SETTIME,            UIMENU_HASVALUE,     "SETTIME.png",             -1},



    {-1,                            UIMENU_TITLE,       NULL,                       -1}
};

//声明存放标题数组
T_UI_MENUITEM g_uiMenuItems[ITEM_CNT(g_uiMenuItemsSrc)];

int g_uiMenuItemTitle = UISTR_MENU_MAINMENU;
int g_uiMenuItemIndex = 1;//标题项目索引
int g_uiMenuTopIndex = 1;//标题项目顶端位置标志
int g_uiPopupTitle = -1;//

//DWORD	g_uiTimeLastAction=0;//记录前一次操作的时间


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
//CMenu::drawReportStyle()函数调用
//获取对应的item类型为：：item->nType == UIMENU_HASVALUE
QString uiProcMenuGetItemValue(int nItemStr)
{
    DWORD dwValue = 0;
    QString str;
    int a, b, c, d;
    char strTemp[16];

    switch (nItemStr)
    {
        case UISTR_MENU_USERENROLLCOUNT:
            str = QString("%1 / %3%4").arg(1000).arg(5000).arg("xxx");
            break;
        case UISTR_MENU_FPENROLLCOUNT:
            str = QString("%1 / %3%4").arg(200).arg(5000).arg("xxx");
            break;
        case UISTR_MENU_PWDENROLLCOUNT:
            str = QString("%1 / %3%4").arg(300).arg(5000).arg("xxx");
            break;
        case UISTR_MENU_GLOGCOUNT:
            str = QString("%1 / %3%4").arg(400).arg(5000).arg("xxx");
            break;
        case UISTR_MENU_MLOGCOUNT:
            str = QString("%1 / %3%4").arg(500).arg(5000).arg("xxx");
            break;
        case UISTR_MENU_SETTIME:
            str = QString("%1:%3:%5").arg(12).arg(34).arg(45);
            break;
        default:
            break;
    }

    if (!str.length())
        str = QString("%1").arg(dwValue);

    return str;
}


//处理 CMenu::OnKeyPressOk 函数下面的 item->nType == UIMENU_HASVALUE选项的处理
//对应的item类型为：：item->nType == UIMENU_HASVALUE
BOOL uiProcMenuHasValue(QWidget *pWnd, int nItemStr)
{
    BOOL bResult;
    int nValue, nValue1;
    int x, y, w, h;
    char *szValue;
    //g_uiMenuRedrawFlag = FALSE;
    x = g_uiMenuCurrentArea.x();
    y = g_uiMenuCurrentArea.y();
    w = g_uiMenuCurrentArea.width();
    h = g_uiMenuCurrentArea.height();

    switch (nItemStr)
    {
        case UISTR_MENU_SETTIME:
            nValue = uiProcBoxTime(pWnd, x, y, w, h, &bResult, /*uiRtcGetSeconds()*/9);
            if (bResult)
            {
                //uiRtcSetTime(nValue);
                qDebug() << "nValue=="<<nValue;
                //uiLogSlogAdd(g_uiProcStatus.nIDCurrentMgr, SLOG_SETTIME, 0, 2);
            }
            break;
        default:
            break;
    }
    //g_uiMenuRedrawFlag = TRUE;
    return TRUE;
}

//处理 CMenu::OnKeyPressOk 函数下面的 item->nType == UIMENU_CUSTOM选项的处理
//对应的item类型为：：item->nType == UIMENU_CUSTOM
BOOL uiProcMenuCustom(QWidget* /*pWnd*/, int nItemStr)
{
    BOOL bResult;
    switch (nItemStr)
    {
        case UISTR_MENU_ENROLLNEWFP:
            qDebug() << "UISTR_MENU_ENROLLNEWFP";
            DIALOGBOX(CEnrollStep1);



            break;
        case UISTR_MENU_ENROLLNEWPWD:
            //uiProcEnroll(&g_UserInfoTemp,nItemStr);
            qDebug() << "UISTR_MENU_ENROLLNEWPWD";
            DIALOGBOX(EnrollPWD);



            break;

    }

    return TRUE;
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
    //uiProcBuildMenu();
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
    qDebug() << "nPopupMenuTitle=="<<nPopupMenuTitle;
    qDebug() << "g_uiMenuItemTitle=="<<g_uiMenuItemTitle;
    qDebug() << "uiProcMenuTitleIndex(nPopupMenuTitle)+1=="<<uiProcMenuTitleIndex(nPopupMenuTitle);
    qDebug() << "g_uiMenuItemIndex=="<<g_uiMenuItemIndex;
    qDebug() << "g_uiMenuTopIndex=="<<g_uiMenuTopIndex;

    OnRedraw();

    while (!m_bTerminateFlag && uiTimeIsTimeout(60000) == FALSE)
    {

        //QApplication::processEvents();
        POST_EVENTS();

        //g_uiBuildMenu = TRUE;
        if(g_uiBuildMenu && nPopupMenuTitle == UISTR_MENU_MAINMENU)
        {
            g_uiBuildMenu = FALSE;
            qDebug() << "xxx";
            uiProcBuildMenu();
            goto _lstart;
        }
        //embedded
        //nKey = GetKey();
        nKey = g_keyvalue;
        g_keyvalue = 0;
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
            goto _Exit;
            break;
        case UIKEY_2:
            qDebug() << "keycode==right"<<2;
            break;
        default:
            break;
        }
    }
    //if(uiTimeIsTimeout(60000))
    //{
       //goto _ExitWithoutSave;
    //}
_Exit:
    MenuSettingEnd(nPopupMenuTitle);
    GUI_DLG_SET_THEME();
    update();

_ExitWithoutSave:

    return;
}

void CMenu::OnRedraw()
{
    int nTitleIndex = uiProcMenuTitleIndex(g_uiMenuItemTitle);

/*    if(g_uiMenuItemTitle == UISTR_MENU_SYSINFOVIEW)
    {
        setTitle(QString(RESOURCE_PATH) + QString(g_uiMenuItems[g_uiMenuItemIndex].szIconFile),
                UISTR(UISTR_SYMBOL_BRACKET_ON) +
                UISTR(g_uiMenuItemTitle) +
                UISTR(UISTR_SYMBOL_BRACKET_OFF));
        uiLcdSetLabelText(ui.lblTitleText1, UISTR(UISTR_UNIT_TOTAL), TITLECOLOR);
        ui.lblTitleText1->show();
    }
     else
 */   {
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
          //uiLcdSetLabelText(ui->lblStatusText, QString("I love ywm!")/*UISTR("Click it")*/, FOREGROUND_COLOR0);
          uiLcdSetLabelText(ui->lblStatusText,UISTR(g_uiMenuItems[g_uiMenuItemIndex].nMenuStr), FOREGROUND_COLOR1);

      }
      else
      {
          //同上
          //uiLcdSetLabelText(ui->lblStatusText, QString("I love world!")/*UISTR(UISTR_MENU_USERMANAGE)*/, FOREGROUND_COLOR1);
          uiLcdSetLabelText(ui->lblStatusText,UISTR(g_uiMenuItems[g_uiMenuItemIndex].nMenuStr), FOREGROUND_COLOR1);
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
                    //painter->setFont(SB_FONT_12());
                    uiLcdDrawText(painter, x + MENU_REPORT_LEFTMARGIN, y, w-x, h, Qt::AlignTop | Qt::AlignLeft, UISTR(item->nMenuStr), MENU_ITEM_SELET_COLOR);
                    if(item->nType == UIMENU_HASVALUE)
                        uiLcdDrawText(painter, x, y, w-x, h, Qt::AlignBottom | Qt::AlignRight, uiProcMenuGetItemValue(item->nMenuStr), MENU_ITEM_SELET_COLOR);
                    //painter->setFont(SB_FONT_13());
            }
            else
            {
                    uiLcdDrawText(painter, x + MENU_REPORT_LEFTMARGIN, y, w-x, h, Qt::AlignTop | Qt::AlignLeft, UISTR(item->nMenuStr), MENU_PEN_COLOR);
                    if(item->nType == UIMENU_HASVALUE)
                        uiLcdDrawText(painter, x, y, w-x, h, Qt::AlignBottom | Qt::AlignRight, uiProcMenuGetItemValue(item->nMenuStr), MENU_PEN_COLOR);
            }
            //如果列表下面type类型为UIMENU_POPUP则其有子菜单，小箭头表示
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

            //uiSoundOut(SOUND_MENUSELECT, UI_BUZZER_NONE);

            qDebug() << "OnKeyPressOk::UIMENU_POPUP";
            MenuProc(g_uiMenuItems[nCurrentIndex].nMenuStr);

_lPopupExit:
            g_uiMenuItemTitle = nCurrentTitle;
            g_uiMenuItemIndex = nCurrentIndex;
            g_uiMenuTopIndex = nTopIndex;
            __MENU_ICON_COL_CNT = __prev_col_cnt;
            __MENU_ICON_ITEM_SIZE = __prev_item_size;
            g_uiPopupTitle = -1;
            OnRedraw();
            qDebug() << "OnKeyPressOk::UIMENU_POPUP is over!!";
            break;
    case UIMENU_HASVALUE:
            uiProcMenuHasValue(ui->lblBackgroundFrame, g_uiMenuItems[nCurrentIndex].nMenuStr);
            GUI_DLG_SET_THEME();
            OnRedraw();
            qDebug() << "OnKeyPressOk::UIMENU_HASVALUE";
            break;
    case UIMENU_CUSTOM:
    case UIMENU_CUSTOM_HASCHILD:
            uiProcMenuCustom(this, g_uiMenuItems[nCurrentIndex].nMenuStr);
            //if (g_uiMenuItems[nCurrentIndex].nMenuStr == UISTR_MENU_ADVANCEDSETTING_DEFAULT)
            //{
            //GUI_DLG_SET_THEME();
            //}
            //OnRedraw();
            qDebug() << "OnKeyPressOk::UIMENU_CUSTOM";
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
            qDebug() << "CMenu::OnKeyPressArrow::g_uiMenuItemIndex111=="<<g_uiMenuItemIndex;
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
            qDebug() << "CMenu::OnKeyPressArrow::g_uiMenuItemIndex222=="<<g_uiMenuItemIndex;
            break;
    }
    qDebug() << "bReport111=="<<bReport;
    //翻页设置
    if (bReport)
    {
            if (g_uiMenuItemIndex < g_uiMenuTopIndex)
                    g_uiMenuTopIndex = g_uiMenuItemIndex;
            if (g_uiMenuItemIndex + 1 > g_uiMenuTopIndex + MENUITEM_ROWS)
                    g_uiMenuTopIndex = g_uiMenuItemIndex - MENUITEM_ROWS + 1;
    }

    OnRedraw();//退出前绘制标题
}

void CMenu::keyPressEvent(QKeyEvent *e)
{
    switch (e->key())
    {
       case Qt::Key_W : qDebug() << "Up";      g_keyvalue = UIKEY_UP;break;
       case Qt::Key_S : qDebug() << "Down";     g_keyvalue = UIKEY_DOWN;break;
       case Qt::Key_E : qDebug() << "ESC";      g_keyvalue = UIKEY_1;break;
       case Qt::Key_O : qDebug() << "OK";       g_keyvalue = UIKEY_OK;break;
       case Qt::Key_M : qDebug() << "Menu";     g_keyvalue = UIKEY_MENU;break;
    }
}





