#include "serverthread.h"
#include "./database/connectionpool.h"
#include <QList>

serverThread::serverThread(int socketDescriptor, QObject *parent) :
    QThread(parent), socketDescriptor(socketDescriptor)
{

}

serverThread::~serverThread()
{
    socket->close();
}

void serverThread::run()
{
    flowbilldb = ConnectionPool::openConnection();
    qDebug() << "In thread run():" << flowbilldb.connectionName();
    dbQuery = QSqlQuery(flowbilldb);

    socket = new MySocket(socketDescriptor, 0);

    if (!socket->setSocketDescriptor(socketDescriptor))
        return ;

    //connect(socket, &MySocket::disconnected, this, &serverThread::disconnectToHost);
    connect(socket, SIGNAL(disconnected()),this, SLOT(disconnectToHost()));
    connect(socket, SIGNAL(revData(QString, QByteArray)), this, SLOT(recvData(QString, QByteArray)));
    connect(this, SIGNAL(sendDat(QByteArray, int)), socket, SLOT(sendMsg(QByteArray, int)));

    exec();
}

void serverThread::sendData(QByteArray data, int id)
{
    if (data == "")
        return ;

    emit sendDat(data, id);
}

void serverThread::savedatatodb(QByteArray data)
{
    flowbilldb::inserttable(dbQuery, ejdata, dataTime);
}

void serverThread::recvData(QString peerAddr, QByteArray data)
{
    QByteArray tmpdata;
    int i;
    static unsigned char crc;
    QByteArray txtdata;
    char databuf[1024 * 4];

	recvdata.append(data);

    if(recvdata.contains("INFO<NAME>") && recvdata.contains("</CRC>"))//判断是否是完整的票据头信息包
    {
        txtdata = recvdata;
        emit revData(peerAddr, txtdata);

        //提取票据头信息 CRC 以及数据长度
        memset(&ejdata, 0, sizeof(ejdata));

        memcpy(ejdata.IP, peerAddr.toLocal8Bit().data(), peerAddr.size());
        qDebug("ejdata.IP = %s", ejdata.IP);

        //INFO<NAME>**</NAME>
        recvdata.remove(0, 10);
        qDebug() << "recvdata = " << recvdata;
        for(i = 0; i < recvdata.length(); i++)
        {
            if(recvdata.at(i) == '<')
                break;
        }
        tmpdata = recvdata.left(i);
        qDebug() << "tmpdata = " << tmpdata;
        recvdata.remove(0, i + 7);
        QList<QByteArray> list = tmpdata.split('-');
        ejdata.Indx = list.at(0).toInt();
        memcpy(ejdata.Name, list.at(1).data(), list.at(1).size());
        qDebug() << "Indx = " << ejdata.Indx;
        qDebug("Name = %s", ejdata.Name);

        //<FS>**</FS>
        recvdata.remove(0, 4);
        qDebug() << "recvdata = " << recvdata;
        for(i = 0; i < recvdata.length(); i++)
        {
            if(recvdata.at(i) == '<')
                break;
        }
        tmpdata = recvdata.left(i);
        qDebug() << "tmpdata = " << tmpdata;
        recvdata.remove(0, i + 5);
        ejdata.datalen = tmpdata.toInt();
        qDebug() << "datalen = " << ejdata.datalen;

        //<FDT>**</FDT>
        recvdata.remove(0, 5);
        qDebug() << "recvdata = " << recvdata;
        for(i = 0; i < recvdata.length(); i++)
        {
            if(recvdata.at(i) == '<')
                break;
        }
        tmpdata = recvdata.left(i);
        qDebug() << "tmpdata = " << tmpdata;
        recvdata.remove(0, i + 6);
        dataTime = QDateTime::fromString(tmpdata, "yyyy-MM-dd hh:mm:ss");
        qDebug() << "dataTime = " << dataTime;

        //<CRC>**</CRC>
        recvdata.remove(0, 5);
        qDebug() << "recvdata = " << recvdata;
        for(i = 0; i < recvdata.length(); i++)
        {
            if(recvdata.at(i) == '<')
                break;
        }
        tmpdata = recvdata.left(i);
        qDebug() << "tmpdata = " << tmpdata;
        recvdata.clear();
        crc = tmpdata.toInt();
        qDebug("crc = %02x", crc);

        sendData("REQUEST", socketDescriptor);
    }

    if(recvdata.contains("FILE<DATA>") && recvdata.contains("</DATA>"))//收到文件数据
    {
        txtdata = recvdata.left(10);
        txtdata.append('\n');

        recvdata.remove(0, 10);

        QByteArray find("</DATA>", 7);
        int idx = 0;
        idx = recvdata.indexOf(find, 0);
        tmpdata = recvdata.mid(0, idx);
        qDebug() << "tmpdata = " << tmpdata;

        if(ejdata.datalen == tmpdata.size())
        {
            memcpy(ejdata.blobbuf, tmpdata.data(), tmpdata.size());
            memset(databuf, 0, sizeof(databuf));
            flowbilldb::receipttotxtbuf(databuf, ejdata.blobbuf, ejdata.datalen);
            ejdata.datalen = strlen(databuf);
            memcpy(ejdata.blobbuf, databuf, ejdata.datalen);

            QByteArray tmp(databuf);
            txtdata.append(tmp);

            flowbilldb::inserttable(dbQuery, ejdata, dataTime);
            sendData("SUCCESS", socketDescriptor);
        }

        tmpdata = recvdata.right(7);
        recvdata.clear();
        txtdata.append('\n');
        txtdata.append(tmpdata);
        emit revData(peerAddr, txtdata);
    }
}

void serverThread::disconnectToHost()
{
    emit disconnectTCP(socketDescriptor);
    socket->disconnectFromHost();
    // 连接使用完后需要释放回数据库连接池
    ConnectionPool::closeConnection(flowbilldb);
    exit();
    //quit();
}
