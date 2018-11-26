#include "dialog.h"
#include "ui_dialog.h"
#include <QDebug>

#include "rs232thread.h"
#include "configure.h"
#include "switchbutton.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    this->setWindowTitle("GLOG TEST");

    initPort();

    ui->textEdit->setReadOnly(true);

    QStringList MODE;
    MODE << "TXT" << "CMP" << "ENC" << "CNC";
    ui->comboBox_sendingmode->addItems(MODE);

    MODE.clear();
    MODE << "HIGHSPEED" << "LOWSPEED";
    ui->comboBox_usbmode->addItems(MODE);

    ui->lineEdit_deviceid->setReadOnly(true);
    ui->lineEdit_username->setReadOnly(true);
    ui->lineEdit_password->setReadOnly(true);

    myconfigure = new configure;

    powerstate = false;
    serialstate = false;
    parallelstate = false;
    usbstate = false;

    powerbtn = new SwitchButton(ui->widget_alarm);
    powerbtn->setGeometry(20, 70, 101, 23);
    powerbtn->setButtonStyle(powerbtn->ButtonStyle_Image);
    powerbtn->setImage(QString(":/images/icons/powerstate.jpg"), QString(":/images/icons/powerconnet.jpg"));
    powerbtn->setEnabled(false);

    serialbtn = new SwitchButton(ui->widget_alarm);
    serialbtn->setGeometry(150, 70, 101, 23);
    serialbtn->setButtonStyle(serialbtn->ButtonStyle_Image);
    serialbtn->setImage(QString(":/images/icons/serialstate.jpg"), QString(":/images/icons/serialconnect.jpg"));
    serialbtn->setEnabled(false);

    parallelbtn = new SwitchButton(ui->widget_alarm);
    parallelbtn->setGeometry(280, 70, 101, 23);
    parallelbtn->setButtonStyle(parallelbtn->ButtonStyle_Image);
    parallelbtn->setImage(QString(":/images/icons/parallstate.jpg"), QString(":/images/icons/parallconnect.jpg"));
    parallelbtn->setEnabled(false);

    usbbtn = new SwitchButton(ui->widget_alarm);
    usbbtn->setGeometry(410, 70, 101, 23);
    usbbtn->setButtonStyle(usbbtn->ButtonStyle_Image);
    usbbtn->setImage(QString(":/images/icons/usbstate.jpg"), QString(":/images/icons/usbconnect.jpg"));
    usbbtn->setEnabled(false);

    batterybtn = new SwitchButton(ui->widget_alarm);
    batterybtn->setGeometry(540, 70, 101, 23);
    batterybtn->setButtonStyle(batterybtn->ButtonStyle_Image);
    batterybtn->setImage(QString(":/images/icons/batterystate.jpg"), QString(":/images/icons/batterystate.jpg"));
    batterybtn->setEnabled(false);

    sdbtn = new SwitchButton(ui->widget_alarm);
    sdbtn->setGeometry(670, 70, 101, 23);
    sdbtn->setButtonStyle(sdbtn->ButtonStyle_Image);
    sdbtn->setImage(QString(":/images/icons/sdstate.jpg"), QString(":/images/icons/sdstate.jpg"));
    sdbtn->setEnabled(false);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::initPort()
{
    ui->comboBox_serial->clear();
    QStringList list;
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        QSerialPort serial;
        serial.setPort(info);
        if (serial.open(QIODevice::ReadWrite))
        {
            list << info.portName();
            serial.close();
        }
    }
    qSort(list.begin(), list.end());
    ui->comboBox_serial->addItems(list);

    list.clear();
    list << "115200";
    ui->comboBox_baudrate->addItems(list);

    list.clear();
    list << "1";
    ui->comboBox_stopbits->addItems(list);

    list.clear();
    list << "None";
    ui->comboBox_parity->addItems(list);

    myserial = new QSerialPort();
    com_opened = false;
    com_stopped = true;
    tx_event = false;
    rx_event = true;
}

int Dialog::PortOpen()
{
    com_opened = true;
    com_stopped = false;

    ui->pushButton_port->setText("Close Port");

    return 0;
}

int Dialog::PortClose()
{
    com_opened = false;
    com_stopped = true;

    ui->pushButton_port->setText("Open Port");
    mythread->closemyserial();

    return 0;
}

