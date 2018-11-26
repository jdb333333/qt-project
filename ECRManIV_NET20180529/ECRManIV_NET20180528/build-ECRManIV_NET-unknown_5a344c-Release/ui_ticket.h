/********************************************************************************
** Form generated from reading UI file 'ticket.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TICKET_H
#define UI_TICKET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QTextEdit>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ticket
{
public:
    QTextEdit *header;
    QLabel *Header;
    QTextEdit *trailer;
    QLabel *Trailer;
    QPushButton *update;
    QPushButton *download;
    QProgressBar *progressBar;

    void setupUi(QWidget *ticket)
    {
        if (ticket->objectName().isEmpty())
            ticket->setObjectName(QString::fromUtf8("ticket"));
        ticket->resize(640, 480);
        header = new QTextEdit(ticket);
        header->setObjectName(QString::fromUtf8("header"));
        header->setGeometry(QRect(20, 40, 281, 361));
        Header = new QLabel(ticket);
        Header->setObjectName(QString::fromUtf8("Header"));
        Header->setGeometry(QRect(130, 10, 61, 21));
        trailer = new QTextEdit(ticket);
        trailer->setObjectName(QString::fromUtf8("trailer"));
        trailer->setGeometry(QRect(340, 40, 281, 361));
        Trailer = new QLabel(ticket);
        Trailer->setObjectName(QString::fromUtf8("Trailer"));
        Trailer->setGeometry(QRect(470, 10, 61, 21));
        update = new QPushButton(ticket);
        update->setObjectName(QString::fromUtf8("update"));
        update->setGeometry(QRect(420, 430, 91, 31));
        download = new QPushButton(ticket);
        download->setObjectName(QString::fromUtf8("download"));
        download->setGeometry(QRect(530, 430, 91, 31));
        progressBar = new QProgressBar(ticket);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(20, 430, 391, 31));
        progressBar->setValue(0);

        retranslateUi(ticket);

        QMetaObject::connectSlotsByName(ticket);
    } // setupUi

    void retranslateUi(QWidget *ticket)
    {
        ticket->setWindowTitle(QApplication::translate("ticket", "Form", 0, QApplication::UnicodeUTF8));
        Header->setText(QApplication::translate("ticket", "HEADER:", 0, QApplication::UnicodeUTF8));
        Trailer->setText(QApplication::translate("ticket", "TRAILER:", 0, QApplication::UnicodeUTF8));
        update->setText(QApplication::translate("ticket", "UPDATE", 0, QApplication::UnicodeUTF8));
        download->setText(QApplication::translate("ticket", "DOWNLOAD", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ticket: public Ui_ticket {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TICKET_H
