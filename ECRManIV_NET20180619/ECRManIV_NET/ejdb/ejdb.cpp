#include "ejdb.h"

#include <QMessageBox>
#include <QDebug>
#include <QSqlError>

//#define EJTEST

ejdb::ejdb(QObject *parent) : QObject(parent)
{
    ej_dbPath = "./EJData.db";
    connectdb();

    sql_query = QSqlQuery(ej_db);

    initdb();

#ifdef EJTEST
    int i, j;

    EJData data;
    memset(&data, 0, sizeof(EJData));
    data.Indx = 1;
    strcpy(data.IP, QString("192.168.99.143").toLocal8Bit().data());

    j = 0;
    for(i = 0; i < 10; i++, j++)
    {
        data.blobbuf[j] = 0x0;
    }

    for(i = 0; i < 10; i++, j++)
    {
        data.blobbuf[j] = i;
    }

    for(i = 0; i < 10; i++, j++)
    {
        data.blobbuf[j] = 0x0;
    }

    for(i = 0; i < 10; i++, j++)
    {
        data.blobbuf[j] = j;
    }

    data.datalen = j;

    inserttable(QString("EJ"), data);

    data.Indx = 2;
    j = 0;
    for(i = 0; i < 5; i++, j++)
    {
        data.blobbuf[j] = i;
    }

    inserttable(QString("EJ"), data);

    EJTimeFrom = QDateTime::fromString(QString("2018-07-08 00:00:00"), "yyyy-MM-dd hh:mm:ss");
    EJTimeTo = QDateTime::fromString(QString("2018-07-08 23:59:59"), "yyyy-MM-dd hh:mm:ss");
    memset(&data, 0, sizeof(EJData));

    data.Indx = 1;
    strcpy(data.IP, QString("192.168.99.143").toLocal8Bit().data());

    int ret;
    while(1)
    {
        ret = selecttable(QString("EJ"), &data);

        if(ret < 0)
        {
            break;
        }

        qDebug("--->ejtest");
        for(i = 0; i < data.datalen; i++)
        {
            qDebug("data.blobbuf[%d] = %02x", i, data.blobbuf[i]);
        }

        data.Indx++;
    }

#endif
}

ejdb::~ejdb()
{

}

int ejdb::connectdb()
{
#if 1
    if (QSqlDatabase::contains("ej_sql_connection"))
    {
        ej_db = QSqlDatabase::database("ej_sql_connection");
    }
    else
#endif
    {
        ej_db = QSqlDatabase::addDatabase("QSQLITE", "ej_sql_connection");
        ej_db.setDatabaseName(ej_dbPath);
        ej_db.setUserName("root");
        ej_db.setPassword("123456");
    }

    if(!ej_db.open())
    {
        QMessageBox::critical(0, "can not open ej_db database",
                              "Unable to establish a ej_db database connection.", QMessageBox::Cancel);
        return false;
    }else
    {
        qDebug("open ej_db database ok!");
    }

    return true;
}

int ejdb::initdb()
{
    ej_db.transaction();

    initej(QString("EJ"));

    ej_db.commit();

    return true;
}

int ejdb::initej(QString tablename)
{
    QString exist_sql = QString("select count(*) from sqlite_master where type='table' and name='%1'").arg(tablename);
    sql_query.prepare(exist_sql);

    if(!sql_query.exec())
    {
        qDebug() << QString("Error: Fail to check %1 Table.").arg(tablename);
    }
    else
    {
        if(sql_query.next())
        {
            if(sql_query.value(0).toInt()==0)
            {
                qDebug() << QString("%1 Table does not exist.").arg(tablename);
            }
            else
            {
                qDebug() << QString("%1 Table exists.").arg(tablename);
                return true;
            }
        }
    }

    QString create_sql = QString("create table %1 ("
                         "Indx INT, IP CHARACTER(32), Name CHARACTER(32), Log BLOB NOT NULL, EJTime DATETIME)").arg(tablename);
    sql_query.prepare(create_sql);
    if(!sql_query.exec())
    {
        qDebug() << QString("Error: Fail to create %1 Table.").arg(tablename);
    }
    else
    {
        qDebug() << QString("%1 Table created!").arg(tablename);
    }

    return true;
}

