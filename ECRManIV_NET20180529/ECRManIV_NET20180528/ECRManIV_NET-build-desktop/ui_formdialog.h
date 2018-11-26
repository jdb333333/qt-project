/********************************************************************************
** Form generated from reading UI file 'formdialog.ui'
**
** Created: Mon May 28 15:41:09 2018
**      by: Qt User Interface Compiler version 4.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMDIALOG_H
#define UI_FORMDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QTableView>

QT_BEGIN_NAMESPACE

class Ui_formDialog
{
public:
    QTableView *tableView;
    QPushButton *openfile;
    QPushButton *update;
    QPushButton *download;
    QProgressBar *progressBar;

    void setupUi(QDialog *formDialog)
    {
        if (formDialog->objectName().isEmpty())
            formDialog->setObjectName(QString::fromUtf8("formDialog"));
        formDialog->resize(640, 480);
        tableView = new QTableView(formDialog);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setGeometry(QRect(0, 1, 641, 431));
        openfile = new QPushButton(formDialog);
        openfile->setObjectName(QString::fromUtf8("openfile"));
        openfile->setGeometry(QRect(10, 440, 91, 31));
        update = new QPushButton(formDialog);
        update->setObjectName(QString::fromUtf8("update"));
        update->setGeometry(QRect(440, 440, 91, 31));
        download = new QPushButton(formDialog);
        download->setObjectName(QString::fromUtf8("download"));
        download->setGeometry(QRect(540, 440, 91, 31));
        progressBar = new QProgressBar(formDialog);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(110, 442, 331, 31));
        progressBar->setValue(0);

        retranslateUi(formDialog);

        QMetaObject::connectSlotsByName(formDialog);
    } // setupUi

    void retranslateUi(QDialog *formDialog)
    {
        formDialog->setWindowTitle(QApplication::translate("formDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        openfile->setText(QApplication::translate("formDialog", "OPENFILE", 0, QApplication::UnicodeUTF8));
        update->setText(QApplication::translate("formDialog", "UPDATE", 0, QApplication::UnicodeUTF8));
        download->setText(QApplication::translate("formDialog", "DOWNLOAD", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class formDialog: public Ui_formDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMDIALOG_H
