/********************************************************************************
** Form generated from reading UI file 'reportdialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REPORTDIALOG_H
#define UI_REPORTDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QStackedWidget>
#include <QtGui/QTableWidget>
#include <QtGui/QTextEdit>
#include <QtGui/QTimeEdit>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_reportDialog
{
public:
    QPushButton *DOWNLOADDATA;
    QProgressBar *progressBar;
    QTextEdit *reportedit;
    QGroupBox *xzreoprt;
    QRadioButton *xreport;
    QRadioButton *zreport;
    QTableWidget *tableWidget;
    QLabel *info;
    QTimeEdit *timeEdit;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QPushButton *DAILYBTN;
    QPushButton *CLERKBTN;
    QPushButton *TIMEBTN;
    QPushButton *PLUBTN;
    QWidget *page_2;
    QPushButton *cleardbreport;

    void setupUi(QDialog *reportDialog)
    {
        if (reportDialog->objectName().isEmpty())
            reportDialog->setObjectName(QString::fromUtf8("reportDialog"));
        reportDialog->resize(640, 480);
        DOWNLOADDATA = new QPushButton(reportDialog);
        DOWNLOADDATA->setObjectName(QString::fromUtf8("DOWNLOADDATA"));
        DOWNLOADDATA->setGeometry(QRect(520, 420, 101, 31));
        progressBar = new QProgressBar(reportDialog);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(10, 420, 501, 31));
        progressBar->setValue(0);
        reportedit = new QTextEdit(reportDialog);
        reportedit->setObjectName(QString::fromUtf8("reportedit"));
        reportedit->setGeometry(QRect(190, 10, 291, 401));
        xzreoprt = new QGroupBox(reportDialog);
        xzreoprt->setObjectName(QString::fromUtf8("xzreoprt"));
        xzreoprt->setGeometry(QRect(10, 10, 171, 51));
        xreport = new QRadioButton(xzreoprt);
        xreport->setObjectName(QString::fromUtf8("xreport"));
        xreport->setGeometry(QRect(10, 20, 71, 16));
        xreport->setChecked(true);
        zreport = new QRadioButton(xzreoprt);
        zreport->setObjectName(QString::fromUtf8("zreport"));
        zreport->setGeometry(QRect(90, 20, 71, 16));
        tableWidget = new QTableWidget(reportDialog);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setGeometry(QRect(490, 10, 141, 401));
        info = new QLabel(reportDialog);
        info->setObjectName(QString::fromUtf8("info"));
        info->setGeometry(QRect(10, 460, 471, 16));
        timeEdit = new QTimeEdit(reportDialog);
        timeEdit->setObjectName(QString::fromUtf8("timeEdit"));
        timeEdit->setGeometry(QRect(50, 350, 101, 22));
        stackedWidget = new QStackedWidget(reportDialog);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setGeometry(QRect(10, 60, 171, 241));
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        DAILYBTN = new QPushButton(page);
        DAILYBTN->setObjectName(QString::fromUtf8("DAILYBTN"));
        DAILYBTN->setGeometry(QRect(40, 10, 101, 23));
        CLERKBTN = new QPushButton(page);
        CLERKBTN->setObjectName(QString::fromUtf8("CLERKBTN"));
        CLERKBTN->setGeometry(QRect(40, 130, 101, 23));
        TIMEBTN = new QPushButton(page);
        TIMEBTN->setObjectName(QString::fromUtf8("TIMEBTN"));
        TIMEBTN->setGeometry(QRect(40, 90, 101, 23));
        PLUBTN = new QPushButton(page);
        PLUBTN->setObjectName(QString::fromUtf8("PLUBTN"));
        PLUBTN->setGeometry(QRect(40, 50, 101, 23));
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        stackedWidget->addWidget(page_2);
        cleardbreport = new QPushButton(reportDialog);
        cleardbreport->setObjectName(QString::fromUtf8("cleardbreport"));
        cleardbreport->setGeometry(QRect(50, 310, 101, 31));

        retranslateUi(reportDialog);

        QMetaObject::connectSlotsByName(reportDialog);
    } // setupUi

    void retranslateUi(QDialog *reportDialog)
    {
        reportDialog->setWindowTitle(QApplication::translate("reportDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        DOWNLOADDATA->setText(QApplication::translate("reportDialog", "DOWNLOAD", 0, QApplication::UnicodeUTF8));
        xzreoprt->setTitle(QApplication::translate("reportDialog", "REPORTR", 0, QApplication::UnicodeUTF8));
        xreport->setText(QApplication::translate("reportDialog", "X REPORT", 0, QApplication::UnicodeUTF8));
        zreport->setText(QApplication::translate("reportDialog", "Z REPORT", 0, QApplication::UnicodeUTF8));
        info->setText(QApplication::translate("reportDialog", "TextLabel", 0, QApplication::UnicodeUTF8));
        DAILYBTN->setText(QApplication::translate("reportDialog", "DAILY REPORT", 0, QApplication::UnicodeUTF8));
        CLERKBTN->setText(QApplication::translate("reportDialog", "CLERK DAILY", 0, QApplication::UnicodeUTF8));
        TIMEBTN->setText(QApplication::translate("reportDialog", "TIME ZONE", 0, QApplication::UnicodeUTF8));
        PLUBTN->setText(QApplication::translate("reportDialog", "PERIOD PLU", 0, QApplication::UnicodeUTF8));
        cleardbreport->setText(QApplication::translate("reportDialog", "CLEARREPORT", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class reportDialog: public Ui_reportDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REPORTDIALOG_H
