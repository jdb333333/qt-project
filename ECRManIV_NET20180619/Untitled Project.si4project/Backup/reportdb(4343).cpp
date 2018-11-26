#include "reportdb.h"

#include "tcpthread.h"

#include <QMessageBox>
#include <QDebug>
#include <QSqlError>



reportdb *ReportDb;
void dbthreadrun();

char dbreportname[8][32] = {
    GRANDTOTAL,
    DEPARTMENT,
    TENDER,
    DRAWER,
    CORRECT,
    DISCOUNT,
    TAX,
    PLU,
};

char ZONETABLE[12][32] = {
    "0:00-2:00",
    "2:00-4:00",
    "4:00-6:00",
    "6:00-8:00",
    "8:00-10:00",
    "10:00-12:00",
    "12:00-14:00",
    "14:00-16:00",
    "16:00-18:00",
    "18:00-20:00",
    "20:00-22:00",
    "22:00-24:00",
};

reportdb::reportdb(QObject *parent) : QObject(parent)
{
    dbPath = "./XZReport.db";
    connectdb();

    sql_query = QSqlQuery(db);

    initdb();

    flag = false;

    ReportDb = this;
    dbThread = new tcpthread;
    dbThread->setapprun(dbthreadrun);

    ZNo = 1;

    XZFlag = 0x01;
}

reportdb::~reportdb()
{
    disconnectdb();
}

void reportdb::SetDataTime(QDateTime pctime)
{
    //XZTime = QDateTime::fromString(timestr, "yyyy-MM-dd hh:mm:ss");
	XZTime = pctime;
}

void reportdb::dbtransaction()
{
    if(flag == false)
    {
        flag = true;
        qDebug() << "db start transaction";
        db.transaction();
    }
}

void reportdb::dbcommit()
{
    if(flag == true)
    {
        qDebug() << "db start commit";
        flag = false;
        db.commit();
    }
}

int reportdb::connectdb()
{
#if 1
    if (QSqlDatabase::contains("my_sql_connection"))
    {
        db = QSqlDatabase::database("my_sql_connection");
    }
    else
#endif
    {
        db = QSqlDatabase::addDatabase("QSQLITE", "my_sql_connection");
        //db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName(dbPath);
        db.setUserName("root");
        db.setPassword("123456");
    }

    if(!db.open())
    {
        QMessageBox::critical(0, "can not open database",
                              "Unable to establish a database connection.", QMessageBox::Cancel);
        return false;
    }else
    {
        qDebug("open database ok!");
    }

    return true;
}

int reportdb::disconnectdb()
{
    if(db.isOpen())
    {
        db.close();
        db.removeDatabase(dbPath);
    }

    return true;
}

int reportdb::inittotal(QString tablename)
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
                         "ID INT, IP CHARACTER(32), Name CHARACTER(32), Code CHARACTER(32), Cc FLOAT, Qty FLOAT, Amt FLOAT, Ret FLOAT, Disc FLOAT, Cost FLOAT, XZTime DATETIME, XZFlag INT, ZNo INT)").arg(tablename);
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

int reportdb::initgrandtotal()
{
    QString suffixname(GRANDTOTAL);
    inittotal(QString("daily%1").arg(suffixname));
	#ifdef WEEK_REPORT
    inittotal(QString("week%1").arg(suffixname));
	#endif
    inittotal(QString("clerk%1%2").arg("1daily").arg(suffixname));
    inittotal(QString("clerk%1%2").arg("2daily").arg(suffixname));
    inittotal(QString("clerk%1%2").arg("3daily").arg(suffixname));
    inittotal(QString("clerk%1%2").arg("4daily").arg(suffixname));
    inittotal(QString("clerk%1%2").arg("5daily").arg(suffixname));
	#ifdef WEEK_REPORT //不需要周报表
    inittotal(QString("clerk%1%2").arg("1week").arg(suffixname));
    inittotal(QString("clerk%1%2").arg("2week").arg(suffixname));
    inittotal(QString("clerk%1%2").arg("3week").arg(suffixname));
    inittotal(QString("clerk%1%2").arg("4week").arg(suffixname));
    inittotal(QString("clerk%1%2").arg("5week").arg(suffixname));
	#endif

    inittotal(QString("zone1%1").arg(suffixname));
    inittotal(QString("zone2%1").arg(suffixname));
    inittotal(QString("zone3%1").arg(suffixname));
    inittotal(QString("zone4%1").arg(suffixname));
    inittotal(QString("zone5%1").arg(suffixname));
    inittotal(QString("zone6%1").arg(suffixname));
    inittotal(QString("zone7%1").arg(suffixname));
    inittotal(QString("zone8%1").arg(suffixname));
    inittotal(QString("zone9%1").arg(suffixname));
    inittotal(QString("zone10%1").arg(suffixname));
    inittotal(QString("zone11%1").arg(suffixname));
    inittotal(QString("zone12%1").arg(suffixname));

    return true;
}

