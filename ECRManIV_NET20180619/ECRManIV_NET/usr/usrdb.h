#ifndef USRDB_H
#define USRDB_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>

#define ADMUSR 1
#define SUPUSR 2
#define ORDUSR 3

#define ADMPMS 1
#define SUPPMS 2
#define ORDPMS 3

#define CLERKPERM           0x01
#define GROUPPERM           0x02
#define DEPARTMENTPERM      0x04
#define PLUPERM             0x08
#define DISCOUNTPERM        0x10
#define TAXPERM             0x20
#define TICKETPERM          0x40
#define OFFERPERM           0x80
#define REPORTPERM          0x100

typedef struct userinfo {
    int group;
    char name[32];
    char password[32];
    unsigned int permission;
}USRINFO;

class usrdb : public QObject
{
    Q_OBJECT
public:
    explicit usrdb(QObject *parent = 0);
    ~usrdb();

    USRINFO UsrInfo;
    USRINFO CUsrInfo;

    int inserttable(USRINFO data, QString tablename = QString("USRMG"));

    int selecttable(USRINFO *data, QString tablename = QString("USRMG"));
    int selectgrouptable(USRINFO usrdata, char *data, QString tablename = QString("USRMG"));

    int deleteusr(USRINFO data, QString tablename = QString("USRMG"));

    int modusr(USRINFO olddata, USRINFO newdata, QString tablename = QString("USRMG"));

    int checkusr(QString UsrName, QString tablename = QString("USRMG"));

private:
    int connectdb();
    int initusr(QString tablename);

    int initdb();

    void initadmin();

private:
    QSqlDatabase usr_db;
    QString usr_dbPath;
    QSqlQuery sql_query;

signals:

public slots:
};

extern usrdb *UsrDb;

#endif // USRDB_H
