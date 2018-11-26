#include "tcpthread.h"

#include "tcpclient.h"

#include "./RS232/rs232dialog.h"

#include <QDebug>

tcpthread::tcpthread()
{
    stopped = false;
}

tcpthread::~tcpthread()
{

}

void tcpthread::run()
{
#if 1
    apprun();
#else
    int ret;
    ret = tcpClient->writeMessage();
    if(ret == 0)
    {
        qDebug() << QString("thread--->tcpClient->readMessage()");
        tcpClient->readMessage();
    }
#endif
}

void tcpthread::stop()
{
    stopped = true;
}
