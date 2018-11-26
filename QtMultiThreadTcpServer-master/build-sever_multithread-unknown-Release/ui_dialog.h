/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTextBrowser>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QTextBrowser *msg;
    QHBoxLayout *horizontalLayout_3;
    QLineEdit *sendMsg;
    QPushButton *sendBtn;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QComboBox *objectBox;
    QCheckBox *hexCheckBox;
    QCheckBox *addrCheckBox;
    QCheckBox *circleCheckBox;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *clearBtn;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLabel *num;
    QSpacerItem *horizontalSpacer;
    QCheckBox *loopCheckBox;
    QLabel *label_3;
    QLineEdit *periodLineEdit;
    QLabel *label_4;
    QPushButton *loopStopBtn;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->resize(629, 488);
        gridLayout = new QGridLayout(Dialog);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        msg = new QTextBrowser(Dialog);
        msg->setObjectName(QString::fromUtf8("msg"));

        verticalLayout->addWidget(msg);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        sendMsg = new QLineEdit(Dialog);
        sendMsg->setObjectName(QString::fromUtf8("sendMsg"));

        horizontalLayout_3->addWidget(sendMsg);

        sendBtn = new QPushButton(Dialog);
        sendBtn->setObjectName(QString::fromUtf8("sendBtn"));
        sendBtn->setEnabled(false);

        horizontalLayout_3->addWidget(sendBtn);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(Dialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        objectBox = new QComboBox(Dialog);
        objectBox->setObjectName(QString::fromUtf8("objectBox"));

        horizontalLayout_2->addWidget(objectBox);

        hexCheckBox = new QCheckBox(Dialog);
        hexCheckBox->setObjectName(QString::fromUtf8("hexCheckBox"));
        hexCheckBox->setEnabled(false);

        horizontalLayout_2->addWidget(hexCheckBox);

        addrCheckBox = new QCheckBox(Dialog);
        addrCheckBox->setObjectName(QString::fromUtf8("addrCheckBox"));
        addrCheckBox->setEnabled(false);

        horizontalLayout_2->addWidget(addrCheckBox);

        circleCheckBox = new QCheckBox(Dialog);
        circleCheckBox->setObjectName(QString::fromUtf8("circleCheckBox"));
        circleCheckBox->setEnabled(false);

        horizontalLayout_2->addWidget(circleCheckBox);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        clearBtn = new QPushButton(Dialog);
        clearBtn->setObjectName(QString::fromUtf8("clearBtn"));

        horizontalLayout_2->addWidget(clearBtn);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(Dialog);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        num = new QLabel(Dialog);
        num->setObjectName(QString::fromUtf8("num"));

        horizontalLayout->addWidget(num);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        loopCheckBox = new QCheckBox(Dialog);
        loopCheckBox->setObjectName(QString::fromUtf8("loopCheckBox"));
        loopCheckBox->setEnabled(false);

        horizontalLayout->addWidget(loopCheckBox);

        label_3 = new QLabel(Dialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout->addWidget(label_3);

        periodLineEdit = new QLineEdit(Dialog);
        periodLineEdit->setObjectName(QString::fromUtf8("periodLineEdit"));

        horizontalLayout->addWidget(periodLineEdit);

        label_4 = new QLabel(Dialog);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout->addWidget(label_4);

        loopStopBtn = new QPushButton(Dialog);
        loopStopBtn->setObjectName(QString::fromUtf8("loopStopBtn"));
        loopStopBtn->setEnabled(false);

        horizontalLayout->addWidget(loopStopBtn);


        verticalLayout->addLayout(horizontalLayout);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);


        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "TCP\346\234\215\345\212\241\345\231\250", 0, QApplication::UnicodeUTF8));
        sendBtn->setText(QApplication::translate("Dialog", "Send", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("Dialog", "Send Object  \357\274\232", 0, QApplication::UnicodeUTF8));
        hexCheckBox->setText(QApplication::translate("Dialog", "HEX Transceiver", 0, QApplication::UnicodeUTF8));
        addrCheckBox->setText(QApplication::translate("Dialog", "Client Address Not Displayed", 0, QApplication::UnicodeUTF8));
        circleCheckBox->setText(QApplication::translate("Dialog", "Loop", 0, QApplication::UnicodeUTF8));
        clearBtn->setText(QApplication::translate("Dialog", "Clear Data", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Dialog", "Connection Number\357\274\232", 0, QApplication::UnicodeUTF8));
        num->setText(QString());
        loopCheckBox->setText(QApplication::translate("Dialog", "Repeat Sending", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("Dialog", "Time Interval\357\274\232", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("Dialog", "ms", 0, QApplication::UnicodeUTF8));
        loopStopBtn->setText(QApplication::translate("Dialog", "\345\201\234\346\255\242", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
