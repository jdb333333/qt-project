/********************************************************************************
** Form generated from reading UI file 'ecrmaniv_net.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ECRMANIV_NET_H
#define UI_ECRMANIV_NET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QStackedWidget>
#include <QtGui/QTableWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ECRManIV_NET
{
public:
    QAction *actionADD;
    QAction *actionDELETE;
    QAction *actionLOCAL;
    QStackedWidget *stackedWidget;
    QWidget *menu;
    QPushButton *clerk;
    QPushButton *dept;
    QPushButton *plu;
    QPushButton *disc;
    QPushButton *zport;
    QLabel *label_clerk;
    QLabel *label_dept;
    QLabel *label_plu;
    QLabel *label_disc;
    QLabel *label_report;
    QPushButton *tax;
    QLabel *label_tax;
    QPushButton *ticket;
    QLabel *label_ticket;
    QPushButton *system;
    QLabel *label_offer;
    QPushButton *usrmng;
    QLabel *label_usrmng;
    QLabel *label_flowbill;
    QPushButton *flowbill;
    QLabel *label_update;
    QPushButton *update;
    QTableWidget *tableWidget_2;
    QPushButton *pushButton;

    void setupUi(QWidget *ECRManIV_NET)
    {
        if (ECRManIV_NET->objectName().isEmpty())
            ECRManIV_NET->setObjectName(QString::fromUtf8("ECRManIV_NET"));
        ECRManIV_NET->resize(800, 600);
        actionADD = new QAction(ECRManIV_NET);
        actionADD->setObjectName(QString::fromUtf8("actionADD"));
        actionADD->setCheckable(false);
        actionADD->setEnabled(true);
        actionDELETE = new QAction(ECRManIV_NET);
        actionDELETE->setObjectName(QString::fromUtf8("actionDELETE"));
        actionLOCAL = new QAction(ECRManIV_NET);
        actionLOCAL->setObjectName(QString::fromUtf8("actionLOCAL"));
        stackedWidget = new QStackedWidget(ECRManIV_NET);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setGeometry(QRect(200, 0, 601, 601));
        stackedWidget->setStyleSheet(QString::fromUtf8(""));
        menu = new QWidget();
        menu->setObjectName(QString::fromUtf8("menu"));
        clerk = new QPushButton(menu);
        clerk->setObjectName(QString::fromUtf8("clerk"));
        clerk->setGeometry(QRect(50, 70, 60, 60));
        clerk->setStyleSheet(QString::fromUtf8("border-image: url(:/images/icons/clerk.png);"));
        clerk->setIconSize(QSize(48, 48));
        dept = new QPushButton(menu);
        dept->setObjectName(QString::fromUtf8("dept"));
        dept->setGeometry(QRect(190, 70, 60, 60));
        dept->setStyleSheet(QString::fromUtf8("border-image: url(:/images/icons/dept.png);"));
        plu = new QPushButton(menu);
        plu->setObjectName(QString::fromUtf8("plu"));
        plu->setGeometry(QRect(330, 70, 60, 60));
        plu->setStyleSheet(QString::fromUtf8("border-image: url(:/images/icons/plu.png);"));
        disc = new QPushButton(menu);
        disc->setObjectName(QString::fromUtf8("disc"));
        disc->setGeometry(QRect(470, 70, 60, 60));
        disc->setStyleSheet(QString::fromUtf8("border-image: url(:/images/icons/disc.png);"));
        zport = new QPushButton(menu);
        zport->setObjectName(QString::fromUtf8("zport"));
        zport->setGeometry(QRect(50, 390, 60, 60));
        zport->setStyleSheet(QString::fromUtf8("border-image: url(:/images/icons/print.png);"));
        label_clerk = new QLabel(menu);
        label_clerk->setObjectName(QString::fromUtf8("label_clerk"));
        label_clerk->setGeometry(QRect(50, 140, 61, 21));
        label_clerk->setLayoutDirection(Qt::LeftToRight);
        label_clerk->setAlignment(Qt::AlignCenter);
        label_clerk->setWordWrap(false);
        label_dept = new QLabel(menu);
        label_dept->setObjectName(QString::fromUtf8("label_dept"));
        label_dept->setGeometry(QRect(190, 140, 61, 21));
        label_dept->setLayoutDirection(Qt::LeftToRight);
        label_dept->setAlignment(Qt::AlignCenter);
        label_dept->setWordWrap(false);
        label_plu = new QLabel(menu);
        label_plu->setObjectName(QString::fromUtf8("label_plu"));
        label_plu->setGeometry(QRect(330, 140, 61, 21));
        label_plu->setLayoutDirection(Qt::LeftToRight);
        label_plu->setAlignment(Qt::AlignCenter);
        label_plu->setWordWrap(false);
        label_disc = new QLabel(menu);
        label_disc->setObjectName(QString::fromUtf8("label_disc"));
        label_disc->setGeometry(QRect(470, 140, 61, 21));
        label_disc->setLayoutDirection(Qt::LeftToRight);
        label_disc->setAlignment(Qt::AlignCenter);
        label_disc->setWordWrap(false);
        label_report = new QLabel(menu);
        label_report->setObjectName(QString::fromUtf8("label_report"));
        label_report->setGeometry(QRect(50, 460, 61, 21));
        label_report->setLayoutDirection(Qt::LeftToRight);
        label_report->setAlignment(Qt::AlignCenter);
        label_report->setWordWrap(false);
        tax = new QPushButton(menu);
        tax->setObjectName(QString::fromUtf8("tax"));
        tax->setGeometry(QRect(50, 230, 60, 60));
        tax->setStyleSheet(QString::fromUtf8("border-image: url(:/images/icons/tax.png);"));
        label_tax = new QLabel(menu);
        label_tax->setObjectName(QString::fromUtf8("label_tax"));
        label_tax->setGeometry(QRect(50, 300, 61, 21));
        label_tax->setLayoutDirection(Qt::LeftToRight);
        label_tax->setAlignment(Qt::AlignCenter);
        label_tax->setWordWrap(false);
        ticket = new QPushButton(menu);
        ticket->setObjectName(QString::fromUtf8("ticket"));
        ticket->setGeometry(QRect(190, 230, 60, 60));
        ticket->setStyleSheet(QString::fromUtf8("border-image: url(:/images/icons/tailer.png);"));
        label_ticket = new QLabel(menu);
        label_ticket->setObjectName(QString::fromUtf8("label_ticket"));
        label_ticket->setGeometry(QRect(190, 300, 61, 21));
        label_ticket->setLayoutDirection(Qt::LeftToRight);
        label_ticket->setAlignment(Qt::AlignCenter);
        label_ticket->setWordWrap(false);
        system = new QPushButton(menu);
        system->setObjectName(QString::fromUtf8("system"));
        system->setGeometry(QRect(330, 230, 60, 60));
        system->setStyleSheet(QString::fromUtf8("border-image: url(:/images/icons/totalRep.png);"));
        label_offer = new QLabel(menu);
        label_offer->setObjectName(QString::fromUtf8("label_offer"));
        label_offer->setGeometry(QRect(330, 300, 61, 21));
        label_offer->setLayoutDirection(Qt::LeftToRight);
        label_offer->setAlignment(Qt::AlignCenter);
        label_offer->setWordWrap(false);
        usrmng = new QPushButton(menu);
        usrmng->setObjectName(QString::fromUtf8("usrmng"));
        usrmng->setGeometry(QRect(190, 390, 60, 60));
        usrmng->setStyleSheet(QString::fromUtf8("border-image: url(:/images/icons/usrmng.png);"));
        label_usrmng = new QLabel(menu);
        label_usrmng->setObjectName(QString::fromUtf8("label_usrmng"));
        label_usrmng->setGeometry(QRect(190, 460, 61, 21));
        label_usrmng->setLayoutDirection(Qt::LeftToRight);
        label_usrmng->setAlignment(Qt::AlignCenter);
        label_usrmng->setWordWrap(false);
        label_flowbill = new QLabel(menu);
        label_flowbill->setObjectName(QString::fromUtf8("label_flowbill"));
        label_flowbill->setGeometry(QRect(470, 300, 61, 21));
        label_flowbill->setLayoutDirection(Qt::LeftToRight);
        label_flowbill->setAlignment(Qt::AlignCenter);
        label_flowbill->setWordWrap(false);
        flowbill = new QPushButton(menu);
        flowbill->setObjectName(QString::fromUtf8("flowbill"));
        flowbill->setGeometry(QRect(470, 230, 60, 60));
        flowbill->setStyleSheet(QString::fromUtf8("border-image: url(:/images/icons/flowbill.png);"));
        label_update = new QLabel(menu);
        label_update->setObjectName(QString::fromUtf8("label_update"));
        label_update->setGeometry(QRect(330, 460, 61, 21));
        label_update->setLayoutDirection(Qt::LeftToRight);
        label_update->setAlignment(Qt::AlignCenter);
        label_update->setWordWrap(false);
        update = new QPushButton(menu);
        update->setObjectName(QString::fromUtf8("update"));
        update->setEnabled(true);
        update->setGeometry(QRect(330, 390, 60, 60));
        update->setStyleSheet(QString::fromUtf8("border-image: url(:/images/icons/update.png);"));
        stackedWidget->addWidget(menu);
        tableWidget_2 = new QTableWidget(ECRManIV_NET);
        if (tableWidget_2->columnCount() < 2)
            tableWidget_2->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidget_2->setObjectName(QString::fromUtf8("tableWidget_2"));
        tableWidget_2->setGeometry(QRect(0, 0, 181, 571));
        tableWidget_2->setMinimumSize(QSize(0, 0));
        tableWidget_2->horizontalHeader()->setMinimumSectionSize(90);
        pushButton = new QPushButton(ECRManIV_NET);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(0, 570, 181, 31));

        retranslateUi(ECRManIV_NET);

        QMetaObject::connectSlotsByName(ECRManIV_NET);
    } // setupUi

    void retranslateUi(QWidget *ECRManIV_NET)
    {
        ECRManIV_NET->setWindowTitle(QApplication::translate("ECRManIV_NET", "ECRManIV_NET", 0, QApplication::UnicodeUTF8));
        actionADD->setText(QApplication::translate("ECRManIV_NET", "ADD", 0, QApplication::UnicodeUTF8));
        actionDELETE->setText(QApplication::translate("ECRManIV_NET", "DELETE", 0, QApplication::UnicodeUTF8));
        actionLOCAL->setText(QApplication::translate("ECRManIV_NET", "set local ip", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionLOCAL->setToolTip(QApplication::translate("ECRManIV_NET", "LOCAL", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        clerk->setText(QString());
        dept->setText(QString());
        plu->setText(QString());
        disc->setText(QString());
        zport->setText(QString());
        label_clerk->setText(QApplication::translate("ECRManIV_NET", "CLERK", 0, QApplication::UnicodeUTF8));
        label_dept->setText(QApplication::translate("ECRManIV_NET", "DEPT", 0, QApplication::UnicodeUTF8));
        label_plu->setText(QApplication::translate("ECRManIV_NET", "PLU", 0, QApplication::UnicodeUTF8));
        label_disc->setText(QApplication::translate("ECRManIV_NET", "DISC", 0, QApplication::UnicodeUTF8));
        label_report->setText(QApplication::translate("ECRManIV_NET", "REPORT", 0, QApplication::UnicodeUTF8));
        tax->setText(QString());
        label_tax->setText(QApplication::translate("ECRManIV_NET", "TAX", 0, QApplication::UnicodeUTF8));
        ticket->setText(QString());
        label_ticket->setText(QApplication::translate("ECRManIV_NET", "TICKET", 0, QApplication::UnicodeUTF8));
        system->setText(QString());
        label_offer->setText(QApplication::translate("ECRManIV_NET", "OFFER", 0, QApplication::UnicodeUTF8));
        usrmng->setText(QString());
        label_usrmng->setText(QApplication::translate("ECRManIV_NET", "USRMNG", 0, QApplication::UnicodeUTF8));
        label_flowbill->setText(QApplication::translate("ECRManIV_NET", "EJ", 0, QApplication::UnicodeUTF8));
        flowbill->setText(QString());
        label_update->setText(QApplication::translate("ECRManIV_NET", "UPDATE", 0, QApplication::UnicodeUTF8));
        update->setText(QString());
        QTableWidgetItem *___qtablewidgetitem = tableWidget_2->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("ECRManIV_NET", "register", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget_2->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("ECRManIV_NET", "ip", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("ECRManIV_NET", "Search IP", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ECRManIV_NET: public Ui_ECRManIV_NET {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ECRMANIV_NET_H
