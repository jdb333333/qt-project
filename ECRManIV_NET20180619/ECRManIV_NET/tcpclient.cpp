#include "tcpclient.h"

#include <QtNetwork>
#include <QWidget>

//waitForConnected() 等待链接的建立
//waitForReadyRead() 等待新数据的到来
//waitForBytesWritten() 等待数据写入socket
//waitForDisconnected() 等待链接断开

tcpclient *TcpClient;
void threadrun();

tcpclient::tcpclient(QWidget *parent) :
    QWidget(parent)
{
    tcpSocket = new QTcpSocket(this);

    isOpen = false;
    abortflag = true;

    //connect(tcpSocket, SIGNAL(connected()), this, SLOT(writeMessage()), Qt::DirectConnection);
    //connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(readMessage()));
    connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(displayError(QAbstractSocket::SocketError)));

    connect(tcpSocket,SIGNAL(stateChanged(QAbstractSocket::SocketState)),this,
            SLOT(sltStateChanged(QAbstractSocket::SocketState)),Qt::DirectConnection);

    tcpThread = new tcpthread;
    tcpThread->settcpclient(this);

    TcpClient = this;
    tcpThread->setapprun(threadrun);
}

tcpclient::~tcpclient()
{
    tcpSocket->close();
}

void tcpclient::resetserver()
{
    if(tcpSocket)
    {
        abortConnect();
        disconnect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
                this, SLOT(displayError(QAbstractSocket::SocketError)));

        disconnect(tcpSocket,SIGNAL(stateChanged(QAbstractSocket::SocketState)),this,
                SLOT(sltStateChanged(QAbstractSocket::SocketState)));

        delete tcpSocket;
    }

    tcpSocket = new QTcpSocket(this);

    isOpen = false;
    abortflag = false;

    //connect(tcpSocket, SIGNAL(connected()), this, SLOT(writeMessage()), Qt::DirectConnection);
    //connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(readMessage()));
    connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(displayError(QAbstractSocket::SocketError)));

    connect(tcpSocket,SIGNAL(stateChanged(QAbstractSocket::SocketState)),this,
            SLOT(sltStateChanged(QAbstractSocket::SocketState)),Qt::DirectConnection);

    tcpThread = new tcpthread;
    tcpThread->settcpclient(this);

    TcpClient = this;
    tcpThread->setapprun(threadrun);
}

void tcpclient::setserverip(QString IP)
{
    serverip = IP;
    qDebug() << "serverip = " << serverip;
}

void tcpclient::sltStateChanged(QAbstractSocket::SocketState state)
{
     qDebug()<<"TcpSocketState------"<<state;

     switch(state)
     {
         case QAbstractSocket::ConnectedState:
         case QAbstractSocket::ConnectingState:
         qDebug() << "--->connect!";
         isOpen=true;//isOpen即为连接标志
         //emit sigCommStateUpdate(state);
         break;
         case QAbstractSocket::ClosingState:
         case QAbstractSocket::UnconnectedState:
         qDebug() << "--->unconnect!";
         isOpen=false;
         //emit sigCommStateUpdate(state);
         break;
         default:
         break;
     }
}

void tcpclient::newConnect()
{
    // 初始化数据大小信息为0
    blockSize = 0;
    // 取消已有的连接
    //tcpSocket->abort();
    //tcpSocket->waitForDisconnected(3000);
    abortConnect();

    tcpSocket->connectToHost(serverip, 11024);
    if(!tcpSocket->waitForConnected(5000))
    {
        abortConnect();
        emit tcpstate(TCPCONNECTERR);
        return;
    }
    abortflag = false;
    emit tcpstate(TCPCONNECTOK);
}

int tcpclient::newConnect2()
{
    blockSize = 0;

    abortConnect();

    tcpSocket->connectToHost(serverip, 11024);
    if(!tcpSocket->waitForConnected(5000))
    {
        //abortConnect();
        emit tcpstate(TCPCONNECTERR);
        return -1;
    }

    abortflag = false;

    return 0;
}

void tcpclient::abortConnect()
{
#if 1
    if(abortflag == false)
    {
        abortflag = true;
        tcpSocket->abort();
        tcpSocket->waitForDisconnected(3000);
    }
#else
    tcpSocket->abort();
    tcpSocket->waitForDisconnected(3000);
#endif
}

void tcpclient::readData(char *buf, int len)
{
    //qDebug() << "tcpcliet --------> readdata, blockSize = " << blockSize;
#if 0
    blockSize = 0;
    readMessage();
#endif

    if(blockSize == 0)
    {
        return;
    }

    if(len > blockSize)
    {
        *((unsigned short *)buf) = blockSize;
        memcpy(buf + 2, data, blockSize);
    }
    else
    {
        *((unsigned short *)buf) = len;
        memcpy(buf + 2, data, len);
    }

    //emit recvdataok(blockSize);
#if 1
    emit tcpstate(TCPRCVOK);
#endif
}

