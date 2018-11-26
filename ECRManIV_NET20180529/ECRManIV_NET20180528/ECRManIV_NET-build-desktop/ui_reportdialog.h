/********************************************************************************
** Form generated from reading UI file 'reportdialog.ui'
**
** Created: Tue May 29 11:34:48 2018
**      by: Qt User Interface Compiler version 4.7.2
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
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_reportDialog
{
public:
    QPushButton *pushButton;
    QProgressBar *progressBar;
    QPushButton *cleardbreport;
    QTextEdit *reportedit;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QPushButton *grandtotal_5;
    QPushButton *correction_5;
    QGroupBox *xzreoprt;
    QRadioButton *xreport;
    QRadioButton *zreport;

    void setupUi(QDialog *reportDialog)
    {
        if (reportDialog->objectName().isEmpty())
            reportDialog->setObjectName(QString::fromUtf8("reportDialog"));
        reportDialog->resize(640, 480);
        pushButton = new QPushButton(reportDialog);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(520, 420, 101, 31));
        progressBar = new QProgressBar(reportDialog);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(10, 420, 501, 31));
        progressBar->setValue(0);
        cleardbreport = new QPushButton(reportDialog);
        cleardbreport->setObjectName(QString::fromUtf8("cleardbreport"));
        cleardbreport->setGeometry(QRect(50, 370, 101, 31));
        reportedit = new QTextEdit(reportDialog);
        reportedit->setObjectName(QString::fromUtf8("reportedit"));
        reportedit->setGeometry(QRect(200, 0, 451, 401));
        pushButton_2 = new QPushButton(reportDialog);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(50, 70, 101, 23));
        pushButton_3 = new QPushButton(reportDialog);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(50, 110, 101, 23));
        pushButton_4 = new QPushButton(reportDialog);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setGeometry(QRect(50, 230, 101, 23));
        pushButton_5 = new QPushButton(reportDialog);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        pushButton_5->setGeometry(QRect(50, 270, 101, 23));
        grandtotal_5 = new QPushButton(reportDialog);
        grandtotal_5->setObjectName(QString::fromUtf8("grandtotal_5"));
        grandtotal_5->setGeometry(QRect(50, 150, 101, 23));
        correction_5 = new QPushButton(reportDialog);
        correction_5->setObjectName(QString::fromUtf8("correction_5"));
        correction_5->setGeometry(QRect(50, 190, 101, 23));
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

        retranslateUi(reportDialog);

        QMetaObject::connectSlotsByName(reportDialog);
    } // setupUi

    void retranslateUi(QDialog *reportDialog)
    {
        reportDialog->setWindowTitle(QApplication::translate("reportDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("reportDialog", "DOWNLOAD", 0, QApplication::UnicodeUTF8));
        cleardbreport->setText(QApplication::translate("reportDialog", "CLEARREPORT", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("reportDialog", "DAILY REPORT", 0, QApplication::UnicodeUTF8));
        pushButton_3->setText(QApplication::translate("reportDialog", "PERIOD REPORT", 0, QApplication::UnicodeUTF8));
        pushButton_4->setText(QApplication::translate("reportDialog", "CLERK DAILY", 0, QApplication::UnicodeUTF8));
        pushButton_5->setText(QApplication::translate("reportDialog", "CLERK PERIOD", 0, QApplication::UnicodeUTF8));
        grandtotal_5->setText(QApplication::translate("reportDialog", "PERIOD PLU", 0, QApplication::UnicodeUTF8));
        correction_5->setText(QApplication::translate("reportDialog", "TIME ZONE", 0, QApplication::UnicodeUTF8));
        xzreoprt->setTitle(QApplication::translate("reportDialog", "REPORTR", 0, QApplication::UnicodeUTF8));
        xreport->setText(QApplication::translate("reportDialog", "X REPORT", 0, QApplication::UnicodeUTF8));
        zreport->setText(QApplication::translate("reportDialog", "Z REPORT", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class reportDialog: public Ui_reportDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REPORTDIALOG_H
