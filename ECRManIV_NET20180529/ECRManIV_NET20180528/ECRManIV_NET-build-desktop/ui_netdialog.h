/********************************************************************************
** Form generated from reading UI file 'netdialog.ui'
**
** Created: Mon May 28 15:41:08 2018
**      by: Qt User Interface Compiler version 4.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NETDIALOG_H
#define UI_NETDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_NetDialog
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *label;
    QLineEdit *lineEdit;

    void setupUi(QDialog *NetDialog)
    {
        if (NetDialog->objectName().isEmpty())
            NetDialog->setObjectName(QString::fromUtf8("NetDialog"));
        NetDialog->resize(320, 120);
        buttonBox = new QDialogButtonBox(NetDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(10, 80, 301, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        label = new QLabel(NetDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(50, 0, 54, 20));
        lineEdit = new QLineEdit(NetDialog);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(50, 30, 201, 31));

        retranslateUi(NetDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), NetDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), NetDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(NetDialog);
    } // setupUi

    void retranslateUi(QDialog *NetDialog)
    {
        NetDialog->setWindowTitle(QApplication::translate("NetDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("NetDialog", "IP", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class NetDialog: public Ui_NetDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NETDIALOG_H
