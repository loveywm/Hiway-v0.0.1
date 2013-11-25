#ifndef CMAINFRAME_H
#define CMAINFRAME_H

#include <QDialog>
#include "Define.h"
//#include <QPixmap>

class QPixmap;

namespace Ui {
class CMainFrame;
}

class CMainFrame : public QDialog
{
    Q_OBJECT
    
public:
    explicit CMainFrame(QWidget *parent = 0);
    ~CMainFrame();
    void setTitle(QString szIcon, QString szTitle);
    int getFrameX() {return m_nFrameX;}
    int getFrameY() {return m_nFrameY;}
    int getFrameWidth() {return m_nFrameWidth;}
    int getFrameHeight() {return m_nFrameHeight;}


    
//private:
    Ui::CMainFrame *ui;
    QPixmap m_pmapFrame;

protected:
    int m_nFrameX;
    int m_nFrameY;
    int m_nFrameWidth;
    int m_nFrameHeight;
};



#endif // CMAINFRAME_H
