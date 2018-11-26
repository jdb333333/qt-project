/********************************************************************************
** Form generated from reading UI file 'logindialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINDIALOG_H
#define UI_LOGINDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_LoginDialog
{
public:
    QLabel *user;
    QLabel *pwd;
    QPushButton *login;
    QPushButton *exit;
    QLineEdit *pwdedit;
    QLineEdit *usredit;

    void setupUi(QDialog *LoginDialog)
    {
        if (LoginDialog->objectName().isEmpty())
            LoginDialog->setObjectName(QString::fromUtf8("LoginDialog"));
        LoginDialog->resize(320, 210);
        user = new QLabel(LoginDialog);
        user->setObjectName(QString::fromUtf8("user"));
        user->setGeometry(QRect(20, 20, 111, 51));
        QFont font;
        font.setPointSize(15);
        font.setBold(true);
        font.setWeight(75);
        user->setFont(font);
        pwd = new QLabel(LoginDialog);
        pwd->setObjectName(QString::fromUtf8("pwd"));
        pwd->setGeometry(QRect(20, 80, 101, 41));
        pwd->setFont(font);
        login = new QPushButton(LoginDialog);
        login->setObjectName(QString::fromUtf8("login"));
        login->setGeometry(QRect(40, 160, 91, 31));
        QFont font1;
        font1.setPointSize(12);
        font1.setBold(true);
        font1.setWeight(75);
        login->setFont(font1);
        exit = new QPushButton(LoginDialog);
        exit->setObjectName(QString::fromUtf8("exit"));
        exit->setGeometry(QRect(190, 160, 91, 31));
        exit->setFont(font1);
        pwdedit = new QLineEdit(LoginDialog);
        pwdedit->setObjectName(QString::fromUtf8("pwdedit"));
        pwdedit->setGeometry(QRect(130, 90, 171, 31));
        pwdedit->setEchoMode(QLineEdit::Password);
        usredit = new QLineEdit(LoginDialog);
        usredit->setObjectName(QString::fromUtf8("usredit"));
        usredit->setGeometry(QRect(130, 30, 171, 31));

        retranslateUi(LoginDialog);
        QObject::connect(exit, SIGNAL(clicked()), LoginDialog, SLOT(close()));

        QMetaObject::connectSlotsByName(LoginDialog);
    } // setupUi

    void retranslateUi(QDialog *LoginDialog)
    {
        LoginDialog->setWindowTitle(QApplication::translate("LoginDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        user->setText(QApplication::translate("LoginDialog", "username:", 0, QApplication::UnicodeUTF8));
        pwd->setText(QApplication::translate("LoginDialog", "password:", 0, QApplication::UnicodeUTF8));
        login->setText(QApplication::translate("LoginDialog", "Login", 0, QApplication::UnicodeUTF8));
        exit->setText(QApplication::translate("LoginDialog", "Exit", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class LoginDialog: public Ui_LoginDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINDIALOG_H