int reportdb::initdepartment()
{
    QString suffixname(DEPARTMENT);
    inittotal(QString("daily%1").arg(suffixname));
	#ifdef WEEK_REPORT
    inittotal(QString("week%1").arg(suffixname));
	#endif

    return true;
}

int reportdb::inittender()
{
    QString suffixname(TENDER);
    inittotal(QString("daily%1").arg(suffixname));
	#ifdef WEEK_REPORT
    inittotal(QString("week%1").arg(suffixname));
	#endif
    inittotal(QString("clerk%1%2").arg("1daily").arg(suffixname));
    inittotal(QString("clerk%1%2").arg("2daily").arg(suffixname));
    inittotal(QString("clerk%1%2").arg("3daily").arg(suffixname));
    inittotal(QString("clerk%1%2").arg("4daily").arg(suffixname));
    inittotal(QString("clerk%1%2").arg("5daily").arg(suffixname));
	#ifdef WEEK_REPORT
    inittotal(QString("clerk%1%2").arg("1week").arg(suffixname));
    inittotal(QString("clerk%1%2").arg("2week").arg(suffixname));
    inittotal(QString("clerk%1%2").arg("3week").arg(suffixname));
    inittotal(QString("clerk%1%2").arg("4week").arg(suffixname));
    inittotal(QString("clerk%1%2").arg("5week").arg(suffixname));
	#endif

    return true;
}

int reportdb::initdrawer()
{
    QString suffixname(DRAWER);
    inittotal(QString("daily%1").arg(suffixname));
	#ifdef WEEK_REPORT
    inittotal(QString("week%1").arg(suffixname));
	#endif
    inittotal(QString("clerk%1%2").arg("1daily").arg(suffixname));
    inittotal(QString("clerk%1%2").arg("2daily").arg(suffixname));
    inittotal(QString("clerk%1%2").arg("3daily").arg(suffixname));
    inittotal(QString("clerk%1%2").arg("4daily").arg(suffixname));
    inittotal(QString("clerk%1%2").arg("5daily").arg(suffixname));

    return true;
}

int reportdb::initcorrect()
{
    QString suffixname(CORRECT);
    inittotal(QString("daily%1").arg(suffixname));
	#ifdef WEEK_REPORT
    inittotal(QString("week%1").arg(suffixname));
	#endif
    inittotal(QString("clerk%1%2").arg("1daily").arg(suffixname));
    inittotal(QString("clerk%1%2").arg("2daily").arg(suffixname));
    inittotal(QString("clerk%1%2").arg("3daily").arg(suffixname));
    inittotal(QString("clerk%1%2").arg("4daily").arg(suffixname));
    inittotal(QString("clerk%1%2").arg("5daily").arg(suffixname));
	#ifdef WEEK_REPORT
    inittotal(QString("clerk%1%2").arg("1week").arg(suffixname));
    inittotal(QString("clerk%1%2").arg("2week").arg(suffixname));
    inittotal(QString("clerk%1%2").arg("3week").arg(suffixname));
    inittotal(QString("clerk%1%2").arg("4week").arg(suffixname));
    inittotal(QString("clerk%1%2").arg("5week").arg(suffixname));
	#endif

    return true;
}

int reportdb::initdiscount()
{
    QString suffixname(DISCOUNT);
    inittotal(QString("daily%1").arg(suffixname));
	#ifdef WEEK_REPORT
    inittotal(QString("week%1").arg(suffixname));
	#endif
    inittotal(QString("clerk%1%2").arg("1daily").arg(suffixname));
    inittotal(QString("clerk%1%2").arg("2daily").arg(suffixname));
    inittotal(QString("clerk%1%2").arg("3daily").arg(suffixname));
    inittotal(QString("clerk%1%2").arg("4daily").arg(suffixname));
    inittotal(QString("clerk%1%2").arg("5daily").arg(suffixname));
	#ifdef WEEK_REPORT
    inittotal(QString("clerk%1%2").arg("1week").arg(suffixname));
    inittotal(QString("clerk%1%2").arg("2week").arg(suffixname));
    inittotal(QString("clerk%1%2").arg("3week").arg(suffixname));
    inittotal(QString("clerk%1%2").arg("4week").arg(suffixname));
    inittotal(QString("clerk%1%2").arg("5week").arg(suffixname));
	#endif

    return true;
}

int reportdb::inittax()
{
    QString suffixname(TAX);
    inittotal(QString("daily%1").arg(suffixname));
	#ifdef WEEK_REPORT
    inittotal(QString("week%1").arg(suffixname));
	#endif

    return true;
}

int reportdb::initplu()
{
    QString suffixname(PLU);
    inittotal(QString("daily%1").arg(suffixname));
}

int reportdb::initdb()
{
    db.transaction();

    initgrandtotal();
    initdepartment();
    inittender();
    initdrawer();
    initcorrect();
    initdiscount();
    inittax();
    initplu();

    db.commit();

    return true;
}

