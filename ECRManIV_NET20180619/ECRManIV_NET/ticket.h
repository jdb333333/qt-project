#ifndef TICKET_H
#define TICKET_H

#include <QWidget>

class tcpclient;

#define cmdUPDATE       'U'     //涓烘洿鏂版暟鎹姹?
#define cmdDOWNLOAD     'D'     //涓轰笅杞芥暟鎹姹?
#define cmdFLOWDATA     'F'     //为请求收款机流水数据
#define cmdANSWER       'A'     //为对host的应答命令

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
#define RHEAD10	    114 //30行
#define RHEAD11	    115
#define RHEAD12	    116
#define RHEAD13	    117 //39行
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

#define F_UPDATA	0x01
#define F_DOWNLOAD  0x02

#define F_CLERK     0x01
#define F_DISC      0x02
#define F_TAX       0x03
#define F_OFFER     0x04
#define F_EJ        0x05

#define F_TICKET    0x06

#define CLERK_WIN   0x01
#define DISC_WIN    0x02
#define TAX_WIN     0x03
#define OFFER_WIN   0x04
#define EJ_WIN      0x05

class MyCheckboxHeader;
class QMenu;
class QModelIndex;

class clerk;
class disc;
class tax;
class offprice;
class flowbill;

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
    void setformtype(char fmtype);
    void setiplist(QString IP, QString SHOPNAME, bool checked);

private:
    Ui::ticket *ui;

    tcpclient *formtcpclient;

    int itemindex;
    int senditemmax;
	int itemslen[40];
	char itemsbuf[40][1024];
    char sendbuf[1024];
    char recvbuf[1024 * 2];

    char formtype;

    int IpIndex;
    int IpIndexMax;
    QString IpStr;
    char udflag;//0x1 上传 0x2 下载

    MyCheckboxHeader *myHeader;

    char win_type;
    QMenu *pop_menu;
    QPoint currpos;

    clerk *ck;
    disc *ds;
    tax *tx;
    offprice *offer;
    flowbill *ej;

private:
    void disc_win(void);
    void clerk_win(void);
    void tax_win(void);
    void offer_win(void);

	void txtparse(char type); //type--->0x01 header 0x02 trailer
	int txtcreate(char type);

    QString getQssContent(char type);
    void ticket_download(void);
    void ticket_update(void);

    void clerk_option_deal();
    void clerk_option_menu();
    void clerk_update(void);
    void clerk_download(void);

    void disc_option_deal();
    void disc_option_menu();
    void disc_update(void);
    void disc_download(void);

    void tax_option_deal();
    void tax_option_menu();
    void tax_update(void);
    void tax_download(void);

    void offer_option_deal();
    void offer_option_menu();
    void offer_update(void);
    void offer_download(void);

    void ej_download(void);

    void tcpconnectcash(char type);

private slots:
    void tcpstate(int type);
    void on_download_clicked();
    void on_update_clicked();
#if 0
    void on_header_textChanged();
#endif
    void slotsSelectAll(int state);
#if 1
    void on_clerkWidget_clicked(const QModelIndex &index);
#endif
    void on_actionVoid_Need_Password_triggered();
    void on_actionCorr_Need_Password_triggered();
    void on_actionCancel_Need_Password_triggered();
    void on_actionReturn_Need_Password_triggered();
    void on_actionPercentage_Discount_Need_Password_triggered();
    void on_actionPercentage_Addition_Need_Password_triggered();
    void on_actionAmount_Discount_Need_Password_triggered();
    void on_actionTrain_Clerk_triggered();
#if 1
    void on_actionFixed_triggered();
    void on_actionFload_triggered();
    void on_actionFixed_Float_triggered();
#endif
    void on_actionFixed_toggled(bool arg1);
    void on_actionFload_toggled(bool arg1);
    void on_actionFixed_Float_toggled(bool arg1);
    void on_actionPrint_Vat_triggered();
    void on_actionPrint_Zero_triggered();
    void on_actionPrint_Tax_triggered();
    void on_actionNo_Discount_triggered();
    void on_actionOffer_Price_triggered();
    void on_actionDiscount_triggered();
    void on_actionNo_Discount_toggled(bool arg1);
    void on_actionOffer_Price_toggled(bool arg1);
    void on_actionDiscount_toggled(bool arg1);
    void on_actionMonday_triggered();
    void on_actionTuesday_triggered();
    void on_actionWednesday_triggered();
    void on_actionThursday_triggered();
    void on_actionFriday_triggered();
    void on_actionSaturday_triggered();
    void on_actionSunday_triggered();
    void on_ejshow_clicked();
    void on_tableWidget_clicked(const QModelIndex &index);

    void ejdataok(char *databuf);
};

#endif // TICKET_H
