/********************************************************************************
** Form generated from reading UI file 'usrmoddialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USRMODDIALOG_H
#define UI_USRMODDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QStackedWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UsrModDialog
{
public:
    QStackedWidget *stackedWidget;
    QWidget *AddUser;
    QLineEdit *Password2edit;
    QLabel *Password1;
    QLabel *UserName;
    QLineEdit *Password1edit;
    QLabel *Password2;
    QLineEdit *usernameedit;
    QWidget *ModPwd;
    QLabel *NewPwd1;
    QLabel *OldPwd;
    QLineEdit *NewPwd1edit;
    QLineEdit *NewPwd2edit;
    QLabel *NewPwd2;
    QLineEdit *OldPwdedit;
    QLineEdit *NewNameEdit;
    QLabel *NewName;
    QPushButton *okbtn;
    QPushButton *exitbtn;

    void setupUi(QDialog *UsrModDialog)
    {
        if (UsrModDialog->objectName().isEmpty())
            UsrModDialog->setObjectName(QString::fromUtf8("UsrModDialog"));
        UsrModDialog->resize(250, 177);
        stackedWidget = new QStackedWidget(UsrModDialog);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setGeometry(QRect(20, 10, 211, 131));
        AddUser = new QWidget();
        AddUser->setObjectName(QString::fromUtf8("AddUser"));
        Password2edit = new QLineEdit(AddUser);
        Password2edit->setObjectName(QString::fromUtf8("Password2edit"));
        Password2edit->setGeometry(QRect(80, 80, 113, 20));
        Password2edit->setEchoMode(QLineEdit::Password);
        Password1 = new QLabel(AddUser);
        Password1->setObjectName(QString::fromUtf8("Password1"));
        Password1->setGeometry(QRect(10, 50, 54, 21));
        UserName = new QLabel(AddUser);
        UserName->setObjectName(QString::fromUtf8("UserName"));
        UserName->setGeometry(QRect(10, 20, 54, 21));
        Password1edit = new QLineEdit(AddUser);
        Password1edit->setObjectName(QString::fromUtf8("Password1edit"));
        Password1edit->setGeometry(QRect(80, 50, 113, 20));
        Password1edit->setEchoMode(QLineEdit::Password);
        Password2 = new QLabel(AddUser);
        Password2->setObjectName(QString::fromUtf8("Password2"));
        Password2->setGeometry(QRect(10, 80, 54, 21));
        usernameedit = new QLineEdit(AddUser);
        usernameedit->setObjectName(QString::fromUtf8("usernameedit"));
        usernameedit->setGeometry(QRect(80, 20, 113, 20));
        stackedWidget->addWidget(AddUser);
        ModPwd = new QWidget();
        ModPwd->setObjectName(QString::fromUtf8("ModPwd"));
        NewPwd1 = new QLabel(ModPwd);
        NewPwd1->setObjectName(QString::fromUtf8("NewPwd1"));
        NewPwd1->setGeometry(QRect(20, 70, 54, 21));
        OldPwd = new QLabel(ModPwd);
        OldPwd->setObjectName(QString::fromUtf8("OldPwd"));
        OldPwd->setGeometry(QRect(20, 40, 54, 21));
        NewPwd1edit = new QLineEdit(ModPwd);
        NewPwd1edit->setObjectName(QString::fromUtf8("NewPwd1edit"));
        NewPwd1edit->setGeometry(QRect(80, 70, 113, 20));
        NewPwd1edit->setEchoMode(QLineEdit::Password);
        NewPwd2edit = new QLineEdit(ModPwd);
        NewPwd2edit->setObjectName(QString::fromUtf8("NewPwd2edit"));
        NewPwd2edit->setGeometry(QRect(80, 100, 113, 20));
        NewPwd2edit->setEchoMode(QLineEdit::Password);
        NewPwd2 = new QLabel(ModPwd);
        NewPwd2->setObjectName(QString::fromUtf8("NewPwd2"));
        NewPwd2->setGeometry(QRect(20, 100, 54, 21));
        OldPwdedit = new QLineEdit(ModPwd);
        OldPwdedit->setObjectName(QString::fromUtf8("OldPwdedit"));
        OldPwdedit->setGeometry(QRect(80, 40, 113, 20));
        OldPwdedit->setEchoMode(QLineEdit::Password);
        NewNameEdit = new QLineEdit(ModPwd);
        NewNameEdit->setObjectName(QString::fromUtf8("NewNameEdit"));
        NewNameEdit->setGeometry(QRect(80, 10, 113, 20));
        NewName = new QLabel(ModPwd);
        NewName->setObjectName(QString::fromUtf8("NewName"));
        NewName->setGeometry(QRect(20, 10, 54, 21));
        stackedWidget->addWidget(ModPwd);
        okbtn = new QPushButton(UsrModDialog);
        okbtn->setObjectName(QString::fromUtf8("okbtn"));
        okbtn->setGeometry(QRect(40, 140, 75, 23));
        exitbtn = new QPushButton(UsrModDialog);
        exitbtn->setObjectName(QString::fromUtf8("exitbtn"));
        exitbtn->setGeometry(QRect(140, 140, 75, 23));

        retranslateUi(UsrModDialog);
        QObject::connect(exitbtn, SIGNAL(clicked()), UsrModDialog, SLOT(close()));

        QMetaObject::connectSlotsByName(UsrModDialog);
    } // setupUi

    void retranslateUi(QDialog *UsrModDialog)
    {
        UsrModDialog->setWindowTitle(QApplication::translate("UsrModDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        Password1->setText(QApplication::translate("UsrModDialog", "Password:", 0, QApplication::UnicodeUTF8));
        UserName->setText(QApplication::translate("UsrModDialog", "UserName:", 0, QApplication::UnicodeUTF8));
        Password2->setText(QApplication::translate("UsrModDialog", "Password:", 0, QApplication::UnicodeUTF8));
        NewPwd1->setText(QApplication::translate("UsrModDialog", "New Pwd:", 0, QApplication::UnicodeUTF8));
        OldPwd->setText(QApplication::translate("UsrModDialog", "Old Pwd:", 0, QApplication::UnicodeUTF8));
        NewPwd2->setText(QApplication::translate("UsrModDialog", "New Pwd:", 0, QApplication::UnicodeUTF8));
        NewName->setText(QApplication::translate("UsrModDialog", "New Name:", 0, QApplication::UnicodeUTF8));
        okbtn->setText(QApplication::translate("UsrModDialog", "Ok", 0, QApplication::UnicodeUTF8));
        exitbtn->setText(QApplication::translate("UsrModDialog", "exit", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class UsrModDialog: public Ui_UsrModDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USRMODDIALOG_H
