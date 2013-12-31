#ifndef MESSAGEBOX_H
#define MESSAGEBOX_H

#include <QDialog>
#include "Define.h"


#define LCD_SIZE_X	320
#define LCD_SIZE_Y	240
#define GUI_DLG_CENTER(_DLG_)	{(_DLG_)->move((LCD_SIZE_X - (_DLG_)->width()) / 2, (LCD_SIZE_Y - (_DLG_)->height()) / 2);}


typedef enum
{
        UI_MSGRET_ESC,
        UI_MSGRET_OK,
        UI_MSGRET_TIMEOUT
}T_UI_MSGRET;

namespace Ui {
    class CMessageBox;
}

class CMessageBox : public QDialog
{
    Q_OBJECT

public:
    explicit CMessageBox(QWidget *parent = 0);
    ~CMessageBox();
    void SetIcon(QString szIconFile);
    void SetText(QString szText);
    void SetType(int nType);
    void SetText2(QString szText);
    int  MsgBoxProc(unsigned int nTimeout = 0xFFFFFFFF);
    //int  MsgBoxProc2(unsigned int nTimeout = 0xFFFFFFFF);
    //BOOL MsgBoxProc_Message(char *szMessage);
    //BOOL MsgBoxProc_Message4(char *szMessage);
    //BOOL MsgBoxProc_Message3(QString szMessage);

public Q_SLOTS:
        ;
        void OnBtnOK();
        void OnBtnESC();

private:
    Ui::CMessageBox *ui;
    bool m_bTerminateFlag;
    int  m_nRet;
};

#endif // MESSAGEBOX_H