int Dialog::PortWrite()
{
    if(com_opened)
    {
        myserial->clear(QSerialPort::AllDirections);
        myserial->write(TxData);

        myserial->waitForBytesWritten(1);
    }

    return 0;
}

int Dialog::PortRead()
{
    if(com_opened)
    {
        if (myserial->waitForReadyRead(1000))//1s
        {
            RxData = myserial->readAll();
            while(myserial->waitForReadyRead(1))
                RxData += myserial->readAll();
        }
    }

    return 0;
}

QString Dialog::ParameterSet()
{
    char value[VAR_VALUE_LEN];

    QString varvalue, varbuff;
    QByteArray chardata;

    varbuff.clear();

    //DEVICE
    varvalue = ui->lineEdit_devicename->text();
    chardata = varvalue.toLocal8Bit();
    memset(value, 0, sizeof(value));
    memcpy(value, chardata.data(), chardata.size());
    varbuff += myconfigure->Set_Configure(value, DEVICENAME);

    varvalue = ui->lineEdit_timeout->text();
    chardata = varvalue.toLocal8Bit();
    memset(value, 0, sizeof(value));
    memcpy(value, chardata.data(), chardata.size());
    varbuff += myconfigure->Set_Configure(value, TIMEOUT);

    varvalue = ui->lineEdit_ssinterval->text();
    chardata = varvalue.toLocal8Bit();
    memset(value, 0, sizeof(value));
    memcpy(value, chardata.data(), chardata.size());
    varbuff += myconfigure->Set_Configure(value, SSINTERVAL);

    varvalue = ui->comboBox_sendingmode->currentText();
    chardata = varvalue.toLocal8Bit();
    memset(value, 0, sizeof(value));
    memcpy(value, chardata.data(), chardata.size());
    varbuff += myconfigure->Set_Configure(value, SENDINGMODE);

    varvalue = ui->lineEdit_key->text();
    chardata = varvalue.toLocal8Bit();
    memset(value, 0, sizeof(value));
    memcpy(value, chardata.data(), chardata.size());
    varbuff += myconfigure->Set_Configure(value, KEY);

    //TAPPING MODE
    varvalue.clear();
    if(ui->radioButton_usb->isChecked()){
        varvalue.append("USB");
    }
    else if(ui->radioButton_serial->isChecked()){
        varvalue.append("SERIAL");
    }
    else{
        varvalue.append("PARALLEL");
    }
    chardata = varvalue.toLocal8Bit();
    memset(value, 0, sizeof(value));
    memcpy(value, chardata.data(), chardata.size());
    varbuff += myconfigure->Set_Configure(value, TAPPINGMODE);

    varvalue = ui->comboBox_usbmode->currentText();
    chardata = varvalue.toLocal8Bit();
    memset(value, 0, sizeof(value));
    memcpy(value, chardata.data(), chardata.size());
    varbuff += myconfigure->Set_Configure(value, USBMODE);

    varvalue = ui->lineEdit_baudrate->text();
    chardata = varvalue.toLocal8Bit();
    memset(value, 0, sizeof(value));
    memcpy(value, chardata.data(), chardata.size());
    varbuff += myconfigure->Set_Configure(value, SERIALBAUDRATE);

    //ALARM GROUP
    varvalue.clear();
    if(ui->checkBox_ALARM_1->isChecked()){
        varvalue.append("1");
    }else{
        varvalue.append("0");
    }
    chardata = varvalue.toLocal8Bit();
    memset(value, 0, sizeof(value));
    memcpy(value, chardata.data(), chardata.size());
    varbuff += myconfigure->Set_Configure(value, ALARM1);

    varvalue.clear();
    if(ui->checkBox_ALARM_2->isChecked()){
        varvalue.append("1");
    }else{
        varvalue.append("0");
    }
    chardata = varvalue.toLocal8Bit();
    memset(value, 0, sizeof(value));
    memcpy(value, chardata.data(), chardata.size());
    varbuff += myconfigure->Set_Configure(value, ALARM2);

    varvalue.clear();
    if(ui->checkBox_ALARM_3->isChecked()){
        varvalue.append("1");
    }else{
        varvalue.append("0");
    }
    chardata = varvalue.toLocal8Bit();
    memset(value, 0, sizeof(value));
    memcpy(value, chardata.data(), chardata.size());
    varbuff += myconfigure->Set_Configure(value, ALARM3);

    varvalue.clear();
    if(ui->checkBox_ALARM_4->isChecked()){
        varvalue.append("1");
    }else{
        varvalue.append("0");
    }
    chardata = varvalue.toLocal8Bit();
    memset(value, 0, sizeof(value));
    memcpy(value, chardata.data(), chardata.size());
    varbuff += myconfigure->Set_Configure(value, ALARM4);

    varvalue.clear();
    if(ui->checkBox_ALARM_5->isChecked()){
        varvalue.append("1");
    }else{
        varvalue.append("0");
    }
    chardata = varvalue.toLocal8Bit();
    memset(value, 0, sizeof(value));
    memcpy(value, chardata.data(), chardata.size());
    varbuff += myconfigure->Set_Configure(value, ALARM5);

    varvalue.clear();
    if(ui->checkBox_ALARM_6->isChecked()){
        varvalue.append("1");
    }else{
        varvalue.append("0");
    }
    chardata = varvalue.toLocal8Bit();
    memset(value, 0, sizeof(value));
    memcpy(value, chardata.data(), chardata.size());
    varbuff += myconfigure->Set_Configure(value, ALARM6);

    varvalue.clear();
    if(ui->checkBox_ALARM_7->isChecked()){
        varvalue.append("1");
    }else{
        varvalue.append("0");
    }
    chardata = varvalue.toLocal8Bit();
    memset(value, 0, sizeof(value));
    memcpy(value, chardata.data(), chardata.size());
    varbuff += myconfigure->Set_Configure(value, ALARM7);

    varvalue.clear();
    if(ui->checkBox_ALARM_8->isChecked()){
        varvalue.append("1");
    }else{
        varvalue.append("0");
    }
    chardata = varvalue.toLocal8Bit();
    memset(value, 0, sizeof(value));
    memcpy(value, chardata.data(), chardata.size());
    varbuff += myconfigure->Set_Configure(value, ALARM8);

    varvalue.clear();
    if(ui->checkBox_ALARM_9->isChecked()){
        varvalue.append("1");
    }else{
        varvalue.append("0");
    }
    chardata = varvalue.toLocal8Bit();
    memset(value, 0, sizeof(value));
    memcpy(value, chardata.data(), chardata.size());
    varbuff += myconfigure->Set_Configure(value, ALARM9);

    varvalue.clear();
    if(ui->checkBox_ALARM_10->isChecked()){
        varvalue.append("1");
    }else{
        varvalue.append("0");
    }
    chardata = varvalue.toLocal8Bit();
    memset(value, 0, sizeof(value));
    memcpy(value, chardata.data(), chardata.size());
    varbuff += myconfigure->Set_Configure(value, ALARM10);

    varvalue.clear();
    if(ui->checkBox_ALARM_11->isChecked()){
        varvalue.append("1");
    }else{
        varvalue.append("0");
    }
    chardata = varvalue.toLocal8Bit();
    memset(value, 0, sizeof(value));
    memcpy(value, chardata.data(), chardata.size());
    varbuff += myconfigure->Set_Configure(value, ALARM11);

    varvalue.clear();
    if(ui->checkBox_ALARM_12->isChecked()){
        varvalue.append("1");
    }else{
        varvalue.append("0");
    }
    chardata = varvalue.toLocal8Bit();
    memset(value, 0, sizeof(value));
    memcpy(value, chardata.data(), chardata.size());
    varbuff += myconfigure->Set_Configure(value, ALARM12);

    //CONNECT
    varvalue.clear();
    if(ui->radioButton_gsm->isChecked()){
        varvalue.append("GSM");
    }else if(ui->radioButton_wifi->isChecked()){
        varvalue.append("WIFI");
    }
    chardata = varvalue.toLocal8Bit();
    memset(value, 0, sizeof(value));
    memcpy(value, chardata.data(), chardata.size());
    varbuff += myconfigure->Set_Configure(value, CONNMODE);

    varvalue = ui->lineEdit_apn->text();
    chardata = varvalue.toLocal8Bit();
    memset(value, 0, sizeof(value));
    memcpy(value, chardata.data(), chardata.size());
    varbuff += myconfigure->Set_Configure(value, APN);

    varvalue = ui->lineEdit_accgprs->text();
    chardata = varvalue.toLocal8Bit();
    memset(value, 0, sizeof(value));
    memcpy(value, chardata.data(), chardata.size());
    varbuff += myconfigure->Set_Configure(value, ACCGPRS);

    varvalue = ui->lineEdit_wifissid->text();
    chardata = varvalue.toLocal8Bit();
    memset(value, 0, sizeof(value));
    memcpy(value, chardata.data(), chardata.size());
    varbuff += myconfigure->Set_Configure(value, WIFISSID);

    varvalue = ui->lineEdit_wifipassword->text();
    chardata = varvalue.toLocal8Bit();
    memset(value, 0, sizeof(value));
    memcpy(value, chardata.data(), chardata.size());
    varbuff += myconfigure->Set_Configure(value, WIFIPASSWORD);

    varvalue = ui->lineEdit_ipserver->text();
    chardata = varvalue.toLocal8Bit();
    memset(value, 0, sizeof(value));
    memcpy(value, chardata.data(), chardata.size());
    varbuff += myconfigure->Set_Configure(value, IPSERVER);

    varvalue = ui->lineEdit_portserver->text();
    chardata = varvalue.toLocal8Bit();
    memset(value, 0, sizeof(value));
    memcpy(value, chardata.data(), chardata.size());
    varbuff += myconfigure->Set_Configure(value, PORTSERVER);

    //SERVICE GROUP
    varvalue.clear();
    if(ui->checkBox_ovpn->isChecked()){
        varvalue.append("ENABLE");
    }else{
        varvalue.append("DISABLE");
    }
    chardata = varvalue.toLocal8Bit();
    memset(value, 0, sizeof(value));
    memcpy(value, chardata.data(), chardata.size());
    varbuff += myconfigure->Set_Configure(value, OVPNSERVICE);

    varvalue.clear();
    if(ui->checkBox_pptp->isChecked()){
        varvalue.append("ENABLE");
    }else{
        varvalue.append("DISABLE");
    }
    chardata = varvalue.toLocal8Bit();
    memset(value, 0, sizeof(value));
    memcpy(value, chardata.data(), chardata.size());
    varbuff += myconfigure->Set_Configure(value, PPTPSERVICE);

    varvalue.clear();
    if(ui->checkBox_telnet->isChecked()){
        varvalue.append("ENABLE");
    }else{
        varvalue.append("DISABLE");
    }
    chardata = varvalue.toLocal8Bit();
    memset(value, 0, sizeof(value));
    memcpy(value, chardata.data(), chardata.size());
    varbuff += myconfigure->Set_Configure(value, TELNETSERVICE);

    varvalue.clear();
    if(ui->checkBox_ssh->isChecked()){
        varvalue.append("ENABLE");
    }else{
        varvalue.append("DISABLE");
    }
    chardata = varvalue.toLocal8Bit();
    memset(value, 0, sizeof(value));
    memcpy(value, chardata.data(), chardata.size());
    varbuff += myconfigure->Set_Configure(value, SSHSERVICE);

    varvalue.clear();
    if(ui->checkBox_ftp->isChecked()){
        varvalue.append("ENABLE");
    }else{
        varvalue.append("DISABLE");
    }
    chardata = varvalue.toLocal8Bit();
    memset(value, 0, sizeof(value));
    memcpy(value, chardata.data(), chardata.size());
    varbuff += myconfigure->Set_Configure(value, FTPSERVICE);

    //OVPN CONFIG
    varvalue = ui->lineEdit_ovpnipserver->text();
    chardata = varvalue.toLocal8Bit();
    memset(value, 0, sizeof(value));
    memcpy(value, chardata.data(), chardata.size());
    varbuff += myconfigure->Set_Configure(value, OVPNIPSERVER);

    varvalue = ui->lineEdit_ovpnuser->text();
    chardata = varvalue.toLocal8Bit();
    memset(value, 0, sizeof(value));
    memcpy(value, chardata.data(), chardata.size());
    varbuff += myconfigure->Set_Configure(value, OVPNUSER);

    varvalue = ui->lineEdit_ovpnpasswd->text();
    chardata = varvalue.toLocal8Bit();
    memset(value, 0, sizeof(value));
    memcpy(value, chardata.data(), chardata.size());
    varbuff += myconfigure->Set_Configure(value, OVPNPASSWD);

    //PPTP CONFIG
    varvalue = ui->lineEdit_pptpipserver->text();
    chardata = varvalue.toLocal8Bit();
    memset(value, 0, sizeof(value));
    memcpy(value, chardata.data(), chardata.size());
    varbuff += myconfigure->Set_Configure(value, PPTPIPSERVER);

    varvalue = ui->lineEdit_pptpuser->text();
    chardata = varvalue.toLocal8Bit();
    memset(value, 0, sizeof(value));
    memcpy(value, chardata.data(), chardata.size());
    varbuff += myconfigure->Set_Configure(value, PPTPUSER);

    varvalue = ui->lineEdit_pptppasswd->text();
    chardata = varvalue.toLocal8Bit();
    memset(value, 0, sizeof(value));
    memcpy(value, chardata.data(), chardata.size());
    varbuff += myconfigure->Set_Configure(value, PPTPPASSWD);

    return varbuff;
}

