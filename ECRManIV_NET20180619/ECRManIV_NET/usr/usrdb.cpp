#include "usrdb.h"

#include <QDebug>
#include <QSqlError>
#include <QMessageBox>

usrdb *UsrDb;

usrdb::usrdb(QObject *parent) : QObject(parent)
{
    usr_dbPath = "./USRData.db";
    connectdb();

    sql_query = QSqlQuery(usr_db);

    initdb();

    UsrDb = this;
}

usrdb::~usrdb()
{

}

void usrdb::initadmin()
{
    USRINFO testusr;
    testusr.group = ADMUSR;

    QString Name("admin");
    strcpy(testusr.name, Name.toLocal8Bit().data());

    QString PWD("123456");
    strcpy(testusr.password, PWD.toLocal8Bit().data());

    testusr.permission = ADMPMS;

    inserttable(testusr);
}

int usrdb::connectdb()
{
#if 1
    if (QSqlDatabase::contains("usr_sql_connection"))
    {
        usr_db = QSqlDatabase::database("usr_sql_connection");
    }
    else
#endif
    {
        usr_db = QSqlDatabase::addDatabase("QSQLITE", "usr_sql_connection");
        usr_db.setDatabaseName(usr_dbPath);
        usr_db.setUserName("root");
        usr_db.setPassword("123456");
    }

    if(!usr_db.open())
    {
        QMessageBox::critical(0, "can not open usr_db database",
                              "Unable to establish a usr_db database connection.", QMessageBox::Cancel);
        return false;
    }else
    {
        qDebug("open usr_db database ok!");
    }

    return true;
}

int usrdb::initusr(QString tablename)
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

#if 0
    QString create_sql = QString("create table %1 ("
                         "Indx INT, IP CHARACTER(32), Name CHARACTER(32), Log BLOB NOT NULL, EJTime DATETIME)").arg(tablename);
#else
    QString create_sql = QString("create table %1 ("
                         "UserGroup INT, UserName CHARACTER(32), UserPassword CHARACTER(32), UserPerm INT)").arg(tablename);
#endif
    qDebug() << "usr create sql:" << create_sql;
    sql_query.prepare(create_sql);
    if(!sql_query.exec())
    {
        qDebug() << QString("Error: Fail to create %1 Table.").arg(tablename);
    }
    else
    {
        qDebug() << QString("%1 Table created!").arg(tablename);
    }

    initadmin();

    return true;
}

int usrdb::initdb()
{
    usr_db.transaction();

    initusr(QString("USRMG"));

    usr_db.commit();

    return true;
}

int usrdb::deleteusr(USRINFO data, QString tablename)
{
    QString clear_sql = QString("DELETE FROM %1 WHERE UserName = :UserName").arg(tablename);

    sql_query.prepare(clear_sql);

    sql_query.bindValue(":UserName", data.name);

    if(!sql_query.exec())
    {
        qDebug()<<sql_query.lastError();
        return false;
    }
    else
    {
        qDebug()<<QString("delete %1 success!").arg(data.name);
    }

    return true;
}

int usrdb::inserttable(USRINFO data, QString tablename)
{
    QString sql_insert = QString("INSERT INTO %1 VALUES(?,?,?,?)").arg(tablename);
    sql_query.prepare(sql_insert);

    sql_query.addBindValue(data.group);
    sql_query.addBindValue(data.name);
    sql_query.addBindValue(data.password);
    sql_query.addBindValue(data.permission);

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

int usrdb::selecttable(USRINFO *data, QString tablename)
{
    QString sql_select = QString("SELECT UserGroup, UserPassword, UserPerm FROM %1 WHERE UserName = :UserName").arg(tablename);
    sql_query.prepare(sql_select);

    sql_query.bindValue(":UserName", data->name);

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
            data->group = sql_query.value(0).toInt();

            QString Password = sql_query.value(1).toString();
            strcpy(data->password, Password.toLocal8Bit().data());

            data->permission = sql_query.value(2).toUInt();

            qDebug() << "data->permission = " << data->permission;
        }
        else
        {
            return -1;
        }
    }

    return 0;
}

int usrdb::checkusr(QString UsrName, QString tablename)
{
    QString sql_select = QString("SELECT UserGroup, UserPassword, UserPerm FROM %1 WHERE UserName = '%2'").arg(tablename).arg(UsrName);
    sql_query.prepare(sql_select);

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
            return -1;
        }
        else
        {
            return 0;
        }
    }

    return 0;
}

int usrdb::selectgrouptable(USRINFO usrdata, char *data, QString tablename)
{
    int datalen = 0;
    USRINFO usrinfo;

    QString sql_select = QString("SELECT UserName, UserPassword, UserPerm FROM %1 WHERE UserGroup = :UserGroup").arg(tablename);
    sql_query.prepare(sql_select);

    sql_query.bindValue(":UserGroup", usrdata.group);

    if(!sql_query.exec())
    {
        qDebug()<<sql_query.lastError();
        return -1;
    }
    else
    {
        qDebug()<<"check exist success!";
        while(1)
        {
            if(sql_query.next())
            {
                memset(&usrinfo, 0, sizeof(usrinfo));
                usrinfo.group = usrdata.group;
                QString Name = sql_query.value(0).toString();
                strcpy(usrinfo.name, Name.toLocal8Bit().data());

                QString Password = sql_query.value(1).toString();
                strcpy(usrinfo.password, Password.toLocal8Bit().data());

                usrinfo.permission = sql_query.value(2).toUInt();

                memcpy(data + datalen, &usrinfo, sizeof(usrinfo));
                datalen += sizeof(usrinfo);
            }
            else
            {
                break;
            }
        }
    }

    return datalen;
}

int usrdb::modusr(USRINFO olddata, USRINFO newdata, QString tablename)
{
    deleteusr(olddata, tablename);
    inserttable(newdata, tablename);

    return true;
}
