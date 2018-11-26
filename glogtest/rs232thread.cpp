#include "rs232thread.h"

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

#include <QDebug>

rs232thread::rs232thread()
{

}

rs232thread::~rs232thread()
{

}

void rs232thread::startlogin()
{
    loginflag = true;
    loginstate = false;
}

int rs232thread::rcvackinfo(QSerialPort *myserial, const char *ackstr, const char *rcvstr1,
                            const char *rcvstr2, const char *rcvstr3, const char *rcvstr4)
{
    QByteArray rcvData;
    int readcount;
    static bool sndlogincmd = false;

    RxData.clear();
    readcount = 0;
    while(1)
    {
        myserial->waitForReadyRead(1000);
        rcvData = myserial->readAll();

        if(loginflag && (!sndlogincmd)){
            sndlogincmd = true;
            TxData.clear();
            TxData.append("admin\n\r");
            myserial->write(TxData);
            myserial->waitForBytesWritten(1000);
        }

        if(loginflag){
            if(RxData.contains("login:") || RxData.contains("Password:")){
                TxData.clear();
                TxData.append("admin\n\r");
                myserial->write(TxData);
                myserial->waitForBytesWritten(1000);
                return -5;
            }
        }

        if(RxData.contains("Processing /etc/profile") || RxData.contains("[admin@osee")){
            loginflag = false;
            sndlogincmd = false;
            emit comRx(RxData);

            if(!loginstate){
                loginstate = true;

                TxData.clear();
                TxData.append("/mnt/mmcblk0p1/glogtest\n\r");
                myserial->write(TxData);
                myserial->waitForBytesWritten(1000);
            }

            return -6;
        }

        if(configflag){
            configflag = false;
            TxData.clear();
            TxData.append("getconfig");
            myserial->write(TxData);
            myserial->waitForBytesWritten(1000);
        }

        if(setconfigflag){
            setconfigflag = false;
            TxData.clear();
            TxData.append("setconfig");
            TxData += ParameterData;
            myserial->write(TxData);
            myserial->waitForBytesWritten(1000);
        }

        if(rcvData.size() > 0){
            qDebug() << "rcvData--->" << rcvData;
            readcount = 0;
            RxData += rcvData;
            continue;
        }
        else if(RxData.size() > 0){
            if(rcvstr1 != NULL){
                if(RxData.contains(rcvstr1)){
                    emit comRx(RxData);
                    TxData.clear();
                    TxData.append(ackstr);
                    myserial->write(TxData);
                    myserial->waitForBytesWritten(1000);
                    return 0;
                }
            }
            if(rcvstr2 != NULL){
                if(RxData.contains(rcvstr2)){
                    emit comRx(RxData);
                    TxData.clear();
                    TxData.append(ackstr);
                    myserial->write(TxData);
                    myserial->waitForBytesWritten(1000);
                    return 0;
                }
            }
            if(rcvstr3 != NULL){
                if(RxData.contains(rcvstr3)){
                    emit comRx(RxData);
                    TxData.clear();
                    TxData.append(ackstr);
                    myserial->write(TxData);
                    myserial->waitForBytesWritten(1000);
                    return 0;
                }
            }
            if(rcvstr4 != NULL){
                if(RxData.contains(rcvstr4)){
                    emit comRx(RxData);
                    TxData.clear();
                    TxData.append(ackstr);
                    myserial->write(TxData);
                    myserial->waitForBytesWritten(1000);
                    return 0;
                }
            }

            if(RxData.contains("communicationerr")){
                return -2;
            }else if(RxData.contains("transmissionerr")){
                return -3;
            }

            qDebug() << "rcv data err";
            emit comRx(RxData);
            return -1;
        }else{
            readcount++;
            if(readcount >= 3){
                if(RxData.size() > 0){
                    emit comRx(RxData);
                }
                qDebug() << "recv time out";
                RxData.clear();
                readcount = 0;

                return -1;
            }
        }
    }
}

void rs232thread::run()
{
    int ret;
    char charbuf[16];
    QSerialPort *myserial= new QSerialPort;

    loginstate = false;
    configflag = false;
    setconfigflag = false;
    loginflag = false;

    myserial->setPortName(portnumber);
    if(myserial->open(QIODevice::ReadWrite))
    {
        serialcloseflag = false;
        qDebug() << "open serial success!";
        myserial->setBaudRate(115200);
        myserial->setDataBits(QSerialPort::Data8);
        myserial->setParity(QSerialPort::NoParity);
        myserial->setStopBits(QSerialPort::OneStop);
        myserial->setFlowControl(QSerialPort::NoFlowControl);

        communication:
        while(1)
        {
            if(serialcloseflag == true)
            {
                break;
            }
            ret = rcvackinfo(myserial, "request", "prepare");
            if(ret < 0)
            {
                if(ret == -3){
                    goto transmission;
                }
                continue;
            }else{
                break;
            }
        }

        qDebug() << "start rcv data";

        transmission:
        while(1)
        {
            if(serialcloseflag == true)
            {
                break;
            }
            ret = rcvackinfo(myserial, "success", "SIGNAL", "CONFIG", "ALARM", "FILE");
            if(ret < 0)
            {
                if(ret == -2){
                    goto communication;
                }
            }
        }

        myserial->close();
    }
}