int reportdb::deleteitem(QString tablename)
{
    //QString clear_sql = QString("DELETE FROM %1").arg(tablename);
    QString clear_sql = QString("DELETE FROM %1 WHERE ZNo = %2").arg(tablename).arg(ZNo);
    qDebug() << "deleteitem ip = " << QString("%1.%2.%3.%4").arg((ZNo >> 24) & 0xff).arg((ZNo >> 16) & 0xff)
                .arg((ZNo >> 8) & 0xff).arg(ZNo & 0xff);

    sql_query.prepare(clear_sql);

    if(!sql_query.exec())
    {
        qDebug()<<sql_query.lastError();
        return false;
    }
    else
    {
        qDebug()<<QString("clear %1 success!").arg(tablename);
    }

    return true;
}

int reportdb::deleteitemByZNo(QString tablename, int zno)
{
    QString clear_sql = QString("DELETE FROM %1 WHERE ZNo = %2").arg(tablename).arg(zno);

    sql_query.prepare(clear_sql);

    if(!sql_query.exec())
    {
        qDebug()<<sql_query.lastError();
        return false;
    }
    else
    {
        qDebug()<<QString("clear %1 success!").arg(tablename);
    }

    return true;
}

int reportdb::cleargrandtotal()
{
    int idx;
    QString suffixname(GRANDTOTAL);
    QString tablename;

    tablename = QString("daily%1").arg(suffixname);
    deleteitem(tablename);
	#ifdef WEEK_REPORT
    tablename = QString("week%1").arg(suffixname);
    deleteitem(tablename);
	#endif

    for(idx = 1; idx <= CLERKNUM; idx++)
    {
        tablename = QString("clerk%1daily%2").arg(idx).arg(suffixname);
        deleteitem(tablename);
		#ifdef WEEK_REPORT
        tablename = QString("clerk%1week%2").arg(idx).arg(suffixname);
        deleteitem(tablename);
		#endif
    }

    for(idx = 1; idx <= ZONENUM; idx++)
    {
        tablename = QString("zone%1%2").arg(idx).arg(suffixname);
        deleteitem(tablename);
    }

    return true;
}

int reportdb::cleardepartment()
{
    QString suffixname(DEPARTMENT);
    QString tablename;

    tablename = QString("daily%1").arg(suffixname);
    deleteitem(tablename);
	#ifdef WEEK_REPORT
    tablename = QString("week%1").arg(suffixname);
    deleteitem(tablename);
	#endif

    return true;
}

int reportdb::cleartender()
{
    int idx;
    QString suffixname(TENDER);
    QString tablename;

    tablename = QString("daily%1").arg(suffixname);
    deleteitem(tablename);
	#ifdef WEEK_REPORT
    tablename = QString("week%1").arg(suffixname);
    deleteitem(tablename);
	#endif

    for(idx = 1; idx <= CLERKNUM; idx++)
    {
        tablename = QString("clerk%1daily%2").arg(idx).arg(suffixname);
        deleteitem(tablename);
		#ifdef WEEK_REPORT
        tablename = QString("clerk%1week%2").arg(idx).arg(suffixname);
        deleteitem(tablename);
		#endif
    }

    return true;
}

int reportdb::cleardrawer()
{
    int idx;
    QString suffixname(DRAWER);
    QString tablename;

    tablename = QString("daily%1").arg(suffixname);
    deleteitem(tablename);
	#ifdef WEEK_REPORT
    tablename = QString("week%1").arg(suffixname);
    deleteitem(tablename);
	#endif

    for(idx = 1; idx <= CLERKNUM; idx++)
    {
        tablename = QString("clerk%1daily%2").arg(idx).arg(suffixname);
        deleteitem(tablename);
    }

    return true;
}

int reportdb::clearcorrect()
{
    int idx;
    QString suffixname(CORRECT);
    QString tablename;

    tablename = QString("daily%1").arg(suffixname);
    deleteitem(tablename);
	#ifdef WEEK_REPORT
    tablename = QString("week%1").arg(suffixname);
    deleteitem(tablename);
	#endif

    for(idx = 1; idx <= CLERKNUM; idx++)
    {
        tablename = QString("clerk%1daily%2").arg(idx).arg(suffixname);
        deleteitem(tablename);
		#ifdef WEEK_REPORT
        tablename = QString("clerk%1week%2").arg(idx).arg(suffixname);
        deleteitem(tablename);
		#endif
    }

    return true;
}

int reportdb::cleardiscount()
{
    int idx;
    QString suffixname(DISCOUNT);
    QString tablename;

    tablename = QString("daily%1").arg(suffixname);
    deleteitem(tablename);
	#ifdef WEEK_REPORT
    tablename = QString("week%1").arg(suffixname);
    deleteitem(tablename);
	#endif

    for(idx = 1; idx <= CLERKNUM; idx++)
    {
        tablename = QString("clerk%1daily%2").arg(idx).arg(suffixname);
        deleteitem(tablename);
		#ifdef WEEK_REPORT
        tablename = QString("clerk%1week%2").arg(idx).arg(suffixname);
        deleteitem(tablename);
		#endif
    }

    return true;
}