void Dialog::ParameterDisplay()
{
    //DEVICE
    ui->lineEdit_devicename->setText(myconfigure->parametervalue(DEVICENAME));
    ui->lineEdit_deviceid->setText(myconfigure->parametervalue(DEVICEID));
    ui->lineEdit_username->setText(myconfigure->parametervalue(USERNAME));
    ui->lineEdit_password->setText(myconfigure->parametervalue(PASSWORD));
    ui->lineEdit_timeout->setText(myconfigure->parametervalue(TIMEOUT));
    ui->lineEdit_ssinterval->setText(myconfigure->parametervalue(SSINTERVAL));
    if(myconfigure->parametervalue(SENDINGMODE).contains("TXT")){
        ui->comboBox_sendingmode->setCurrentIndex(0);
    }else if(myconfigure->parametervalue(SENDINGMODE).contains("CMP")){
        ui->comboBox_sendingmode->setCurrentIndex(1);
    }else if(myconfigure->parametervalue(SENDINGMODE).contains("ENC")){
        ui->comboBox_sendingmode->setCurrentIndex(2);
    }else if(myconfigure->parametervalue(SENDINGMODE).contains("CNC")){
        ui->comboBox_sendingmode->setCurrentIndex(3);
    }else{
        ui->comboBox_sendingmode->setCurrentIndex(0);
    }
    ui->lineEdit_key->setText(myconfigure->parametervalue(KEY));

    //TAPPING MODE
    if(myconfigure->parametervalue(TAPPINGMODE).contains("USB"))
    {
        ui->radioButton_usb->setChecked(true);
    }
    else if(myconfigure->parametervalue(TAPPINGMODE).contains("SERIAL"))
    {
        ui->radioButton_serial->setChecked(true);
    }
    else if(myconfigure->parametervalue(TAPPINGMODE).contains("PARALLEL"))
    {
        ui->radioButton_parallel->setChecked(true);
    }

    if(myconfigure->parametervalue(USBMODE).contains("HIGHSPEED"))
    {
        ui->comboBox_usbmode->setCurrentIndex(0);
    }
    else if(myconfigure->parametervalue(USBMODE).contains("LOWSPEED"))
    {
        ui->comboBox_usbmode->setCurrentIndex(1);
    }else{
        ui->comboBox_usbmode->setCurrentIndex(0);
    }
    ui->lineEdit_baudrate->setText(myconfigure->parametervalue(SERIALBAUDRATE));

    //ALARM GROUP
    if(myconfigure->parametervalue(ALARM1).contains("1"))
    {
        ui->checkBox_ALARM_1->setChecked(true);
    }
    else
    {
        ui->checkBox_ALARM_1->setChecked(false);
    }

    if(myconfigure->parametervalue(ALARM2).contains("1"))
    {
        ui->checkBox_ALARM_2->setChecked(true);
    }
    else
    {
        ui->checkBox_ALARM_2->setChecked(false);
    }

    if(myconfigure->parametervalue(ALARM3).contains("1"))
    {
        ui->checkBox_ALARM_3->setChecked(true);
    }
    else
    {
        ui->checkBox_ALARM_3->setChecked(false);
    }

    if(myconfigure->parametervalue(ALARM4).contains("1"))
    {
        ui->checkBox_ALARM_4->setChecked(true);
    }
    else
    {
        ui->checkBox_ALARM_4->setChecked(false);
    }

    if(myconfigure->parametervalue(ALARM5).contains("1"))
    {
        ui->checkBox_ALARM_5->setChecked(true);
    }
    else
    {
        ui->checkBox_ALARM_5->setChecked(false);
    }

    if(myconfigure->parametervalue(ALARM6).contains("1"))
    {
        ui->checkBox_ALARM_6->setChecked(true);
    }
    else
    {
        ui->checkBox_ALARM_6->setChecked(false);
    }

    if(myconfigure->parametervalue(ALARM7).contains("1"))
    {
        ui->checkBox_ALARM_7->setChecked(true);
    }
    else
    {
        ui->checkBox_ALARM_7->setChecked(false);
    }

    if(myconfigure->parametervalue(ALARM8).contains("1"))
    {
        ui->checkBox_ALARM_8->setChecked(true);
    }
    else
    {
        ui->checkBox_ALARM_8->setChecked(false);
    }

    if(myconfigure->parametervalue(ALARM9).contains("1"))
    {
        ui->checkBox_ALARM_9->setChecked(true);
    }
    else
    {
        ui->checkBox_ALARM_9->setChecked(false);
    }

    if(myconfigure->parametervalue(ALARM10).contains("1"))
    {
        ui->checkBox_ALARM_10->setChecked(true);
    }
    else
    {
        ui->checkBox_ALARM_10->setChecked(false);
    }

    if(myconfigure->parametervalue(ALARM11).contains("1"))
    {
        ui->checkBox_ALARM_11->setChecked(true);
    }
    else
    {
        ui->checkBox_ALARM_11->setChecked(false);
    }

    if(myconfigure->parametervalue(ALARM12).contains("1"))
    {
        ui->checkBox_ALARM_12->setChecked(true);
    }
    else
    {
        ui->checkBox_ALARM_12->setChecked(false);
    }

    //CONNECT
    if(myconfigure->parametervalue(CONNMODE).contains("GSM"))
    {
        ui->radioButton_gsm->setChecked(true);
    }
    else if(myconfigure->parametervalue(CONNMODE).contains("WIFI"))
    {
        ui->radioButton_wifi->setChecked(true);
    }

    ui->lineEdit_apn->setText(myconfigure->parametervalue(APN));
    ui->lineEdit_accgprs->setText(myconfigure->parametervalue(ACCGPRS));
    ui->lineEdit_wifissid->setText(myconfigure->parametervalue(WIFISSID));
    ui->lineEdit_wifipassword->setText(myconfigure->parametervalue(WIFIPASSWORD));

    ui->lineEdit_ipserver->setText(myconfigure->parametervalue(IPSERVER));
    ui->lineEdit_portserver->setText(myconfigure->parametervalue(PORTSERVER));

    //SERVICE GROUP
    if(myconfigure->parametervalue(OVPNSERVICE).contains("ENABLE"))
    {
        ui->checkBox_ovpn->setChecked(true);
    }else{
        ui->checkBox_ovpn->setChecked(false);
    }

    if(myconfigure->parametervalue(PPTPSERVICE).contains("ENABLE"))
    {
        ui->checkBox_pptp->setChecked(true);
    }else{
        ui->checkBox_pptp->setChecked(false);
    }

    if(myconfigure->parametervalue(TELNETSERVICE).contains("ENABLE"))
    {
        ui->checkBox_telnet->setChecked(true);
    }else{
        ui->checkBox_telnet->setChecked(false);
    }

    if(myconfigure->parametervalue(SSHSERVICE).contains("ENABLE"))
    {
        ui->checkBox_ssh->setChecked(true);
    }else{
        ui->checkBox_ssh->setChecked(false);
    }

    if(myconfigure->parametervalue(FTPSERVICE).contains("ENABLE"))
    {
        ui->checkBox_ftp->setChecked(true);
    }else{
        ui->checkBox_ftp->setChecked(false);
    }

    //OVPN CONFIG
    ui->lineEdit_ovpnipserver->setText(myconfigure->parametervalue(OVPNIPSERVER));
    ui->lineEdit_ovpnuser->setText(myconfigure->parametervalue(OVPNUSER));
    ui->lineEdit_ovpnpasswd->setText(myconfigure->parametervalue(OVPNPASSWD));
    if(ui->checkBox_ovpn->isChecked())
    {
        ui->lineEdit_ovpnipserver->setEnabled(true);
        ui->lineEdit_ovpnuser->setEnabled(true);
        ui->lineEdit_ovpnpasswd->setEnabled(true);
    }else{
        ui->lineEdit_ovpnipserver->setEnabled(false);
        ui->lineEdit_ovpnuser->setEnabled(false);
        ui->lineEdit_ovpnpasswd->setEnabled(false);
    }

    //PPTP CONFIG
    ui->lineEdit_pptpipserver->setText(myconfigure->parametervalue(PPTPIPSERVER));
    ui->lineEdit_pptpuser->setText(myconfigure->parametervalue(PPTPUSER));
    ui->lineEdit_pptppasswd->setText(myconfigure->parametervalue(PPTPPASSWD));
    if(ui->checkBox_ovpn->isChecked())
    {
        ui->lineEdit_pptpipserver->setEnabled(true);
        ui->lineEdit_pptpuser->setEnabled(true);
        ui->lineEdit_pptppasswd->setEnabled(true);
    }else{
        ui->lineEdit_pptpipserver->setEnabled(false);
        ui->lineEdit_pptpuser->setEnabled(false);
        ui->lineEdit_pptppasswd->setEnabled(false);
    }
}

