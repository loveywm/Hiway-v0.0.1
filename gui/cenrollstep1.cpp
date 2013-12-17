

#include "cenrollstep1.h"
#include "ui_cenrollstep1.h"

#include "Define.h"
#include "../hiwaylib.h"
#include <QDebug>

#define     IDNUMBER_LENGTH    9

CEnrollStep1::CEnrollStep1(QWidget *parent /* = NULL */, UINT64 nID /* = 0 */, BOOL bNew /* = TRUE */, BOOL/* bEdit*/ /*= FALSE*/)
    : QDialog(parent),
      ui(new Ui::CEnrollStep1)
{
    ui->setupUi(this);

    GUI_DLG_IMPL(TRUE);
    GUI_DLG_SET_THEME();
    show();

    //connect(qApp, SIGNAL(focusChanged(QWidget*, QWidget*)), this, SLOT(OnFocusChanged(QWidget*, QWidget*)));
    //connect(ui.txtID, SIGNAL(textEdited(const QString &)), this, SLOT(OnIDChange(const QString &)));
    //connect(ui->btnESC, SIGNAL(clicked()), this, SLOT(OnBtnESC()));

    //ui->comboPart->setFont(SB_FONT_12());
    //ui->

    //EDITBOX_2_T9InputBox(ui.txtName);
    //EDITBOX_2_T9InputBox(ui.txtID);

    m_bNew = bNew;
    m_nCandidateID = -1;
    m_nID = nID;

    //QString szTitle = QString("[%1]-%2").arg("love").arg("xxx");
    QString szTitle = QString("[%1]-%2")
            .arg(UISTR(UISTR_USER_NEW))
            .arg(UISTR(bNew ? UISTR_MENU_ENROLLNEWFP : UISTR_MENU_ENROLLBACKUP));
    //ui->lblTitleText->setFont(SB_FONT_15());
    uiLcdSetLabelText(ui->lblTitleText,szTitle,TITLECOLOR,QColor());
    int nParts = DbPartCount();
    for (int i=0; i<nParts; i++)
    ui->comboPart->addItem(DbPartGet(i));

    ui->lblPart->hide();
    ui->comboPart->hide();
    ui->lblLevel->hide();

    ui->lblName->setText(UISTR(UISTR_USER_NAME));
    ui->txtName->setText("loveywm");
    ui->lblID->setText(UISTR(UISTR_USER_ID));


    ui->txtName->setMaxLength(12);
    ui->txtID->setMaxLength(IDNUMBER_LENGTH);

    m_bTerminateFlag = !EnrollParamSet();
    //m_bTerminateFlag = FALSE;
}

CEnrollStep1::~CEnrollStep1()
{
    delete ui;
}

