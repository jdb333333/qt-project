/********************************************************************************
** Form generated from reading UI file 'rs232dialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RS232DIALOG_H
#define UI_RS232DIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_RS232Dialog
{
public:
    QGroupBox *groupBox;
    QLabel *label;
    QComboBox *comboBox_baudrate;
    QLabel *label_2;
    QComboBox *comboBox_stopbits;
    QLabel *label_3;
    QComboBox *comboBox_parity;
    QComboBox *comboBox_serial;
    QPushButton *pushButton_port;
    QTextEdit *textEdit;
    QPushButton *pushButton_update;
    QProgressBar *progressBar;
    QPushButton *pushButton;

    void setupUi(QDialog *RS232Dialog)
    {
        if (RS232Dialog->objectName().isEmpty())
            RS232Dialog->setObjectName(QString::fromUtf8("RS232Dialog"));
        RS232Dialog->resize(640, 480);
        groupBox = new QGroupBox(RS232Dialog);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 0, 621, 71));
        QFont font;
        font.setPointSize(12);
        font.setBold(false);
        font.setWeight(50);
        groupBox->setFont(font);
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 30, 81, 21));
        comboBox_baudrate = new QComboBox(groupBox);
        comboBox_baudrate->setObjectName(QString::fromUtf8("comboBox_baudrate"));
        comboBox_baudrate->setGeometry(QRect(90, 30, 101, 22));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(200, 30, 71, 21));
        comboBox_stopbits = new QComboBox(groupBox);
        comboBox_stopbits->setObjectName(QString::fromUtf8("comboBox_stopbits"));
        comboBox_stopbits->setGeometry(QRect(280, 30, 41, 22));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(330, 30, 54, 21));
        comboBox_parity = new QComboBox(groupBox);
        comboBox_parity->setObjectName(QString::fromUtf8("comboBox_parity"));
        comboBox_parity->setGeometry(QRect(390, 30, 61, 22));
        comboBox_serial = new QComboBox(groupBox);
        comboBox_serial->setObjectName(QString::fromUtf8("comboBox_serial"));
        comboBox_serial->setGeometry(QRect(460, 30, 61, 22));
        pushButton_port = new QPushButton(groupBox);
        pushButton_port->setObjectName(QString::fromUtf8("pushButton_port"));
        pushButton_port->setGeometry(QRect(530, 30, 81, 23));
        textEdit = new QTextEdit(RS232Dialog);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(10, 80, 621, 351));
        pushButton_update = new QPushButton(RS232Dialog);
        pushButton_update->setObjectName(QString::fromUtf8("pushButton_update"));
        pushButton_update->setGeometry(QRect(10, 440, 111, 31));
        progressBar = new QProgressBar(RS232Dialog);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(130, 440, 411, 31));
        progressBar->setValue(0);
        pushButton = new QPushButton(RS232Dialog);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(550, 440, 81, 31));

        retranslateUi(RS232Dialog);

        QMetaObject::connectSlotsByName(RS232Dialog);
    } // setupUi

    void retranslateUi(QDialog *RS232Dialog)
    {
        RS232Dialog->setWindowTitle(QApplication::translate("RS232Dialog", "Dialog", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("RS232Dialog", "Protocol For communication", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("RS232Dialog", "Baud Rate", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("RS232Dialog", "Stop Bits", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("RS232Dialog", "Parity", 0, QApplication::UnicodeUTF8));
        pushButton_port->setText(QApplication::translate("RS232Dialog", "Open Port", 0, QApplication::UnicodeUTF8));
        pushButton_update->setText(QApplication::translate("RS232Dialog", "Open Firmware", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("RS232Dialog", "Update", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class RS232Dialog: public Ui_RS232Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RS232DIALOG_H