int tcpclient::readData2(char *buf, int len)
{
    blockSize = 0;
    readMessage2();

    if(len > blockSize)
    {
        memcpy(buf, data, blockSize);
    }
    else
    {
        memcpy(buf, data, len);
    }

    if(blockSize > 0)
    {
        return blockSize;
    }

    return -1;
}

void tcpclient::readMessage2()
{
    while (tcpSocket->bytesAvailable() < 4) {
        if (!tcpSocket->waitForReadyRead(3000)) {
            //emit error(tcpSocket->error(), tcpSocket->errorString());
            qDebug() << tcpSocket->error() << tcpSocket->errorString();
            abortConnect();
            emit tcpstate(TCPRCVERR);
            return;
        }
    }

    memset(data, 0, sizeof(data));

    blockSize = tcpSocket->bytesAvailable();
    QByteArray datagram = tcpSocket->readAll();
    memcpy(data, datagram.data(), blockSize);
}

void tcpclient::readMessage()
{
    //qDebug() << "start read message!";
#if 1
    while (tcpSocket->bytesAvailable() < 4) {
        if (!tcpSocket->waitForReadyRead(3000)) {
            //emit error(tcpSocket->error(), tcpSocket->errorString());
            qDebug() << tcpSocket->error() << tcpSocket->errorString();
            abortConnect();
            emit tcpstate(TCPRCVERR);
            return;
        }
    }
#endif

    memset(data, 0, 1024);
#if 0
    blockSize = tcpSocket->read(data, 1024);
#else
    blockSize = tcpSocket->bytesAvailable();
    QByteArray datagram = tcpSocket->readAll();
    memcpy(data, datagram.data(), blockSize);
#endif
#if 1
    if(blockSize == 6)
    {
    qDebug() << "rcev data = ";
    for(int i = 0; i < blockSize; i++)
    {
        qDebug("%02x ", data[i]&0xff);
    }
    }
#endif
    emit tcpstate(TCPSENDOK);
}

void tcpclient::writeData(char *buf, int len)
{
    //memset(data, 0, 1024);
    if(len < 1024)
    {
        memcpy(data, buf, len);
        blockSize = len;
    }
    else
    {
        memcpy(data, buf, 1024);
        blockSize = 1024;
    }

    if(isOpen)
    {
#if 1
        //writeMessage();
        int ret;
        ret = writeMessage();
        if(ret == 0)
        {
            //qDebug() << QString("thread--->tcpClient->readMessage()");
            readMessage();
        }
#else
        tcpThread->stop();

        tcpThread->run();
#endif
    }
}

int tcpclient::writeData2(char *buf, int len)
{
    int ret;

    if(len < 1024)
    {
        memcpy(data, buf, len);
        blockSize = len;
    }
    else
    {
        memcpy(data, buf, 1024);
        blockSize = 1024;
    }

    if(isOpen)
    {
        ret = writeMessage2();
    }
    else
    {
        return -1;
    }

    return ret;
}

int tcpclient::writeMessage2()
{
    qDebug("send data len = %d", blockSize);
    for(int count = 0; count < blockSize; count++)
    {
        qDebug("%02x", data[count]);
    }

    tcpSocket->write(data, blockSize);

    if(tcpSocket->waitForBytesWritten(3000))
    {
        tcpSocket->flush();

        return 0;
    }
    else
    {
        abortConnect();
        emit tcpstate(TCPSENDERR);

        return -1;
    }

    return 0;
}

int tcpclient::writeMessage()
{
    //qDebug() << "senddatalen = " << blockSize;

    tcpSocket->write(data, blockSize);
    //tcpSocket
    //tcpSocket->flush();

    if(tcpSocket->waitForBytesWritten(3000))
    {
        //emit SockCondition("successful");
        tcpSocket->flush();
#if 0
        emit tcpstate(TCPSENDOK);
#else
        //tcpThread->run();
#endif
        //qDebug() << "send successful";
        return 0;
    }
    else
    {
        //emit SockCondition("failed");
        abortConnect();
        emit tcpstate(TCPSENDERR);
        qDebug() << "send failed";
        //tcpSocket->disconnect();
        return -1;
    }

    return 0;
}

void tcpclient::displayError(QAbstractSocket::SocketError)
{
    qDebug() << tcpSocket->errorString();
}

void threadrun()
{
    int ret;
    ret = TcpClient->writeMessage();
    if(ret == 0)
    {
        //qDebug() << QString("thread--->tcpClient->readMessage()");
        TcpClient->readMessage();
    }
}