int ejdb::inserttable(QString tablename, EJData data)
{
    //EJTime = QDateTime::currentDateTime();

    //判断数据是否存在，不存在插入
    QString sql_select = QString("SELECT Indx FROM %1 WHERE IP = :IP AND EJTime = '%2'").arg(tablename)
            .arg(EJTime.toString("yyyy-MM-dd hh:mm:ss"));
    sql_query.prepare(sql_select);
    sql_query.bindValue(":IP", data.IP);
    if(!sql_query.exec())
    {
        qDebug()<<sql_query.lastError();
        return false;
    }
    else
    {
        if(sql_query.next())
        {
            if(sql_query.value(0).toInt() > 0)
            {
                qDebug() << "data is exist!";
                return -1;//数据存在
            }
        }
    }

    QString sql_insert = QString("INSERT INTO %1 VALUES(?,?,?,?,?)").arg(tablename);
    sql_query.prepare(sql_insert);

    sql_query.addBindValue(data.Indx);
    sql_query.addBindValue(data.IP);
    sql_query.addBindValue(data.Name);

    QByteArray blobdata;
    blobdata.resize(data.datalen);
    qDebug() << "--->data.datalen = " << data.datalen;
    memcpy(blobdata.data(), data.blobbuf, data.datalen);
    sql_query.addBindValue(blobdata, QSql::Binary);

    sql_query.addBindValue(EJTime.toString("yyyy-MM-dd hh:mm:ss"));

    if(!sql_query.exec())
    {
        qDebug()<<sql_query.lastError();
        return false;
    }
    else
    {
        qDebug()<<"inserted success!";
    }

    return true;
}

int ejdb::selecttable(QString tablename, EJData *data)
{
    int maxindx;

    QString sql_select = QString("SELECT MAX(Indx) FROM %1 WHERE IP = :IP AND EJTime >= '%2' AND EJTime <= '%3'").arg(tablename)
            .arg(EJTimeFrom.toString("yyyy-MM-dd hh:mm:ss")).arg(EJTimeTo.toString("yyyy-MM-dd hh:mm:ss"));

    sql_query.prepare(sql_select);

    qDebug("--->data->IP = %s", data->IP);
    sql_query.bindValue(":IP", data->IP);

    qDebug() << sql_select;


    if(!sql_query.exec())
    {
        qDebug()<<sql_query.lastError();
        return false;
    }
    else
    {
        while(sql_query.next())
        {
            maxindx = sql_query.value(0).toInt();
        }
        qDebug() << "--->maxindx = " << maxindx;
    }

    if(maxindx < data->Indx)
    {
        return -1;
    }

    sql_select = QString("SELECT Name, Log FROM %1 WHERE IP = :IP AND EJTime >= '%2' AND EJTime <= '%3' AND Indx = :Indx").arg(tablename)
            .arg(EJTimeFrom.toString("yyyy-MM-dd hh:mm:ss")).arg(EJTimeTo.toString("yyyy-MM-dd hh:mm:ss"));
    sql_query.prepare(sql_select);

    sql_query.bindValue(":Indx", data->Indx);
    sql_query.bindValue(":IP", data->IP);

    if(!sql_query.exec())
    {
        qDebug()<<sql_query.lastError();
        return false;
    }
    else
    {
        qDebug()<<"check exist success!";
        if(sql_query.next())
        {
            QString Name = sql_query.value(0).toString();
            int NameLen = Name.toLocal8Bit().length();
            memcpy(data->Name, Name.toLocal8Bit().data(), NameLen);

            QByteArray blobdata;
            blobdata = sql_query.value(1).toByteArray();

            data->datalen = blobdata.size();
            qDebug("--->data->datalen = %d", data->datalen);

            memcpy(data->blobbuf, blobdata.data(), data->datalen);
        }
    }

    return 0;
}