void Dialog::SignalDisplay(QByteArray sigData)
{
    int a, b;

    a = sigData.indexOf("<S>");
    a += 3;
    b = sigData.indexOf("</S>");
    ui->label_signal->setText(sigData.mid(a, b - a));

    a = sigData.indexOf("<GDT>");
    a += 5;
    b = sigData.indexOf("</GDT>");
    ui->label_systime->setText(sigData.mid(a, b - a));

    a = sigData.indexOf("<IP>");
    a += 4;
    b = sigData.indexOf("</IP>");
    if(b > 0)
    ui->label_localip->setText(sigData.mid(a, b - a));

    a = sigData.indexOf("<RTC>");
    a += 5;
    b = sigData.indexOf("</RTC>");
    if(b > 0)
    ui->label_rtctime->setText(sigData.mid(a, b - a));
}

void Dialog::AlarmDisplay(QByteArray alarmData)
{
    int a, b;
    QByteArray DateTime;

    a = alarmData.indexOf("<GDT>");
    a += 5;
    b = alarmData.indexOf("</GDT>");
    DateTime = alarmData.mid(a, b - a);

    a = DateTime.indexOf(' ');
    DateTime.remove(0, a + 1);

    if(alarmData.contains("<A>4</A>")){//usb break
        ui->label_usb->setText(DateTime);

        if(!usbstate){
            usbstate = true;

            usbbtn->setImage(QString(":/images/icons/usbbreak.jpg"), QString(":/images/icons/usbconnect.jpg"));
        }
        usbbtn->setChecked(false);
    }

    if(alarmData.contains("<A>7</A>")){//usb connect
        ui->label_usb->setText(DateTime);

        if(!usbstate){
            usbstate = true;

            usbbtn->setImage(QString(":/images/icons/usbbreak.jpg"), QString(":/images/icons/usbconnect.jpg"));
        }
        usbbtn->setChecked(true);
    }

    if(alarmData.contains("<A>5</A>")){//parallel break
        ui->label_parallel->setText(DateTime);

        if(!parallelstate){
            parallelstate = true;

            parallelbtn->setImage(QString(":/images/icons/parallbreak.jpg"), QString(":/images/icons/parallconnect.jpg"));
        }
        parallelbtn->setChecked(false);
    }

    if(alarmData.contains("<A>8</A>")){//parallel connect
        ui->label_parallel->setText(DateTime);

        if(!parallelstate){
            parallelstate = true;

            parallelbtn->setImage(QString(":/images/icons/parallbreak.jpg"), QString(":/images/icons/parallconnect.jpg"));
        }
        parallelbtn->setChecked(true);
    }

    if(alarmData.contains("<A>6</A>")){//serial break
        ui->label_serial->setText(DateTime);

        if(!serialstate){
            serialstate = true;

            serialbtn->setImage(QString(":/images/icons/serialbreak.jpg"), QString(":/images/icons/serialconnect.jpg"));
        }
        serialbtn->setChecked(false);
    }

    if(alarmData.contains("<A>9</A>")){//parallel connect
        ui->label_serial->setText(DateTime);

        if(!serialstate){
            serialstate = true;

            serialbtn->setImage(QString(":/images/icons/serialbreak.jpg"), QString(":/images/icons/serialconnect.jpg"));
        }
        serialbtn->setChecked(true);
    }

    if(alarmData.contains("<A>1</A>")){//power break
        ui->label_power->setText(DateTime);

        if(!powerstate){
            powerstate = true;

            powerbtn->setImage(QString(":/images/icons/powerbreak.jpg"), QString(":/images/icons/powerconnet.jpg"));
        }
        powerbtn->setChecked(false);
    }

    if(alarmData.contains("<A>2</A>")){//power connect
        ui->label_power->setText(DateTime);

        if(!powerstate){
            powerstate = true;

            powerbtn->setImage(QString(":/images/icons/powerbreak.jpg"), QString(":/images/icons/powerconnet.jpg"));
        }
        powerbtn->setChecked(true);
    }
}