int reportdb::cleartax()
{
    QString suffixname(TAX);
    QString tablename;

    tablename = QString("daily%1").arg(suffixname);
    deleteitem(tablename);
	#ifdef WEEK_REPORT
    tablename = QString("week%1").arg(suffixname);
    deleteitem(tablename);
	#endif

    return true;
}

int reportdb::clearplu()
{
    QString suffixname(PLU);
    QString tablename;

    tablename = QString("daily%1").arg(suffixname);
    deleteitem(tablename);

    return true;
}

int reportdb::cleartable()
{
    db.transaction();

    cleargrandtotal();
    cleardepartment();
    cleartender();
    cleardrawer();
    clearcorrect();
    cleardiscount();
    cleartax();
    clearplu();

    db.commit();

    return true;
}

int reportdb::selecttable(QString tablename, unsigned int options, int ZNo, RData *data, QStandardItemModel *reportModel, int rows, char *Name, char Type)
{
    int rows_display = rows;
    float tmpdata;
    QString Datetime;

	QString sql_select = QString("SELECT MAX(XZTime) FROM %1 WHERE ZNo = :ZNo AND XZFlag = :XZFlag").arg(tablename);
    sql_query.prepare(sql_select);

	sql_query.bindValue(":ZNo", ZNo);
    sql_query.bindValue(":XZFlag", XZFlag);

	if(!sql_query.exec())
    {
        qDebug()<<sql_query.lastError();
        return false;
    }
	else
	{
		while(sql_query.next())
        {
            Datetime = sql_query.value(0).toString();
		}
        qDebug() << "--->Datetime = " << Datetime;
	}

    //QString sql_select = QString("SELECT ID, IP, Name, Cc, Qty, Amt, Ret, Disc, Cost, MAX(XZTime) FROM %1 WHERE ZNo = :ZNo AND XZFlag = :XZFlag").arg(tablename);
    sql_select = QString("SELECT ID, IP, Name, Code, Cc, Qty, Amt, Ret, Disc, Cost FROM %1 WHERE XZTime = :XZTime AND ZNo = :ZNo AND XZFlag = :XZFlag").arg(tablename);
    sql_query.prepare(sql_select);

    sql_query.bindValue(":XZTime", Datetime);
    sql_query.bindValue(":ZNo", ZNo);
    sql_query.bindValue(":XZFlag", XZFlag);

    if(!sql_query.exec())
    {
        qDebug()<<sql_query.lastError();
        return false;
    }
    else
    {
        qDebug()<<"check exist success!";
        while(sql_query.next())
        {
            if(data)
            {
            QString Name = sql_query.value(2).toString();
            int NameLen = Name.toLocal8Bit().length();
            memcpy(data->Name, Name.toLocal8Bit().data(), NameLen);

            data->Cc = sql_query.value(3).toDouble();
            data->Qty = sql_query.value(4).toDouble();
            data->Amt = sql_query.value(5).toDouble();
            data->Ret = sql_query.value(6).toDouble();
            data->Disc = sql_query.value(7).toDouble();
            data->Cost = sql_query.value(8).toDouble();

            qDebug() << "data->Name = " << QString(QLatin1String(data->Name)) << "data->Cc = " << data->Cc << "data->Qty = " << data->Qty << "data->Amt = " << data->Amt <<
                        "data->Ret = " << data->Ret << "data->Disc = " << data->Disc << "data->Cost = " << data->Cost;
            }

            if(reportModel)
            {
                reportModel->insertRow(rows_display);

                if((Type & GRANDTOTALREPORT) && (options != ZONEREPORT && options != CLERKDAILY && options != CLERKWEEK))
                {
                    //不提取名�?
                }
                else if(Name == NULL)
                {
                    reportModel->setData(reportModel->index(rows_display, 0), sql_query.value(2).toString());
                    reportModel->item(rows_display, 0)->setTextAlignment(Qt::AlignCenter);
                    reportModel->item(rows_display, 0)->setForeground(QBrush(QColor(0, 0, 255)));
                }
                else
                {
                    if(options == CLERKDAILY || options == CLERKWEEK)
                    {
                        reportModel->setData(reportModel->index(rows_display, 0),
                                             QString("%1(%2)").arg(QString(QLatin1String(Name))).arg(sql_query.value(2).toString()));
                    }
                    else
                    {
                        reportModel->setData(reportModel->index(rows_display, 0), QString(QLatin1String(Name)));
                    }

                    reportModel->item(rows_display, 0)->setTextAlignment(Qt::AlignCenter);
                    reportModel->item(rows_display, 0)->setForeground(QBrush(QColor(0, 0, 255)));
                }

                qDebug() << "Cc = " << sql_query.value(4).toDouble() << "Qty = " << sql_query.value(5).toDouble()
                                << "Amt = " << sql_query.value(6).toDouble() << "Ret = " << sql_query.value(7).toDouble()
                                << "Disc = " << sql_query.value(8).toDouble() << "Cost = " << sql_query.value(9).toDouble();

                if((Type & GRANDTOTALREPORT) && (options != ZONEREPORT && options != CLERKDAILY && options != CLERKWEEK))
                {
                    reportModel->setData(reportModel->index(rows_display, 0), sql_query.value(7).toString());
                    reportModel->item(rows_display, 0)->setTextAlignment(Qt::AlignCenter);
                    reportModel->item(rows_display, 0)->setForeground(QBrush(QColor(255, 0, 0)));
                    //tmpdata = sql_query.value(6).toDouble();
                    tmpdata = sql_query.value(9).toDouble() + sql_query.value(7).toDouble();
                    reportModel->setData(reportModel->index(rows_display, 1), QString("%1").arg(tmpdata));
                    reportModel->item(rows_display, 1)->setTextAlignment(Qt::AlignCenter);
                    reportModel->item(rows_display, 1)->setForeground(QBrush(QColor(255, 0, 0)));
                    tmpdata = sql_query.value(6).toDouble() + sql_query.value(8).toDouble();
                    reportModel->setData(reportModel->index(rows_display, 2), QString("%1").arg(tmpdata));
                    reportModel->item(rows_display, 2)->setTextAlignment(Qt::AlignCenter);
                    reportModel->item(rows_display, 2)->setForeground(QBrush(QColor(255, 0, 0)));
                }
                else
                {
#if 1
                    reportModel->setData(reportModel->index(rows_display, 1), sql_query.value(4).toString());
                    reportModel->item(rows_display, 1)->setTextAlignment(Qt::AlignCenter);
                    reportModel->item(rows_display, 1)->setForeground(QBrush(QColor(255, 0, 0)));

                    reportModel->setData(reportModel->index(rows_display, 2), sql_query.value(5).toString());
                    reportModel->item(rows_display, 2)->setTextAlignment(Qt::AlignCenter);
                    reportModel->item(rows_display, 2)->setForeground(QBrush(QColor(255, 0, 0)));

                    reportModel->setData(reportModel->index(rows_display, 3), sql_query.value(6).toString());
                    reportModel->item(rows_display, 3)->setTextAlignment(Qt::AlignCenter);
                    reportModel->item(rows_display, 3)->setForeground(QBrush(QColor(255, 0, 0)));

                    reportModel->setData(reportModel->index(rows_display, 4), sql_query.value(7).toString());
                    reportModel->item(rows_display, 4)->setTextAlignment(Qt::AlignCenter);
                    reportModel->item(rows_display, 4)->setForeground(QBrush(QColor(255, 0, 0)));

                    reportModel->setData(reportModel->index(rows_display, 5), sql_query.value(8).toString());
                    reportModel->item(rows_display, 5)->setTextAlignment(Qt::AlignCenter);
                    reportModel->item(rows_display, 5)->setForeground(QBrush(QColor(255, 0, 0)));

                    reportModel->setData(reportModel->index(rows_display, 6), sql_query.value(9).toString());
                    reportModel->item(rows_display, 6)->setTextAlignment(Qt::AlignCenter);
                    reportModel->item(rows_display, 6)->setForeground(QBrush(QColor(255, 0, 0)));
#else //去掉 Cc
                    reportModel->setData(reportModel->index(rows_display, 1), sql_query.value(2).toString());
                    reportModel->item(rows_display, 1)->setTextAlignment(Qt::AlignCenter);
                    reportModel->item(rows_display, 1)->setForeground(QBrush(QColor(255, 0, 0)));

                    reportModel->setData(reportModel->index(rows_display, 2), sql_query.value(3).toString());
                    reportModel->item(rows_display, 2)->setTextAlignment(Qt::AlignCenter);
                    reportModel->item(rows_display, 2)->setForeground(QBrush(QColor(255, 0, 0)));

                    reportModel->setData(reportModel->index(rows_display, 3), sql_query.value(4).toString());
                    reportModel->item(rows_display, 3)->setTextAlignment(Qt::AlignCenter);
                    reportModel->item(rows_display, 3)->setForeground(QBrush(QColor(255, 0, 0)));

                    reportModel->setData(reportModel->index(rows_display, 4), sql_query.value(5).toString());
                    reportModel->item(rows_display, 4)->setTextAlignment(Qt::AlignCenter);
                    reportModel->item(rows_display, 4)->setForeground(QBrush(QColor(255, 0, 0)));

                    reportModel->setData(reportModel->index(rows_display, 5), sql_query.value(6).toString());
                    reportModel->item(rows_display, 5)->setTextAlignment(Qt::AlignCenter);
                    reportModel->item(rows_display, 5)->setForeground(QBrush(QColor(255, 0, 0)));
#endif
                }

                rows_display++;
            }
        }
    }

    return rows_display;
}