int CEnrollStep1::DoProcess(int nEdit /*=0*/)//注册处理第一步
{
    int nKey;
    BOOL bRet;
    QPushButton *pCurrentBtn;
    qDebug("nedit==%d",nEdit);
    qDebug("ID_NEW==%d",ID_NEW);
    m_nEdit = nEdit;
    if (m_nEdit == ID_NEW)
        m_bNew = TRUE;
    else if (m_nEdit == ID_BACKUP)
        m_bNew = FALSE;

    /*     if(!m_bNew)
        {
                uiLcdSetLabelText(ui->lblTitleText,UISTR(UISTR_USER_EDIT),TITLECOLOR,QColor());
                ui->txtID->setText(UserId_BCDtoSTR(gUserInfoTemp.ID));
                EnrollCheck(TRUE);
                EnrollParamSet(-1);
        }*/
    qDebug("CEnrollStep1::DoProcess::m_nEdit==%d",m_nEdit);
    //m_nEdit = 1;
    if(m_nEdit == ID_NEW)
    {
        uiLcdSetLabelText(ui->lblTitleText,UISTR(UISTR_USER_NEW),TITLECOLOR,QColor());
    }

    //ui->txtID->selectAll();
    while (!m_bTerminateFlag && uiTimeIsTimeout(60000) == FALSE)
    {
        POST_EVENTS();
        //DM9000_Check();
        //nKey = GetKey();
        nKey = g_keyvalue;
        g_keyvalue = 0;

        switch (nKey)
        {
        case UIKEY_1://UIKEY_ESC
            //if (OnBtnESC())
            //goto _lExit;
            qDebug("UIKEY_ESC");
            goto _lExit;
            break;
        case UIKEY_OK:

            //pCurrentBtn = (QPushButton*)QApplication::focusWidget();
            //if(pCurrentBtn == ui->btnOK)
            bRet = OnBtnOK();  //转入下步骤
            qDebug("UIKEY_OK");
            break;
        case  UIKEY_DOWN:
            //ui->txtID->setFocus(Qt::MouseFocusReason);
            qDebug("UIKEY_DOWN");
            break;
        case  UIKEY_UP:
            //ui->txtName->setFocus(Qt::MouseFocusReason);
            qDebug("UIKEY_UP");
            break;
        default:
            break;
        }
    }

    _lExit:
        return 0;
}
void CEnrollStep1::OnFocusChanged(QWidget *from, QWidget *to)
{
    BOOL  bResult;
    //qDebug("xxxx1");
    if (from == (QWidget*)ui->txtID)
    {
        qDebug("xxxx2");
        //UINT64 nID = UserId_STRtoBCD(STR2ASCII(ui->txtID->text()));
        UINT64 nID = 1;
        //ui.txtID->setText(UserId_BCDtoSTR(nID)); //for empty string
        ui->txtID->setText("1");
        /*	if(UserId_isOk()==0)
                {
                        uiLcdMessageBox(UI_MSG_ERROR, UISTR_ENROLL_INVALID_ID, 3000);
                        ui.txtID->setFocus(Qt::MouseFocusReason);
                        ui.txtID->selectAll();
                        return ;
                }*/

        qDebug("xxxx3");
        if (!nID && (to == (QWidget*)ui->txtName || to == (QWidget*)ui->btnESC))
        {
            //if (!EnrollCheck())
            {
                //ui->txtID->setFocus(Qt::MouseFocusReason);
                //ui->txtID->selectAll();
            }
            //EnrollParamSet(-1);
        }
        qDebug("xxxx4");
    }

    //if (to == (QWidget*)ui->txtID)
        //ui->txtID->selectAll();
    //uiProcDrawStatusbar(ui->lblStatusText, UISTR_STATUS_OK_SELECT, UISTR_STATUS_ESC_BACK);

}

BOOL CEnrollStep1::OnBtnESC()
{
    // 	if (!uiLcdMessageBox(UI_MSG_QUESTION, UISTR_ACTION_CONFIRM, UITIME_OUT))
    // 		return FALSE;

    m_bTerminateFlag = TRUE;
    return TRUE;
}

void CEnrollStep1::keyPressEvent(QKeyEvent *e)
{
    switch (e->key())
    {
       case Qt::Key_W : qDebug() << "Up";       g_keyvalue = UIKEY_UP;break;
       case Qt::Key_S : qDebug() << "Down";     g_keyvalue = UIKEY_DOWN;break;
       case Qt::Key_E : qDebug() << "ESC";      g_keyvalue = UIKEY_1;break;
       case Qt::Key_O : qDebug() << "OK";       g_keyvalue = UIKEY_OK;break;
       case Qt::Key_M : qDebug() << "Menu";     g_keyvalue = UIKEY_MENU;break;
    }

}

BOOL CEnrollStep1::OnBtnOK()
{
    int nRet;
    if (!EnrollCheck())//检测要注册的相关信息
            return FALSE;

    USER_INFO BACKUP;
    USER_INFO *pUI = (USER_INFO*)DbUserInfoGetPointer(gUserInfoTemp.ID);
    bzero(&BACKUP, sizeof(USER_INFO));
    if(pUI)
        memcpy(&BACKUP, pUI, sizeof(USER_INFO));

    //memset(&gUserInfoTemp.NAME, 0, sizeof(gUserInfoTemp.NAME));
    //STRING2UNICODE(ui.txtName->text(), gUserInfoTemp.NAME, USERNAME_LENGTH);
    //xprintf("ui.txtName=%s \r\n", (const char*)U2G(ui.txtName->text()));

    if (pUI && memcmp(pUI, &gUserInfoTemp, sizeof(USER_INFO)))
            //uiEnrollUserInfo(&gUserInfoTemp);//用户注册
/*
    nRet = DIALOGBOXEX(CEnrollStep2,CEnrollStep2::NEW);//进入第二阶段注册
    pUI = (USER_INFO*)DbUserInfoGetPointer(gUserInfoTemp.ID);
    if (pUI && memcmp(&BACKUP, pUI, sizeof(USER_INFO)))
    {
            if (m_nEdit == ID_ALL)
            {
                    m_bNew = TRUE;
                    if (Db_GetUserCount() == dbLicense.nMaxEnrollCount)
                    {
                            m_bNew = FALSE;
                            m_nCandidateID = 0;
                    }
                    EnrollParamSet(0);
            }
            else
            {
                    if (Db_GetUserCount() == dbLicense.nMaxEnrollCount)
                    {
                            m_bTerminateFlag = TRUE;
                            return TRUE;
                    }
                    EnrollParamSet(1);
            }
    }
    else
    {
            ui.txtID->setFocus(Qt::MouseFocusReason);
            ui.txtID->selectAll();
    }

*/
    qDebug() << "CEnrollStep1::OnBtnOK()";
}