void Dialog::FileDataDisplay(QByteArray FileData)
{
    int a, b;

    a = FileData.indexOf("<DATA>");
    a += 6;
    b = FileData.indexOf("</DATA>");
    ui->textEdit_receipt->append(FileData.mid(a, b - a));
}

void Dialog::comRx(QByteArray rcvData)
{
    if(rcvData.contains("CONFIG")){
        myconfigure->Get_Configure(rcvData);
        ParameterDisplay();
    }else if(rcvData.contains("SIGNAL")){
        SignalDisplay(rcvData);
    }else if(rcvData.contains("ALARM")){
        AlarmDisplay(rcvData);
    }else if(rcvData.contains("FILE")){
        FileDataDisplay(rcvData);
    }else{
        ui->textEdit->append(rcvData);
    }
}

void Dialog::on_pushButton_port_clicked()
{
    if(com_opened){
        PortClose();
    }else{
        PortOpen();

        mythread = new rs232thread;
        connect(mythread, SIGNAL(comRx(QByteArray)), this, SLOT(comRx(QByteArray)));

        mythread->setPortnum(ui->comboBox_serial->currentText());
        mythread->start();
    }
}


void Dialog::on_radioButton_usb_toggled(bool checked)
{
    if(checked)
    {
        ui->stackedWidget_tappingmode->setVisible(true);
        ui->stackedWidget_tappingmode->setCurrentIndex(0);
    }
}

