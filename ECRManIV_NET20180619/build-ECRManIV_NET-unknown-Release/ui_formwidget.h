/********************************************************************************
** Form generated from reading UI file 'formwidget.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMWIDGET_H
#define UI_FORMWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QTableWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Formwidget
{
public:
    QAction *actionFIXED;
    QAction *actionFLOAT;
    QAction *actionFIXED_FLOAT;
    QAction *actionPERADD;
    QAction *actionPERRED;
    QAction *clerk_actionVoid;
    QAction *clerk_actionCorrect;
    QAction *clerk_actionCancle;
    QAction *clerk_actionReturn;
    QAction *clerk_actionDisc;
    QAction *clerk_actionAdd;
    QAction *clerk_actionAmountdisc;
    QAction *clerk_actionTrain;
    QTableWidget *tableWidget;
    QPushButton *UPDATA;
    QPushButton *DOWNLOAD;
    QPushButton *OPENFILE;
    QProgressBar *progressBar;

    void setupUi(QWidget *Formwidget)
    {
        if (Formwidget->objectName().isEmpty())
            Formwidget->setObjectName(QString::fromUtf8("Formwidget"));
        Formwidget->resize(640, 480);
        actionFIXED = new QAction(Formwidget);
        actionFIXED->setObjectName(QString::fromUtf8("actionFIXED"));
        actionFIXED->setCheckable(true);
        actionFLOAT = new QAction(Formwidget);
        actionFLOAT->setObjectName(QString::fromUtf8("actionFLOAT"));
        actionFLOAT->setCheckable(true);
        actionFIXED_FLOAT = new QAction(Formwidget);
        actionFIXED_FLOAT->setObjectName(QString::fromUtf8("actionFIXED_FLOAT"));
        actionFIXED_FLOAT->setCheckable(true);
        actionPERADD = new QAction(Formwidget);
        actionPERADD->setObjectName(QString::fromUtf8("actionPERADD"));
        actionPERADD->setCheckable(true);
        actionPERRED = new QAction(Formwidget);
        actionPERRED->setObjectName(QString::fromUtf8("actionPERRED"));
        actionPERRED->setCheckable(true);
        clerk_actionVoid = new QAction(Formwidget);
        clerk_actionVoid->setObjectName(QString::fromUtf8("clerk_actionVoid"));
        clerk_actionVoid->setCheckable(true);
        clerk_actionCorrect = new QAction(Formwidget);
        clerk_actionCorrect->setObjectName(QString::fromUtf8("clerk_actionCorrect"));
        clerk_actionCorrect->setCheckable(true);
        clerk_actionCancle = new QAction(Formwidget);
        clerk_actionCancle->setObjectName(QString::fromUtf8("clerk_actionCancle"));
        clerk_actionCancle->setCheckable(true);
        clerk_actionReturn = new QAction(Formwidget);
        clerk_actionReturn->setObjectName(QString::fromUtf8("clerk_actionReturn"));
        clerk_actionReturn->setCheckable(true);
        clerk_actionDisc = new QAction(Formwidget);
        clerk_actionDisc->setObjectName(QString::fromUtf8("clerk_actionDisc"));
        clerk_actionDisc->setCheckable(true);
        clerk_actionAdd = new QAction(Formwidget);
        clerk_actionAdd->setObjectName(QString::fromUtf8("clerk_actionAdd"));
        clerk_actionAdd->setCheckable(true);
        clerk_actionAmountdisc = new QAction(Formwidget);
        clerk_actionAmountdisc->setObjectName(QString::fromUtf8("clerk_actionAmountdisc"));
        clerk_actionAmountdisc->setCheckable(true);
        clerk_actionTrain = new QAction(Formwidget);
        clerk_actionTrain->setObjectName(QString::fromUtf8("clerk_actionTrain"));
        clerk_actionTrain->setCheckable(true);
        tableWidget = new QTableWidget(Formwidget);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setGeometry(QRect(10, 10, 621, 421));
        UPDATA = new QPushButton(Formwidget);
        UPDATA->setObjectName(QString::fromUtf8("UPDATA"));
        UPDATA->setGeometry(QRect(440, 440, 91, 31));
        DOWNLOAD = new QPushButton(Formwidget);
        DOWNLOAD->setObjectName(QString::fromUtf8("DOWNLOAD"));
        DOWNLOAD->setGeometry(QRect(540, 440, 91, 31));
        OPENFILE = new QPushButton(Formwidget);
        OPENFILE->setObjectName(QString::fromUtf8("OPENFILE"));
        OPENFILE->setGeometry(QRect(10, 440, 91, 31));
        progressBar = new QProgressBar(Formwidget);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(110, 440, 321, 31));
        progressBar->setValue(0);

        retranslateUi(Formwidget);

        QMetaObject::connectSlotsByName(Formwidget);
    } // setupUi

    void retranslateUi(QWidget *Formwidget)
    {
        Formwidget->setWindowTitle(QApplication::translate("Formwidget", "Form", 0, QApplication::UnicodeUTF8));
        actionFIXED->setText(QApplication::translate("Formwidget", "FIXED", 0, QApplication::UnicodeUTF8));
        actionFLOAT->setText(QApplication::translate("Formwidget", "FLOAT", 0, QApplication::UnicodeUTF8));
        actionFIXED_FLOAT->setText(QApplication::translate("Formwidget", "FIXED/FLOAT", 0, QApplication::UnicodeUTF8));
        actionPERADD->setText(QApplication::translate("Formwidget", "(+%)", 0, QApplication::UnicodeUTF8));
        actionPERRED->setText(QApplication::translate("Formwidget", "(-%)", 0, QApplication::UnicodeUTF8));
        clerk_actionVoid->setText(QApplication::translate("Formwidget", "void", 0, QApplication::UnicodeUTF8));
        clerk_actionCorrect->setText(QApplication::translate("Formwidget", "correct", 0, QApplication::UnicodeUTF8));
        clerk_actionCancle->setText(QApplication::translate("Formwidget", "cancle", 0, QApplication::UnicodeUTF8));
        clerk_actionReturn->setText(QApplication::translate("Formwidget", "return", 0, QApplication::UnicodeUTF8));
        clerk_actionDisc->setText(QApplication::translate("Formwidget", "disc", 0, QApplication::UnicodeUTF8));
        clerk_actionAdd->setText(QApplication::translate("Formwidget", "add", 0, QApplication::UnicodeUTF8));
        clerk_actionAmountdisc->setText(QApplication::translate("Formwidget", "amountdisc", 0, QApplication::UnicodeUTF8));
        clerk_actionTrain->setText(QApplication::translate("Formwidget", "train", 0, QApplication::UnicodeUTF8));
        UPDATA->setText(QApplication::translate("Formwidget", "UPDATA", 0, QApplication::UnicodeUTF8));
        DOWNLOAD->setText(QApplication::translate("Formwidget", "DOWNLOAD", 0, QApplication::UnicodeUTF8));
        OPENFILE->setText(QApplication::translate("Formwidget", "OPENFILE", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Formwidget: public Ui_Formwidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMWIDGET_H
