#include "serverthread.h"
#include "./database/connectionpool.h"
#include "./database/flowbill/flowbilldb.h"

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
    QDateTime dataTime;
    EJData ejdata;

    flowbilldb::inserttable(dbQuery, ejdata, dataTime);
}

void serverThread::recvData(QString peerAddr, QByteArray data)
{
    emit revData(peerAddr, data);
    //savedatatodb(data);
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