int reportdb::readtable(QString suffixtablename, unsigned int options, int ZNo, RData *data, QStandardItemModel *reportModel, char Type)
{
    QString tablename;
    int rows = 0;
    int idx;
    char name[32] = {0};

	qDebug("--------------->ZNo = %04x", ZNo);

    if(options & DAILYREPORT)
    {
        tablename = QString("daily%1").arg(suffixtablename);
        qDebug() << "tablename = " << tablename;
    }
    else if(options & WEEKREPORT)
    {
        tablename = QString("week%1").arg(suffixtablename);
        qDebug() << "tablename = " << tablename;
    }
    else if(options & CLERKDAILY)
    {
    	#if 0
        for(idx = 1; idx <= CLERKNUM; idx++)
        {
            tablename = QString("clerk%1daily%2").arg(idx).arg(suffixtablename);
            qDebug() << "tablename = " << tablename;
            strcpy(name, QString("clerk%1").arg(idx).toLocal8Bit().data());
            rows = selecttable(tablename, options, ZNo, data, reportModel, rows, name, Type);
        }
		return true;
		#else
		tablename = QString("clerk%1daily%2").arg(clerknum).arg(suffixtablename);
        qDebug() << "tablename = " << tablename;
		#endif
    }
    else if(options & CLERKWEEK)
    {
        for(idx = 1; idx <= CLERKNUM; idx++)
        {
            tablename = QString("clerk%1week%2").arg(idx).arg(suffixtablename);
            qDebug() << "tablename = " << tablename;
            strcpy(name, QString("clerk%1").arg(idx).toLocal8Bit().data());
            rows = selecttable(tablename, options, ZNo, data, reportModel, rows, name, Type);
        }
        return true;
    }
    else if(options & ZONEREPORT)
    {
        for(idx = 1; idx <= ZONENUM; idx++)
        {
            tablename = QString("zone%1%2").arg(idx).arg(suffixtablename);
            qDebug() << "tablename = " << tablename;
            //strcpy(name, QString("ZONE%1").arg(idx).toLocal8Bit().data());
            strcpy(name, ZONETABLE[idx - 1]);
            rows = selecttable(tablename, options, ZNo, data, reportModel, rows, name, Type);
        }
        return true;
    }
    else if(options & PLUDAILY)
    {
        tablename = QString("daily%1").arg(suffixtablename);
        qDebug() << "tablename = " << tablename;
    }
    else
    {
        return false;
    }

    return selecttable(tablename, options, ZNo, data, reportModel, rows, NULL, Type);
}

