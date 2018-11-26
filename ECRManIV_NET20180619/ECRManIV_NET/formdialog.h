#ifndef FORMDIALOG_H
#define FORMDIALOG_H

#include <QDialog>
#include <QScopedPointer>
#include <excelbase.h>
#include <QFile>

class ExcelBase;
class dept;
class plu;
class QModelIndex;

class csv;

#define cmdUPDATE       'U'     //为更新数据请�?
#define cmdDOWNLOAD     'D'     //为下载数据请�?
#define cmdFLOWDATA     'F'     //为请求收款机流水数据
#define cmdANSWER       'A'     //为对host的应答命�?
#define cmdGRAPHIC      'G'     //为下载图�?
#define cmdCLEAR        'C'     //清除报表
#define cmdINIT         'I'     //收款机初始化
#define cmdSERVER       'S'     //设置收款机的服务器地址
#define cmdPASSWORD     'W'     //设置收款员密�?

#define F_UPDATA	0x01
#define F_DOWNLOAD  0x02

#define F_GROUP     0x01
#define F_DEPT      0x02
#define F_PLU       0x03

#define ITEMMODEL 1

namespace Ui {
class formDialog;
}

class QVariantListListModel;
class QStandardItemModel;
class tcpclient;
class csv;

class formDialog : public QDialog
{
    Q_OBJECT

public:
    explicit formDialog(QWidget *parent = 0);
    ~formDialog();

    void setformtype(char fmtype);
    void setiplist(QString IP, QString SHOPNAME, bool checked);

private:
    Ui::formDialog *ui;

    //QScopedPointer<ExcelBase> m_xls;
    QList< QList<QVariant> > m_datas;
#if ITEMMODEL
#else
    QVariantListListModel* m_md;
#endif

    QScopedPointer<csv> m_csv;
    QFile csvFile;

    char formtype;
    dept *DeptType;
    plu *PluType;

    int itemindex;
    int senditemmax;
    char recvbuf[1024];
    char sendbuf[1024];

	int IpIndex;
    int IpIndexMax;
    QString IpStr;
    char udflag;//0x1 上传 0x2 下载

    QTimer *timer;

    QString savexlsFile;

    void createdata(int type);
    void dataparse(char *buf, int len);
    QString getQssContent(char type); //0x01 tableview 0x02 tablewidget
    void save_xlsfile(char type);

    void save_csvfile(char type);

#if ITEMMODEL
    QStandardItemModel *itemModel;
    void itemModel_setvalue(QList< QList<QVariant> > *datas);
    void itemModel_getvalue(QList< QList<QVariant> > *datas);
#endif

    tcpclient *formtcpclient;
    QString xlsFiledir;
    QString csvFiledir;

    void tcpconnectcash(char type);

signals:
    void unconnecthost();
    void connecthost();
    void recvdata(char *buf, int len);
    void senddata(char *buf, int len);

    void resetserver();

private slots:
    void recvdataok(int sizelen);
    void tcpstate(int type);
    void on_openfile_clicked();
    void on_update_clicked();
    void on_download_clicked();
    void slotsSelectAll(int state);
    void cmpTime();

    void on_tableView_doubleClicked(const QModelIndex &index);

public:
    void settcpclient(tcpclient *fmtcpclient);
};

#endif // FORMDIALOG_H
