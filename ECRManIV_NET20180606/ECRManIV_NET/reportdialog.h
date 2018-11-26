#ifndef REPORTDIALOG_H
#define REPORTDIALOG_H

#include <QDialog>

namespace Ui {
class reportDialog;
}

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

#define DOWNLOAD        0x01
#define UPDATE          0x02

#define TXTWIDTH        42

class QStandardItemModel;
class QModelIndex;

class reportDialog : public QDialog
{
    Q_OBJECT

public:
    explicit reportDialog(QWidget *parent = 0);
    ~reportDialog();

    void setzno(int zno){ZNo = zno;}
    void setiplist(QString IP, bool checked);

private:
    Ui::reportDialog *ui;

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
    char reporttxt[4096];
    char XZModle;
    QList< QList<QVariant> > m_datas;

    char udflag;//0x1 上传 0x2 下载
    int cashid;
    int IpIndex;
    int IpIndexMax;
    QString IpStr;

    SwitchButton *timebtn;
    QTimer *timer;
    int timecount;

    float BcdToFloat(char *bcd, int len, int decimal);
    void creatreport(QString suffixname, char Idx, char * Titel, char Type);
    void StrFormat(char *str, int len, int formattype);
    void NStrFormat(char *strs, char *str1, char *str2, char *str3, char *str4, char *str5, int len);
    void ChToStr(char *str, char ch, int len);
    void ReportToTxt(QStandardItemModel *reportModel, char *txtstr, char *Titel, char reporttype, char reportmod);
    void tcpconnectcash();
    void StripToZno(QString ipstr);

    QString getQssContent();

signals:
    void unconnecthost();
    void connecthost();
    void recvdata(char *buf, int len);
    void senddata(char *buf, int len);
    void setserverip(QString IP);
private slots:
    void on_pushButton_clicked();
    void recvdataok(int sizelen);
    void tcpstate(int type);
    void dbstate(int type);
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
    void on_cleardbreport_clicked();
    void on_correction_5_clicked();
    void on_grandtotal_5_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_xreport_clicked();
    void on_zreport_clicked();

    void slotsSelectAll(int state);
    void changeTest(int row, int col);
    void on_tableWidget_clicked(const QModelIndex &index);
    void checkedChanged(bool btnchecked);
    void showTime();
};

#endif // REPORTDIALOG_H
