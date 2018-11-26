#ifndef REPORTDIALOG_H
#define REPORTDIALOG_H

#include <QDialog>

namespace Ui {
class reportDialog;
}

class tcpclient;
class reportdb;
class SwitchButton;

#if 0
#define DAILY_REPORT    0x01
#define WEEK_REPORT     0x02
#define PERIOD_PLU      0x04
#define PERIOD_TABLES   0x08
#define TIME_ZONE       0x10
#define CLERK_DAILY     0x20
#define CLERK_PERIOD    0x40
#endif
#define CLEAR_REPORT    0x80

#define DOWNLOAD_DATA        0x01
#define UPDATE_DATA          0x02
#define PRINT_ECR			0x03

//#define TXTWIDTH        42
#define TXTWIDTH        56

class QStandardItemModel;
class QModelIndex;

class reportDialog : public QDialog
{
    Q_OBJECT

public:
    explicit reportDialog(QWidget *parent = 0);
    ~reportDialog();

	void settcpclient(tcpclient *fmtcpclient);
    void setzno(int zno){ZNo = zno;}
    void setiplist(QString IP, QString SHOPNAME, bool checked);

private:
    Ui::reportDialog *ui;

	tcpclient *formtcpclient;
    reportdb *MyDb;
    char sendbuf[1024][32];
    int itemindex;
    int senditemmax;
    char recvbuf[1024];
    int downloaddata(unsigned char datatype);
    unsigned char tcpstat;
    unsigned char dbstat;
    int sendlen;
    int itemcount;
    int ZNo;
    char reporttxt[8192];
	QString totalaccum;
    char XZModle;
    QList< QList<QVariant> > m_datas;

    char udflag;//0x1 涓婁紶 0x2 涓嬭浇 0x03 鎵撳嵃
    int cashid;
    int IpIndex;
    int IpIndexMax;
    QString IpStr;
    QString ShopName;

    SwitchButton *zdailybtn;
	#ifdef WEEK_REPORT
    SwitchButton *zweekbtn;
	#endif
    SwitchButton *zplubtn;
    SwitchButton *ztimebtn;
    SwitchButton *zclerkbtn;
	#ifdef WEEK_REPORT
    SwitchButton *zclerkweekbtn;
	#endif
	int zbtnnum;

    SwitchButton *timebtn;
    QTimer *timer;
    int timecount;

	char DataReportType;
	bool recvflag; //jdb2018-06-20 0x01表示接收没有完成

    float BcdToFloat(char *bcd, int len, int decimal);
    void creatreport(QString suffixname, char Idx, char * Titel, char Type);
    void StrFormat(char *str, int len, int formattype);
    void StrAlignment(char *buf, int buflen, char *data, int datalen, int flag);
    void NStrFormat(char *strs, char *str1, char *str2, char *str3, char *str4, char *str5, int len);
    void ChToStr(char *str, char ch, int len);
    void ReportToTxt(QStandardItemModel *reportModel, char *txtstr, char *Titel, char reporttype, char reportmod);
    void tcpconnectcash();
    void StripToZno(QString ipstr);

    QString getQssContent();

    void Delay_MSec(unsigned int msec);

	void Print_Z(void);
	int recvdataok(int sizelen);
	void ZREPORT_PRINT(char type);

signals:
    void unconnecthost();
    void connecthost();
    void recvdata(char *buf, int len);
    void senddata(char *buf, int len);
    void setserverip(QString IP);
private slots:
    void on_DOWNLOADDATA_clicked();
    
    void tcpstate(int type);
    void dbstate(int type);

	#if 0
    void on_grandtotal_clicked();
    void on_department_clicked();
    void on_tender_clicked();
    void on_drawer_clicked();
    void on_correction_clicked();
    void on_discount_clicked();
    void on_tax_clicked();
    void on_grandtotal_2_clicked();
    void on_department_2_clicked();
    void on_tender_2_clicked();
    void on_drawer_2_clicked();
    void on_correction_2_clicked();
    void on_discount_2_clicked();
    void on_tax_2_clicked();
    void on_grandtotal_3_clicked();
    void on_tender_3_clicked();
    void on_drawer_3_clicked();
    void on_correction_3_clicked();
    void on_discount_3_clicked();
    void on_grandtotal_4_clicked();
    void on_tender_4_clicked();
    void on_correction_4_clicked();
    void on_discount_4_clicked();
	#endif
    void on_cleardbreport_clicked();
	
    void on_TIMEBTN_clicked();
    void on_PLUBTN_clicked();
    void on_DAILYBTN_clicked();
	#ifdef WEEK_REPORT
    void on_PERIODREPORT_clicked();
	#endif
    void on_CLERKBTN_clicked();
	#ifdef WEEK_REPORT
    void on_CLERKPERIOD_clicked();
	#endif
	
    void on_xreport_clicked();
    void on_zreport_clicked();

    void slotsSelectAll(int state);
    void changeTest(int row, int col);
    void on_tableWidget_clicked(const QModelIndex &index);
    void checkedChanged(bool btnchecked);
    void showTime();

    void zdailycheckedChanged(bool btnchecked);
	#ifdef WEEK_REPORT
	void zweekcheckedChanged(bool btnchecked);
	#endif
	void zplucheckedChanged(bool btnchecked);
	void ztimecheckedChanged(bool btnchecked);
	void zclerkcheckedChanged(bool btnchecked);
	#ifdef WEEK_REPORT
	void zclerkweekcheckedChanged(bool btnchecked);
	#endif
};

#endif // REPORTDIALOG_H
