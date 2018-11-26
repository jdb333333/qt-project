/********************************************************************************
** Form generated from reading UI file 'usrdialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USRDIALOG_H
#define UI_USRDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_usrDialog
{
public:
    QGroupBox *groupBox;
    QRadioButton *OrdinaryUser;
    QRadioButton *SupevisorUser;
    QGroupBox *UserPerm;
    QCheckBox *clerkcheckBox;
    QCheckBox *plucheckBox;
    QCheckBox *ticketcheckBox;
    QCheckBox *offercheckBox;
    QCheckBox *groupcheckBox;
    QCheckBox *discountcheckBox;
    QCheckBox *reportcheckBox;
    QCheckBox *departmentcheckBox;
    QCheckBox *taxcheckBox;
    QGroupBox *groupBox_3;
    QPushButton *modpwd;
    QLabel *label;
    QLineEdit *pwdedit;
    QLineEdit *adminedit;
    QLabel *label_2;
    QGroupBox *groupBox_4;
    QTableWidget *UserList;
    QGroupBox *groupBox_5;
    QPushButton *add;
    QPushButton *delete_2;
    QPushButton *modify;
    QPushButton *setperm;
    QGroupBox *UsrInfo;
    QLabel *UsrName;
    QLineEdit *UsrPwdEdit;
    QLineEdit *UsrNameEdit;
    QLabel *UsrPwd;

    void setupUi(QDialog *usrDialog)
    {
        if (usrDialog->objectName().isEmpty())
            usrDialog->setObjectName(QString::fromUtf8("usrDialog"));
        usrDialog->resize(640, 321);
        groupBox = new QGroupBox(usrDialog);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 120, 71));
        OrdinaryUser = new QRadioButton(groupBox);
        OrdinaryUser->setObjectName(QString::fromUtf8("OrdinaryUser"));
        OrdinaryUser->setGeometry(QRect(10, 20, 101, 16));
        OrdinaryUser->setChecked(true);
        SupevisorUser = new QRadioButton(groupBox);
        SupevisorUser->setObjectName(QString::fromUtf8("SupevisorUser"));
        SupevisorUser->setGeometry(QRect(10, 40, 101, 16));
        SupevisorUser->raise();
        OrdinaryUser->raise();
        UserPerm = new QGroupBox(usrDialog);
        UserPerm->setObjectName(QString::fromUtf8("UserPerm"));
        UserPerm->setGeometry(QRect(150, 120, 471, 131));
        clerkcheckBox = new QCheckBox(UserPerm);
        clerkcheckBox->setObjectName(QString::fromUtf8("clerkcheckBox"));
        clerkcheckBox->setGeometry(QRect(50, 30, 71, 16));
        plucheckBox = new QCheckBox(UserPerm);
        plucheckBox->setObjectName(QString::fromUtf8("plucheckBox"));
        plucheckBox->setGeometry(QRect(50, 60, 71, 16));
        ticketcheckBox = new QCheckBox(UserPerm);
        ticketcheckBox->setObjectName(QString::fromUtf8("ticketcheckBox"));
        ticketcheckBox->setGeometry(QRect(50, 90, 71, 16));
        offercheckBox = new QCheckBox(UserPerm);
        offercheckBox->setObjectName(QString::fromUtf8("offercheckBox"));
        offercheckBox->setGeometry(QRect(200, 90, 71, 16));
        groupcheckBox = new QCheckBox(UserPerm);
        groupcheckBox->setObjectName(QString::fromUtf8("groupcheckBox"));
        groupcheckBox->setGeometry(QRect(200, 30, 71, 16));
        discountcheckBox = new QCheckBox(UserPerm);
        discountcheckBox->setObjectName(QString::fromUtf8("discountcheckBox"));
        discountcheckBox->setGeometry(QRect(200, 60, 71, 16));
        reportcheckBox = new QCheckBox(UserPerm);
        reportcheckBox->setObjectName(QString::fromUtf8("reportcheckBox"));
        reportcheckBox->setGeometry(QRect(370, 90, 71, 16));
        departmentcheckBox = new QCheckBox(UserPerm);
        departmentcheckBox->setObjectName(QString::fromUtf8("departmentcheckBox"));
        departmentcheckBox->setGeometry(QRect(370, 30, 81, 16));
        taxcheckBox = new QCheckBox(UserPerm);
        taxcheckBox->setObjectName(QString::fromUtf8("taxcheckBox"));
        taxcheckBox->setGeometry(QRect(370, 60, 71, 16));
        groupBox_3 = new QGroupBox(usrDialog);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(150, 10, 471, 51));
        modpwd = new QPushButton(groupBox_3);
        modpwd->setObjectName(QString::fromUtf8("modpwd"));
        modpwd->setGeometry(QRect(400, 20, 61, 21));
        label = new QLabel(groupBox_3);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 20, 51, 21));
        QFont font;
        font.setPointSize(12);
        label->setFont(font);
        label->setLayoutDirection(Qt::LeftToRight);
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        pwdedit = new QLineEdit(groupBox_3);
        pwdedit->setObjectName(QString::fromUtf8("pwdedit"));
        pwdedit->setGeometry(QRect(270, 20, 113, 21));
        pwdedit->setEchoMode(QLineEdit::Password);
        adminedit = new QLineEdit(groupBox_3);
        adminedit->setObjectName(QString::fromUtf8("adminedit"));
        adminedit->setGeometry(QRect(70, 20, 113, 21));
        label_2 = new QLabel(groupBox_3);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(190, 20, 71, 21));
        label_2->setFont(font);
        label_2->setLayoutDirection(Qt::LeftToRight);
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        groupBox_4 = new QGroupBox(usrDialog);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setGeometry(QRect(10, 90, 120, 221));
        UserList = new QTableWidget(groupBox_4);
        UserList->setObjectName(QString::fromUtf8("UserList"));
        UserList->setGeometry(QRect(10, 20, 101, 191));
        groupBox_5 = new QGroupBox(usrDialog);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        groupBox_5->setGeometry(QRect(150, 250, 471, 61));
        add = new QPushButton(groupBox_5);
        add->setObjectName(QString::fromUtf8("add"));
        add->setGeometry(QRect(30, 20, 91, 31));
        delete_2 = new QPushButton(groupBox_5);
        delete_2->setObjectName(QString::fromUtf8("delete_2"));
        delete_2->setGeometry(QRect(140, 20, 91, 31));
        modify = new QPushButton(groupBox_5);
        modify->setObjectName(QString::fromUtf8("modify"));
        modify->setGeometry(QRect(250, 20, 91, 31));
        setperm = new QPushButton(groupBox_5);
        setperm->setObjectName(QString::fromUtf8("setperm"));
        setperm->setGeometry(QRect(360, 20, 91, 31));
        UsrInfo = new QGroupBox(usrDialog);
        UsrInfo->setObjectName(QString::fromUtf8("UsrInfo"));
        UsrInfo->setGeometry(QRect(150, 60, 471, 51));
        UsrName = new QLabel(UsrInfo);
        UsrName->setObjectName(QString::fromUtf8("UsrName"));
        UsrName->setGeometry(QRect(30, 20, 71, 21));
        UsrName->setFont(font);
        UsrName->setLayoutDirection(Qt::LeftToRight);
        UsrName->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        UsrPwdEdit = new QLineEdit(UsrInfo);
        UsrPwdEdit->setObjectName(QString::fromUtf8("UsrPwdEdit"));
        UsrPwdEdit->setGeometry(QRect(310, 20, 113, 21));
        UsrPwdEdit->setEchoMode(QLineEdit::Normal);
        UsrNameEdit = new QLineEdit(UsrInfo);
        UsrNameEdit->setObjectName(QString::fromUtf8("UsrNameEdit"));
        UsrNameEdit->setGeometry(QRect(110, 20, 113, 21));
        UsrPwd = new QLabel(UsrInfo);
        UsrPwd->setObjectName(QString::fromUtf8("UsrPwd"));
        UsrPwd->setGeometry(QRect(230, 20, 71, 21));
        UsrPwd->setFont(font);
        UsrPwd->setLayoutDirection(Qt::LeftToRight);
        UsrPwd->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        retranslateUi(usrDialog);

        QMetaObject::connectSlotsByName(usrDialog);
    } // setupUi

    void retranslateUi(QDialog *usrDialog)
    {
        usrDialog->setWindowTitle(QApplication::translate("usrDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("usrDialog", "UserGroup", 0, QApplication::UnicodeUTF8));
        OrdinaryUser->setText(QApplication::translate("usrDialog", "OrdinaryUser", 0, QApplication::UnicodeUTF8));
        SupevisorUser->setText(QApplication::translate("usrDialog", "SupevisorUser", 0, QApplication::UnicodeUTF8));
        UserPerm->setTitle(QApplication::translate("usrDialog", "UserPermissions", 0, QApplication::UnicodeUTF8));
        clerkcheckBox->setText(QApplication::translate("usrDialog", "CLERK", 0, QApplication::UnicodeUTF8));
        plucheckBox->setText(QApplication::translate("usrDialog", "PLU", 0, QApplication::UnicodeUTF8));
        ticketcheckBox->setText(QApplication::translate("usrDialog", "TICKET", 0, QApplication::UnicodeUTF8));
        offercheckBox->setText(QApplication::translate("usrDialog", "OFFER", 0, QApplication::UnicodeUTF8));
        groupcheckBox->setText(QApplication::translate("usrDialog", "EJ", 0, QApplication::UnicodeUTF8));
        discountcheckBox->setText(QApplication::translate("usrDialog", "DISCOUNT", 0, QApplication::UnicodeUTF8));
        reportcheckBox->setText(QApplication::translate("usrDialog", "REPORT", 0, QApplication::UnicodeUTF8));
        departmentcheckBox->setText(QApplication::translate("usrDialog", "DEPARTMENT", 0, QApplication::UnicodeUTF8));
        taxcheckBox->setText(QApplication::translate("usrDialog", "TAX", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("usrDialog", "AdminEdit", 0, QApplication::UnicodeUTF8));
        modpwd->setText(QApplication::translate("usrDialog", "Modify", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("usrDialog", "Admin:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("usrDialog", "Password:", 0, QApplication::UnicodeUTF8));
        groupBox_4->setTitle(QApplication::translate("usrDialog", "UserList", 0, QApplication::UnicodeUTF8));
        groupBox_5->setTitle(QApplication::translate("usrDialog", "UserEdit", 0, QApplication::UnicodeUTF8));
        add->setText(QApplication::translate("usrDialog", "Add", 0, QApplication::UnicodeUTF8));
        delete_2->setText(QApplication::translate("usrDialog", "Delete", 0, QApplication::UnicodeUTF8));
        modify->setText(QApplication::translate("usrDialog", "Modify", 0, QApplication::UnicodeUTF8));
        setperm->setText(QApplication::translate("usrDialog", "SetPerm", 0, QApplication::UnicodeUTF8));
        UsrInfo->setTitle(QApplication::translate("usrDialog", "UsrInfo", 0, QApplication::UnicodeUTF8));
        UsrName->setText(QApplication::translate("usrDialog", "UsrName:", 0, QApplication::UnicodeUTF8));
        UsrPwd->setText(QApplication::translate("usrDialog", "Password:", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class usrDialog: public Ui_usrDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USRDIALOG_H
