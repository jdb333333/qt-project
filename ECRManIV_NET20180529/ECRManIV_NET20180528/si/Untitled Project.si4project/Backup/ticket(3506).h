#ifndef TICKET_H
#define TICKET_H

#include <QWidget>

class tcpclient;

#define cmdUPDATE       'U'     //为更新数据请求
#define cmdDOWNLOAD     'D'     //为下载数据请求

#define RHEAD1	    70
#define RHEAD2	    71
#define RHEAD3	    72

#define RTRAIL1     73
#define RTRAIL2     74
#define RTRAIL3     75

namespace Ui {
class ticket;
}

class ticket : public QWidget
{
    Q_OBJECT

public:
    explicit ticket(QWidget *parent = 0);
    ~ticket();

    void settcpclient(tcpclient *fmtcpclient);

private:
    Ui::ticket *ui;

    tcpclient *formtcpclient;

    int itemindex;
    int senditemmax;
    char sendbuf[1024];
    char recvbuf[1024];

private slots:
    void tcpstate(int type);
    void on_download_clicked();
    void on_update_clicked();
};

#endif // TICKET_H
