#include "messagebox.h"
#include "ui_messagebox.h"

#define INPUTBOX_IMAGE		":/images/res/bg-inputbox1.png" //g_bgImageFilename
typedef enum
{
        UI_MSG_ERROR,
        UI_MSG_OK,
        UI_MSG_QUESTION
} T_UI_MSG_TYPE;

CMessageBox::CMessageBox(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CMessageBox)
{
    ui->setupUi(this);
    ////GUI_DLG_IMPL(TRUE);
    this->setWindowTitle("Infomation Title");
    this->setGeometry(0,0,270,120);
    this->move((LCD_SIZE_X-this->width())/2,(LCD_SIZE_Y-this->height())/2);


    //GUI_DLG_CENTER(this);
    //GUI_DLG_SET_THEME_1();
    ui->lblBackground->setPixmap(QPixmap(INPUTBOX_IMAGE));
    SET_DLG_ITEM_COLOR(this);

    m_bTerminateFlag = FALSE;
    ui->lblMoreText->hide();    //add

    connect(ui->btnOK, SIGNAL(clicked()), this, SLOT(OnBtnOK()));
    connect(ui->btnESC, SIGNAL(clicked()), this, SLOT(OnBtnESC()));
    //pMessageBoxbtnOK=ui.btnOK;
}

CMessageBox::~CMessageBox()
{
    delete ui;
}

void CMessageBox::SetIcon(QString szIconFile)
{
        QPixmap pmap(szIconFile);
        ui->lblIcon->setPixmap(pmap);
}

//////////////////////////////////////////////////////////////////////////
void CMessageBox::SetText(QString szText)
{
        int i;
        int w = ui->lblStatus->width();
        QFontMetrics fm = ui->lblStatus->fontMetrics();

        for (i=0; i<szText.length(); i++)
        {
                if (fm.width(szText, i + 1) > w)
                        break;
        }

        QString szMessage = szText;
        if (i < szText.length())
                szMessage.insert(i, "\r\n");

        ui->lblStatus->setText(szMessage);
}
void CMessageBox::SetText2(QString szText)
{
        //int i;
        //int w = ui->lblMoreText->width();
        //QFontMetrics fm = ui->lblMoreText->fontMetrics();

        ui->lblMoreText->setText(szText);
}
void CMessageBox::SetType(int nType)
{
        int w = width();
        QPoint pos = ui->btnOK->pos();
        int w_btnOK = ui->btnOK->width();

        switch (nType)
        {
        case UI_MSG_OK:
        case UI_MSG_ERROR:
                ui->btnESC->hide();
//		ui.btnOK->hide();
//		ui.lblBackground->setGeometry(0, 0, ui.lblBackground->width(), 75);
                ui->btnOK->move(w / 2 - w_btnOK / 2, pos.y());
                break;
        }
}
int CMessageBox::MsgBoxProc(unsigned int nTimeout /* = 0xFFFFFFFF */)
{
        int nKey;
        m_nRet = UI_MSGRET_ESC;

        //if (LCD_BLANK_STATUS() == FBINFO_BLANK_PAUSE)
                //LCD_BLANK(FBINFO_BLANK_RESUME);

        while (!m_bTerminateFlag && uiTimeIsTimeout(nTimeout) == FALSE)
        {
                POST_EVENTS();

                //nKey = uiKeyGetKey(TRUE);
                //if (nKey == UIKEY_ESC)
                        //OnBtnESC();
        }

//_lExit:
        return m_nRet;
}


//////////////////////////////////////////////////////////////////////////
void CMessageBox::OnBtnOK()
{
        m_nRet = UI_MSGRET_OK;
        m_bTerminateFlag = TRUE;
}

//////////////////////////////////////////////////////////////////////////
void CMessageBox::OnBtnESC()
{
        m_nRet = UI_MSGRET_ESC;
        m_bTerminateFlag = TRUE;
}
