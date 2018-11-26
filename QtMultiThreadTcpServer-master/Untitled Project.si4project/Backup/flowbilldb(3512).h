#ifndef FLOWBILLDB_H
#define FLOWBILLDB_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDateTime>
#include <QTime>
#include <QMutex>
#include <QMutexLocker>

typedef struct Ej_Data{
    int Indx;
    char IP[32];
    char  Name[32];
    int datalen;
    char blobbuf[4096];
}EJData;

class flowbilldb
{
public:
    flowbilldb();
    ~flowbilldb();

public:
    int connectdb();
    int disconnectdb();
    void setejtime(QString data_time){EJTime = QDateTime::fromString(data_time, "yyyy-MM-dd hh:mm:ss");}
    void setejTimeFrom(QDateTime ejtimefrom){EJTimeFrom = ejtimefrom;}
    void setejTimeTo(QDateTime ejtimeto){EJTimeTo = ejtimeto;}
    int inserttable(QString tablename, EJData data);
    int selecttable(QString tablename, EJData *data);
    int selecttable(QString tablename, EJData *data, QDateTime ejTimeFrom, QDateTime ejTimeTo);

private:
    int initej(QString tablename);
    int initdb();

private:
    QSqlDatabase ej_db;
    QString ej_dbPath;
    QSqlQuery sql_query;
    QDateTime EJTime;
    QDateTime EJTimeFrom;
    QDateTime EJTimeTo;
    QTime TimeFrom;
};

#endif // FLOWBILLDB_H