int reportdb::inserttable(QString tablename, RData data)
{
    //XZTime = QDateTime::currentDateTime();

    QString sql_insert = QString("INSERT INTO %1 VALUES(?,?,?,?,?,?,?,?,?,?,?,?,?)").arg(tablename);
    sql_query.prepare(sql_insert);

    sql_query.addBindValue(data.ID);
    sql_query.addBindValue(data.IP);
    sql_query.addBindValue(data.Name);
	sql_query.addBindValue(data.Code);
    sql_query.addBindValue(data.Cc);
    sql_query.addBindValue(data.Qty);
    sql_query.addBindValue(data.Amt);
    sql_query.addBindValue(data.Ret);
    sql_query.addBindValue(data.Disc);
    sql_query.addBindValue(data.Cost);
    sql_query.addBindValue(XZTime.toString("yyyy-MM-dd hh:mm:ss"));
    sql_query.addBindValue(XZFlag);
    sql_query.addBindValue(data.ZNo);

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

int reportdb::updatatable(QString tablename, RData data)
{
    QString update_sql = QString("update %1 set ID = :ID, IP = :IP, Cc = :Cc, Qty = :Qty, Amt = :Amt, "
                                 "Ret = :Ret, Disc = :Disc, Cost = :Cost where Name = :Name AND ZNo = :ZNo").arg(tablename);
    sql_query.prepare(update_sql);

    sql_query.bindValue(":ID", data.ID);
    sql_query.bindValue(":IP", data.IP);
    sql_query.bindValue(":Name", data.Name);
    sql_query.bindValue(":Cc", data.Cc);
    sql_query.bindValue(":Qty", data.Qty);
    sql_query.bindValue(":Amt", data.Amt);
    sql_query.bindValue(":Ret", data.Ret);
    sql_query.bindValue(":Disc", data.Disc);
    sql_query.bindValue(":Cost", data.Cost);
    sql_query.bindValue(":ZNo", data.ZNo);

    if(!sql_query.exec())
    {
        qDebug()<<sql_query.lastError();
        return false;
    }
    else
    {
        qDebug()<<"update success!";
    }

    return true;
}

int reportdb::writetable(QString suffixtablename, int idx, unsigned int options, RData data)
{
#if 1
    DbSuffixTablename = suffixtablename;
    DbIdx = idx;
    DbOptions = options;
    DbData = data;

    dbThread->run();
#else
    QString tablename;

    if(options & DAILYREPORT)
    {
        tablename = QString("daily%1").arg(suffixtablename);
        qDebug() << "tablename = " << tablename;
    }
    else if(options & WEEKREPORT)
    {
        tablename = QString("week%1").arg(suffixtablename);
        qDebug() << "tablename = " << tablename;
    }
    else if(options & ZONEREPORT)
    {
        inittotal(QString("zone%1%2").arg(idx).arg(suffixtablename));
    }
    else if(options & CLERKDAILY)
    {
        tablename = QString("clerk%1daily%2").arg(idx).arg(suffixtablename);
    }
    else if(options & CLERKWEEK)
    {
        tablename = QString("clerk%1week%2").arg(idx).arg(suffixtablename);
    }
    else
    {
        return false;
    }

    QString exist_sql = QString("select count(*) from %1 where Name = :Name AND ZNo = :ZNo").arg(tablename);
    qDebug() << exist_sql;
    sql_query.prepare(exist_sql);

    sql_query.bindValue(":Name", data.Name);
    sql_query.bindValue(":ZNo", data.ZNo);

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
            if(sql_query.value(0).toInt()==0)
            {
                qDebug() << QString("%1 data does not exist.insert data.").arg(tablename);
                return inserttable(tablename, data);
            }
            else
            {
                qDebug() << QString("%1 data exists.updata data.").arg(tablename);
                return updatatable(tablename, data);
            }
        }
    }
