

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

    connect(qApp, SIGNAL(focusChanged(QWidget*, QWidget*)), this, SLOT(OnFocusChanged(QWidget*, QWidget*)));
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
    //int nParts = DbPartCount();
    //for (int i=0; i<nParts; i++)
    //ui.comboPart->addItem(DbPartGet(i));

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
    if(m_nEdit == ID_NEW)
    {
        uiLcdSetLabelText(ui->lblTitleText,UISTR(UISTR_USER_NEW),TITLECOLOR,QColor());
    }

    ui->txtID->selectAll();
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

            pCurrentBtn = (QPushButton*)QApplication::focusWidget();
            if(pCurrentBtn == ui->btnOK)
                bRet = OnBtnOK();  //转入下步骤
            qDebug("UIKEY_OK");
            break;
        case  UIKEY_DOWN:
            ui->txtID->setFocus(Qt::MouseFocusReason);
            qDebug("UIKEY_DOWN");
            break;
        case  UIKEY_UP:
            ui->txtName->setFocus(Qt::MouseFocusReason);
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
                ui->txtID->setFocus(Qt::MouseFocusReason);
                ui->txtID->selectAll();
            }
            //EnrollParamSet(-1);
        }
        qDebug("xxxx4");
    }

    if (to == (QWidget*)ui->txtID)
        ui->txtID->selectAll();
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


    qDebug() << "CEnrollStep1::OnBtnOK()";
}


BOOL CEnrollStep1::EnrollParamSet(int nCandidateDiff)
{
    if (nCandidateDiff >= 0)
    {
        if(m_nCandidateID == (UINT64)(-1))
            m_nCandidateID = 1;
        else
            m_nCandidateID += nCandidateDiff;
        m_nCandidateID = Db_GetCandidateID(m_bNew, m_nCandidateID);
        if (!m_nCandidateID)
        {
            if(m_bNew)
                uiLcdMessageBox(UI_MSG_ERROR, UISTR_ENROLL_OVERFLOW, UI_MSGTIMEOUT);
            else
                uiLcdMessageBox(UI_MSG_ERROR, UISTR_ENROLL_NOUSER, UI_MSGTIMEOUT);
            return FALSE;
        }
        ui->txtID->setText(UserId_BCDtoSTR(m_nCandidateID));
        m_nID = m_nCandidateID;
    }

    USER_INFO* pUserInfo = (USER_INFO*)DbUserInfoGetPointer(m_nID);

    if (m_bNew || !pUserInfo)
    {
            ui.txtName->clear();
            //ui.txtPassword->setText(PWD2STRING(DEFAULT_PASSWORD));
            //ui.txtPasswordConfirm->setText(PWD2STRING(DEFAULT_PASSWORD));
            ui.comboLevel->setCurrentIndex(0);
            if(DbPartCount()>1)
            ui.comboPart->setCurrentIndex(1);
            else
            ui.comboPart->setCurrentIndex(0);
    }
    else
    {
            ui.txtName->setText(UNICODE2STRING(pUserInfo->NAME, USERNAME_LENGTH));
            //ui.txtPassword->setText(PWD2STRING(pUserInfo->PWD));
            //ui.txtPasswordConfirm->setText(PWD2STRING(pUserInfo->PWD));
            ui.comboLevel->setCurrentIndex(PRIV_INDEX(DbUserInfoFlagManagerGet(pUserInfo)));
            if (pUserInfo->PART < DbPartCount())
                    ui.comboPart->setCurrentIndex(pUserInfo->PART);
            else
                    ui.comboPart->setCurrentIndex(0);
    }

    if (nCandidateDiff >= 0)
    {
            ui->txtID->setFocus(Qt::MouseFocusReason);
            ui->txtID->selectAll();
    }
    return TRUE;
}