void Dialog::on_radioButton_serial_toggled(bool checked)
{
    if(checked)
    {
        ui->stackedWidget_tappingmode->setVisible(true);
        ui->stackedWidget_tappingmode->setCurrentIndex(1);
    }
}

void Dialog::on_radioButton_parallel_toggled(bool checked)
{
    if(checked)
    {
        ui->stackedWidget_tappingmode->setVisible(false);
    }
}

void Dialog::on_radioButton_gsm_toggled(bool checked)
{
    if(checked)
    {
        ui->stackedWidget_connect->setCurrentIndex(0);
    }
}

void Dialog::on_radioButton_wifi_toggled(bool checked)
{
    if(checked)
    {
        ui->stackedWidget_connect->setCurrentIndex(1);
    }
}

void Dialog::on_checkBox_ovpn_toggled(bool checked)
{
    if(checked)
    {
        ui->lineEdit_ovpnipserver->setEnabled(true);
        ui->lineEdit_ovpnuser->setEnabled(true);
        ui->lineEdit_ovpnpasswd->setEnabled(true);
    }else{
        ui->lineEdit_ovpnipserver->setEnabled(false);
        ui->lineEdit_ovpnuser->setEnabled(false);
        ui->lineEdit_ovpnpasswd->setEnabled(false);
    }
}

void Dialog::on_checkBox_pptp_toggled(bool checked)
{
    if(checked)
    {
        ui->lineEdit_pptpipserver->setEnabled(true);
        ui->lineEdit_pptpuser->setEnabled(true);
        ui->lineEdit_pptppasswd->setEnabled(true);
    }else{
        ui->lineEdit_pptpipserver->setEnabled(false);
        ui->lineEdit_pptpuser->setEnabled(false);
        ui->lineEdit_pptppasswd->setEnabled(false);
    }
}

void Dialog::on_pushButton_download_clicked()
{
    mythread->getconfig();
}

void Dialog::on_pushButton_update_clicked()
{
    QByteArray SendParameter;

    SendParameter.append(ParameterSet());

    qDebug() << "SendParameter = " << SendParameter;

    mythread->setconfig(SendParameter);
}

void Dialog::on_pushButton_login_clicked()
{
    myconfigure->Clear_Configure();
    ParameterDisplay();
    ui->textEdit_receipt->clear();

    mythread->startlogin();
}
