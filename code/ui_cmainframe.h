/********************************************************************************
** Form generated from reading ui file 'cmainframe.ui'
**
** Created: Fri Nov 29 10:35:45 2013
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_CMAINFRAME_H
#define UI_CMAINFRAME_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>

QT_BEGIN_NAMESPACE

class Ui_CMainFrame
{
public:
    QLabel *lblBackground;
    QLabel *lblBackgroundFrame;
    QLabel *lblStatusIcon;
    QLabel *lblStatusText;
    QLabel *lblTitleBackground;
    QLabel *lblTitleIcon;
    QLabel *lblTitleText;
    QLabel *lblTitleText1;

    void setupUi(QDialog *CMainFrame)
    {
        if (CMainFrame->objectName().isEmpty())
            CMainFrame->setObjectName(QString::fromUtf8("CMainFrame"));
        CMainFrame->resize(320, 240);
        lblBackground = new QLabel(CMainFrame);
        lblBackground->setObjectName(QString::fromUtf8("lblBackground"));
        lblBackground->setGeometry(QRect(0, 0, 320, 240));
        lblBackground->setPixmap(QPixmap(QString::fromUtf8(":/images/res/bg-main2.png")));
        lblBackgroundFrame = new QLabel(CMainFrame);
        lblBackgroundFrame->setObjectName(QString::fromUtf8("lblBackgroundFrame"));
        lblBackgroundFrame->setGeometry(QRect(12, 10, 297, 217));
        lblBackgroundFrame->setPixmap(QPixmap(QString::fromUtf8(":/images/res/bg-main2.png")));
        lblStatusIcon = new QLabel(CMainFrame);
        lblStatusIcon->setObjectName(QString::fromUtf8("lblStatusIcon"));
        lblStatusIcon->setGeometry(QRect(20, 215, 16, 16));
        lblStatusText = new QLabel(CMainFrame);
        lblStatusText->setObjectName(QString::fromUtf8("lblStatusText"));
        lblStatusText->setGeometry(QRect(40, 210, 275, 25));
        lblTitleBackground = new QLabel(CMainFrame);
        lblTitleBackground->setObjectName(QString::fromUtf8("lblTitleBackground"));
        lblTitleBackground->setGeometry(QRect(0, 0, 320, 30));
        lblTitleBackground->setPixmap(QPixmap(QString::fromUtf8(":/images/res/title-2.png")));
        lblTitleIcon = new QLabel(CMainFrame);
        lblTitleIcon->setObjectName(QString::fromUtf8("lblTitleIcon"));
        lblTitleIcon->setGeometry(QRect(9, 0, 26, 26));
        lblTitleText = new QLabel(CMainFrame);
        lblTitleText->setObjectName(QString::fromUtf8("lblTitleText"));
        lblTitleText->setGeometry(QRect(40, 0, 273, 28));
        lblTitleText1 = new QLabel(CMainFrame);
        lblTitleText1->setObjectName(QString::fromUtf8("lblTitleText1"));
        lblTitleText1->setGeometry(QRect(201, 0, 110, 28));
        lblBackground->raise();
        lblBackgroundFrame->raise();
        lblStatusIcon->raise();
        lblStatusText->raise();
        lblTitleText1->raise();
        lblTitleIcon->raise();
        lblTitleBackground->raise();
        lblTitleText->raise();

        retranslateUi(CMainFrame);

        QMetaObject::connectSlotsByName(CMainFrame);
    } // setupUi

    void retranslateUi(QDialog *CMainFrame)
    {
        CMainFrame->setWindowTitle(QApplication::translate("CMainFrame", "CMainFrame", 0, QApplication::UnicodeUTF8));
        lblBackground->setText(QString());
        lblBackgroundFrame->setText(QString());
        lblStatusIcon->setText(QString());
        lblStatusText->setText(QString());
        lblTitleBackground->setText(QString());
        lblTitleIcon->setText(QString());
        lblTitleText->setText(QString());
        lblTitleText1->setText(QString());
        Q_UNUSED(CMainFrame);
    } // retranslateUi

};

namespace Ui {
    class CMainFrame: public Ui_CMainFrame {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CMAINFRAME_H
