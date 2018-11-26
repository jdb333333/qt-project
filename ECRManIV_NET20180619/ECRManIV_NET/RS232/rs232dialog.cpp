#include "rs232dialog.h"
#include "ui_rs232dialog.h"

#include <QFile>
#include <QFileDialog>
#include <QDebug>

#include <QTime>
#include <QMessageBox>

#include "tcpthread.h"

#include "rs232thread.h"

#include "./update/updateapp.h"

void mysleep(unsigned int msec)
{
    QTime reachTime = QTime::currentTime().addMSecs(msec);

    while(QTime::currentTime() < reachTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

RS232Dialog::RS232Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RS232Dialog)
{
    ui->setupUi(this);

    this->setWindowTitle("Update Firmware");

    initPort();

    ui->textEdit->setReadOnly(true);
}

RS232Dialog::~RS232Dialog()
{
    if(com_opened)
        PortClose();

    delete myserial;

    delete ui;
}

void RS232Dialog::initPort()
{
    ui->comboBox_serial->clear();
    QStringList list;
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        // Example use QSerialPort
        QSerialPort serial;
        serial.setPort(info);
        if (serial.open(QIODevice::ReadWrite))
        {
            list << info.portName();
            serial.close();
        }

        //list << info.portName();
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

int RS232Dialog::PortOpen()
{
#if 0
    myserial->setPortName(ui->comboBox_serial->currentText());
    myserial->setBaudRate(115200, QSerialPort::AllDirections);
    myserial->setDataBits(QSerialPort::Data8);
    myserial->setParity(QSerialPort::NoParity);
    myserial->setStopBits(QSerialPort::OneStop);
    myserial->setFlowControl(QSerialPort::NoFlowControl);

    //通讯的双方A和B，假如A给B发送数据时，B反应过慢，A不管不顾的不停发送数据，结果会导致数据丢失。为了防止这种情况发生，可使用流控制（也叫握手）。
    if(myserial->open(QIODevice::ReadWrite))
    {
#if 0
        myserial->setRequestToSend(true);             //设置 RTS 为高电平
        myserial->setDataTerminalReady(true);         //设置 DTR 为高电平
#endif
    }
#endif
    com_opened = true;
    com_stopped = false;

    ui->pushButton_port->setText("Close Port");

    return 0;
}

int RS232Dialog::PortClose()
{
#if 0
    myserial->close();
#endif
    com_opened = false;
    com_stopped = true;

    ui->pushButton_port->setText("Open Port");

    return 0;
}

int RS232Dialog::PortWrite()
{
    //char CMD[1024];

    if(com_opened)
    {
        //qDebug() << "start tx!!!";
#if 0
        memcpy(CMD, TxData.data(), TxData.size());
        CMD[TxData.size()] = '\0';
        for(int i = 0; i < TxData.size(); i++)
        {
            qDebug("CMD[%d] = %02x\n", i, CMD[i]);
        }
#endif
        //tx_event = false;
        //txloop:
        myserial->clear(QSerialPort::AllDirections);
        myserial->write(TxData);
#if 0
        myserial->waitForBytesWritten(15);
#else
        if(!myserial->waitForBytesWritten(1))//50ms
        {
            //qDebug() << "Brush:" << "send data success";
            //tx_event = true;
        }
#if 1
        else
        {
            //qDebug() << "Brush:" << "send data failed!";
            //return -1;
            //goto txloop;
        }
#endif
#endif
    }

    return 0;
}

int RS232Dialog::PortRead()
{
    //char CMD[1024];

    if(com_opened)
    {
        //qDebug() << "start rx!!!";
        //rx_event = false;
        if (myserial->waitForReadyRead(1000))//1s
        {
            RxData = myserial->readAll();
            //qDebug() << "RxData:" << RxData;
            while(myserial->waitForReadyRead(1))
                RxData += myserial->readAll();
            //rx_event = true;
#if 0
            memcpy(CMD, RxData.data(), RxData.size());
            CMD[RxData.size()] = '\0';
            for(int i = 0; i < strlen(CMD); i++)
            {
                qDebug("CMD[%d] = %02x\n", i, CMD[i]);
            }
#endif

            //qDebug() << "Brush:" << "receive data success";
        }
        else
        {
            //qDebug() << "Brush:" << "receive data failed!";
            //return -1;
        }
    }

    return 0;
}

int RS232Dialog::PortReadOneByte()
{
    if(com_opened)
    {
        if (myserial->waitForReadyRead(1000))//1s
        {
            RxData = myserial->readAll();
            if(RxData.size() > 0)
                return 0;

            while(myserial->waitForReadyRead(5))
                RxData += myserial->readAll();
        }
    }

    return 0;
}

int RS232Dialog::SendOneChar(char data)
{
    int ret;
    char CMD[8];

    CMD[0] = data;
    CMD[1] = '\0';

    TxData.clear();
    TxData.append(CMD, strlen(CMD));
    ret = PortWrite();
    if(ret < 0)
        return -1;
}

int RS232Dialog::ReceiveOneChar(char *data)
{
    int ret;
    ret = PortRead();
    if(ret < 0)
        return -1;

    memcpy(data, RxData.data(), 1);

    return 0;
}

int RS232Dialog::PreUpdate()
{
    int ret;

    char CMD[64];
    unsigned char bcc;

#if 1
    ret = SendOneChar(SOH);
    if(ret < 0)
        return -1;
    ret = ReceiveOneChar(CMD);
    if(ret < 0)
        return -1;
    if(CMD[0] != ACK)
        return -1;

    CMD[0] = 0x05;
    CMD[1] = 'U';
    CMD[2] = 'B';
    CMD[3] = 'I';
    CMD[4] = 'O';
    CMD[5] = 'S';

    bcc = CMD[0];
    bcc += CMD[1];
    bcc += CMD[2];
    bcc += CMD[3];
    bcc += CMD[4];
    bcc += CMD[5];

    CMD[6] = (0xff - bcc & 0xff) + 1;
    CMD[7] = '\0';

    TxData.clear();
    TxData.append(CMD, strlen(CMD));
    ret = PortWrite();
    if(ret < 0)
        return -1;

    ret = PortRead();
    if(ret < 0)
        return -1;
    memcpy(CMD, RxData.data(), RxData.size());
    CMD[RxData.size()] = '\0';
    if(CMD[0] != ACK)
        return -1;
#else
    CMD[0] = SOH;

    CMD[1] = 0x05;
    CMD[2] = 'U';
    CMD[3] = 'B';
    CMD[4] = 'I';
    CMD[5] = 'O';
    CMD[6] = 'S';

    bcc = CMD[1];
    bcc += CMD[2];
    bcc += CMD[3];
    bcc += CMD[4];
    bcc += CMD[5];
    bcc += CMD[6];

    CMD[7] = (0xff - bcc & 0xff) + 1;
    CMD[8] = '\0';

    TxData.clear();
    TxData.append(CMD, strlen(CMD));
    ret = PortWrite();
    if(ret < 0)
        return -1;

    ret = PortRead();
    if(ret < 0)
        return -1;
    memcpy(CMD, RxData.data(), RxData.size());
    CMD[RxData.size()] = '\0';
    if(CMD[0] != ACK && CMD[1] != ACK)
    {
        qDebug() << "pre err!";
        return -1;
    }
#endif

    return 0;
}

void RS232Dialog::StrToHex(QByteArray Data, char *databuf)
{
    char buf[1024];
    char highdata, lowdata;

    memcpy(buf, Data.data(), Data.size());
    buf[Data.size()] = '\0';

    int j = 0;
    databuf[j++] = buf[0];
    for(int i = 1; i < Data.size();)
    {
        highdata = buf[i++] & 0xff;
        lowdata = buf[i++] & 0xff;
        databuf[j++] = highdata << 4 | lowdata;
        qDebug("databuf[%d]--->%02x", j-1, databuf[j-1]);
    }

    databuf[j] = '\0';
}

unsigned char RS232Dialog::HexAcc(QByteArray Data)
{
    char buf[1024];
    unsigned char Acc;

    Acc = 0x0;

    memcpy(buf, Data.data(), Data.size());
    buf[Data.size()] = '\0';

    for(int i = 0; i < Data.size(); i++)
    {
        Acc += buf[i] & 0xff;
        //qDebug("Acc---------->%02x", Acc);
    }

    Acc = 0xff - (Acc & 0xff) + 1;
    //qDebug("Acc>>>>>>>>%02x", Acc);

    return Acc;
}

int RS232Dialog::UpdateFirm()
{
    int ret;

    char CMD[1024];

    ret = PreUpdate();
    if(ret < 0)
        return -1;

    //******************建立通讯
    ret = PortRead();
    if(ret < 0)
        return -1;
    memcpy(CMD, RxData.data(), RxData.size());
    CMD[RxData.size()] = '\0';
    if(CMD[0] != SOH)
        return -1;

    CMD[0] = ACK;
    CMD[1] = '\0';

    TxData.clear();
    TxData.append(CMD, strlen(CMD));
    ret = PortWrite();
    if(ret < 0)
        return -1;

    ret = PortRead();
    if(ret < 0)
        return -1;
    memcpy(CMD, RxData.data(), RxData.size());
    CMD[RxData.size()] = '\0';
    if(CMD[1] != 'U' && CMD[2] != 'O' && CMD[3] != 'K')
        return -1;

    CMD[0] = ACK;
    CMD[1] = '\0';

    TxData.clear();
    TxData.append(CMD, strlen(CMD));
    ret = PortWrite();
    if(ret < 0)
        return -1;

    ret = PortRead();
    if(ret < 0)
        return -1;
    memcpy(CMD, RxData.data(), RxData.size());
    CMD[RxData.size()] = '\0';
    if(CMD[0] != ACK)
        return -1;
    //*******************

    QString text = ui->textEdit->toPlainText();
    number_list.clear();
    number_list = text.split("\n");
#if 0
    senditemmax = number_list.size() - 1;
#else
    itemindex = number_list.size() - 1;

    if(itemindex > 10000)
    {
        onecountmax = 1000;

    }
    else
    {
        onecountmax = 100;
    }
    senditemmax = itemindex / onecountmax;
    if(itemindex % onecountmax)
    {
        senditemmax += 1;
    }
#endif
    ui->progressBar->setRange(0,senditemmax);
    ui->progressBar->setValue(0);
    itemindex = 0;
#if 1
    int itemcount = number_list.size() - 1;
    for (int i = 0; i < itemcount; ++i)
    {
        CMD[0] = SOH;
        CMD[1] = '\0';

        TxData.clear();
        TxData.append(CMD, strlen(CMD));
        ret = PortWrite();
        if(ret < 0)
            return -1;
        //mysleep(10);

        ret = PortRead();
        if(ret < 0)
            return -1;
        memcpy(CMD, RxData.data(), RxData.size());
        CMD[RxData.size()] = '\0';
        if(CMD[0] != ACK)
            return -1;
        //mysleep(10);

        CMD[0] = number_list.at(i).size();
        CMD[1] = '\0';
        TxData.clear();
        TxData.append(CMD, strlen(CMD));

        TxData += number_list.at(i).toAscii();
        //MyTxData = number_list.at(i).toAscii();
        CMD[0] = HexAcc(TxData);
        //qDebug("CMD[0] = %02x", CMD[0]);
        CMD[1] = '\0';
        TxData.append(CMD, 1);
        ret = PortWrite();
        if(ret < 0)
            return -1;

        RxData.clear();
        ret = PortRead();
        if(ret < 0)
            return -1;
        if(RxData.size() > 0)
        {
            memcpy(CMD, RxData.data(), RxData.size());
            CMD[RxData.size()] = '\0';
            if(CMD[0] != ACK)
            {
                qDebug() << "<<<<<<<<<<<<<<<<<<<<<<<<<<";
                qDebug("receive data = %02x", CMD[0]);
                qDebug() << ">>>>>>>>>>>>>>>>>>>>>>>>>>";
                return -1;
            }
            else
            {
                //qDebug() << "*************************************";
            }
        }
        else
        {
            qDebug() << "receive 0 data!";
            return -1;
        }

#if 0
        itemindex++;
        //qDebug() << "--------------------------------->";
        //qDebug() << "--------------------------------->" << itemindex;
        ui->progressBar->setValue(itemindex);
#else
        if((itemindex + 1 < senditemmax) && (i+1)%onecountmax == 0)//一百的整数倍
        {
            itemindex++;
            ui->progressBar->setValue(itemindex);
            QCoreApplication::processEvents();
        }
        else if((i + 1) == itemcount)
        {
            itemindex++;
            ui->progressBar->setValue(itemindex);
            QCoreApplication::processEvents();
        }
#endif
    }
#else
#endif
}

void RS232Dialog::itempro_slot()
{
    qDebug() << "receive emit!";
    itemindex++;
    ui->progressBar->setValue(itemindex);
    QCoreApplication::processEvents();

    if(itemindex == senditemmax)
    {
        ui->pushButton->setDisabled(false);
    }
}

void RS232Dialog::errState_slot(int state)
{
    if(state == OPENFAILED)
    {
        QMessageBox message(QMessageBox::NoIcon, "Warning", "<font color='red'>serial err, please check serial!</font>.");
        message.exec();
    }
    else if(state == NODATA)
    {
        QMessageBox message(QMessageBox::NoIcon, "Warning", "<font color='red'>serial err, no receive data!</font>.");
        message.exec();
    }
    else if(state == DATAERR)
    {
        QMessageBox message(QMessageBox::NoIcon, "Warning", "<font color='red'>serial err, data err!</font>.");
        message.exec();
    }
    else if(state == DATATIMEOUT)
    {
        QMessageBox message(QMessageBox::NoIcon, "Warning", "<font color='red'>serial err, receive data timeout!</font>.");
        message.exec();
    }

    ui->pushButton->setDisabled(false);
}

void RS232Dialog::on_pushButton_update_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,QString(),QString(),"hex file(*.hex)");
    QFile file(fileName);
    if(file.open(QIODevice::ReadOnly)){
        QString textFill=file.readAll();

        ui->textEdit->clear();
        ui->textEdit->append(textFill);
      }

    QString text = ui->textEdit->toPlainText();
    number_list.clear();
    number_list = text.split("\n");

    itemindex = number_list.size() - 1;
    if(itemindex > 10000)
    {
        onecountmax = 1000;
    }
    else
    {
        onecountmax = 100;
    }
    senditemmax = itemindex / onecountmax;
    if(itemindex % onecountmax)
    {
        senditemmax += 1;
    }

    itemindex = 0;
    ui->progressBar->setRange(0,senditemmax);
    ui->progressBar->setValue(0);
}

void RS232Dialog::on_pushButton_clicked()
{
#if 0
    UpdateFirm();
#else
    if(com_opened)
    {
        ui->pushButton->setDisabled(true);
        mythread = new rs232thread;
        connect(mythread, SIGNAL(comTx()), this, SLOT(itempro_slot()));
        connect(mythread, SIGNAL(errState(int)), this, SLOT(errState_slot(int)));

        mythread->setPortnum(ui->comboBox_serial->currentText());

        mythread->setMessage(number_list);
        mythread->setitemcount(onecountmax);
        qDebug() << "start update!";
        mythread->start();
    }
#endif
}

void RS232Dialog::on_pushButton_port_clicked()
{
    if(com_opened)
        PortClose();
    else
        PortOpen();
}
