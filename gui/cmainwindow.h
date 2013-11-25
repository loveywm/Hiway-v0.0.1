#ifndef CMAINWINDOW_H
#define CMAINWINDOW_H

#include <QWidget>
#include "Define.h"

namespace Ui {
    class CMainWindow;
}

class CMainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit CMainWindow(QWidget *parent = 0);
    ~CMainWindow();
    //int SetTimer(DWORD dwTimerID, int nElapse, DWORD dwParam, TIMERPROC lpTimerFunc);
    //void StopTimer(DWORD dwTimerID);
    void DrawClock(BOOL bFirst = FALSE);

public Q_SLOTS:;
    void OnTimer();

private:
    Ui::CMainWindow *ui;
    QPixmap m_ClockPixmap;
    int m_ClockW, m_ClockH;
};

#endif // CMAINWINDOW_H
