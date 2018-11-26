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
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_reportDialog
{
public:
    QGroupBox *groupBox;
    QCheckBox *grandtotalbox;
    QCheckBox *departmentbox;
    QCheckBox *tenderbox;
    QCheckBox *drawerbox;
    QCheckBox *correctionbox;
    QCheckBox *discountbox;
    QCheckBox *taxbox;
    QCheckBox *clearreport;
    QPushButton *pushButton;
    QWidget *dailywidget;
    QLabel *label;
    QPushButton *grandtotal;
    QPushButton *department;
    QPushButton *tender;
    QPushButton *drawer;
    QPushButton *discount;
    QPushButton *tax;
    QPushButton *correction;
    QWidget *widget;
    QLabel *label_2;
    QPushButton *grandtotal_2;
    QPushButton *discount_2;
    QPushButton *tax_2;
    QPushButton *department_2;
    QPushButton *correction_2;
    QPushButton *tender_2;
    QPushButton *drawer_2;
    QWidget *clerkdailywidget;
    QLabel *label_3;
    QPushButton *tender_3;
    QPushButton *correction_3;
    QPushButton *drawer_3;
    QPushButton *discount_3;
    QPushButton *grandtotal_3;
    QWidget *widget_2;
    QLabel *label_4;
    QPushButton *tender_4;
    QPushButton *correction_4;
    QPushButton *discount_4;
    QPushButton *grandtotal_4;
    QWidget *widget_3;
    QPushButton *grandtotal_5;
    QLabel *label_5;
    QPushButton *correction_5;
    QPushButton *tender_5;
    QProgressBar *progressBar;
    QPushButton *cleardbreport;

    void setupUi(QDialog *reportDialog)
    {
        if (reportDialog->objectName().isEmpty())
            reportDialog->setObjectName(QString::fromUtf8("reportDialog"));
        reportDialog->resize(640, 480);
        groupBox = new QGroupBox(reportDialog);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(509, 10, 121, 261));
        grandtotalbox = new QCheckBox(groupBox);
        grandtotalbox->setObjectName(QString::fromUtf8("grandtotalbox"));
        grandtotalbox->setGeometry(QRect(10, 20, 101, 16));
        departmentbox = new QCheckBox(groupBox);
        departmentbox->setObjectName(QString::fromUtf8("departmentbox"));
        departmentbox->setGeometry(QRect(10, 50, 101, 16));
        tenderbox = new QCheckBox(groupBox);
        tenderbox->setObjectName(QString::fromUtf8("tenderbox"));
        tenderbox->setGeometry(QRect(10, 80, 101, 16));
        drawerbox = new QCheckBox(groupBox);
        drawerbox->setObjectName(QString::fromUtf8("drawerbox"));
        drawerbox->setGeometry(QRect(10, 110, 101, 16));
        correctionbox = new QCheckBox(groupBox);
        correctionbox->setObjectName(QString::fromUtf8("correctionbox"));
        correctionbox->setGeometry(QRect(10, 140, 91, 16));
        discountbox = new QCheckBox(groupBox);
        discountbox->setObjectName(QString::fromUtf8("discountbox"));
        discountbox->setGeometry(QRect(10, 170, 101, 16));
        taxbox = new QCheckBox(groupBox);
        taxbox->setObjectName(QString::fromUtf8("taxbox"));
        taxbox->setGeometry(QRect(10, 200, 101, 16));
        clearreport = new QCheckBox(groupBox);
        clearreport->setObjectName(QString::fromUtf8("clearreport"));
        clearreport->setGeometry(QRect(10, 230, 101, 16));
        pushButton = new QPushButton(reportDialog);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(520, 420, 101, 31));
        dailywidget = new QWidget(reportDialog);
        dailywidget->setObjectName(QString::fromUtf8("dailywidget"));
        dailywidget->setGeometry(QRect(0, -1, 501, 91));
        label = new QLabel(dailywidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 10, 91, 16));
        grandtotal = new QPushButton(dailywidget);
        grandtotal->setObjectName(QString::fromUtf8("grandtotal"));
        grandtotal->setGeometry(QRect(50, 30, 75, 23));
        department = new QPushButton(dailywidget);
        department->setObjectName(QString::fromUtf8("department"));
        department->setGeometry(QRect(160, 30, 75, 23));
        tender = new QPushButton(dailywidget);
        tender->setObjectName(QString::fromUtf8("tender"));
        tender->setGeometry(QRect(270, 30, 75, 23));
        drawer = new QPushButton(dailywidget);
        drawer->setObjectName(QString::fromUtf8("drawer"));
        drawer->setGeometry(QRect(380, 30, 75, 23));
        discount = new QPushButton(dailywidget);
        discount->setObjectName(QString::fromUtf8("discount"));
        discount->setGeometry(QRect(160, 60, 75, 23));
        tax = new QPushButton(dailywidget);
        tax->setObjectName(QString::fromUtf8("tax"));
        tax->setGeometry(QRect(270, 60, 75, 23));
        correction = new QPushButton(dailywidget);
        correction->setObjectName(QString::fromUtf8("correction"));
        correction->setGeometry(QRect(50, 60, 75, 23));
        widget = new QWidget(reportDialog);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(0, 90, 501, 91));
        label_2 = new QLabel(widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 10, 101, 16));
        grandtotal_2 = new QPushButton(widget);
        grandtotal_2->setObjectName(QString::fromUtf8("grandtotal_2"));
        grandtotal_2->setGeometry(QRect(50, 30, 75, 23));
        discount_2 = new QPushButton(widget);
        discount_2->setObjectName(QString::fromUtf8("discount_2"));
        discount_2->setGeometry(QRect(160, 60, 75, 23));
        tax_2 = new QPushButton(widget);
        tax_2->setObjectName(QString::fromUtf8("tax_2"));
        tax_2->setGeometry(QRect(270, 60, 75, 23));
        department_2 = new QPushButton(widget);
        department_2->setObjectName(QString::fromUtf8("department_2"));
        department_2->setGeometry(QRect(160, 30, 75, 23));
        correction_2 = new QPushButton(widget);
        correction_2->setObjectName(QString::fromUtf8("correction_2"));
        correction_2->setGeometry(QRect(50, 60, 75, 23));
        tender_2 = new QPushButton(widget);
        tender_2->setObjectName(QString::fromUtf8("tender_2"));
        tender_2->setGeometry(QRect(270, 30, 75, 23));
        drawer_2 = new QPushButton(widget);
        drawer_2->setObjectName(QString::fromUtf8("drawer_2"));
        drawer_2->setGeometry(QRect(380, 30, 75, 23));
        clerkdailywidget = new QWidget(reportDialog);
        clerkdailywidget->setObjectName(QString::fromUtf8("clerkdailywidget"));
        clerkdailywidget->setGeometry(QRect(0, 180, 501, 91));
        label_3 = new QLabel(clerkdailywidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 10, 101, 16));
        tender_3 = new QPushButton(clerkdailywidget);
        tender_3->setObjectName(QString::fromUtf8("tender_3"));
        tender_3->setGeometry(QRect(160, 30, 75, 23));
        correction_3 = new QPushButton(clerkdailywidget);
        correction_3->setObjectName(QString::fromUtf8("correction_3"));
        correction_3->setGeometry(QRect(50, 60, 75, 23));
        drawer_3 = new QPushButton(clerkdailywidget);
        drawer_3->setObjectName(QString::fromUtf8("drawer_3"));
        drawer_3->setGeometry(QRect(270, 30, 75, 23));
        discount_3 = new QPushButton(clerkdailywidget);
        discount_3->setObjectName(QString::fromUtf8("discount_3"));
        discount_3->setGeometry(QRect(160, 60, 75, 23));
        grandtotal_3 = new QPushButton(clerkdailywidget);
        grandtotal_3->setObjectName(QString::fromUtf8("grandtotal_3"));
        grandtotal_3->setGeometry(QRect(50, 30, 75, 23));
        widget_2 = new QWidget(reportDialog);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        widget_2->setGeometry(QRect(0, 270, 501, 71));
        label_4 = new QLabel(widget_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(10, 10, 101, 16));
        tender_4 = new QPushButton(widget_2);
        tender_4->setObjectName(QString::fromUtf8("tender_4"));
        tender_4->setGeometry(QRect(160, 30, 75, 23));
        correction_4 = new QPushButton(widget_2);
        correction_4->setObjectName(QString::fromUtf8("correction_4"));
        correction_4->setGeometry(QRect(270, 30, 75, 23));
        discount_4 = new QPushButton(widget_2);
        discount_4->setObjectName(QString::fromUtf8("discount_4"));
        discount_4->setGeometry(QRect(380, 30, 75, 23));
        grandtotal_4 = new QPushButton(widget_2);
        grandtotal_4->setObjectName(QString::fromUtf8("grandtotal_4"));
        grandtotal_4->setGeometry(QRect(50, 30, 75, 23));
        widget_3 = new QWidget(reportDialog);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        widget_3->setGeometry(QRect(0, 340, 501, 71));
        grandtotal_5 = new QPushButton(widget_3);
        grandtotal_5->setObjectName(QString::fromUtf8("grandtotal_5"));
        grandtotal_5->setGeometry(QRect(50, 30, 75, 23));
        label_5 = new QLabel(widget_3);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(10, 10, 101, 16));
        correction_5 = new QPushButton(widget_3);
        correction_5->setObjectName(QString::fromUtf8("correction_5"));
        correction_5->setGeometry(QRect(270, 30, 75, 23));
        tender_5 = new QPushButton(widget_3);
        tender_5->setObjectName(QString::fromUtf8("tender_5"));
        tender_5->setGeometry(QRect(160, 30, 75, 23));
        progressBar = new QProgressBar(reportDialog);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(10, 420, 501, 31));
        progressBar->setValue(0);
        cleardbreport = new QPushButton(reportDialog);
        cleardbreport->setObjectName(QString::fromUtf8("cleardbreport"));
        cleardbreport->setGeometry(QRect(520, 370, 101, 31));

        retranslateUi(reportDialog);

        QMetaObject::connectSlotsByName(reportDialog);
    } // setupUi

    void retranslateUi(QDialog *reportDialog)
    {
        reportDialog->setWindowTitle(QApplication::translate("reportDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("reportDialog", "Operation options", 0, QApplication::UnicodeUTF8));
        grandtotalbox->setText(QApplication::translate("reportDialog", "grandtotal", 0, QApplication::UnicodeUTF8));
        departmentbox->setText(QApplication::translate("reportDialog", "department", 0, QApplication::UnicodeUTF8));
        tenderbox->setText(QApplication::translate("reportDialog", "tender", 0, QApplication::UnicodeUTF8));
        drawerbox->setText(QApplication::translate("reportDialog", "drawer", 0, QApplication::UnicodeUTF8));
        correctionbox->setText(QApplication::translate("reportDialog", "correction", 0, QApplication::UnicodeUTF8));
        discountbox->setText(QApplication::translate("reportDialog", "discount", 0, QApplication::UnicodeUTF8));
        taxbox->setText(QApplication::translate("reportDialog", "tax", 0, QApplication::UnicodeUTF8));
        clearreport->setText(QApplication::translate("reportDialog", "clear report", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("reportDialog", "DOWNLOAD", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("reportDialog", "DAILY REPORT:", 0, QApplication::UnicodeUTF8));
        grandtotal->setText(QApplication::translate("reportDialog", "GRAND TOTAL", 0, QApplication::UnicodeUTF8));
        department->setText(QApplication::translate("reportDialog", "DEPARTMENT", 0, QApplication::UnicodeUTF8));
        tender->setText(QApplication::translate("reportDialog", "TENDER", 0, QApplication::UnicodeUTF8));
        drawer->setText(QApplication::translate("reportDialog", "DRAWER", 0, QApplication::UnicodeUTF8));
        discount->setText(QApplication::translate("reportDialog", "DISCOUNT", 0, QApplication::UnicodeUTF8));
        tax->setText(QApplication::translate("reportDialog", "TAX", 0, QApplication::UnicodeUTF8));
        correction->setText(QApplication::translate("reportDialog", "CORRECTION", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("reportDialog", "PERIOD REPORT:", 0, QApplication::UnicodeUTF8));
        grandtotal_2->setText(QApplication::translate("reportDialog", "GRAND TOTAL", 0, QApplication::UnicodeUTF8));
        discount_2->setText(QApplication::translate("reportDialog", "DISCOUNT", 0, QApplication::UnicodeUTF8));
        tax_2->setText(QApplication::translate("reportDialog", "TAX", 0, QApplication::UnicodeUTF8));
        department_2->setText(QApplication::translate("reportDialog", "DEPARTMENT", 0, QApplication::UnicodeUTF8));
        correction_2->setText(QApplication::translate("reportDialog", "CORRECTION", 0, QApplication::UnicodeUTF8));
        tender_2->setText(QApplication::translate("reportDialog", "TENDER", 0, QApplication::UnicodeUTF8));
        drawer_2->setText(QApplication::translate("reportDialog", "DRAWER", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("reportDialog", "CLERK DAILY:", 0, QApplication::UnicodeUTF8));
        tender_3->setText(QApplication::translate("reportDialog", "TENDER", 0, QApplication::UnicodeUTF8));
        correction_3->setText(QApplication::translate("reportDialog", "CORRECTION", 0, QApplication::UnicodeUTF8));
        drawer_3->setText(QApplication::translate("reportDialog", "DRAWER", 0, QApplication::UnicodeUTF8));
        discount_3->setText(QApplication::translate("reportDialog", "DISCOUNT", 0, QApplication::UnicodeUTF8));
        grandtotal_3->setText(QApplication::translate("reportDialog", "GRAND TOTAL", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("reportDialog", "CLERK REPORT:", 0, QApplication::UnicodeUTF8));
        tender_4->setText(QApplication::translate("reportDialog", "TENDER", 0, QApplication::UnicodeUTF8));
        correction_4->setText(QApplication::translate("reportDialog", "CORRECTION", 0, QApplication::UnicodeUTF8));
        discount_4->setText(QApplication::translate("reportDialog", "DISCOUNT", 0, QApplication::UnicodeUTF8));
        grandtotal_4->setText(QApplication::translate("reportDialog", "GRAND TOTAL", 0, QApplication::UnicodeUTF8));
        grandtotal_5->setText(QApplication::translate("reportDialog", "PERIOD PLU", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("reportDialog", "OTHER REPORT:", 0, QApplication::UnicodeUTF8));
        correction_5->setText(QApplication::translate("reportDialog", "TIME ZONE", 0, QApplication::UnicodeUTF8));
        tender_5->setText(QApplication::translate("reportDialog", "PERIOD TABLES", 0, QApplication::UnicodeUTF8));
        cleardbreport->setText(QApplication::translate("reportDialog", "CLEARREPORT", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class reportDialog: public Ui_reportDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REPORTDIALOG_H
