#include "cenrollstep1.h"
#include "ui_cenrollstep1.h"

#include "Define.h"
#include "../hiwaylib.h"

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

    //m_bTerminateFlag = !EnrollParamSet();
    m_bTerminateFlag = FALSE;
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
                nKey = GetKey();

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
                        //if(pCurrentBtn == ui.btnOK)
                        //bRet = OnBtnOK();  //转入下步骤
                    qDebug("UIKEY_OK");
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
        qDebug("xxxx1");
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