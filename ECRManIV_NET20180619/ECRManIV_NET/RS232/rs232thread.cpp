#include "rs232thread.h"

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

#include "./update/updateapp.h"
#include <QDebug>

rs232thread::rs232thread()
{

}

rs232thread::~rs232thread()
{

}

void rs232thread::run()
{
    char CMD[1024];
    unsigned char bcc;
    static int errcount = 0;

    qDebug() << "rs232thread run start!";

    QSerialPort *myserial= new QSerialPort;

    myserial->setPortName(portnumber);
    if(myserial->open(QIODevice::ReadWrite))
    {
        qDebug() << "open serial success!";
    }
    else
    {
        qDebug() << "open serial failed!";
        emit errState(OPENFAILED);
        return;
    }
    myserial->setBaudRate(115200);
    myserial->setDataBits(QSerialPort::Data8);
    myserial->setParity(QSerialPort::NoParity);
    myserial->setStopBits(QSerialPort::OneStop);
    myserial->setFlowControl(QSerialPort::NoFlowControl);

#if 0
    CMD[0] = SOH;
    CMD[1] = '\0';
    TxData.clear();
    TxData.append(CMD, strlen(CMD));
    myserial->clear(QSerialPort::AllDirections);
    myserial->write(TxData);
    myserial->waitForBytesWritten(1);

    RxData.clear();
    if(myserial->waitForReadyRead(1000))//1s
    {
        RxData = myserial->readAll();
        while(myserial->waitForReadyRead(1))
            RxData += myserial->readAll();
    }
    if(RxData.size() > 0)
    {
        memcpy(CMD, RxData.data(), 1);
        if(CMD[0] != ACK)
        {
            qDebug() << "<<<<<<<<<<<<<<<<<<<<<<<<<<";
            qDebug("0--->receive data = %02x", CMD[0]);
            qDebug() << ">>>>>>>>>>>>>>>>>>>>>>>>>>";
            myserial->close();
            return;
        }
    }
    else
    {
        qDebug() << "0--->receive 0 data!";
        myserial->close();
        return;
    }

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
    myserial->clear(QSerialPort::AllDirections);
    myserial->write(TxData);
    myserial->waitForBytesWritten(1);

    RxData.clear();
    if(myserial->waitForReadyRead(1000))//1s
    {
        RxData = myserial->readAll();
        while(myserial->waitForReadyRead(1))
            RxData += myserial->readAll();
    }
    if(RxData.size() > 0)
    {
        memcpy(CMD, RxData.data(), 1);
        if(CMD[0] != ACK)
        {
            qDebug() << "<<<<<<<<<<<<<<<<<<<<<<<<<<";
            qDebug("1--->receive data = %02x", CMD[0]);
            qDebug() << ">>>>>>>>>>>>>>>>>>>>>>>>>>";
            myserial->close();
            return;
        }
    }
    else
    {
        qDebug() << "1--->receive 0 data!";
        myserial->close();
        return;
    }

    RxData.clear();
    if(myserial->waitForReadyRead(1000))//1s
    {
        RxData = myserial->readAll();
        while(myserial->waitForReadyRead(1))
            RxData += myserial->readAll();
    }
    if(RxData.size() > 0)
    {
        memcpy(CMD, RxData.data(), 1);
        if(CMD[0] != SOH)
        {
            qDebug() << "<<<<<<<<<<<<<<<<<<<<<<<<<<";
            qDebug("3--->receive data = %02x", CMD[0]);
            qDebug() << ">>>>>>>>>>>>>>>>>>>>>>>>>>";
            myserial->close();
            return;
        }
    }
    else
    {
        qDebug() << "3--->receive 0 data!";
        myserial->close();
        return;
    }
#else
    CMD[0] = SOH;
    CMD[1] = '\0';
    TxData.clear();
    TxData.append(CMD, strlen(CMD));

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
    TxData.append(CMD, strlen(CMD));
    myserial->clear(QSerialPort::AllDirections);
    myserial->write(TxData);
    //myserial->write(CMD, strlen(CMD));
    myserial->waitForBytesWritten(1);

    RxData.clear();
    while(myserial->waitForReadyRead(1000))
    {
        RxData = myserial->readAll();
    }
#if 1
    if(RxData.size() > 0)
    {
        memcpy(CMD, RxData.data(), 1);
        for(int k = 0; k < RxData.size(); k++)
            qDebug("[%d]%02x ", k, CMD[k]);
    }
    else
    {
        qDebug() << "receive 0 data!";
        //return;
    }
#endif
#endif

    CMD[0] = ACK;
    CMD[1] = '\0';
    TxData.clear();
    TxData.append(CMD, strlen(CMD));
    myserial->clear(QSerialPort::AllDirections);
    myserial->write(TxData);
    myserial->waitForBytesWritten(1);

    RxData.clear();
    if(myserial->waitForReadyRead(1000))//1s
    {
        RxData = myserial->readAll();
        while(myserial->waitForReadyRead(1))
            RxData += myserial->readAll();
    }
    if(RxData.size() > 0)
    {
        memcpy(CMD, RxData.data(), RxData.size());
        CMD[RxData.size()] = '\0';
        if(CMD[1] != 'U' && CMD[2] != 'O' && CMD[3] != 'K')
        {
            qDebug() << "receive data err!";
            myserial->close();
            emit errState(DATAERR);
            return;
        }
    }
    else
    {
        qDebug() << "receive 0 data!";
        myserial->close();
        emit errState(NODATA);
        return;
    }

    CMD[0] = ACK;
    CMD[1] = '\0';
    TxData.clear();
    TxData.append(CMD, strlen(CMD));
    myserial->clear(QSerialPort::AllDirections);
    myserial->write(TxData);
    myserial->waitForBytesWritten(1);

    RxData.clear();
    myserial->waitForReadyRead(1000);//1s
#if 0
    if(RxData.size() > 0)
    {
        memcpy(CMD, RxData.data(), 1);
        for(int k = 0; k < RxData.size(); k++)
            qDebug("[%d]%02x ", k, CMD[k]);
    }
    else
    {
        qDebug() << "receive 0 data!";
        return;
    }
#endif

    int items = messageStrList.size() - 1;
    qDebug() << "items = " << items;
    qDebug() << "itemcount = " << itemcount;
    for (int i = 0; i < items; ++i)
    {
        CMD[0] = SOH;
        CMD[1] = '\0';
        TxData.clear();
        TxData.append(CMD, strlen(CMD));
        myserial->clear(QSerialPort::AllDirections);
        myserial->write(TxData);
        myserial->waitForBytesWritten(1);

        RxData.clear();
        if(myserial->waitForReadyRead(100))//100ms
        {
            RxData = myserial->readAll();
            while(myserial->waitForReadyRead(1))
                RxData += myserial->readAll();
        }
        if(RxData.size() > 0)
        {
            memcpy(CMD, RxData.data(), 1);
            if(CMD[0] != ACK)
            {
                qDebug() << "<<<<<<<<<<<<<<<<<<<<<<<<<<" << i;
                qDebug("receive data = %02x", CMD[0]);
                qDebug() << ">>>>>>>>>>>>>>>>>>>>>>>>>>" << i;
                myserial->close();
                emit errState(DATAERR);
                return;
            }
        }

        CMD[0] = messageStrList.at(i).size();
        CMD[1] = '\0';
        TxData.clear();
        TxData.append(CMD, strlen(CMD));
        TxData += messageStrList.at(i).toAscii();
        bcc = 0x0;
        memcpy(CMD, TxData.data(), TxData.size());
        for(int j = 0; j < TxData.size(); j++)
        {
            bcc += CMD[j] & 0xff;
        }
        bcc = 0xff - (bcc & 0xff) + 1;
        CMD[0] = bcc;
        CMD[1] = '\0';
        TxData.append(CMD, 1);
        myserial->clear(QSerialPort::AllDirections);
        myserial->write(TxData);
        myserial->waitForBytesWritten(1);

        RxData.clear();
        if(myserial->waitForReadyRead(100))//100ms
        {
            RxData = myserial->readAll();
            while(myserial->waitForReadyRead(1))
                RxData += myserial->readAll();
        }
        if(RxData.size() > 0)
        {
            memcpy(CMD, RxData.data(), 1);
            if(CMD[0] != ACK)
            {
                qDebug() << "<<<<<<<<<<<<<<<<<<<<<<<<<<" << i;
                qDebug("receive data = %02x", CMD[0]);
                qDebug() << ">>>>>>>>>>>>>>>>>>>>>>>>>>" << i;
                myserial->close();
                emit errState(DATAERR);
                return;
            }
            errcount = 0;
        }
        else
        {
            if(errcount>100)
            {
                qDebug() << ">>>>>>>>>>>>>>>>>updata failed!";
                myserial->close();
                emit errState(DATATIMEOUT);
                return;
            }
            errcount++;
        }

        if((i+1)%itemcount == 0)
        {
            qDebug() << "i = " << i;
            emit comTx();
        }
        else if((i + 1) == items)
        {
            emit comTx();
        }
    }

    myserial->close();
}
