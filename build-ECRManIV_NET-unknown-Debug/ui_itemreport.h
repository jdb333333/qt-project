/********************************************************************************
** Form generated from reading UI file 'itemreport.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ITEMREPORT_H
#define UI_ITEMREPORT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_itemreport
{
public:
    QLabel *Cc;
    QLabel *Qty;
    QLabel *Amt;
    QLabel *Ret;
    QLabel *Disc;
    QLabel *Cost;
    QLineEdit *CcValue;
    QLineEdit *QtyValue;
    QLineEdit *AmtValue;
    QLineEdit *RetValue;
    QLineEdit *DiscValue;
    QLineEdit *CostValue;
    QLabel *ReportName;

    void setupUi(QWidget *itemreport)
    {
        if (itemreport->objectName().isEmpty())
            itemreport->setObjectName(QString::fromUtf8("itemreport"));
        itemreport->resize(240, 240);
        Cc = new QLabel(itemreport);
        Cc->setObjectName(QString::fromUtf8("Cc"));
        Cc->setGeometry(QRect(20, 50, 54, 12));
        Qty = new QLabel(itemreport);
        Qty->setObjectName(QString::fromUtf8("Qty"));
        Qty->setGeometry(QRect(20, 80, 54, 12));
        Amt = new QLabel(itemreport);
        Amt->setObjectName(QString::fromUtf8("Amt"));
        Amt->setGeometry(QRect(20, 110, 54, 12));
        Ret = new QLabel(itemreport);
        Ret->setObjectName(QString::fromUtf8("Ret"));
        Ret->setGeometry(QRect(20, 140, 54, 12));
        Disc = new QLabel(itemreport);
        Disc->setObjectName(QString::fromUtf8("Disc"));
        Disc->setGeometry(QRect(20, 170, 54, 12));
        Cost = new QLabel(itemreport);
        Cost->setObjectName(QString::fromUtf8("Cost"));
        Cost->setGeometry(QRect(20, 200, 54, 12));
        CcValue = new QLineEdit(itemreport);
        CcValue->setObjectName(QString::fromUtf8("CcValue"));
        CcValue->setGeometry(QRect(100, 50, 113, 20));
        QtyValue = new QLineEdit(itemreport);
        QtyValue->setObjectName(QString::fromUtf8("QtyValue"));
        QtyValue->setGeometry(QRect(100, 80, 113, 20));
        AmtValue = new QLineEdit(itemreport);
        AmtValue->setObjectName(QString::fromUtf8("AmtValue"));
        AmtValue->setGeometry(QRect(100, 110, 113, 20));
        RetValue = new QLineEdit(itemreport);
        RetValue->setObjectName(QString::fromUtf8("RetValue"));
        RetValue->setGeometry(QRect(100, 140, 113, 20));
        DiscValue = new QLineEdit(itemreport);
        DiscValue->setObjectName(QString::fromUtf8("DiscValue"));
        DiscValue->setGeometry(QRect(100, 170, 113, 20));
        CostValue = new QLineEdit(itemreport);
        CostValue->setObjectName(QString::fromUtf8("CostValue"));
        CostValue->setGeometry(QRect(100, 200, 113, 20));
        ReportName = new QLabel(itemreport);
        ReportName->setObjectName(QString::fromUtf8("ReportName"));
        ReportName->setGeometry(QRect(20, 20, 121, 16));

        retranslateUi(itemreport);

        QMetaObject::connectSlotsByName(itemreport);
    } // setupUi

    void retranslateUi(QWidget *itemreport)
    {
        itemreport->setWindowTitle(QApplication::translate("itemreport", "Form", 0, QApplication::UnicodeUTF8));
        Cc->setText(QApplication::translate("itemreport", "Cc:", 0, QApplication::UnicodeUTF8));
        Qty->setText(QApplication::translate("itemreport", "Qty:", 0, QApplication::UnicodeUTF8));
        Amt->setText(QApplication::translate("itemreport", "Amt:", 0, QApplication::UnicodeUTF8));
        Ret->setText(QApplication::translate("itemreport", "Ret:", 0, QApplication::UnicodeUTF8));
        Disc->setText(QApplication::translate("itemreport", "Disc", 0, QApplication::UnicodeUTF8));
        Cost->setText(QApplication::translate("itemreport", "Cost", 0, QApplication::UnicodeUTF8));
        ReportName->setText(QApplication::translate("itemreport", "ReportName", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class itemreport: public Ui_itemreport {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ITEMREPORT_H
