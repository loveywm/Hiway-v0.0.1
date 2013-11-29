#ifndef MENU_H
#define MENU_H
#include "cmainframe.h"


class CMenu : public CMainFrame
{
    Q_OBJECT

public:
    CMenu(QWidget *parent = NULL);
    ~CMenu() { };
    void MenuProc(int nPopupMenuTitle = -1);

private:
    void OnKeyPressOk(int nTitle);
    void OnKeyPressArrow(int nKey, int nTitle);
    void OnRedraw();

protected:
    void paintEvent(QPaintEvent *e);
    void drawIconStyle(QPainter *painter, int nCurrentIndex, int from, int to);
    void drawReportStyle(QPainter *painter, int nCurrentIndex, int from, int to, bool bDrawIcon);

private:
    unsigned char m_bTerminateFlag;
};

#endif // MENU_H
