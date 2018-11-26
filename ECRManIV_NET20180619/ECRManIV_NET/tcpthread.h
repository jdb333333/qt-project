#ifndef TCPTHREAD_H
#define TCPTHREAD_H

#include <QThread>

class tcpclient;
class reportdb;
class RS232Dialog;

class tcpthread : public QThread
{
    Q_OBJECT
public:
    tcpthread();
    ~tcpthread();

    void settcpclient(tcpclient *Client){tcpClient = Client;}

protected:
    void run();

public:
    void stop();

    void (*apprun)();

    void setapprun(void (*threadrun)()){apprun = threadrun;}

private:
    volatile bool stopped;
    friend class reportdb;
    friend class tcpclient;
    friend class RS232Dialog;
    tcpclient *tcpClient;
};

#endif // TCPTHREAD_H
