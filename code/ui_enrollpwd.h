/********************************************************************************
** Form generated from reading UI file 'enrollpwd.ui'
**
** Created by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ENROLLPWD_H
#define UI_ENROLLPWD_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_EnrollPWD
{
public:
    QLabel *lblID;
    QLabel *lblName;
    QLabel *lblPart;
    QLabel *lblBackground;
    QLineEdit *txtName;
    QLabel *lblPwd;
    QLineEdit *txtID;
    QLabel *lblTitleIcon;
    QLabel *lblTitleBackground;
    QLabel *lblTitleText;
    QLineEdit *txtPwd;
    QLabel *lblStatus;
    QPushButton *pushButton;

    void setupUi(QDialog *EnrollPWD)
    {
        if (EnrollPWD->objectName().isEmpty())
            EnrollPWD->setObjectName(QString::fromUtf8("EnrollPWD"));
        EnrollPWD->resize(320, 240);
        lblID = new QLabel(EnrollPWD);
        lblID->setObjectName(QString::fromUtf8("lblID"));
        lblID->setGeometry(QRect(40, 60, 62, 20));
        lblName = new QLabel(EnrollPWD);
        lblName->setObjectName(QString::fromUtf8("lblName"));
        lblName->setGeometry(QRect(40, 90, 62, 20));
        lblPart = new QLabel(EnrollPWD);
        lblPart->setObjectName(QString::fromUtf8("lblPart"));
        lblPart->setGeometry(QRect(440, 160, 62, 20));
        lblBackground = new QLabel(EnrollPWD);
        lblBackground->setObjectName(QString::fromUtf8("lblBackground"));
        lblBackground->setGeometry(QRect(0, 30, 320, 240));
        txtName = new QLineEdit(EnrollPWD);
        txtName->setObjectName(QString::fromUtf8("txtName"));
        txtName->setGeometry(QRect(130, 90, 131, 22));
        lblPwd = new QLabel(EnrollPWD);
        lblPwd->setObjectName(QString::fromUtf8("lblPwd"));
        lblPwd->setGeometry(QRect(40, 120, 62, 20));
        txtID = new QLineEdit(EnrollPWD);
        txtID->setObjectName(QString::fromUtf8("txtID"));
        txtID->setGeometry(QRect(130, 60, 131, 22));
        lblTitleIcon = new QLabel(EnrollPWD);
        lblTitleIcon->setObjectName(QString::fromUtf8("lblTitleIcon"));
        lblTitleIcon->setGeometry(QRect(0, 0, 26, 26));
        lblTitleBackground = new QLabel(EnrollPWD);
        lblTitleBackground->setObjectName(QString::fromUtf8("lblTitleBackground"));
        lblTitleBackground->setGeometry(QRect(0, 0, 320, 30));
        lblTitleText = new QLabel(EnrollPWD);
        lblTitleText->setObjectName(QString::fromUtf8("lblTitleText"));
        lblTitleText->setGeometry(QRect(50, 0, 240, 28));
        txtPwd = new QLineEdit(EnrollPWD);
        txtPwd->setObjectName(QString::fromUtf8("txtPwd"));
        txtPwd->setGeometry(QRect(130, 120, 131, 21));
        lblStatus = new QLabel(EnrollPWD);
        lblStatus->setObjectName(QString::fromUtf8("lblStatus"));
        lblStatus->setGeometry(QRect(30, 200, 251, 31));
        pushButton = new QPushButton(EnrollPWD);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(190, 160, 98, 31));
        lblPart->raise();
        lblBackground->raise();
        txtName->raise();
        lblPwd->raise();
        txtID->raise();
        lblTitleIcon->raise();
        lblTitleBackground->raise();
        lblTitleText->raise();
        txtPwd->raise();
        lblStatus->raise();
        pushButton->raise();
        lblName->raise();
        lblID->raise();
        QWidget::setTabOrder(pushButton, txtID);
        QWidget::setTabOrder(txtID, txtPwd);
        QWidget::setTabOrder(txtPwd, txtName);

        retranslateUi(EnrollPWD);

        QMetaObject::connectSlotsByName(EnrollPWD);
    } // setupUi

    void retranslateUi(QDialog *EnrollPWD)
    {
        EnrollPWD->setWindowTitle(QApplication::translate("EnrollPWD", "Dialog", 0, QApplication::UnicodeUTF8));
        lblID->setText(QApplication::translate("EnrollPWD", "ID", 0, QApplication::UnicodeUTF8));
        lblName->setText(QApplication::translate("EnrollPWD", "Name", 0, QApplication::UnicodeUTF8));
        lblPart->setText(QApplication::translate("EnrollPWD", "Part", 0, QApplication::UnicodeUTF8));
        lblBackground->setText(QString());
        lblPwd->setText(QApplication::translate("EnrollPWD", "Pwd", 0, QApplication::UnicodeUTF8));
        lblTitleIcon->setText(QString());
        lblTitleBackground->setText(QString());
        lblTitleText->setText(QApplication::translate("EnrollPWD", "Title", 0, QApplication::UnicodeUTF8));
        lblStatus->setText(QApplication::translate("EnrollPWD", "OK :Next             ESC:Back", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("EnrollPWD", "OK", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class EnrollPWD: public Ui_EnrollPWD {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ENROLLPWD_H
