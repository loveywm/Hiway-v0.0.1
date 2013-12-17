#ifndef ENROLLPWD_H
#define ENROLLPWD_H

#include <QDialog>
#include <QKeyEvent>


typedef unsigned char			BOOL;
typedef unsigned short			WORD, UINT16,u16;
typedef unsigned int			DWORD, UINT32, u32;
typedef long				LONG;
typedef unsigned long long		UINT64, u64;

namespace Ui {
    class EnrollPWD;
}

class EnrollPWD : public QDialog
{
    Q_OBJECT

public:
    explicit EnrollPWD(QWidget *parent = 0);
    ~EnrollPWD();
    int DoProcess(int nEdit = 0);
    BOOL EnrollParamSet(int nCandidateDiff = 1);
    BOOL EnrollCheck(BOOL bIDChange = FALSE);
    BOOL OnBtnOK();

public Q_SLOTS:
    ;
    void OnFocusChanged(QWidget *from, QWidget *to);
    void OnIDChange(const QString & szID);
    void OnPasswordChange(const QString & szPassword);

protected:
    //bool event(QEvent *e);
    //位了pc端模拟测试
    void keyPressEvent(QKeyEvent *e);

private:
    Ui::EnrollPWD *ui;
    BOOL m_bTerminateFlag;
    UINT64 m_newID;
    UINT64 m_nCandidateID;




};

#endif // ENROLLPWD_H
