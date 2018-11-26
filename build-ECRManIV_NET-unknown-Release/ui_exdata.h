/********************************************************************************
** Form generated from reading UI file 'exdata.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EXDATA_H
#define UI_EXDATA_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QTableView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_exdata
{
public:
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *openfile;
    QTableView *tableView;

    void setupUi(QWidget *exdata)
    {
        if (exdata->objectName().isEmpty())
            exdata->setObjectName(QString::fromUtf8("exdata"));
        exdata->resize(640, 480);
        pushButton = new QPushButton(exdata);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(340, 440, 91, 31));
        pushButton_2 = new QPushButton(exdata);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(490, 440, 91, 31));
        openfile = new QPushButton(exdata);
        openfile->setObjectName(QString::fromUtf8("openfile"));
        openfile->setGeometry(QRect(30, 440, 91, 31));
        tableView = new QTableView(exdata);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setGeometry(QRect(0, 0, 651, 431));

        retranslateUi(exdata);

        QMetaObject::connectSlotsByName(exdata);
    } // setupUi

    void retranslateUi(QWidget *exdata)
    {
        exdata->setWindowTitle(QApplication::translate("exdata", "Form", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("exdata", "UPDATA", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("exdata", "DOWNLOAD", 0, QApplication::UnicodeUTF8));
        openfile->setText(QApplication::translate("exdata", "OPENFILE", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class exdata: public Ui_exdata {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EXDATA_H