#endif

    return true;
}

int reportdb::writetable2(QString suffixtablename, int idx, unsigned int options, RData data)
{
    QString tablename;

    if(options & DAILYREPORT)
    {
        tablename = QString("daily%1").arg(suffixtablename);
        qDebug() << "tablename = " << tablename;
    }
	else if(options & PLUDAILY)
    {
        tablename = QString("daily%1").arg(suffixtablename);
    }
	else if(options & ZONEREPORT)
    {
        tablename = QString("zone%1%2").arg(idx).arg(suffixtablename);
    }
	else if(options & CLERKDAILY)
    {
        tablename = QString("clerk%1daily%2").arg(idx).arg(suffixtablename);
    }
	#ifdef WEEK_REPORT //不需要周报表
    else if(options & WEEKREPORT)
    {
        tablename = QString("week%1").arg(suffixtablename);
        qDebug() << "tablename = " << tablename;
    }
    else if(options & CLERKWEEK)
    {
        tablename = QString("clerk%1week%2").arg(idx).arg(suffixtablename);
    }
	#endif
    else
    {
        return false;
    }

    //XZTime = QDateTime::currentDateTime();

    QString exist_sql = QString("select count(*) from %1 where Name = :Name AND ZNo = :ZNo AND XZTime = :XZTime").arg(tablename);
    qDebug() << exist_sql;
    sql_query.prepare(exist_sql);

    sql_query.bindValue(":Name", data.Name);
    sql_query.bindValue(":ZNo", data.ZNo);
    sql_query.bindValue(":XZTime", XZTime.toString("yyyy-MM-dd hh:mm:ss"));

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
            if(sql_query.value(0).toInt()==0)
            {
                qDebug() << QString("%1 data does not exist.insert data.").arg(tablename);
                inserttable(tablename, data);
            }
            else
            {
                qDebug() << QString("%1 data exists.updata data.").arg(tablename);
                updatatable(tablename, data);
            }

            qDebug() << "-------->start emit write db ok";
            //emit dbstate(WRITEDBOK);
        }
    }

    return true;
}

int reportdb::datadeal(char *buf, int len)
{
    memcpy(recvbuf, buf, len);
    recvlen = len;

    dbThread->run();

    return true;
}

float reportdb::BcdToFloat(char *bcd, int len, int decimal)
{
    int count;
    float data = 0;
    int tmp1, tmp2;

    if(bcd[len - 1] == 0xff)
    {
        return 0;
    }

    //qDebug() << "------->len = " << len;

    for(count = 1; count <= len; count++)
    {
        data *= 100.0;
        tmp1 = bcd[len - count] & 0x0f;
        tmp2 = (bcd[len - count] >> 4) & 0x0f;
        //qDebug() << "tmp2 = " << tmp2 << "tmp1 = " << tmp1;
        data += tmp2 * 10 + tmp1;
        //qDebug() << "data = tmp2*10 + tmp1 = " << data;
    }

    for(count = 0; count < decimal; count++)
    {
        data /= 10.0;
    }

    //qDebug() << "data = " << data;

    return data;
}

void reportdb::BcdToStr(char *bcd, int len, char *Str)
{
    int count;
    int tmp1, tmp2;
	QString data;

    if(bcd[len - 1] == 0xff)
    {
        return 0;
    }

    //qDebug() << "------->len = " << len;

    for(count = 1; count <= len; count++)
    {
        tmp1 = bcd[len - count] & 0x0f;
        tmp2 = (bcd[len - count] >> 4) & 0x0f;
        //qDebug() << "tmp2 = " << tmp2 << "tmp1 = " << tmp1;
        data += QString("%1%2").arg(tmp2).arg(tmp1);
        //qDebug() << "data = tmp2*10 + tmp1 = " << data;
    }

    strcpy(Str, data.toLocal8Bit().data());

    //qDebug() << "data = " << data;
}


