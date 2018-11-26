#include "flowbilldb.h"
#include <QMessageBox>
#include <QDebug>
#include <QSqlError>

flowbilldb::flowbilldb()
{
    ej_dbPath = "./EJData.db";
    connectdb();

    sql_query = QSqlQuery(ej_db);

    initdb();
}

flowbilldb::~flowbilldb()
{
    qDebug() << "close ej_db!";
    ej_db.close();//关闭数据库
}

int flowbilldb::connectdb()
{
    if (QSqlDatabase::contains("ej_sql_connection"))
    {
        ej_db = QSqlDatabase::database("ej_sql_connection");
    }
    else
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

int flowbilldb::initdb()
{
    ej_db.transaction();

    initej(QString("EJ"));

    ej_db.commit();

    return true;
}

int flowbilldb::initej(QString tablename)
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

int flowbilldb::inserttable(QString tablename, EJData data)
{
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

int flowbilldb::inserttable(QSqlQuery dbQuery, EJData data, QDateTime dataTime)
{
    //判断数据是否存在，不存在插入
    QString sql_select = QString("SELECT Indx FROM EJ WHERE IP = :IP AND EJTime = '%2'")
            .arg(dataTime.toString("yyyy-MM-dd hh:mm:ss"));
    dbQuery.prepare(sql_select);
    dbQuery.bindValue(":IP", data.IP);
    if(!dbQuery.exec())
    {
        qDebug()<<dbQuery.lastError();
        return false;
    }
    else
    {
        if(dbQuery.next())
        {
            if(dbQuery.value(0).toInt() > 0)
            {
                qDebug() << "data is exist!";
                return -1;//数据存在
            }
        }
    }

    QString sql_insert = QString("INSERT INTO EJ VALUES(?,?,?,?,?)");
    dbQuery.prepare(sql_insert);

    dbQuery.addBindValue(data.Indx);
    dbQuery.addBindValue(data.IP);
    dbQuery.addBindValue(data.Name);

    QByteArray blobdata;
    blobdata.resize(data.datalen);
    qDebug() << "--->data.datalen = " << data.datalen;
    memcpy(blobdata.data(), data.blobbuf, data.datalen);
    dbQuery.addBindValue(blobdata, QSql::Binary);

    dbQuery.addBindValue(dataTime.toString("yyyy-MM-dd hh:mm:ss"));

    if(!dbQuery.exec())
    {
        qDebug()<<dbQuery.lastError();
        return false;
    }
    else
    {
        qDebug()<<"inserted success!";
    }

    return true;
}


int flowbilldb::selecttable(QString tablename, EJData *data)
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

int flowbilldb::selecttable(QString tablename, EJData *data, QDateTime ejTimeFrom, QDateTime ejTimeTo)
{
    QString MinDateTime;

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

    sql_select = QString("SELECT Indx, Name, Log FROM %1 WHERE IP = :IP AND EJTime = '%2'").arg(tablename)
            .arg(MinDateTime);
    sql_query.prepare(sql_select);

    sql_query.bindValue(":IP", data->IP);

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
            data->Indx = sql_query.value(0).toInt();

            QString Name = sql_query.value(1).toString();
            int NameLen = Name.toLocal8Bit().length();
            memcpy(data->Name, Name.toLocal8Bit().data(), NameLen);

            QByteArray blobdata;
            blobdata = sql_query.value(2).toByteArray();

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
