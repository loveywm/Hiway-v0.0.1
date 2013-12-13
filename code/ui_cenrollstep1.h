/********************************************************************************
** Form generated from reading ui file 'cenrollstep1.ui'
**
** Created: Mon Dec 2 17:00:11 2013
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_CENROLLSTEP1_H
#define UI_CENROLLSTEP1_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_CEnrollStep1
{
public:
    QPushButton *btnESC;
    QPushButton *btnOK;
    QComboBox *comboLevel;
    QComboBox *comboPart;
    QLabel *lblBackground;
    QLabel *lblID;
    QLabel *lblLevel;
    QLabel *lblName;
    QLabel *lblPart;
    QLabel *lblStatusIcon;
    QLabel *lblStatusText;
    QLabel *lblTitleBackground;
    QLabel *lblTitleIcon;
    QLabel *lblTitleText;
    QLineEdit *txtID;
    QLineEdit *txtName;

    void setupUi(QDialog *CEnrollStep1)
    {
        if (CEnrollStep1->objectName().isEmpty())
            CEnrollStep1->setObjectName(QString::fromUtf8("CEnrollStep1"));
        CEnrollStep1->resize(320, 240);
        btnESC = new QPushButton(CEnrollStep1);
        btnESC->setObjectName(QString::fromUtf8("btnESC"));
        btnESC->setGeometry(QRect(180, 160, 71, 25));
        btnOK = new QPushButton(CEnrollStep1);
        btnOK->setObjectName(QString::fromUtf8("btnOK"));
        btnOK->setGeometry(QRect(70, 160, 71, 25));
        comboLevel = new QComboBox(CEnrollStep1);
        comboLevel->setObjectName(QString::fromUtf8("comboLevel"));
        comboLevel->setGeometry(QRect(100, 120, 181, 22));
        comboPart = new QComboBox(CEnrollStep1);
        comboPart->setObjectName(QString::fromUtf8("comboPart"));
        comboPart->setGeometry(QRect(130, 40, 181, 22));
        lblBackground = new QLabel(CEnrollStep1);
        lblBackground->setObjectName(QString::fromUtf8("lblBackground"));
        lblBackground->setGeometry(QRect(0, 0, 320, 240));
        lblID = new QLabel(CEnrollStep1);
        lblID->setObjectName(QString::fromUtf8("lblID"));
        lblID->setGeometry(QRect(37, 50, 62, 20));
        lblLevel = new QLabel(CEnrollStep1);
        lblLevel->setObjectName(QString::fromUtf8("lblLevel"));
        lblLevel->setGeometry(QRect(37, 120, 62, 20));
        lblName = new QLabel(CEnrollStep1);
        lblName->setObjectName(QString::fromUtf8("lblName"));
        lblName->setGeometry(QRect(37, 85, 62, 20));
        lblPart = new QLabel(CEnrollStep1);
        lblPart->setObjectName(QString::fromUtf8("lblPart"));
        lblPart->setGeometry(QRect(240, 70, 62, 20));
        lblStatusIcon = new QLabel(CEnrollStep1);
        lblStatusIcon->setObjectName(QString::fromUtf8("lblStatusIcon"));
        lblStatusIcon->setGeometry(QRect(20, 205, 16, 16));
        lblStatusText = new QLabel(CEnrollStep1);
        lblStatusText->setObjectName(QString::fromUtf8("lblStatusText"));
        lblStatusText->setGeometry(QRect(40, 200, 270, 25));
        lblTitleBackground = new QLabel(CEnrollStep1);
        lblTitleBackground->setObjectName(QString::fromUtf8("lblTitleBackground"));
        lblTitleBackground->setGeometry(QRect(0, 6, 320, 30));
        lblTitleIcon = new QLabel(CEnrollStep1);
        lblTitleIcon->setObjectName(QString::fromUtf8("lblTitleIcon"));
        lblTitleIcon->setGeometry(QRect(20, 9, 26, 26));
        lblTitleText = new QLabel(CEnrollStep1);
        lblTitleText->setObjectName(QString::fromUtf8("lblTitleText"));
        lblTitleText->setGeometry(QRect(58, 10, 240, 28));
        txtID = new QLineEdit(CEnrollStep1);
        txtID->setObjectName(QString::fromUtf8("txtID"));
        txtID->setGeometry(QRect(100, 50, 131, 22));
        txtName = new QLineEdit(CEnrollStep1);
        txtName->setObjectName(QString::fromUtf8("txtName"));
        txtName->setGeometry(QRect(100, 85, 131, 22));

        retranslateUi(CEnrollStep1);

        QMetaObject::connectSlotsByName(CEnrollStep1);
    } // setupUi

    void retranslateUi(QDialog *CEnrollStep1)
    {
        CEnrollStep1->setWindowTitle(QApplication::translate("CEnrollStep1", "Dialog", 0, QApplication::UnicodeUTF8));
        btnESC->setText(QApplication::translate("CEnrollStep1", "ESC", 0, QApplication::UnicodeUTF8));
        btnOK->setText(QApplication::translate("CEnrollStep1", "OK", 0, QApplication::UnicodeUTF8));
        lblBackground->setText(QString());
        lblID->setText(QApplication::translate("CEnrollStep1", "ID", 0, QApplication::UnicodeUTF8));
        lblLevel->setText(QApplication::translate("CEnrollStep1", "Level", 0, QApplication::UnicodeUTF8));
        lblName->setText(QApplication::translate("CEnrollStep1", "Name", 0, QApplication::UnicodeUTF8));
        lblPart->setText(QApplication::translate("CEnrollStep1", "Part", 0, QApplication::UnicodeUTF8));
        lblStatusIcon->setText(QString());
        lblStatusText->setText(QApplication::translate("CEnrollStep1", "OK: Select  Or T9 Input   ESC: Back", 0, QApplication::UnicodeUTF8));
        lblTitleBackground->setText(QString());
        lblTitleIcon->setText(QString());
        lblTitleText->setText(QApplication::translate("CEnrollStep1", "Title", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(CEnrollStep1);
    } // retranslateUi

};

namespace Ui {
    class CEnrollStep1: public Ui_CEnrollStep1 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CENROLLSTEP1_H
