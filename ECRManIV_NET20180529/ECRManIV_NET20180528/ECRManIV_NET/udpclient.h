#ifndef UDPCLIENT_H
#define UDPCLIENT_H

#include <QObject>

#define GET_HOST_COMMAND "IP_FOUND"
#define TRY_TIMES 1
#define UDP_LOCAL_PORT 6000
#define UDP_DEST_PORT 6000

class QUdpSocket;

class udpclient : public QObject
{
    Q_OBJECT
public:
    explicit udpclient(QObject *parent = 0);
    ~udpclient();

    int BroadcastGetIpCommand(char (*ipgroup)[64]);
    void BindLocalIp(char *localip);

signals:
    void searchipok(int ipitem);

public slots:
    void processPengingDatagram();
private:
    QUdpSocket * receiver;
    char (*IPGROUP)[64];
    int ipcount;
};

#endif // UDPCLIENT_H
