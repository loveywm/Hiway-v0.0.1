/********************************************************************************
** Form generated from reading UI file 'cmainwindow.ui'
**
** Created by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CMAINWINDOW_H
#define UI_CMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CMainWindow
{
public:
    QLabel *lblMenu;
    QLabel *lblNum;
    QLabel *lblBackground;
    QLabel *label;
    QLabel *lblTime;
    QLabel *lblDate;

    void setupUi(QWidget *CMainWindow)
    {
        if (CMainWindow->objectName().isEmpty())
            CMainWindow->setObjectName(QString::fromUtf8("CMainWindow"));
        CMainWindow->resize(320, 240);
        lblMenu = new QLabel(CMainWindow);
        lblMenu->setObjectName(QString::fromUtf8("lblMenu"));
        lblMenu->setGeometry(QRect(0, 190, 100, 50));
        lblMenu->setPixmap(QPixmap(QString::fromUtf8(":/images/res/menu.png")));
        lblNum = new QLabel(CMainWindow);
        lblNum->setObjectName(QString::fromUtf8("lblNum"));
        lblNum->setGeometry(QRect(220, 190, 100, 50));
        lblNum->setPixmap(QPixmap(QString::fromUtf8(":/images/res/num.png")));
        lblBackground = new QLabel(CMainWindow);
        lblBackground->setObjectName(QString::fromUtf8("lblBackground"));
        lblBackground->setGeometry(QRect(0, 0, 320, 240));
        label = new QLabel(CMainWindow);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(0, 0, 100, 25));
        lblTime = new QLabel(CMainWindow);
        lblTime->setObjectName(QString::fromUtf8("lblTime"));
        lblTime->setGeometry(QRect(100, 190, 120, 21));
        lblDate = new QLabel(CMainWindow);
        lblDate->setObjectName(QString::fromUtf8("lblDate"));
        lblDate->setGeometry(QRect(100, 220, 120, 21));
        lblBackground->raise();
        lblMenu->raise();
        lblNum->raise();
        label->raise();
        lblTime->raise();
        lblDate->raise();

        retranslateUi(CMainWindow);

        QMetaObject::connectSlotsByName(CMainWindow);
    } // setupUi

    void retranslateUi(QWidget *CMainWindow)
    {
        CMainWindow->setWindowTitle(QApplication::translate("CMainWindow", "Form", 0, QApplication::UnicodeUTF8));
        lblMenu->setText(QString());
        lblNum->setText(QString());
        lblBackground->setText(QString());
        label->setText(QApplication::translate("CMainWindow", "Hiway", 0, QApplication::UnicodeUTF8));
        lblTime->setText(QApplication::translate("CMainWindow", "Time", 0, QApplication::UnicodeUTF8));
        lblDate->setText(QApplication::translate("CMainWindow", "Date", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class CMainWindow: public Ui_CMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CMAINWINDOW_H
