#include "enrollpwd.h"
#include "ui_enrollpwd.h"

#include "Define.h"
#include "../hiwaylib.h"
#include <QDebug>

#define PWDNUMBER_LENGTH   8
#define IDNUMBER_LENGTH    8

EnrollPWD::EnrollPWD(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EnrollPWD)
{
    ui->setupUi(this);
    GUI_DLG_IMPL(TRUE);
    GUI_DLG_SET_THEME();
    show();
    qDebug("EnrollPWD::EnrollPWD");

    connect(qApp, SIGNAL(focusChanged(QWidget*, QWidget*)), this, SLOT(OnFocusChanged(QWidget*, QWidget*)));
    connect(ui->txtID, SIGNAL(textEdited(const QString &)), this, SLOT(OnIDChange(const QString &)));

    m_nCandidateID = -1;

    QString szTitle = QString("[%1]-%2")
            .arg(UISTR(UISTR_USER_NEW))
            .arg(UISTR(UISTR_USER_ENROLL_PWD));
    uiLcdSetLabelText(ui->lblTitleText,szTitle,TITLECOLOR,QColor());
    //ui->lblName->setText(UISTR(UISTR_USER_NAME));
    //ui->txtName->setText("loveywm");
    ui->lblID->setText(UISTR(UISTR_USER_ID));
    ui->lblPwd->setText(UISTR(UISTR_ENTER_USER_PWD));
    ui->lblName->setText(UISTR(UISTR_USER_NAME));
    //ui->pushButton->hide();

    //ui->txtID->setFocus(Qt::MouseFocusReason);
    //ui->txtID->selectAll();

    //this->setFocusProxy();
    ui->txtName->setMaxLength(12);
    ui->txtID->setMaxLength(IDNUMBER_LENGTH);
    ui->txtPwd->setMaxLength(PWDNUMBER_LENGTH);


    m_bTerminateFlag = !EnrollParamSet();
}

EnrollPWD::~EnrollPWD()
{
    delete ui;
}

int EnrollPWD::DoProcess(int nEdit)
{
    int nKey;
    qDebug("EnrollPWD::DoProcess");

    while (!m_bTerminateFlag && uiTimeIsTimeout(60000) == FALSE)
    {

        POST_EVENTS();
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
            OnBtnOK();  //转入下步骤

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

void EnrollPWD::keyPressEvent(QKeyEvent *e)
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

BOOL EnrollPWD::OnBtnOK()
{
    int i,ret;
    int nRet;

    if(!EnrollCheck())
    {

        return FALSE;
    }

    gUserInfoTemp.ID = m_newID;

    nRet = DbUserInfoEnroll(&gUserInfoTemp,BACKUP_PASSWORD,&m_newID);
    qDebug() << "nRet==" << nRet;
    qDebug() << "1 DbUserInfoGetCount()==" << DbUserInfoGetCount();

    /*
    DbUserInfoDeleteAll();
    for(i=1;i<11;i++)
    {
        gUserInfoTemp.ID = i;
        gUserInfoTemp.PWD = i;
        ret = i;
        nRet = DbUserInfoEnroll(&gUserInfoTemp,BACKUP_PASSWORD,&ret);
        qDebug() << "nRet==" << nRet;
        qDebug() << "i==" << i;
    }
    */
    qDebug() << "dbLicense.nMaxEnrollCount==" << dbLicense.nMaxEnrollCount;
    for(i=0;i<dbLicense.nMaxEnrollCount;i++)
    {
        if(gpUserInfoEnrollData[i].ID == 0)
        {
            break;
        }
        qDebug() << "gpUserInfoEnrollData["<<i<<"].ID=="<< gpUserInfoEnrollData[i].ID;
        qDebug() << "gpUserInfoEnrollData["<<i<<"].PWD=="<<gpUserInfoEnrollData[i].PWD;
    }

    DbUserInfoGetCount();
    qDebug() << "2 DbUserInfoGetCount()==" << DbUserInfoGetCount();



}

BOOL EnrollPWD::EnrollParamSet(int nCandidateDiff)
{
    BOOL m_bNew = TRUE;
    if(nCandidateDiff >= 0)
    {
        if(m_nCandidateID == (UINT64)(-1))
            m_nCandidateID = 1;
        else
            m_nCandidateID += nCandidateDiff;

        qDebug() << "m_nCandidateID ==" << m_nCandidateID;

        m_nCandidateID = Db_GetCandidateID(m_bNew, m_nCandidateID);

        qDebug() << "m_nCandidateID 222==" << m_nCandidateID;;
        if (!m_nCandidateID)
        {
            //if(m_bNew)
                //uiLcdMessageBox(UI_MSG_ERROR, UISTR_ENROLL_OVERFLOW, UI_MSGTIMEOUT);
            //else
                //uiLcdMessageBox(UI_MSG_ERROR, UISTR_ENROLL_NOUSER, UI_MSGTIMEOUT);
            //return FALSE;
        }
        ui->txtID->setText(UserId_BCDtoSTR(m_nCandidateID));
        ui->txtPwd->setText(UserId_BCDtoSTR(m_nCandidateID));
        m_newID = m_nCandidateID;
    }
    return TRUE;
}

BOOL EnrollPWD::EnrollCheck(BOOL bIDChange)
{
    BOOL bRet = TRUE;
    //int MGR_LIST[] = {PRIV_USER, PRIV_MGR, PRIV_SMGR};

    m_newID = UserId_STRtoBCD(STR2ASCII(ui->txtID->text()));
    //m_nManager = MGR_LIST[ui->comboLevel->currentIndex()];

    qDebug() << "EnrollCheck::m_newID==" <<m_newID;



    if(DbUserInfoIsUsedID(m_newID))
    {
        qDebug() << "DbUserInfo Is UsedID" ;

        uiLcdMessageBox(UI_MSG_ERROR,UISTR_ENROLL_USED_ID,UI_MSGTIMEOUT);

        return FALSE;
    }




    //m_nCandidateID = m_nID;

_lExit:
    return bRet;

}

void EnrollPWD::OnFocusChanged(QWidget *from, QWidget *to)
{
    BOOL  bResult;
    if (to == (QWidget*)ui->txtID)
    {
        qDebug("to == (QWidget*)ui->txtID");
        //if(to == (QWidget*)ui->txtPwd)
        //{
            //qDebug("to == (QWidget*)ui->txtPwd");
        //}

    }
    if(to == (QWidget*)ui->txtPwd)
    {
        qDebug("to == (QWidget*)ui->txtPWD");
    }

    if(to == (QWidget*)ui->txtName)
    {
        qDebug("to == (QWidget*)ui->txtName");
    }


}

void EnrollPWD::OnIDChange(const QString &szID)
{
    UINT64 nID = UserId_STRtoBCD(STR2ASCII(szID));
    m_newID = nID;
    qDebug() << "EnrollPWD::OnIDChange  nID==" << nID;
    if (nID > 999999999)
    {
            //uiSoundOut(SOUND_ERROR, UI_BUZZER_ERROR);
            ui->txtID->setText(UserId_BCDtoSTR(99999999));
            ui->txtID->selectAll();
    }
    EnrollCheck(TRUE);
    EnrollParamSet(-1);
}

void EnrollPWD::OnPasswordChange(const QString &szPassword)
{
}
