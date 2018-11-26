/********************************************************************************
** Form generated from reading UI file 'formdialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
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
#include <QtGui/QLabel>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QTableView>
#include <QtGui/QTableWidget>
#include <QtGui/QTimeEdit>

QT_BEGIN_NAMESPACE

class Ui_formDialog
{
public:
    QTableView *tableView;
    QPushButton *openfile;
    QPushButton *update;
    QPushButton *download;
    QProgressBar *progressBar;
    QTableWidget *tableWidget;
    QLabel *info;
    QTimeEdit *timeEdit;

    void setupUi(QDialog *formDialog)
    {
        if (formDialog->objectName().isEmpty())
            formDialog->setObjectName(QString::fromUtf8("formDialog"));
        formDialog->resize(640, 480);
        tableView = new QTableView(formDialog);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setGeometry(QRect(10, 11, 471, 401));
        openfile = new QPushButton(formDialog);
        openfile->setObjectName(QString::fromUtf8("openfile"));
        openfile->setGeometry(QRect(10, 420, 91, 31));
        update = new QPushButton(formDialog);
        update->setObjectName(QString::fromUtf8("update"));
        update->setGeometry(QRect(440, 420, 91, 31));
        download = new QPushButton(formDialog);
        download->setObjectName(QString::fromUtf8("download"));
        download->setGeometry(QRect(540, 420, 91, 31));
        progressBar = new QProgressBar(formDialog);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(110, 422, 231, 31));
        progressBar->setValue(0);
        tableWidget = new QTableWidget(formDialog);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setGeometry(QRect(490, 10, 141, 401));
        info = new QLabel(formDialog);
        info->setObjectName(QString::fromUtf8("info"));
        info->setGeometry(QRect(110, 460, 301, 16));
        timeEdit = new QTimeEdit(formDialog);
        timeEdit->setObjectName(QString::fromUtf8("timeEdit"));
        timeEdit->setGeometry(QRect(340, 421, 91, 31));

        retranslateUi(formDialog);

        QMetaObject::connectSlotsByName(formDialog);
    } // setupUi

    void retranslateUi(QDialog *formDialog)
    {
        formDialog->setWindowTitle(QApplication::translate("formDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        openfile->setText(QApplication::translate("formDialog", "OPENFILE", 0, QApplication::UnicodeUTF8));
        update->setText(QApplication::translate("formDialog", "UPDATE", 0, QApplication::UnicodeUTF8));
        download->setText(QApplication::translate("formDialog", "DOWNLOAD", 0, QApplication::UnicodeUTF8));
        info->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class formDialog: public Ui_formDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMDIALOG_H