//获取候选用户
BOOL CEnrollStep1::EnrollParamSet(int nCandidateDiff)
{
    qDebug() << "CEnrollStep1::EnrollParamSet::nCandidateDiff ==" << nCandidateDiff;
    qDebug() << "CEnrollStep1::EnrollParamSet::m_nCandidateID  111 ==" << m_nCandidateID;
    if (nCandidateDiff >= 0)
    {
        if(m_nCandidateID == (UINT64)(-1))
            m_nCandidateID = 1;
        else
            m_nCandidateID += nCandidateDiff;

        qDebug() << "CEnrollStep1::EnrollParamSet::m_nCandidateID 222==" << m_nCandidateID;
        qDebug() << "CEnrollStep1::EnrollParamSet::m_bNew==" << m_bNew;
        m_nCandidateID = Db_GetCandidateID(m_bNew, m_nCandidateID);

        qDebug() << "CEnrollStep1::EnrollParamSet::m_nCandidateID 333==" << m_nCandidateID;;
        if (!m_nCandidateID)
        {
            if(m_bNew)
                //uiLcdMessageBox(UI_MSG_ERROR, UISTR_ENROLL_OVERFLOW, UI_MSGTIMEOUT);
            //else
                //uiLcdMessageBox(UI_MSG_ERROR, UISTR_ENROLL_NOUSER, UI_MSGTIMEOUT);
            return FALSE;
        }
        //ui->txtID->setText(UserId_BCDtoSTR(m_nCandidateID));
        m_nID = m_nCandidateID;
    }

    USER_INFO* pUserInfo = (USER_INFO*)DbUserInfoGetPointer(m_nID);

    if (m_bNew || !pUserInfo)
    {
            ui->txtName->clear();
            //ui.txtPassword->setText(PWD2STRING(DEFAULT_PASSWORD));
            //ui.txtPasswordConfirm->setText(PWD2STRING(DEFAULT_PASSWORD));
            ui->comboLevel->setCurrentIndex(0);
            if(DbPartCount()>1)
            ui->comboPart->setCurrentIndex(1);
            else
            ui->comboPart->setCurrentIndex(0);
    }
    else
    {
            //ui->txtName->setText(UNICODE2STRING(pUserInfo->NAME, USERNAME_LENGTH));
            //ui.txtPassword->setText(PWD2STRING(pUserInfo->PWD));
            //ui.txtPasswordConfirm->setText(PWD2STRING(pUserInfo->PWD));
            ui->comboLevel->setCurrentIndex(PRIV_INDEX(DbUserInfoFlagManagerGet(pUserInfo)));
            if (pUserInfo->PART < DbPartCount())
                    ui->comboPart->setCurrentIndex(pUserInfo->PART);
            else
                    ui->comboPart->setCurrentIndex(0);
    }

    if (nCandidateDiff >= 0)
    {
            //ui->txtID->setFocus(Qt::MouseFocusReason);
            //ui->txtID->selectAll();
        qDebug() << "CEnrollStep1::EnrollParamSet::nCandidateDiff >= 0==" << nCandidateDiff;
    }
    return TRUE;
}

