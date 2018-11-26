#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include "tcpthread.h"

#include <QWidget>
#include <QAbstractSocket>
#include <QObject>
class QTcpSocket;

#define TCPCONNECTOK    0x1
#define TCPCONNECTERR   0x2
#define TCPSENDOK       0x3
#define TCPSENDERR      0x4
#define TCPRCVOK        0x5
#define TCPRCVERR       0x6

class tcpclient : public QWidget
{
    Q_OBJECT
public:
    explicit tcpclient(QWidget *parent = 0);
    ~tcpclient();

private:
    friend class tcpthread;
    tcpthread *tcpThread;
    QTcpSocket *tcpSocket;
    char data[1024];
    quint16 blockSize; // 用来存放数据的大小信息
    bool isOpen;
    QString serverip;
    bool abortflag;

public:
    void abortConnect();
    void newConnect();
    void readData(char *buf, int len);
    void writeData(char *buf, int len);
    void setserverip(QString IP);

    friend void threadrun();

signals:
    void recvdataok(int sizelen);
    void tcpstate(int type);

private slots:
    void readMessage();
    int writeMessage();
    void displayError(QAbstractSocket::SocketError);
    void sltStateChanged(QAbstractSocket::SocketState state);
};

#endif // TCPCLIENT_H
