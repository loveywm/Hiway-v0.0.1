#include "cmainframe.h"
#include "ui_cmainframe.h"

//#include <QPixmap>
#include <QDebug>
#include "Define.h"

CMainFrame::CMainFrame(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CMainFrame)
{
    ui->setupUi(this);
    GUI_DLG_IMPL(TRUE);
    //ui->lblBackground->set
    //ui->lblTitleBackground->setPixmap(QPixmap(":/images/title-1.png"));
    //ui->lblTitleBackground->setPixmap(QPixmap(":/images/title-1.png"));
    //ui->lblBackground->setPixmap(QPixmap(":/images/res/bg-main2.png"));
    GUI_DLG_SET_THEME();

    m_pmapFrame = *ui->lblBackgroundFrame->pixmap();
    m_nFrameX = 0;
    m_nFrameY = ui->lblTitleIcon->height();
    m_nFrameWidth = ui->lblBackgroundFrame->width();
    m_nFrameHeight = ui->lblBackgroundFrame->height() - m_nFrameY - ui->lblStatusText->height();

    qDebug() <<"m_nFrameX="<<m_nFrameX ;
    qDebug() <<"m_nFrameY="<<m_nFrameY ;
    qDebug() <<"m_nFrameWidth="<<m_nFrameWidth ;
    qDebug() <<"m_nFrameHeight="<<m_nFrameHeight ;

    uiLcdSetLabelText(ui->lblTitleText,"Hiway",TITLECOLOR,QColor());

}

CMainFrame::~CMainFrame()
{
    delete ui;
}

void CMainFrame::setTitle(QString szIcon, QString szTitle)
{
    //QPixmap pmap_icon(szIcon);
    //ui->lblTitleIcon->setPixmap(pmap_icon);
    uiLcdSetLabelText(ui->lblTitleText, szTitle, TITLECOLOR,QColor());
}