BOOL CEnrollStep1::EnrollCheck(BOOL bIDChange)
{
    BOOL bRet = TRUE;
    int MGR_LIST[] = {PRIV_USER, PRIV_MGR, PRIV_SMGR};

    ui->txtID->setText("1");//loveywm

    m_nID = UserId_STRtoBCD(STR2ASCII(ui->txtID->text()));
    m_nManager = MGR_LIST[ui->comboLevel->currentIndex()];

    qDebug() << "CEnrollStep1::EnrollCheck::m_nID==" <<m_nID;
    qDebug() << "CEnrollStep1::EnrollCheck::m_nManager==" <<m_nManager;;

    if (m_nEdit == ID_ALL)
            m_bNew = !DbUserInfoIsUsedID(m_nID);
    if (bIDChange)
    {
            m_nCandidateID = m_nID;
            qDebug() << "CEnrollStep1::EnrollCheck::bIDChange==" << bIDChange;
            goto _lExit;
    }

    if (m_bNew && Db_GetUserCount() >= dbLicense.nMaxEnrollCount)
    {
            //uiLcdMessageBox(UI_MSG_ERROR, UISTR_ENROLL_OVERFLOW, UI_MSGTIMEOUT);
            qDebug() << "CEnrollStep1::EnrollCheck::UISTR_ENROLL_OVERFLOW";
            bRet = FALSE;
            goto _lExit;
    }
/*
    if (    m_nManager != PRIV_USER &&
            m_nManager != DbUserInfoGetPrivilege(m_nID) &&
            Db_GetManagerCount((BYTE)m_nManager) + 1 > dbSetupTotal.setSystem.nManagersNumber)
    {
            uiLcdMessageBox(UI_MSG_ERROR, UISTR_ENROLL_MANAGER_OVERFLOW, UI_MSGTIMEOUT);
            bRet = FALSE;
            goto _lExit;
    }

    if (g_uiProcStatus.byMgr != PRIV_SMGR && Db_GetManagerCount(PRIV_SMGR))
    {
            if(DbUserInfoGetPrivilege(m_nID) == PRIV_SMGR)
            {
                    uiLcdMessageBox(UI_MSG_ERROR, UISTR_VERIFY_ILLEGAL, UI_MSGTIMEOUT);
                    ui.comboLevel->setFocus(Qt::MouseFocusReason);
                    bRet = FALSE;
                    goto _lExit;
            }
            if (m_nManager == PRIV_SMGR ||
                    (m_nManager == PRIV_MGR && m_nID != g_uiProcStatus.nIDCurrentMgr))
            {
                    uiLcdMessageBox(UI_MSG_ERROR, UISTR_VERIFY_ILLEGAL, UI_MSGTIMEOUT);
                    ui.comboLevel->setFocus(Qt::MouseFocusReason);
                    bRet = FALSE;
                    goto _lExit;
            }
    }

    if (!m_nID ||
            (m_bNew && DbUserInfoIsUsedID(m_nID)) ||
            (!m_bNew && !DbUserInfoIsUsedID(m_nID)))
    {
            int nStr = UISTR_ENROLL_INVALID_ID;
            if (!m_nID)
                    nStr = UISTR_ENROLL_INVALID_ID;
            else if (m_bNew)
                    nStr = UISTR_ENROLL_USED_ID;
            else if (!m_bNew)
                    nStr = UISTR_ENROLLDELETE_NODATA;
            uiLcdMessageBox(UI_MSG_ERROR,nStr,UI_MSGTIMEOUT);
            EnrollParamSet(0);
            bRet = FALSE;
            goto _lExit;
    }
*/

    if (TRUE)
    {
            USER_INFO *pUserInfo = (USER_INFO*)DbUserInfoGetPointer(m_nID);

            memset(&gUserInfoTemp, 0, sizeof(gUserInfoTemp));
            if (pUserInfo)
                    memcpy(&gUserInfoTemp, pUserInfo, sizeof(USER_INFO));

            gUserInfoTemp.ID = m_nID;
            //STRING2UNICODE(ui.txtName->text(), gUserInfoTemp.NAME, USERNAME_LENGTH);
            //gUserInfoTemp.PWD = STRING2PWD(STR2ASCII(ui.txtPassword->text()));
            DbUserInfoFlagManagerSet(&gUserInfoTemp, m_nManager);
            gUserInfoTemp.PART = ui->comboPart->currentIndex();
    }

    m_nCandidateID = m_nID;

_lExit:
    return bRet;

}