int ejdb::selecttable(QString tablename, EJData *data, QDateTime ejTimeFrom, QDateTime ejTimeTo)
{
    int maxindx;
    QString MinDateTime;

#if 0
    QString sql_select = QString("SELECT MAX(Indx) FROM %1 WHERE IP = :IP AND EJTime > '%2' AND EJTime <= '%3'").arg(tablename)
            .arg(ejTimeFrom.toString("yyyy-MM-dd hh:mm:ss")).arg(ejTimeTo.toString("yyyy-MM-dd hh:mm:ss"));

    sql_query.prepare(sql_select);

    qDebug("--->data->IP = %s", data->IP);
    sql_query.bindValue(":IP", data->IP);

    qDebug() << sql_select;

    if(!sql_query.exec())
    {
        qDebug()<<sql_query.lastError();
        return -1;
    }
    else
    {
        while(sql_query.next())
        {
            maxindx = sql_query.value(0).toInt();
        }
        qDebug() << "--->maxindx = " << maxindx;
    }

    if(maxindx < data->Indx)
    {
        return -1;
    }
#else
    QString sql_select = QString("SELECT MIN(EJTime) FROM %1 WHERE IP = :IP AND EJTime > '%2' AND EJTime <= '%3'").arg(tablename)
            .arg(EJTimeFrom.toString("yyyy-MM-dd hh:mm:ss")).arg(EJTimeTo.toString("yyyy-MM-dd hh:mm:ss"));

    sql_query.prepare(sql_select);

    qDebug("--->data->IP = %s", data->IP);
    sql_query.bindValue(":IP", data->IP);

    qDebug() << sql_select;

    if(!sql_query.exec())
    {
        qDebug()<<sql_query.lastError();
        return -1;
    }
    else
    {
        if(sql_query.next())
        {
            MinDateTime = sql_query.value(0).toString();
            if(MinDateTime.size() > 0)
            {
                EJTimeFrom = QDateTime::fromString(MinDateTime, "yyyy-MM-dd hh:mm:ss");
            }
            else
            {
                return -1;
            }

            qDebug() << "--->MinDateTime = " << MinDateTime;
            qDebug() << "--->EJTimeFrom = " << EJTimeFrom;
            //return -1;
        }
        else
        {
            return -1;
        }
    }

#endif

#if 0
    sql_select = QString("SELECT Name, Log FROM %1 WHERE IP = :IP AND EJTime > '%2' AND EJTime <= '%3' AND Indx = :Indx").arg(tablename)
            .arg(ejTimeFrom.toString("yyyy-MM-dd hh:mm:ss")).arg(ejTimeTo.toString("yyyy-MM-dd hh:mm:ss"));
    sql_query.prepare(sql_select);

    sql_query.bindValue(":Indx", data->Indx);
    sql_query.bindValue(":IP", data->IP);
#else
    sql_select = QString("SELECT Indx, Name, Log FROM %1 WHERE IP = :IP AND EJTime = '%2'").arg(tablename)
            .arg(MinDateTime);
    sql_query.prepare(sql_select);

    sql_query.bindValue(":IP", data->IP);
#endif

    if(!sql_query.exec())
    {
        qDebug()<<sql_query.lastError();
        return -1;
    }
    else
    {
        qDebug()<<"check exist success!";
        if(sql_query.next())
        {
#if 0
            QString Name = sql_query.value(0).toString();
            int NameLen = Name.toLocal8Bit().length();
            memcpy(data->Name, Name.toLocal8Bit().data(), NameLen);

            QByteArray blobdata;
            blobdata = sql_query.value(1).toByteArray();
#else
            data->Indx = sql_query.value(0).toInt();

            QString Name = sql_query.value(1).toString();
            int NameLen = Name.toLocal8Bit().length();
            memcpy(data->Name, Name.toLocal8Bit().data(), NameLen);

            QByteArray blobdata;
            blobdata = sql_query.value(2).toByteArray();
#endif

            data->datalen = blobdata.size();
            qDebug("--->data->datalen = %d", data->datalen);

            memcpy(data->blobbuf, blobdata.data(), data->datalen);
        }
        else
        {
            return 0;
        }
    }

    return data->datalen;
}
