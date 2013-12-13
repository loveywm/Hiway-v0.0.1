#ifndef CENROLLSTEP1_H
#define CENROLLSTEP1_H

#include <QDialog>


//typedef unsigned char			BYTE, u8, uchar;
typedef unsigned char			BOOL;
typedef unsigned short			WORD, UINT16,u16;
typedef unsigned int			DWORD, UINT32, u32;
typedef long				LONG;
typedef unsigned long long		UINT64, u64;

namespace Ui {
    class CEnrollStep1;
}

class CEnrollStep1 : public QDialog
{
    Q_OBJECT

public:
    enum {ID_ALL, ID_NEW, ID_BACKUP};
    CEnrollStep1(QWidget *parent = NULL, UINT64 nID = 0, BOOL bNew = TRUE,BOOL bEdit = FALSE);
    ~CEnrollStep1();
    //BOOL EnrollParamSet(int nCandidateDiff = 1);
    //BOOL EnrollCheck(BOOL bIDChange = FALSE);
    //BOOL EnrollUserInfo();
    int DoProcess(int nEdit = 0);

public Q_SLOTS:
    ;
    void OnFocusChanged(QWidget *from, QWidget *to);
    //void OnIDChange(const QString & szID);
    //void OnPasswordChange(const QString & szPassword);
    //BOOL OnBtnOK();
    BOOL OnBtnESC();

protected:
    //bool event(QEvent *e);

private:
    BOOL m_bTerminateFlag;

    BOOL m_bNew;
    BOOL m_nEdit;
    UINT64 m_nCandidateID;
    UINT64 m_nID;
    int m_nManager;

    Ui::CEnrollStep1 *ui;
};

#endif // CENROLLSTEP1_H
