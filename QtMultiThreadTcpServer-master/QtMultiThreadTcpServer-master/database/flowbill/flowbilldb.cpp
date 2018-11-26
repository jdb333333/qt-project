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
                         "ShopID INT, IP CHARACTER(32), CashID CHARACTER(32), Log BLOB NOT NULL, EJTime DATETIME)").arg(tablename);
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

void flowbilldb::receipttotxtbuf(char *txtbuf, char *PrBuffer2, int datasize)
{
    int i, k, datalen;

    int j, m, n;
    unsigned char numchar;

    unsigned char flag;
    unsigned char pribuf[64];

    unsigned char databuf[64];
    unsigned char tmpdata1, tmpdata2;

    datalen = datasize;

    qDebug() << "receipttotxtbuf--->datalen = " << datalen;

    k = 0;
    flag = PrBuffer2[0];
    for(i = 1; i < datalen; i++)
    {
        if(PrBuffer2[i] != '\n')
        {
            databuf[k++] = PrBuffer2[i];
        }
        else
        {
            databuf[k] = '\0';
            m = strlen((char *)databuf);
            j = 0;
            for(n = 0; n < m; n++)
            {
                tmpdata1 = databuf[n] & 0xff;
                tmpdata2 = databuf[n + 1] & 0xff;
                //qDebug("tmpdata1 = %02x, tmpdata2 = %02x", tmpdata1, tmpdata2);
                //if(tmpdata1 == 0xf8 && tmpdata2 == 0xd0)//进纸
                if(tmpdata1 == 0x38 && tmpdata2 == 0xd8)//进纸
                {
                    //pribuf[j++] = databuf[n];
                    //pribuf[j++] = databuf[n + 1];
                    //pribuf[j++] = '\n';
                    //break;
                    qDebug() << "to skip";
                    goto skip;
                }
                else if(databuf[n] & 0x80)
                {
                    numchar = databuf[n] & 0x7f;
                    while(numchar)
                    {
                        pribuf[j++] = databuf[n - 1];
                        numchar = (numchar - 1) & 0xff;
                    }
                }
                else
                {
                    pribuf[j++] = databuf[n];
                }
            }
            pribuf[j] = '\0';

            strcpy(txtbuf + strlen(txtbuf), (char *)pribuf);

            skip:
            txtbuf[strlen(txtbuf)] = '\n';
            //qDebug("%s", pribuf);

            k = 0;
            i++;//跳过回车符
            flag = PrBuffer2[i];
        }
    }
}

int flowbilldb::inserttable(QString tablename, EJData data)
{
    //判断数据是否存在，不存在插入
    QString sql_select = QString("SELECT ShopID FROM %1 WHERE IP = :IP AND EJTime = '%2'").arg(tablename)
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
    QString sql_select = QString("SELECT ShopID FROM EJ WHERE IP = :IP AND EJTime = '%2'")
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

    QString sql_select = QString("SELECT MAX(ShopID) FROM %1 WHERE IP = :IP AND EJTime >= '%2' AND EJTime <= '%3'").arg(tablename)
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

    sql_select = QString("SELECT CashID, Log FROM %1 WHERE IP = :IP AND EJTime >= '%2' AND EJTime <= '%3' AND ShopID = :ShopID").arg(tablename)
            .arg(EJTimeFrom.toString("yyyy-MM-dd hh:mm:ss")).arg(EJTimeTo.toString("yyyy-MM-dd hh:mm:ss"));
    sql_query.prepare(sql_select);

    sql_query.bindValue(":ShopID", data->Indx);
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

    sql_select = QString("SELECT ShopID, CashID, Log FROM %1 WHERE IP = :IP AND EJTime = '%2'").arg(tablename)
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
