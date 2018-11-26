#include "server.h"
#include "./database/flowbill/flowbilldb.h"

Server::Server(QObject *parent) :
    QTcpServer(parent)
{
    /* get current dialog object */
    dialog = dynamic_cast<Dialog *>(parent);

    flowbilldb *myejdb = new flowbilldb;//初始化，数据库不存在则创建
    delete myejdb;
}

Server::~Server()
{

}

void Server::incomingConnection(int socketDescriptor)
{
    socketList.append(socketDescriptor);

    serverThread *thread = new serverThread(socketDescriptor, 0);

    connect(thread, SIGNAL(started()), dialog, SLOT(showConnection()));
    connect(thread, SIGNAL(disconnectTCP(int)), dialog, SLOT(showDisconnection(int)));
    connect(thread, SIGNAL(revData(QString, QByteArray)), dialog, SLOT(revData(QString, QByteArray)));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    connect(dialog, SIGNAL(sendData(QByteArray, int)), thread, SLOT(sendData(QByteArray, int)));

    thread->start();
}

