/********************************************************************************
** Form generated from reading UI file 'reportdisp.ui'
**
** Created: Mon May 28 15:41:09 2018
**      by: Qt User Interface Compiler version 4.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REPORTDISP_H
#define UI_REPORTDISP_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QTableView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_reportdisp
{
public:
    QTableView *tableView;

    void setupUi(QWidget *reportdisp)
    {
        if (reportdisp->objectName().isEmpty())
            reportdisp->setObjectName(QString::fromUtf8("reportdisp"));
        reportdisp->resize(480, 320);
        tableView = new QTableView(reportdisp);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setGeometry(QRect(0, 11, 481, 301));

        retranslateUi(reportdisp);

        QMetaObject::connectSlotsByName(reportdisp);
    } // setupUi

    void retranslateUi(QWidget *reportdisp)
    {
        reportdisp->setWindowTitle(QApplication::translate("reportdisp", "Form", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class reportdisp: public Ui_reportdisp {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REPORTDISP_H
