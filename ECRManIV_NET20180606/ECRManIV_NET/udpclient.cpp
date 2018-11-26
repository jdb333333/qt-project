#include "udpclient.h"

#include<QtNetwork>

udpclient::udpclient(QObject *parent) : QObject(parent)
{
    receiver = new QUdpSocket(this);

#if 0
    QString strIpAddress;
    strIpAddress = QHostAddress(QHostAddress::LocalHost).toString();
    qDebug() << "strIpAddress = " << strIpAddress;
    receiver->bind(QHostAddress(QHostAddress::LocalHost),UDP_LOCAL_PORT,QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);
#else
    //receiver->bind(QHostAddress("192.168.99.143"),UDP_LOCAL_PORT,QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);
    receiver->bind(UDP_LOCAL_PORT,QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);
#endif

    connect(receiver,SIGNAL(readyRead()),this,SLOT(processPengingDatagram()));
}

udpclient::~udpclient()
{

}

void udpclient::BindLocalIp(char *localip)
{
    if(receiver)
    {
        disconnect(receiver,SIGNAL(readyRead()),this,SLOT(processPengingDatagram()));
        delete receiver;
    }

    qDebug("local ip = %s", localip);

    receiver = new QUdpSocket(this);
    receiver->bind(QHostAddress(localip),UDP_LOCAL_PORT,QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);
    connect(receiver,SIGNAL(readyRead()),this,SLOT(processPengingDatagram()));
}

int udpclient::BroadcastGetIpCommand(char (*ipgroup)[64])
{
    QByteArray datagram = GET_HOST_COMMAND;
    int times = TRY_TIMES;
    while(times--)
    {
        qDebug("start BroadcastGetIpCommand");
        receiver->writeDatagram(datagram.data(),datagram.size(),QHostAddress::Broadcast,UDP_DEST_PORT);
    }

    IPGROUP = ipgroup;
    ipcount = 0;
}

void udpclient::processPengingDatagram()
{
    QString s;
    char ip[64] = {0};
    char *p;

    while( receiver->hasPendingDatagrams() )
    {
        QByteArray datagram;

        datagram.resize( receiver->pendingDatagramSize() );

        receiver->readDatagram(datagram.data(),datagram.size());

        s = datagram;

        qDebug() << "IP = " << s;
        memset(ip, 0, 64);
        strcpy(ip, s.toLocal8Bit().data());
        if(p = strstr(ip, "IP_ACK:"))
        {
            ipcount = 0;
            strcpy(IPGROUP[ipcount++], p + 7);
            emit searchipok(ipcount);
        }
    }
}
