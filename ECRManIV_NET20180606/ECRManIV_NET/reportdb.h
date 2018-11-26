#ifndef REPORTDB_H
#define REPORTDB_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QStandardItemModel>

#define GRANDTOTALREPORT    0x1
#define DEPARTMENTREPORT    0x2
#define TENDERREPORT        0x4
#define DRAWERREPORT        0x8
#define CORRECTREPORT       0x10
#define DISCOUNTREPORT      0x20
#define TAXREPORT           0x40
#define PLUREPORT           0x80

#define DAILYREPORT         0x1
#define WEEKREPORT          0x2
#define ZONEREPORT          0x10
#define CLERKDAILY          0x20
#define CLERKWEEK           0x40
#define PLUDAILY            0x80

#define GRANDTOTAL          "grandtotal"
#define DEPARTMENT          "department"
#define TENDER              "tender"
#define DRAWER              "drawer"
#define CORRECT             "correction"
#define DISCOUNT            "discount"
#define TAX                 "tax"
#define PLU                 "plu"

#define CLERKNUM    5
#define ZONENUM     12

#define WRITEDBOK   0x8

class tcpthread;

typedef struct reportdata{
    int ID;
    char IP[32];
    char  Name[32];
    float Cc;
    float Qty;
    float Amt;
    float Ret;
    float Disc;
    float Cost;
    int ZNo;
}RData;

class reportdb : public QObject
{
    Q_OBJECT
public:
    explicit reportdb(QObject *parent = 0);
    ~reportdb();

    int connectdb();
    int disconnectdb();
    void dbtransaction();
    void dbcommit();

    int writetable(QString suffixtablename, int idx, unsigned int options, RData data);
    int writetable2(QString suffixtablename, int idx, unsigned int options, RData data);
    int readtable(QString suffixtablename, unsigned int options, int ZNo = 1,
                  RData *data = NULL, QStandardItemModel *reportModel = NULL, char Type = GRANDTOTALREPORT);

    int cleartable();

    int datadeal(char *buf, int len);

    int DataParse();
    friend void dbthreadrun();

    void setzno(int zno){ZNo = zno;}
    void setcashid(int id){cashid = id;}
    void setcaship(QString ip){IpStr = ip;}

private:
    int inserttable(QString tablename, RData data);
    int updatatable(QString tablename, RData data);

    int selecttable(QString tablename, unsigned int options, int ZNo, RData *data, QStandardItemModel *reportModel, int rows, char *Name, char Type);

    float BcdToFloat(char *bcd, int len, int decimal);

private:
    QSqlDatabase db;
    QString dbPath;
    QSqlQuery sql_query;
    int ZNo;
    int cashid;
    QString IpStr;
    bool flag;
    int initgrandtotal();
    int initdepartment();
    int inittender();
    int initdrawer();
    int initcorrect();
    int initdiscount();
    int inittax();
    int initplu();

    int inittotal(QString tablename);
    int initdb();

    int deleteitem(QString tablename);
    int deleteitemByZNo(QString tablename, int ZNo);
    int cleargrandtotal();
    int cleardepartment();
    int cleartender();
    int cleardrawer();
    int clearcorrect();
    int cleardiscount();
    int cleartax();
    int clearplu();

    friend class tcpthread;
    tcpthread *dbThread;

    QString DbSuffixTablename;
    int DbIdx;
    unsigned int DbOptions;
    RData DbData;

    char recvbuf[1024];
    int recvlen;

signals:
    void dbstate(int type);

public slots:
};

#endif // REPORTDB_H
