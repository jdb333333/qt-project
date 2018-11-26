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
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QStackedWidget>
#include <QtGui/QTextEdit>
#include <QtGui/QWidget>

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
    QLabel *label_19;
    QComboBox *comboBox_serial;
    QPushButton *pushButton_port;
    QTextEdit *textEdit;
    QGroupBox *ALARMGROUP;
    QCheckBox *checkBox_ALARM_1;
    QCheckBox *checkBox_ALARM_2;
    QCheckBox *checkBox_ALARM_3;
    QCheckBox *checkBox_ALARM_4;
    QCheckBox *checkBox_ALARM_5;
    QCheckBox *checkBox_ALARM_6;
    QCheckBox *checkBox_ALARM_7;
    QCheckBox *checkBox_ALARM_8;
    QCheckBox *checkBox_ALARM_9;
    QCheckBox *checkBox_ALARM_10;
    QCheckBox *checkBox_ALARM_11;
    QCheckBox *checkBox_ALARM_12;
    QGroupBox *OVPNCONFIG;
    QLabel *label_11;
    QLineEdit *lineEdit_ovpnipserver;
    QLabel *label_12;
    QLabel *label_13;
    QLineEdit *lineEdit_ovpnuser;
    QLineEdit *lineEdit_ovpnpasswd;
    QGroupBox *PPTPCONFIG;
    QLineEdit *lineEdit_pptpipserver;
    QLabel *label_14;
    QLineEdit *lineEdit_pptpuser;
    QLabel *label_15;
    QLabel *label_16;
    QLineEdit *lineEdit_pptppasswd;
    QGroupBox *SERVICEGROUP;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QCheckBox *checkBox_ovpn;
    QCheckBox *checkBox_pptp;
    QCheckBox *checkBox_telnet;
    QCheckBox *checkBox_ssh;
    QCheckBox *checkBox_ftp;
    QGroupBox *CONNECT;
    QRadioButton *radioButton_gsm;
    QRadioButton *radioButton_wifi;
    QStackedWidget *stackedWidget_connect;
    QWidget *page;
    QLineEdit *lineEdit_apn;
    QLabel *label_6;
    QLabel *label_8;
    QLineEdit *lineEdit_accgprs;
    QWidget *page_2;
    QLabel *label_9;
    QLabel *label_10;
    QLineEdit *lineEdit_wifissid;
    QLineEdit *lineEdit_wifipassword;
    QLabel *label_17;
    QLineEdit *lineEdit_ipserver;
    QLineEdit *lineEdit_portserver;
    QLabel *label_18;
    QGroupBox *TAPPINGMODE;
    QRadioButton *radioButton_usb;
    QRadioButton *radioButton_serial;
    QRadioButton *radioButton_parallel;
    QStackedWidget *stackedWidget_tappingmode;
    QWidget *page_3;
    QComboBox *comboBox_usbmode;
    QLabel *label_5;
    QWidget *page_4;
    QLabel *label_4;
    QLineEdit *lineEdit_baudrate;
    QGroupBox *DEVICE;
    QLabel *label_20;
    QLineEdit *lineEdit_devicename;
    QLineEdit *lineEdit_deviceid;
    QLabel *label_21;
    QLineEdit *lineEdit_username;
    QLabel *label_22;
    QLineEdit *lineEdit_password;
    QLabel *label_23;
    QLineEdit *lineEdit_timeout;
    QLabel *label_24;
    QLineEdit *lineEdit_ssinterval;
    QLabel *label_25;
    QLabel *label_26;
    QComboBox *comboBox_sendingmode;
    QLineEdit *lineEdit_key;
    QLabel *label_27;
    QWidget *widget_alarm;
    QLabel *label_power;
    QLabel *label_serial;
    QLabel *label_parallel;
    QLabel *label_usb;
    QLabel *label_battery;
    QLabel *label_sd;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_7;
    QLabel *label_signal;
    QLabel *label_28;
    QLabel *label_localip;
    QLabel *label_29;
    QLabel *label_rtctime;
    QLabel *label_30;
    QLabel *label_systime;
    QPushButton *pushButton_download;
    QPushButton *pushButton_login;
    QPushButton *pushButton_update;
    QTextEdit *textEdit_receipt;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->resize(800, 600);
        Dialog->setStyleSheet(QString::fromUtf8(""));
        groupBox = new QGroupBox(Dialog);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 0, 781, 62));
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
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout->addWidget(label_2);

        comboBox_stopbits = new QComboBox(groupBox);
        comboBox_stopbits->setObjectName(QString::fromUtf8("comboBox_stopbits"));

        horizontalLayout->addWidget(comboBox_stopbits);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout->addWidget(label_3);

        comboBox_parity = new QComboBox(groupBox);
        comboBox_parity->setObjectName(QString::fromUtf8("comboBox_parity"));

        horizontalLayout->addWidget(comboBox_parity);

        label_19 = new QLabel(groupBox);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        label_19->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout->addWidget(label_19);

        comboBox_serial = new QComboBox(groupBox);
        comboBox_serial->setObjectName(QString::fromUtf8("comboBox_serial"));

        horizontalLayout->addWidget(comboBox_serial);

        pushButton_port = new QPushButton(groupBox);
        pushButton_port->setObjectName(QString::fromUtf8("pushButton_port"));

        horizontalLayout->addWidget(pushButton_port);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        textEdit = new QTextEdit(Dialog);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(470, 340, 321, 131));
        ALARMGROUP = new QGroupBox(Dialog);
        ALARMGROUP->setObjectName(QString::fromUtf8("ALARMGROUP"));
        ALARMGROUP->setGeometry(QRect(10, 270, 371, 61));
        checkBox_ALARM_1 = new QCheckBox(ALARMGROUP);
        checkBox_ALARM_1->setObjectName(QString::fromUtf8("checkBox_ALARM_1"));
        checkBox_ALARM_1->setGeometry(QRect(10, 20, 61, 16));
        checkBox_ALARM_2 = new QCheckBox(ALARMGROUP);
        checkBox_ALARM_2->setObjectName(QString::fromUtf8("checkBox_ALARM_2"));
        checkBox_ALARM_2->setGeometry(QRect(70, 20, 61, 16));
        checkBox_ALARM_3 = new QCheckBox(ALARMGROUP);
        checkBox_ALARM_3->setObjectName(QString::fromUtf8("checkBox_ALARM_3"));
        checkBox_ALARM_3->setGeometry(QRect(130, 20, 61, 16));
        checkBox_ALARM_4 = new QCheckBox(ALARMGROUP);
        checkBox_ALARM_4->setObjectName(QString::fromUtf8("checkBox_ALARM_4"));
        checkBox_ALARM_4->setGeometry(QRect(190, 20, 61, 16));
        checkBox_ALARM_5 = new QCheckBox(ALARMGROUP);
        checkBox_ALARM_5->setObjectName(QString::fromUtf8("checkBox_ALARM_5"));
        checkBox_ALARM_5->setGeometry(QRect(250, 20, 61, 16));
        checkBox_ALARM_6 = new QCheckBox(ALARMGROUP);
        checkBox_ALARM_6->setObjectName(QString::fromUtf8("checkBox_ALARM_6"));
        checkBox_ALARM_6->setGeometry(QRect(310, 20, 61, 16));
        checkBox_ALARM_7 = new QCheckBox(ALARMGROUP);
        checkBox_ALARM_7->setObjectName(QString::fromUtf8("checkBox_ALARM_7"));
        checkBox_ALARM_7->setGeometry(QRect(10, 40, 61, 16));
        checkBox_ALARM_8 = new QCheckBox(ALARMGROUP);
        checkBox_ALARM_8->setObjectName(QString::fromUtf8("checkBox_ALARM_8"));
        checkBox_ALARM_8->setGeometry(QRect(70, 40, 61, 16));
        checkBox_ALARM_9 = new QCheckBox(ALARMGROUP);
        checkBox_ALARM_9->setObjectName(QString::fromUtf8("checkBox_ALARM_9"));
        checkBox_ALARM_9->setGeometry(QRect(130, 40, 61, 16));
        checkBox_ALARM_10 = new QCheckBox(ALARMGROUP);
        checkBox_ALARM_10->setObjectName(QString::fromUtf8("checkBox_ALARM_10"));
        checkBox_ALARM_10->setGeometry(QRect(190, 40, 61, 16));
        checkBox_ALARM_11 = new QCheckBox(ALARMGROUP);
        checkBox_ALARM_11->setObjectName(QString::fromUtf8("checkBox_ALARM_11"));
        checkBox_ALARM_11->setGeometry(QRect(250, 40, 61, 16));
        checkBox_ALARM_12 = new QCheckBox(ALARMGROUP);
        checkBox_ALARM_12->setObjectName(QString::fromUtf8("checkBox_ALARM_12"));
        checkBox_ALARM_12->setGeometry(QRect(310, 40, 61, 16));
        OVPNCONFIG = new QGroupBox(Dialog);
        OVPNCONFIG->setObjectName(QString::fromUtf8("OVPNCONFIG"));
        OVPNCONFIG->setGeometry(QRect(390, 220, 401, 54));
        label_11 = new QLabel(OVPNCONFIG);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(0, 20, 61, 21));
        label_11->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lineEdit_ovpnipserver = new QLineEdit(OVPNCONFIG);
        lineEdit_ovpnipserver->setObjectName(QString::fromUtf8("lineEdit_ovpnipserver"));
        lineEdit_ovpnipserver->setGeometry(QRect(60, 20, 91, 20));
        label_12 = new QLabel(OVPNCONFIG);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(150, 20, 61, 21));
        label_12->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_13 = new QLabel(OVPNCONFIG);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(280, 20, 51, 21));
        label_13->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lineEdit_ovpnuser = new QLineEdit(OVPNCONFIG);
        lineEdit_ovpnuser->setObjectName(QString::fromUtf8("lineEdit_ovpnuser"));
        lineEdit_ovpnuser->setGeometry(QRect(210, 20, 71, 20));
        lineEdit_ovpnpasswd = new QLineEdit(OVPNCONFIG);
        lineEdit_ovpnpasswd->setObjectName(QString::fromUtf8("lineEdit_ovpnpasswd"));
        lineEdit_ovpnpasswd->setGeometry(QRect(330, 20, 71, 20));
        PPTPCONFIG = new QGroupBox(Dialog);
        PPTPCONFIG->setObjectName(QString::fromUtf8("PPTPCONFIG"));
        PPTPCONFIG->setGeometry(QRect(390, 280, 401, 51));
        lineEdit_pptpipserver = new QLineEdit(PPTPCONFIG);
        lineEdit_pptpipserver->setObjectName(QString::fromUtf8("lineEdit_pptpipserver"));
        lineEdit_pptpipserver->setGeometry(QRect(60, 20, 91, 20));
        label_14 = new QLabel(PPTPCONFIG);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(0, 20, 61, 21));
        label_14->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lineEdit_pptpuser = new QLineEdit(PPTPCONFIG);
        lineEdit_pptpuser->setObjectName(QString::fromUtf8("lineEdit_pptpuser"));
        lineEdit_pptpuser->setGeometry(QRect(210, 20, 71, 20));
        label_15 = new QLabel(PPTPCONFIG);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(150, 20, 61, 21));
        label_15->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_16 = new QLabel(PPTPCONFIG);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setGeometry(QRect(280, 20, 51, 21));
        label_16->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lineEdit_pptppasswd = new QLineEdit(PPTPCONFIG);
        lineEdit_pptppasswd->setObjectName(QString::fromUtf8("lineEdit_pptppasswd"));
        lineEdit_pptppasswd->setGeometry(QRect(330, 20, 71, 20));
        SERVICEGROUP = new QGroupBox(Dialog);
        SERVICEGROUP->setObjectName(QString::fromUtf8("SERVICEGROUP"));
        SERVICEGROUP->setGeometry(QRect(390, 160, 401, 50));
        gridLayout_2 = new QGridLayout(SERVICEGROUP);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        checkBox_ovpn = new QCheckBox(SERVICEGROUP);
        checkBox_ovpn->setObjectName(QString::fromUtf8("checkBox_ovpn"));

        horizontalLayout_2->addWidget(checkBox_ovpn);

        checkBox_pptp = new QCheckBox(SERVICEGROUP);
        checkBox_pptp->setObjectName(QString::fromUtf8("checkBox_pptp"));

        horizontalLayout_2->addWidget(checkBox_pptp);

        checkBox_telnet = new QCheckBox(SERVICEGROUP);
        checkBox_telnet->setObjectName(QString::fromUtf8("checkBox_telnet"));

        horizontalLayout_2->addWidget(checkBox_telnet);

        checkBox_ssh = new QCheckBox(SERVICEGROUP);
        checkBox_ssh->setObjectName(QString::fromUtf8("checkBox_ssh"));

        horizontalLayout_2->addWidget(checkBox_ssh);

        checkBox_ftp = new QCheckBox(SERVICEGROUP);
        checkBox_ftp->setObjectName(QString::fromUtf8("checkBox_ftp"));

        horizontalLayout_2->addWidget(checkBox_ftp);


        gridLayout_2->addLayout(horizontalLayout_2, 0, 0, 1, 1);

        CONNECT = new QGroupBox(Dialog);
        CONNECT->setObjectName(QString::fromUtf8("CONNECT"));
        CONNECT->setGeometry(QRect(390, 70, 331, 91));
        radioButton_gsm = new QRadioButton(CONNECT);
        radioButton_gsm->setObjectName(QString::fromUtf8("radioButton_gsm"));
        radioButton_gsm->setGeometry(QRect(10, 20, 51, 16));
        radioButton_wifi = new QRadioButton(CONNECT);
        radioButton_wifi->setObjectName(QString::fromUtf8("radioButton_wifi"));
        radioButton_wifi->setGeometry(QRect(10, 40, 51, 16));
        stackedWidget_connect = new QStackedWidget(CONNECT);
        stackedWidget_connect->setObjectName(QString::fromUtf8("stackedWidget_connect"));
        stackedWidget_connect->setGeometry(QRect(60, 20, 271, 31));
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        lineEdit_apn = new QLineEdit(page);
        lineEdit_apn->setObjectName(QString::fromUtf8("lineEdit_apn"));
        lineEdit_apn->setGeometry(QRect(40, 10, 71, 20));
        label_6 = new QLabel(page);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(10, 10, 21, 21));
        label_6->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_8 = new QLabel(page);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(130, 10, 51, 21));
        label_8->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lineEdit_accgprs = new QLineEdit(page);
        lineEdit_accgprs->setObjectName(QString::fromUtf8("lineEdit_accgprs"));
        lineEdit_accgprs->setGeometry(QRect(190, 10, 71, 20));
        stackedWidget_connect->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        label_9 = new QLabel(page_2);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(130, 10, 51, 21));
        label_9->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_10 = new QLabel(page_2);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(0, 10, 31, 21));
        label_10->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lineEdit_wifissid = new QLineEdit(page_2);
        lineEdit_wifissid->setObjectName(QString::fromUtf8("lineEdit_wifissid"));
        lineEdit_wifissid->setGeometry(QRect(40, 10, 71, 20));
        lineEdit_wifipassword = new QLineEdit(page_2);
        lineEdit_wifipassword->setObjectName(QString::fromUtf8("lineEdit_wifipassword"));
        lineEdit_wifipassword->setGeometry(QRect(190, 10, 71, 20));
        stackedWidget_connect->addWidget(page_2);
        label_17 = new QLabel(CONNECT);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setGeometry(QRect(10, 60, 61, 21));
        label_17->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lineEdit_ipserver = new QLineEdit(CONNECT);
        lineEdit_ipserver->setObjectName(QString::fromUtf8("lineEdit_ipserver"));
        lineEdit_ipserver->setGeometry(QRect(80, 60, 91, 20));
        lineEdit_portserver = new QLineEdit(CONNECT);
        lineEdit_portserver->setObjectName(QString::fromUtf8("lineEdit_portserver"));
        lineEdit_portserver->setGeometry(QRect(250, 60, 71, 20));
        label_18 = new QLabel(CONNECT);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setGeometry(QRect(210, 60, 31, 21));
        label_18->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        TAPPINGMODE = new QGroupBox(Dialog);
        TAPPINGMODE->setObjectName(QString::fromUtf8("TAPPINGMODE"));
        TAPPINGMODE->setGeometry(QRect(10, 220, 371, 51));
        radioButton_usb = new QRadioButton(TAPPINGMODE);
        radioButton_usb->setObjectName(QString::fromUtf8("radioButton_usb"));
        radioButton_usb->setGeometry(QRect(10, 20, 41, 21));
        radioButton_serial = new QRadioButton(TAPPINGMODE);
        radioButton_serial->setObjectName(QString::fromUtf8("radioButton_serial"));
        radioButton_serial->setGeometry(QRect(70, 20, 61, 21));
        radioButton_parallel = new QRadioButton(TAPPINGMODE);
        radioButton_parallel->setObjectName(QString::fromUtf8("radioButton_parallel"));
        radioButton_parallel->setGeometry(QRect(140, 20, 81, 21));
        stackedWidget_tappingmode = new QStackedWidget(TAPPINGMODE);
        stackedWidget_tappingmode->setObjectName(QString::fromUtf8("stackedWidget_tappingmode"));
        stackedWidget_tappingmode->setGeometry(QRect(220, 10, 131, 31));
        page_3 = new QWidget();
        page_3->setObjectName(QString::fromUtf8("page_3"));
        comboBox_usbmode = new QComboBox(page_3);
        comboBox_usbmode->setObjectName(QString::fromUtf8("comboBox_usbmode"));
        comboBox_usbmode->setGeometry(QRect(60, 10, 69, 21));
        label_5 = new QLabel(page_3);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(10, 10, 41, 21));
        stackedWidget_tappingmode->addWidget(page_3);
        page_4 = new QWidget();
        page_4->setObjectName(QString::fromUtf8("page_4"));
        label_4 = new QLabel(page_4);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(10, 10, 54, 21));
        lineEdit_baudrate = new QLineEdit(page_4);
        lineEdit_baudrate->setObjectName(QString::fromUtf8("lineEdit_baudrate"));
        lineEdit_baudrate->setGeometry(QRect(60, 10, 71, 20));
        stackedWidget_tappingmode->addWidget(page_4);
        DEVICE = new QGroupBox(Dialog);
        DEVICE->setObjectName(QString::fromUtf8("DEVICE"));
        DEVICE->setGeometry(QRect(10, 70, 371, 141));
        DEVICE->setStyleSheet(QString::fromUtf8(""));
        label_20 = new QLabel(DEVICE);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        label_20->setGeometry(QRect(10, 20, 31, 21));
        label_20->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lineEdit_devicename = new QLineEdit(DEVICE);
        lineEdit_devicename->setObjectName(QString::fromUtf8("lineEdit_devicename"));
        lineEdit_devicename->setGeometry(QRect(50, 20, 113, 20));
        lineEdit_deviceid = new QLineEdit(DEVICE);
        lineEdit_deviceid->setObjectName(QString::fromUtf8("lineEdit_deviceid"));
        lineEdit_deviceid->setGeometry(QRect(240, 20, 113, 20));
        label_21 = new QLabel(DEVICE);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        label_21->setGeometry(QRect(200, 20, 31, 21));
        label_21->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lineEdit_username = new QLineEdit(DEVICE);
        lineEdit_username->setObjectName(QString::fromUtf8("lineEdit_username"));
        lineEdit_username->setGeometry(QRect(50, 50, 113, 20));
        label_22 = new QLabel(DEVICE);
        label_22->setObjectName(QString::fromUtf8("label_22"));
        label_22->setGeometry(QRect(10, 50, 31, 21));
        label_22->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lineEdit_password = new QLineEdit(DEVICE);
        lineEdit_password->setObjectName(QString::fromUtf8("lineEdit_password"));
        lineEdit_password->setGeometry(QRect(240, 50, 113, 20));
        label_23 = new QLabel(DEVICE);
        label_23->setObjectName(QString::fromUtf8("label_23"));
        label_23->setGeometry(QRect(180, 50, 51, 21));
        label_23->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lineEdit_timeout = new QLineEdit(DEVICE);
        lineEdit_timeout->setObjectName(QString::fromUtf8("lineEdit_timeout"));
        lineEdit_timeout->setGeometry(QRect(72, 80, 91, 20));
        label_24 = new QLabel(DEVICE);
        label_24->setObjectName(QString::fromUtf8("label_24"));
        label_24->setGeometry(QRect(10, 80, 51, 21));
        label_24->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lineEdit_ssinterval = new QLineEdit(DEVICE);
        lineEdit_ssinterval->setObjectName(QString::fromUtf8("lineEdit_ssinterval"));
        lineEdit_ssinterval->setGeometry(QRect(240, 80, 113, 20));
        label_25 = new QLabel(DEVICE);
        label_25->setObjectName(QString::fromUtf8("label_25"));
        label_25->setGeometry(QRect(170, 80, 61, 21));
        label_25->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_26 = new QLabel(DEVICE);
        label_26->setObjectName(QString::fromUtf8("label_26"));
        label_26->setGeometry(QRect(10, 110, 71, 21));
        label_26->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        comboBox_sendingmode = new QComboBox(DEVICE);
        comboBox_sendingmode->setObjectName(QString::fromUtf8("comboBox_sendingmode"));
        comboBox_sendingmode->setGeometry(QRect(90, 110, 71, 22));
        lineEdit_key = new QLineEdit(DEVICE);
        lineEdit_key->setObjectName(QString::fromUtf8("lineEdit_key"));
        lineEdit_key->setGeometry(QRect(240, 110, 113, 20));
        label_27 = new QLabel(DEVICE);
        label_27->setObjectName(QString::fromUtf8("label_27"));
        label_27->setGeometry(QRect(200, 110, 31, 21));
        label_27->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        widget_alarm = new QWidget(Dialog);
        widget_alarm->setObjectName(QString::fromUtf8("widget_alarm"));
        widget_alarm->setGeometry(QRect(10, 480, 781, 111));
        widget_alarm->setStyleSheet(QString::fromUtf8("background-color: rgb(219, 219, 219);"));
        label_power = new QLabel(widget_alarm);
        label_power->setObjectName(QString::fromUtf8("label_power"));
        label_power->setGeometry(QRect(20, 50, 101, 20));
        label_power->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 255);"));
        label_power->setAlignment(Qt::AlignCenter);
        label_serial = new QLabel(widget_alarm);
        label_serial->setObjectName(QString::fromUtf8("label_serial"));
        label_serial->setGeometry(QRect(150, 50, 101, 20));
        label_serial->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 255);"));
        label_serial->setAlignment(Qt::AlignCenter);
        label_parallel = new QLabel(widget_alarm);
        label_parallel->setObjectName(QString::fromUtf8("label_parallel"));
        label_parallel->setGeometry(QRect(280, 50, 101, 20));
        label_parallel->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 255);"));
        label_parallel->setAlignment(Qt::AlignCenter);
        label_usb = new QLabel(widget_alarm);
        label_usb->setObjectName(QString::fromUtf8("label_usb"));
        label_usb->setGeometry(QRect(410, 50, 101, 20));
        label_usb->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 255);"));
        label_usb->setAlignment(Qt::AlignCenter);
        label_battery = new QLabel(widget_alarm);
        label_battery->setObjectName(QString::fromUtf8("label_battery"));
        label_battery->setGeometry(QRect(540, 50, 101, 20));
        label_battery->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 255);"));
        label_battery->setAlignment(Qt::AlignCenter);
        label_sd = new QLabel(widget_alarm);
        label_sd->setObjectName(QString::fromUtf8("label_sd"));
        label_sd->setGeometry(QRect(670, 50, 101, 20));
        label_sd->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 255);"));
        label_sd->setAlignment(Qt::AlignCenter);
        layoutWidget = new QWidget(widget_alarm);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(70, 10, 624, 16));
        horizontalLayout_4 = new QHBoxLayout(layoutWidget);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        label_7 = new QLabel(layoutWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        QFont font1;
        font1.setBold(true);
        font1.setWeight(75);
        label_7->setFont(font1);

        horizontalLayout_4->addWidget(label_7);

        label_signal = new QLabel(layoutWidget);
        label_signal->setObjectName(QString::fromUtf8("label_signal"));
        label_signal->setStyleSheet(QString::fromUtf8("color: rgb(255, 85, 0);"));

        horizontalLayout_4->addWidget(label_signal);

        label_28 = new QLabel(layoutWidget);
        label_28->setObjectName(QString::fromUtf8("label_28"));
        label_28->setFont(font1);

        horizontalLayout_4->addWidget(label_28);

        label_localip = new QLabel(layoutWidget);
        label_localip->setObjectName(QString::fromUtf8("label_localip"));
        label_localip->setStyleSheet(QString::fromUtf8("color: rgb(255, 85, 0);"));

        horizontalLayout_4->addWidget(label_localip);

        label_29 = new QLabel(layoutWidget);
        label_29->setObjectName(QString::fromUtf8("label_29"));
        label_29->setFont(font1);

        horizontalLayout_4->addWidget(label_29);

        label_rtctime = new QLabel(layoutWidget);
        label_rtctime->setObjectName(QString::fromUtf8("label_rtctime"));
        label_rtctime->setStyleSheet(QString::fromUtf8("color: rgb(255, 85, 0);"));

        horizontalLayout_4->addWidget(label_rtctime);

        label_30 = new QLabel(layoutWidget);
        label_30->setObjectName(QString::fromUtf8("label_30"));
        label_30->setFont(font1);

        horizontalLayout_4->addWidget(label_30);

        label_systime = new QLabel(layoutWidget);
        label_systime->setObjectName(QString::fromUtf8("label_systime"));
        label_systime->setStyleSheet(QString::fromUtf8("color: rgb(255, 85, 0);"));

        horizontalLayout_4->addWidget(label_systime);

        pushButton_download = new QPushButton(Dialog);
        pushButton_download->setObjectName(QString::fromUtf8("pushButton_download"));
        pushButton_download->setGeometry(QRect(730, 110, 61, 21));
        pushButton_login = new QPushButton(Dialog);
        pushButton_login->setObjectName(QString::fromUtf8("pushButton_login"));
        pushButton_login->setGeometry(QRect(730, 80, 61, 21));
        pushButton_update = new QPushButton(Dialog);
        pushButton_update->setObjectName(QString::fromUtf8("pushButton_update"));
        pushButton_update->setGeometry(QRect(730, 140, 61, 21));
        textEdit_receipt = new QTextEdit(Dialog);
        textEdit_receipt->setObjectName(QString::fromUtf8("textEdit_receipt"));
        textEdit_receipt->setGeometry(QRect(10, 340, 451, 131));

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
        label_19->setText(QApplication::translate("Dialog", "Serial Number", 0, QApplication::UnicodeUTF8));
        pushButton_port->setText(QApplication::translate("Dialog", "Open Port", 0, QApplication::UnicodeUTF8));
        ALARMGROUP->setTitle(QApplication::translate("Dialog", "ALARM GROUP", 0, QApplication::UnicodeUTF8));
        checkBox_ALARM_1->setText(QApplication::translate("Dialog", "ALARM1", 0, QApplication::UnicodeUTF8));
        checkBox_ALARM_2->setText(QApplication::translate("Dialog", "ALARM2", 0, QApplication::UnicodeUTF8));
        checkBox_ALARM_3->setText(QApplication::translate("Dialog", "ALARM3", 0, QApplication::UnicodeUTF8));
        checkBox_ALARM_4->setText(QApplication::translate("Dialog", "ALARM4", 0, QApplication::UnicodeUTF8));
        checkBox_ALARM_5->setText(QApplication::translate("Dialog", "ALARM5", 0, QApplication::UnicodeUTF8));
        checkBox_ALARM_6->setText(QApplication::translate("Dialog", "ALARM6", 0, QApplication::UnicodeUTF8));
        checkBox_ALARM_7->setText(QApplication::translate("Dialog", "ALARM7", 0, QApplication::UnicodeUTF8));
        checkBox_ALARM_8->setText(QApplication::translate("Dialog", "ALARM8", 0, QApplication::UnicodeUTF8));
        checkBox_ALARM_9->setText(QApplication::translate("Dialog", "ALARM9", 0, QApplication::UnicodeUTF8));
        checkBox_ALARM_10->setText(QApplication::translate("Dialog", "ALARM10", 0, QApplication::UnicodeUTF8));
        checkBox_ALARM_11->setText(QApplication::translate("Dialog", "ALARM11", 0, QApplication::UnicodeUTF8));
        checkBox_ALARM_12->setText(QApplication::translate("Dialog", "ALARM12", 0, QApplication::UnicodeUTF8));
        OVPNCONFIG->setTitle(QApplication::translate("Dialog", "OVPN CONFIG", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("Dialog", "SERVER IP", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("Dialog", "USERNAME", 0, QApplication::UnicodeUTF8));
        label_13->setText(QApplication::translate("Dialog", "PASSWD", 0, QApplication::UnicodeUTF8));
        PPTPCONFIG->setTitle(QApplication::translate("Dialog", "PPTP CONFIG", 0, QApplication::UnicodeUTF8));
        label_14->setText(QApplication::translate("Dialog", "SERVER IP", 0, QApplication::UnicodeUTF8));
        label_15->setText(QApplication::translate("Dialog", "USERNAME", 0, QApplication::UnicodeUTF8));
        label_16->setText(QApplication::translate("Dialog", "PASSWD", 0, QApplication::UnicodeUTF8));
        SERVICEGROUP->setTitle(QApplication::translate("Dialog", "SERVICE GROUP", 0, QApplication::UnicodeUTF8));
        checkBox_ovpn->setText(QApplication::translate("Dialog", "OVPN", 0, QApplication::UnicodeUTF8));
        checkBox_pptp->setText(QApplication::translate("Dialog", "PPTP", 0, QApplication::UnicodeUTF8));
        checkBox_telnet->setText(QApplication::translate("Dialog", "TELNET", 0, QApplication::UnicodeUTF8));
        checkBox_ssh->setText(QApplication::translate("Dialog", "SSH", 0, QApplication::UnicodeUTF8));
        checkBox_ftp->setText(QApplication::translate("Dialog", "FTP", 0, QApplication::UnicodeUTF8));
        CONNECT->setTitle(QApplication::translate("Dialog", "CONNECT", 0, QApplication::UnicodeUTF8));
        radioButton_gsm->setText(QApplication::translate("Dialog", "GSM", 0, QApplication::UnicodeUTF8));
        radioButton_wifi->setText(QApplication::translate("Dialog", "WIFI", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("Dialog", "APN", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("Dialog", "ACCGPRS", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("Dialog", "PASSWORD", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("Dialog", "SSID", 0, QApplication::UnicodeUTF8));
        label_17->setText(QApplication::translate("Dialog", "SERVER IP", 0, QApplication::UnicodeUTF8));
        lineEdit_portserver->setText(QString());
        label_18->setText(QApplication::translate("Dialog", "PPORT", 0, QApplication::UnicodeUTF8));
        TAPPINGMODE->setTitle(QApplication::translate("Dialog", "TAPPING MODE", 0, QApplication::UnicodeUTF8));
        radioButton_usb->setText(QApplication::translate("Dialog", "USB", 0, QApplication::UnicodeUTF8));
        radioButton_serial->setText(QApplication::translate("Dialog", "SERIAL", 0, QApplication::UnicodeUTF8));
        radioButton_parallel->setText(QApplication::translate("Dialog", "PARALLEL", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("Dialog", "USBMODE", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("Dialog", "BAUDRATE", 0, QApplication::UnicodeUTF8));
        DEVICE->setTitle(QApplication::translate("Dialog", "DEVICE", 0, QApplication::UnicodeUTF8));
        label_20->setText(QApplication::translate("Dialog", "NAME", 0, QApplication::UnicodeUTF8));
        lineEdit_deviceid->setText(QString());
        label_21->setText(QApplication::translate("Dialog", "ID", 0, QApplication::UnicodeUTF8));
        label_22->setText(QApplication::translate("Dialog", "USER", 0, QApplication::UnicodeUTF8));
        label_23->setText(QApplication::translate("Dialog", "PASSWORD", 0, QApplication::UnicodeUTF8));
        label_24->setText(QApplication::translate("Dialog", "TIMEOUT", 0, QApplication::UnicodeUTF8));
        label_25->setText(QApplication::translate("Dialog", "SSINTERVAL", 0, QApplication::UnicodeUTF8));
        label_26->setText(QApplication::translate("Dialog", "SENDINGMODE", 0, QApplication::UnicodeUTF8));
        label_27->setText(QApplication::translate("Dialog", "KEY", 0, QApplication::UnicodeUTF8));
        label_power->setText(QString());
        label_serial->setText(QString());
        label_parallel->setText(QString());
        label_usb->setText(QString());
        label_battery->setText(QString());
        label_sd->setText(QString());
        label_7->setText(QApplication::translate("Dialog", "SIGNAL:", 0, QApplication::UnicodeUTF8));
        label_signal->setText(QString());
        label_28->setText(QApplication::translate("Dialog", "LOCAL IP:", 0, QApplication::UnicodeUTF8));
        label_localip->setText(QApplication::translate("Dialog", "0.0.0.0", 0, QApplication::UnicodeUTF8));
        label_29->setText(QApplication::translate("Dialog", "RTC TIME:", 0, QApplication::UnicodeUTF8));
        label_rtctime->setText(QString());
        label_30->setText(QApplication::translate("Dialog", "SYS TIME:", 0, QApplication::UnicodeUTF8));
        label_systime->setText(QString());
        pushButton_download->setText(QApplication::translate("Dialog", "DOWNLOAD", 0, QApplication::UnicodeUTF8));
        pushButton_login->setText(QApplication::translate("Dialog", "LOGIN", 0, QApplication::UnicodeUTF8));
        pushButton_update->setText(QApplication::translate("Dialog", "UPDATE", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
