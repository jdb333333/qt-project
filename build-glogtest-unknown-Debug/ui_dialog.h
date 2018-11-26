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
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *comboBox_baudrate;
    QLabel *label_2;
    QComboBox *comboBox_stopbits;
    QLabel *label_3;
    QComboBox *comboBox_parity;
    QComboBox *comboBox_serial;
    QPushButton *pushButton_port;
    QTextEdit *textEdit;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->resize(640, 480);
        groupBox = new QGroupBox(Dialog);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(0, 0, 641, 62));
        QFont font;
        font.setPointSize(12);
        font.setBold(false);
        font.setWeight(50);
        groupBox->setFont(font);
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        comboBox_baudrate = new QComboBox(groupBox);
        comboBox_baudrate->setObjectName(QString::fromUtf8("comboBox_baudrate"));

        horizontalLayout->addWidget(comboBox_baudrate);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);

        comboBox_stopbits = new QComboBox(groupBox);
        comboBox_stopbits->setObjectName(QString::fromUtf8("comboBox_stopbits"));

        horizontalLayout->addWidget(comboBox_stopbits);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout->addWidget(label_3);

        comboBox_parity = new QComboBox(groupBox);
        comboBox_parity->setObjectName(QString::fromUtf8("comboBox_parity"));

        horizontalLayout->addWidget(comboBox_parity);

        comboBox_serial = new QComboBox(groupBox);
        comboBox_serial->setObjectName(QString::fromUtf8("comboBox_serial"));

        horizontalLayout->addWidget(comboBox_serial);

        pushButton_port = new QPushButton(groupBox);
        pushButton_port->setObjectName(QString::fromUtf8("pushButton_port"));

        horizontalLayout->addWidget(pushButton_port);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        textEdit = new QTextEdit(Dialog);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(10, 80, 621, 351));

        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("Dialog", "Protocol For communication", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Dialog", "Baud Rate", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("Dialog", "Stop Bits", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("Dialog", "Parity", 0, QApplication::UnicodeUTF8));
        pushButton_port->setText(QApplication::translate("Dialog", "Open Port", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
