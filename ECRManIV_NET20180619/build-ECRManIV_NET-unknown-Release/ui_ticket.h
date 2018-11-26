/********************************************************************************
** Form generated from reading UI file 'ticket.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TICKET_H
#define UI_TICKET_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDateEdit>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QStackedWidget>
#include <QtGui/QTableView>
#include <QtGui/QTableWidget>
#include <QtGui/QTextEdit>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ticket
{
public:
    QAction *actionVoid_Need_Password;
    QAction *actionCorr_Need_Password;
    QAction *actionCancel_Need_Password;
    QAction *actionReturn_Need_Password;
    QAction *actionPercentage_Discount_Need_Password;
    QAction *actionPercentage_Addition_Need_Password;
    QAction *actionAmount_Discount_Need_Password;
    QAction *actionTrain_Clerk;
    QAction *actionFixed;
    QAction *actionFload;
    QAction *actionFixed_Float;
    QAction *actionPrint_Vat;
    QAction *actionPrint_Zero;
    QAction *actionPrint_Tax;
    QAction *actionNo_Discount;
    QAction *actionOffer_Price;
    QAction *actionDiscount;
    QAction *actionMonday;
    QAction *actionTuesday;
    QAction *actionWednesday;
    QAction *actionThursday;
    QAction *actionFriday;
    QAction *actionSaturday;
    QAction *actionSunday;
    QPushButton *download;
    QStackedWidget *stackedWidget;
    QWidget *Ticket;
    QLabel *Header;
    QTextEdit *header;
    QLabel *Trailer;
    QTextEdit *trailer;
    QWidget *Clerk;
    QTableWidget *clerkWidget;
    QWidget *Ej;
    QLabel *DateFrom;
    QLabel *DateTo;
    QDateEdit *datefrom;
    QDateEdit *dateto;
    QPushButton *ejshow;
    QStackedWidget *EJ_SW;
    QWidget *page_2;
    QTableView *tableView;
    QWidget *page_3;
    QTextEdit *EJ_TXT;
    QTableWidget *tableWidget;
    QLabel *info;
    QStackedWidget *stackedWidget_2;
    QWidget *page;
    QProgressBar *progressBar;
    QPushButton *update;
    QWidget *flowbill;
    QLabel *flowinfo;

    void setupUi(QWidget *ticket)
    {
        if (ticket->objectName().isEmpty())
            ticket->setObjectName(QString::fromUtf8("ticket"));
        ticket->resize(640, 480);
        actionVoid_Need_Password = new QAction(ticket);
        actionVoid_Need_Password->setObjectName(QString::fromUtf8("actionVoid_Need_Password"));
        actionVoid_Need_Password->setCheckable(true);
        actionCorr_Need_Password = new QAction(ticket);
        actionCorr_Need_Password->setObjectName(QString::fromUtf8("actionCorr_Need_Password"));
        actionCorr_Need_Password->setCheckable(true);
        actionCancel_Need_Password = new QAction(ticket);
        actionCancel_Need_Password->setObjectName(QString::fromUtf8("actionCancel_Need_Password"));
        actionCancel_Need_Password->setCheckable(true);
        actionReturn_Need_Password = new QAction(ticket);
        actionReturn_Need_Password->setObjectName(QString::fromUtf8("actionReturn_Need_Password"));
        actionReturn_Need_Password->setCheckable(true);
        actionPercentage_Discount_Need_Password = new QAction(ticket);
        actionPercentage_Discount_Need_Password->setObjectName(QString::fromUtf8("actionPercentage_Discount_Need_Password"));
        actionPercentage_Discount_Need_Password->setCheckable(true);
        actionPercentage_Addition_Need_Password = new QAction(ticket);
        actionPercentage_Addition_Need_Password->setObjectName(QString::fromUtf8("actionPercentage_Addition_Need_Password"));
        actionPercentage_Addition_Need_Password->setCheckable(true);
        actionAmount_Discount_Need_Password = new QAction(ticket);
        actionAmount_Discount_Need_Password->setObjectName(QString::fromUtf8("actionAmount_Discount_Need_Password"));
        actionAmount_Discount_Need_Password->setCheckable(true);
        actionTrain_Clerk = new QAction(ticket);
        actionTrain_Clerk->setObjectName(QString::fromUtf8("actionTrain_Clerk"));
        actionTrain_Clerk->setCheckable(true);
        actionFixed = new QAction(ticket);
        actionFixed->setObjectName(QString::fromUtf8("actionFixed"));
        actionFixed->setCheckable(true);
        actionFload = new QAction(ticket);
        actionFload->setObjectName(QString::fromUtf8("actionFload"));
        actionFload->setCheckable(true);
        actionFixed_Float = new QAction(ticket);
        actionFixed_Float->setObjectName(QString::fromUtf8("actionFixed_Float"));
        actionFixed_Float->setCheckable(true);
        actionPrint_Vat = new QAction(ticket);
        actionPrint_Vat->setObjectName(QString::fromUtf8("actionPrint_Vat"));
        actionPrint_Vat->setCheckable(true);
        actionPrint_Zero = new QAction(ticket);
        actionPrint_Zero->setObjectName(QString::fromUtf8("actionPrint_Zero"));
        actionPrint_Zero->setCheckable(true);
        actionPrint_Tax = new QAction(ticket);
        actionPrint_Tax->setObjectName(QString::fromUtf8("actionPrint_Tax"));
        actionPrint_Tax->setCheckable(true);
        actionNo_Discount = new QAction(ticket);
        actionNo_Discount->setObjectName(QString::fromUtf8("actionNo_Discount"));
        actionNo_Discount->setCheckable(true);
        actionOffer_Price = new QAction(ticket);
        actionOffer_Price->setObjectName(QString::fromUtf8("actionOffer_Price"));
        actionOffer_Price->setCheckable(true);
        actionDiscount = new QAction(ticket);
        actionDiscount->setObjectName(QString::fromUtf8("actionDiscount"));
        actionDiscount->setCheckable(true);
        actionMonday = new QAction(ticket);
        actionMonday->setObjectName(QString::fromUtf8("actionMonday"));
        actionMonday->setCheckable(true);
        actionTuesday = new QAction(ticket);
        actionTuesday->setObjectName(QString::fromUtf8("actionTuesday"));
        actionTuesday->setCheckable(true);
        actionWednesday = new QAction(ticket);
        actionWednesday->setObjectName(QString::fromUtf8("actionWednesday"));
        actionWednesday->setCheckable(true);
        actionThursday = new QAction(ticket);
        actionThursday->setObjectName(QString::fromUtf8("actionThursday"));
        actionThursday->setCheckable(true);
        actionFriday = new QAction(ticket);
        actionFriday->setObjectName(QString::fromUtf8("actionFriday"));
        actionFriday->setCheckable(true);
        actionSaturday = new QAction(ticket);
        actionSaturday->setObjectName(QString::fromUtf8("actionSaturday"));
        actionSaturday->setCheckable(true);
        actionSunday = new QAction(ticket);
        actionSunday->setObjectName(QString::fromUtf8("actionSunday"));
        actionSunday->setCheckable(true);
        download = new QPushButton(ticket);
        download->setObjectName(QString::fromUtf8("download"));
        download->setGeometry(QRect(530, 420, 91, 31));
        stackedWidget = new QStackedWidget(ticket);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setGeometry(QRect(0, 0, 471, 411));
        Ticket = new QWidget();
        Ticket->setObjectName(QString::fromUtf8("Ticket"));
        Header = new QLabel(Ticket);
        Header->setObjectName(QString::fromUtf8("Header"));
        Header->setGeometry(QRect(100, 10, 61, 21));
        header = new QTextEdit(Ticket);
        header->setObjectName(QString::fromUtf8("header"));
        header->setGeometry(QRect(10, 40, 221, 371));
        Trailer = new QLabel(Ticket);
        Trailer->setObjectName(QString::fromUtf8("Trailer"));
        Trailer->setGeometry(QRect(320, 10, 61, 21));
        trailer = new QTextEdit(Ticket);
        trailer->setObjectName(QString::fromUtf8("trailer"));
        trailer->setGeometry(QRect(240, 40, 221, 371));
        stackedWidget->addWidget(Ticket);
        Clerk = new QWidget();
        Clerk->setObjectName(QString::fromUtf8("Clerk"));
        clerkWidget = new QTableWidget(Clerk);
        clerkWidget->setObjectName(QString::fromUtf8("clerkWidget"));
        clerkWidget->setGeometry(QRect(10, 10, 451, 401));
        stackedWidget->addWidget(Clerk);
        Ej = new QWidget();
        Ej->setObjectName(QString::fromUtf8("Ej"));
        DateFrom = new QLabel(Ej);
        DateFrom->setObjectName(QString::fromUtf8("DateFrom"));
        DateFrom->setGeometry(QRect(20, 10, 71, 21));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        DateFrom->setFont(font);
        DateFrom->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        DateTo = new QLabel(Ej);
        DateTo->setObjectName(QString::fromUtf8("DateTo"));
        DateTo->setGeometry(QRect(210, 10, 61, 21));
        DateTo->setFont(font);
        DateTo->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        datefrom = new QDateEdit(Ej);
        datefrom->setObjectName(QString::fromUtf8("datefrom"));
        datefrom->setGeometry(QRect(100, 10, 101, 22));
        datefrom->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        datefrom->setCalendarPopup(true);
        dateto = new QDateEdit(Ej);
        dateto->setObjectName(QString::fromUtf8("dateto"));
        dateto->setGeometry(QRect(280, 10, 101, 22));
        dateto->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        dateto->setCalendarPopup(true);
        ejshow = new QPushButton(Ej);
        ejshow->setObjectName(QString::fromUtf8("ejshow"));
        ejshow->setGeometry(QRect(400, 10, 71, 23));
        EJ_SW = new QStackedWidget(Ej);
        EJ_SW->setObjectName(QString::fromUtf8("EJ_SW"));
        EJ_SW->setGeometry(QRect(10, 40, 461, 371));
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        tableView = new QTableView(page_2);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setGeometry(QRect(0, 0, 461, 371));
        tableView->horizontalHeader()->setCascadingSectionResizes(false);
        tableView->horizontalHeader()->setDefaultSectionSize(200);
        tableView->horizontalHeader()->setMinimumSectionSize(100);
        tableView->horizontalHeader()->setStretchLastSection(false);
        EJ_SW->addWidget(page_2);
        page_3 = new QWidget();
        page_3->setObjectName(QString::fromUtf8("page_3"));
        EJ_TXT = new QTextEdit(page_3);
        EJ_TXT->setObjectName(QString::fromUtf8("EJ_TXT"));
        EJ_TXT->setGeometry(QRect(0, 0, 461, 371));
        EJ_SW->addWidget(page_3);
        stackedWidget->addWidget(Ej);
        tableWidget = new QTableWidget(ticket);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setGeometry(QRect(490, 10, 141, 401));
        info = new QLabel(ticket);
        info->setObjectName(QString::fromUtf8("info"));
        info->setGeometry(QRect(20, 460, 391, 16));
        stackedWidget_2 = new QStackedWidget(ticket);
        stackedWidget_2->setObjectName(QString::fromUtf8("stackedWidget_2"));
        stackedWidget_2->setGeometry(QRect(10, 420, 511, 80));
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        progressBar = new QProgressBar(page);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(10, 0, 391, 31));
        progressBar->setValue(0);
        update = new QPushButton(page);
        update->setObjectName(QString::fromUtf8("update"));
        update->setGeometry(QRect(410, 0, 91, 31));
        stackedWidget_2->addWidget(page);
        flowbill = new QWidget();
        flowbill->setObjectName(QString::fromUtf8("flowbill"));
        flowinfo = new QLabel(flowbill);
        flowinfo->setObjectName(QString::fromUtf8("flowinfo"));
        flowinfo->setGeometry(QRect(10, 0, 441, 31));
        stackedWidget_2->addWidget(flowbill);

        retranslateUi(ticket);

        QMetaObject::connectSlotsByName(ticket);
    } // setupUi

    void retranslateUi(QWidget *ticket)
    {
        ticket->setWindowTitle(QApplication::translate("ticket", "Form", 0, QApplication::UnicodeUTF8));
        actionVoid_Need_Password->setText(QApplication::translate("ticket", "Void Need Password", 0, QApplication::UnicodeUTF8));
        actionCorr_Need_Password->setText(QApplication::translate("ticket", "Corr Need Password", 0, QApplication::UnicodeUTF8));
        actionCancel_Need_Password->setText(QApplication::translate("ticket", "Cancel Need Password", 0, QApplication::UnicodeUTF8));
        actionReturn_Need_Password->setText(QApplication::translate("ticket", "Return Need Password", 0, QApplication::UnicodeUTF8));
        actionPercentage_Discount_Need_Password->setText(QApplication::translate("ticket", "Percentage Discount Need Password", 0, QApplication::UnicodeUTF8));
        actionPercentage_Addition_Need_Password->setText(QApplication::translate("ticket", "Percentage Addition Need Password", 0, QApplication::UnicodeUTF8));
        actionAmount_Discount_Need_Password->setText(QApplication::translate("ticket", "Amount Discount Need Password", 0, QApplication::UnicodeUTF8));
        actionTrain_Clerk->setText(QApplication::translate("ticket", "Train Clerk", 0, QApplication::UnicodeUTF8));
        actionFixed->setText(QApplication::translate("ticket", "Fixed", 0, QApplication::UnicodeUTF8));
        actionFload->setText(QApplication::translate("ticket", "Float", 0, QApplication::UnicodeUTF8));
        actionFixed_Float->setText(QApplication::translate("ticket", "Fixed/Float", 0, QApplication::UnicodeUTF8));
        actionPrint_Vat->setText(QApplication::translate("ticket", "Print Vat", 0, QApplication::UnicodeUTF8));
        actionPrint_Zero->setText(QApplication::translate("ticket", "Print Zero", 0, QApplication::UnicodeUTF8));
        actionPrint_Tax->setText(QApplication::translate("ticket", "Print Tax", 0, QApplication::UnicodeUTF8));
        actionNo_Discount->setText(QApplication::translate("ticket", "No Discount", 0, QApplication::UnicodeUTF8));
        actionOffer_Price->setText(QApplication::translate("ticket", "Offer Price", 0, QApplication::UnicodeUTF8));
        actionDiscount->setText(QApplication::translate("ticket", "Discount", 0, QApplication::UnicodeUTF8));
        actionMonday->setText(QApplication::translate("ticket", "Monday", 0, QApplication::UnicodeUTF8));
        actionTuesday->setText(QApplication::translate("ticket", "Tuesday", 0, QApplication::UnicodeUTF8));
        actionWednesday->setText(QApplication::translate("ticket", "Wednesday", 0, QApplication::UnicodeUTF8));
        actionThursday->setText(QApplication::translate("ticket", "Thursday", 0, QApplication::UnicodeUTF8));
        actionFriday->setText(QApplication::translate("ticket", "Friday", 0, QApplication::UnicodeUTF8));
        actionSaturday->setText(QApplication::translate("ticket", "Saturday", 0, QApplication::UnicodeUTF8));
        actionSunday->setText(QApplication::translate("ticket", "Sunday", 0, QApplication::UnicodeUTF8));
        download->setText(QApplication::translate("ticket", "DOWNLOAD", 0, QApplication::UnicodeUTF8));
        Header->setText(QApplication::translate("ticket", "HEADER:", 0, QApplication::UnicodeUTF8));
        Trailer->setText(QApplication::translate("ticket", "TRAILER:", 0, QApplication::UnicodeUTF8));
        DateFrom->setText(QApplication::translate("ticket", "Date From:", 0, QApplication::UnicodeUTF8));
        DateTo->setText(QApplication::translate("ticket", "Date To:", 0, QApplication::UnicodeUTF8));
        ejshow->setText(QApplication::translate("ticket", "show", 0, QApplication::UnicodeUTF8));
        info->setText(QString());
        update->setText(QApplication::translate("ticket", "UPDATE", 0, QApplication::UnicodeUTF8));
        flowinfo->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ticket: public Ui_ticket {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TICKET_H
