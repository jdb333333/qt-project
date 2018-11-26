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
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QPushButton *tax;
    QLabel *tax_2;
    QPushButton *group;
    QLabel *group_2;
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
        clerk->setGeometry(QRect(60, 50, 100, 100));
        clerk->setStyleSheet(QString::fromUtf8("border-image: url(:/images/icons/clerk.png);"));
        clerk->setIconSize(QSize(48, 48));
        dept = new QPushButton(menu);
        dept->setObjectName(QString::fromUtf8("dept"));
        dept->setGeometry(QRect(420, 50, 100, 100));
        dept->setStyleSheet(QString::fromUtf8("border-image: url(:/images/icons/dept.png);"));
        plu = new QPushButton(menu);
        plu->setObjectName(QString::fromUtf8("plu"));
        plu->setGeometry(QRect(60, 240, 100, 100));
        plu->setStyleSheet(QString::fromUtf8("border-image: url(:/images/icons/plu.png);"));
        disc = new QPushButton(menu);
        disc->setObjectName(QString::fromUtf8("disc"));
        disc->setGeometry(QRect(240, 240, 100, 100));
        disc->setStyleSheet(QString::fromUtf8("border-image: url(:/images/icons/disc.png);"));
        zport = new QPushButton(menu);
        zport->setObjectName(QString::fromUtf8("zport"));
        zport->setGeometry(QRect(420, 430, 100, 100));
        zport->setStyleSheet(QString::fromUtf8("border-image: url(:/images/icons/print.png);"));
        label = new QLabel(menu);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(80, 160, 61, 21));
        label->setLayoutDirection(Qt::LeftToRight);
        label->setAlignment(Qt::AlignCenter);
        label->setWordWrap(false);
        label_2 = new QLabel(menu);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(440, 160, 61, 21));
        label_2->setLayoutDirection(Qt::LeftToRight);
        label_2->setAlignment(Qt::AlignCenter);
        label_2->setWordWrap(false);
        label_3 = new QLabel(menu);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(80, 350, 61, 21));
        label_3->setLayoutDirection(Qt::LeftToRight);
        label_3->setAlignment(Qt::AlignCenter);
        label_3->setWordWrap(false);
        label_4 = new QLabel(menu);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(260, 350, 61, 21));
        label_4->setLayoutDirection(Qt::LeftToRight);
        label_4->setAlignment(Qt::AlignCenter);
        label_4->setWordWrap(false);
        label_5 = new QLabel(menu);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(440, 540, 61, 21));
        label_5->setLayoutDirection(Qt::LeftToRight);
        label_5->setAlignment(Qt::AlignCenter);
        label_5->setWordWrap(false);
        tax = new QPushButton(menu);
        tax->setObjectName(QString::fromUtf8("tax"));
        tax->setGeometry(QRect(420, 240, 100, 100));
        tax->setStyleSheet(QString::fromUtf8("border-image: url(:/images/icons/tax.png);"));
        tax_2 = new QLabel(menu);
        tax_2->setObjectName(QString::fromUtf8("tax_2"));
        tax_2->setGeometry(QRect(440, 350, 61, 21));
        tax_2->setLayoutDirection(Qt::LeftToRight);
        tax_2->setAlignment(Qt::AlignCenter);
        tax_2->setWordWrap(false);
        group = new QPushButton(menu);
        group->setObjectName(QString::fromUtf8("group"));
        group->setGeometry(QRect(240, 50, 100, 100));
        group->setStyleSheet(QString::fromUtf8("border-image: url(:/images/icons/group.png);"));
        group_2 = new QLabel(menu);
        group_2->setObjectName(QString::fromUtf8("group_2"));
        group_2->setGeometry(QRect(260, 160, 61, 21));
        group_2->setLayoutDirection(Qt::LeftToRight);
        group_2->setAlignment(Qt::AlignCenter);
        group_2->setWordWrap(false);
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
        label->setText(QApplication::translate("ECRManIV_NET", "CLERK", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("ECRManIV_NET", "DEPT", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("ECRManIV_NET", "PLU", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("ECRManIV_NET", "DISC", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("ECRManIV_NET", "REPORT", 0, QApplication::UnicodeUTF8));
        tax->setText(QString());
        tax_2->setText(QApplication::translate("ECRManIV_NET", "TAX", 0, QApplication::UnicodeUTF8));
        group->setText(QString());
        group_2->setText(QApplication::translate("ECRManIV_NET", "GROUP", 0, QApplication::UnicodeUTF8));
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