int reportdb::DataParse()
{
    int NIdx, type, Cc, Qty, Amt, Ret, Disc, Cost;
    QString suffixname;
    int NameLen, CodeLen;
    char NType;
    char ReportName[32];

    for(NIdx = 0; 1; NIdx++) //获取报表后缀�?GRAND DEPT...
    {
        if(((recvbuf[3]&0xff) >> NIdx) == 0x01)
        {
            break;
        }
    }
    suffixname = QString(QLatin1String(dbreportname[NIdx]));

    int count = 4; //第四个字节开始是有效数据

    if((recvbuf[3]&0xff) == 0x80)
    {
        //plu
        qDebug() << "---------------->plu";
    }
    else
    {
        NameLen = recvbuf[count++];
        if(NameLen > 0) //获取名字
        {
            memcpy(ReportName, recvbuf + count, NameLen);
            count += NameLen;
        }
        else
        {
            memcpy(ReportName, dbreportname[NIdx], strlen(dbreportname[NIdx]));
            NameLen = strlen(dbreportname[NIdx]);
        }
    }

    while(count < recvlen)
    {
    RData data;
    memset((char *)(&data), 0, sizeof(RData));

    NType = recvbuf[count++]; //报表类型
    NIdx = recvbuf[count++]; //报表索引 TIME1, TIME2, TIME3...

    qDebug("NType = %02x, NIdx = %02x", NType, NIdx);

    Cc = recvbuf[count++];
    Qty = recvbuf[count++];
    Amt = recvbuf[count++];
    Ret = recvbuf[count++];
    Disc = recvbuf[count++];
    Cost = recvbuf[count++];

    qDebug() << "Cc = " << Cc << ", Qty = " << Qty << ", Amt = " << Amt <<
                ", Ret = " << Ret << ", Disc = " << Disc << ", Cost = " << Cost;

    if(Cc == -1 && Qty == -1 && Amt == -1 && Ret == -1 && Disc == -1 && Cost == -1)
    {
        qDebug() << "------->data is zero! ------->continue!";
        //count += 6;
        continue;
    }

    if(Cc > 0)
    {
        data.Cc = BcdToFloat(recvbuf + count, Cc, 0);
        count += Cc;
    }

    if(Qty > 0)
    {
        data.Qty = BcdToFloat(recvbuf + count, Qty, 0);
        count += Qty;
    }

    if(Amt > 0)
    {
        data.Amt = BcdToFloat(recvbuf + count, Amt, 2);
        count += Amt;
    }

    if(Ret > 0)
    {
        data.Ret = BcdToFloat(recvbuf + count, Ret, 2);
        count += Ret;
    }

    if(Disc > 0)
    {
        data.Disc = BcdToFloat(recvbuf + count, Disc, 2);
        count += Disc;
    }

    if(Cost > 0)
    {
        data.Cost = BcdToFloat(recvbuf + count, Cost, 2);
        count += Cost;
    }

    if((recvbuf[3]&0xff) == 0x80)
    {
        NameLen = recvbuf[count++];
        qDebug() << "NameLen = " << NameLen;
        if(NameLen > 0) //获取名字
        {
            memcpy(ReportName, recvbuf + count, NameLen);
            count += NameLen;
            qDebug() << "ReportName = " << ReportName;

			CodeLen = recvbuf[count++];
			if(CodeLen > 0) //获取编码
			{
			}
        }
        else
        {
            memcpy(ReportName, dbreportname[NIdx], strlen(dbreportname[NIdx]));
            NameLen = strlen(dbreportname[NIdx]);
        }

        qDebug() << "ReportName = " << ReportName;
    }

    memset(data.Name, 0, sizeof(data.Name));
    memcpy(data.Name, ReportName, NameLen);

    qDebug() << "data.Name = " << data.Name
             << "data.Cc = " << data.Cc << ", data.Qty = " << data.Qty << ", data.Amt = " << data.Amt <<
                ", data.Ret = " << data.Ret << ", data.Disc = " << data.Disc << ", data.Cost = " << data.Cost;

    data.ZNo = ZNo;

    data.ID = cashid;

#if 0
    QString IP = QString("%1.%2.%3.%4").arg((ZNo >> 24) & 0xff).arg((ZNo >> 16) & 0xff)
                                      .arg((ZNo >> 8) & 0xff).arg(ZNo & 0xff);
    strcpy(data.IP, IP.toLocal8Bit().data());
#else
    strcpy(data.IP, IpStr.toLocal8Bit().data());
#endif

    qDebug("------------->data.ID = %d, data.ZNo = %04x, data.IP = %s", data.ID, data.ZNo, data.IP);
	if(DataTableType == 0x0 || DataTableType & NType)
	{
		writetable2(suffixname, NIdx, NType, data);
	}
    }

    return 0;
}

void dbthreadrun()
{
    //ReportDb->writetable2(ReportDb->DbSuffixTablename, ReportDb->DbIdx, ReportDb->DbOptions, ReportDb->DbData);
    ReportDb->db.transaction();
    ReportDb->DataParse();
    ReportDb->db.commit();

    qDebug() << "-------->start emit write db ok";
    emit ReportDb->dbstate(WRITEDBOK);
}
