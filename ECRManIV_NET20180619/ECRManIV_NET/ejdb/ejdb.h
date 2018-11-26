#ifndef EJDB_H
#define EJDB_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDateTime>
#include <QTime>

typedef struct Ej_Data{
    int Indx;
    char IP[32];
    char  Name[32];
    int datalen;
    char blobbuf[4096];
}EJData;

class ejdb : public QObject
{
    Q_OBJECT
public:
    explicit ejdb(QObject *parent = 0);
    ~ejdb();

    int connectdb();
    int disconnectdb();

    void setejtime(QString data_time){EJTime = QDateTime::fromString(data_time, "yyyy-MM-dd hh:mm:ss");}
    void setejTimeFrom(QDateTime ejtimefrom){EJTimeFrom = ejtimefrom;}
    void setejTimeTo(QDateTime ejtimeto){EJTimeTo = ejtimeto;}

private:
    QSqlDatabase ej_db;
    QString ej_dbPath;
    QSqlQuery sql_query;
    QDateTime EJTime;

    QDateTime EJTimeFrom;
    QDateTime EJTimeTo;

    QTime TimeFrom;

    int initej(QString tablename);

    int initdb();

public:
    int inserttable(QString tablename, EJData data);

    int selecttable(QString tablename, EJData *data);
    int selecttable(QString tablename, EJData *data, QDateTime ejTimeFrom, QDateTime ejTimeTo);

signals:

public slots:
};

#endif // EJDB_H
