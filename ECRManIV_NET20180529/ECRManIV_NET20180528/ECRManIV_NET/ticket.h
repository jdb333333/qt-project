#ifndef TICKET_H
#define TICKET_H

#include <QWidget>

class tcpclient;

#define cmdUPDATE       'U'     //为更新数据请�?
#define cmdDOWNLOAD     'D'     //为下载数据请�?

#define RHEAD1	    70
#define RHEAD2	    71
#define RHEAD3	    72

#define RTRAIL1     73
#define RTRAIL2     74
#define RTRAIL3     75

#define RHEAD4	    108
#define RHEAD5	    109
#define RHEAD6	    110
#define RHEAD7	    111
#define RHEAD8	    112
#define RHEAD9	    113
#define RHEAD10	    114 //30��
#define RHEAD11	    115
#define RHEAD12	    116
#define RHEAD13	    117 //39��
#define RHEAD14	    118

#define RTRAIL4     119
#define RTRAIL5     120
#define RTRAIL6     121
#define RTRAIL7     122
#define RTRAIL8     123
#define RTRAIL9     124
#define RTRAIL10    125
#define RTRAIL11    126
#define RTRAIL12    127
#define RTRAIL13    128
#define RTRAIL14    129

namespace Ui {
class ticket;
}

#pragma pack (1)
typedef struct itemdata {
	char buf[1024];
	int datalen;
}ItemData;
#pragma pack ()

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
	int itemslen[40];
	char itemsbuf[40][1024];
    char sendbuf[1024];
    char recvbuf[1024];

	void txtparse(char type); //type--->0x01 header 0x02 trailer
	int txtcreate(char type);

private slots:
    void tcpstate(int type);
    void on_download_clicked();
    void on_update_clicked();
};

#endif // TICKET_H
