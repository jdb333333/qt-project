#include "formdialog.h"
#include "ui_formdialog.h"

#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>

#include <QStandardItemModel>

#include "excelbase.h"
#include "qvariantlistlistmodel.h"

#include "plu.h"
#include "dept/dept.h"
#include "tcpclient.h"
#include "./csv/csv.h"

#include "mycheckboxheader.h"
#include "./message/message.h"

formDialog::formDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::formDialog)
{
    ui->setupUi(this);

#if ITEMMODEL
    itemModel = new QStandardItemModel(this);
#else
    m_md = new QVariantListListModel(this);
    ui->tableView->setModel(m_md);
    m_md->setVariantListListPtr(&m_datas);
#endif

    udflag = 0;

    formtype = 0x0;
    DeptType = NULL;
    PluType = NULL;
    //PluType = new plu(&m_datas);

    ui->tableView->setAlternatingRowColors(true);

    ui->tableView->setStyleSheet(getQssContent(0x01));

    formtcpclient = NULL;

    ui->tableWidget->setStyleSheet(getQssContent(0x02));

    MyCheckboxHeader *myHeader = new MyCheckboxHeader(Qt::Horizontal, ui->tableWidget);
    ui->tableWidget->resizeColumnsToContents();
    ui->tableWidget->setHorizontalHeader(myHeader);
    ui->tableWidget->horizontalHeader()->setResizeMode(QHeaderView::Stretch);

    connect(myHeader, SIGNAL(signalStateTrange(int)), this, SLOT(slotsSelectAll(int)));

    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setColumnWidth(0, 80);
    ui->tableWidget->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    ui->tableWidget->horizontalHeader()->setResizeMode(0, QHeaderView::Fixed);
    ui->tableWidget->resizeColumnsToContents();

    ui->tableWidget->setAlternatingRowColors(true);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->tableWidget->horizontalHeader()->setResizeMode(1, QHeaderView::ResizeToContents);
    ui->tableWidget->horizontalHeader()->setResizeMode(2, QHeaderView::ResizeToContents);

    qDebug() << ">>>>>>>>>>>>>>cashname = " << CASHNAME;
    ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<""<<CASHNAME<<"IP");

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(cmpTime()));
    timer->start(1000);
}

formDialog::~formDialog()
{
    if(PluType)
        delete PluType;
    if(DeptType)
        delete DeptType;

#if ITEMMODEL
    if(itemModel)
    {
        delete itemModel;
    }
#else
    delete m_md;
#endif
    delete timer;
    delete ui;
}

void formDialog::cmpTime()
{
    QTime setime = ui->timeEdit->time();
    QTime crtime = QTime::currentTime();

    if(setime.hour() == crtime.hour() && setime.minute() == crtime.minute() && setime.second() == crtime.second())
    {
        on_update_clicked();
    }
}

void formDialog::setiplist(QString IP, QString SHOPNAME, bool checked)
{
    int rows=ui->tableWidget->rowCount();

    ui->tableWidget->insertRow(rows);

    QTableWidgetItem *checkBox = new QTableWidgetItem();

    if(checked)
    {
        checkBox->setCheckState(Qt::Checked);
    }
    else
    {
        checkBox->setCheckState(Qt::Unchecked);
    }

    ui->tableWidget->setItem(rows, 0, checkBox);

    ui->tableWidget->setItem(rows,2,new QTableWidgetItem(IP));
    ui->tableWidget->item(rows, 2)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    ui->tableWidget->setItem(rows,1,new QTableWidgetItem(SHOPNAME));
    ui->tableWidget->item(rows, 1)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    if(checked)
    {
        //ui->tableWidget->item(rows, 2)->setSelected(true);
        ui->tableWidget->selectRow(rows);
    }
}

void formDialog::slotsSelectAll(int state)
{
    qDebug() << "slotsSelectAll state = " << state;

    int rows=ui->tableWidget->rowCount();
    if(rows > 0)
    {
        for(int count =0; count < rows; count++)
        {
            if(state == 1)
            {
                ui->tableWidget->item(count, 0)->setCheckState(Qt::Checked);
            }
            else
            {
                ui->tableWidget->item(count, 0)->setCheckState(Qt::Unchecked);
            }
        }
    }
}

void formDialog::setformtype(char fmtype)
{
    formtype = fmtype;

    if(formtype == F_GROUP)
    {

    }
    else if(formtype == F_DEPT)
    {
        if(DeptType == NULL)
        {
            DeptType = new dept(&m_datas);
#if ITEMMODEL
            itemModel->setColumnCount(DEPTITEMS);
#endif
        }
    }
    else if(formtype == F_PLU)
    {
        if(PluType == NULL)
        {
            PluType = new plu(&m_datas);
#if ITEMMODEL
            itemModel->setColumnCount(PLUITEMS);
#endif
        }
    }
#if ITEMMODEL
    ui->tableView->setModel(itemModel);
    ui->tableView->horizontalHeader()->setVisible(false);
    ui->tableView->verticalHeader()->setVisible(false);
#endif
}

void formDialog::settcpclient(tcpclient *fmtcpclient)
{
    formtcpclient = fmtcpclient;
    connect(formtcpclient, SIGNAL(tcpstate(int)), this, SLOT(tcpstate(int)));
}

QString formDialog::getQssContent(char type)
{
    QFile styleSheet;

    if(type == 0x01)
    {
        styleSheet.setFileName(QString("./tableviewstyle.txt"));
    }
    else if(type == 0x02)
    {
        styleSheet.setFileName(QString("./tablewidgetstyle.txt"));
    }

    if(!styleSheet.open(QIODevice::ReadOnly))
    {
        qDebug("Can't open the style sheet file.");
        return "";
    }

    return styleSheet.readAll();
}

void formDialog::tcpstate(int type)
{
    int tcpstat = type;

    if(tcpstat == TCPCONNECTERR)
    {
        ui->info->setText(QString("can not connection to %1").arg(IpStr));
        QCoreApplication::processEvents();//避免界面冻结
    }

    if(tcpstat == TCPSENDERR)
    {
        ui->info->setText(QString("send data to %1 time out.").arg(IpStr));
        QCoreApplication::processEvents();//避免界面冻结
    }

    if(tcpstat == TCPRCVERR)
    {
        ui->info->setText(QString("recv data from %1 time out.").arg(IpStr));
        QCoreApplication::processEvents();//避免界面冻结
    }
}

void formDialog::dataparse(char *buf, int len)
{
    //qDebug("---->type = %02x, udflag = %02x", buf[0], udflag);
    if(udflag == F_UPDATA)
    {
        return;
    }
    else if(udflag == F_DOWNLOAD)
    {
        //qDebug("---->type = %02x", buf[0]);
        if(buf[0] == 'P')
        {
            int pluitems = *(unsigned short *)(buf + 4);
            //qDebug() << "pluitems = " << pluitems;
            itemindex = 0;
            senditemmax = pluitems;

            ui->progressBar->setRange(0,senditemmax);
            ui->progressBar->setValue(0);

            createdata(1);

            int datalen = sendbuf[1] + 2;
            emit senddata(sendbuf, datalen);
        }
        else if(buf[0] == cmdUPDATE)
        {
            if(formtype == F_DEPT)
            {
                DeptType->DataParse(buf + 4, buf[1] - 2);
            }
            else if(formtype == F_PLU)
            {
                PluType->DataParse(buf + 4, buf[1] - 2);
            }
        }
    }
}

void formDialog::createdata(int type)
{
    char databuf[128] = {0};
    int ret = 0;

    switch(formtype)
    {
        case F_DEPT: //dept
            if(udflag == F_UPDATA)
            {
                qDebug() << "--->dept itemindex = " << itemindex;
                ret = DeptType->DataCreate(itemindex + 1, databuf);

                memset(sendbuf, 0, sizeof(sendbuf));

                sendbuf[0] = cmdUPDATE;
                sendbuf[1] = ret+2;
                *((unsigned short *)(sendbuf + 2)) = DEPT + itemindex + 1;
                memcpy(sendbuf + 4, databuf, ret);
            }
            else if(udflag == F_DOWNLOAD)
            {
                sendbuf[0] = cmdDOWNLOAD;
                sendbuf[1] = 2;
                *((unsigned short *)(sendbuf + 2)) = DEPT + itemindex + 1;
            }
            break;
        case F_PLU: //plu
            if(udflag == F_UPDATA)
            {
                qDebug() << "--->plu itemindex = " << itemindex;
                ret = PluType->DataCreate(itemindex + 1, databuf);

                memset(sendbuf, 0, sizeof(sendbuf));

                sendbuf[0] = cmdUPDATE;
                sendbuf[1] = ret+2;
                //*((unsigned short *)(sendbuf + 2)) = ADDPLU;
                *((unsigned short *)(sendbuf + 2)) = PLU1 + itemindex + 1;
                memcpy(sendbuf + 4, databuf, ret);
            }
            else if(udflag == F_DOWNLOAD)
            {
                sendbuf[0] = cmdDOWNLOAD;
                sendbuf[1] = 2;
                *((unsigned short *)(sendbuf + 2)) = PLU1 + itemindex + 1;
            }
            break;
        default:
            break;
    }
}

void formDialog::recvdataok(int sizelen)
{
    int datalen;

    dataparse(recvbuf + 2, sizelen);

    //qDebug() << "itemindex = " << itemindex << "senditemmax = " << senditemmax;

    if((itemindex%500) == 0)
    {
        qDebug() << "debug--->itemindex = " << itemindex;

        createdata(1);
        emit resetserver();
        emit connecthost();
        return;
    }

    //QCoreApplication::processEvents();//避免界面冻结
    if(itemindex < senditemmax)
    {
        createdata(1);

        datalen = sendbuf[1] + 2;
        emit senddata(sendbuf, datalen);
    }
    else if(senditemmax > 0)
    {
        if(udflag == F_DOWNLOAD)
        {
            QVariantListListModel* md = qobject_cast<QVariantListListModel*>(ui->tableView->model());
            if(md)
            {
                md->updateData();
            }
        }
    }
}

#if ITEMMODEL
void formDialog::itemModel_setvalue(QList<QList<QVariant> > *datas)
{
    int rows = datas->size();
    int columns = datas->at(0).size();

    itemModel->removeRows(0, itemModel->rowCount());

    for(int i = 0; i < rows; i++)
    {
        itemModel->insertRow(i);
        for(int j = 0; j < columns; j++)
        {
            QVariant item = datas->at(i).at(j);
            itemModel->setData(itemModel->index(i, j), item.toString());
            itemModel->item(i, j)->setTextAlignment(Qt::AlignCenter);
            itemModel->item(i, j)->setForeground(QBrush(QColor(87, 250, 255)));

            if(formtype == F_DEPT)
            {
                if(j == 0 || j == 3)
                {
                    itemModel->item(i, j)->setFlags(itemModel->item(i,j)->flags() & (~Qt::ItemIsEditable));
                }
            }
            else if(formtype == F_PLU)
            {
                if(j == 0)
                {
                    itemModel->item(i, j)->setFlags(itemModel->item(i,j)->flags() & (~Qt::ItemIsEditable));
                }
            }
        }
    }
}

void formDialog::itemModel_getvalue(QList<QList<QVariant> > *datas)
{
    int rows = itemModel->rowCount();
    int columns = itemModel->columnCount();

    datas->clear();
    QVariantList iteminfo;
    for(int i = 0; i < rows; i++)
    {
        iteminfo.clear();
        for(int j = 0; j < columns; j++)
        {
            iteminfo << itemModel->item(i, j)->text();
        }
        datas->push_back(iteminfo);
    }
}

#endif

void formDialog::on_openfile_clicked()
{
#if 0
    QString xlsFile = QFileDialog::getOpenFileName(this,QString(),QString(),"excel(*.xls *.xlsx)");

    if(xlsFile.isEmpty())
    {
        qDebug() << xlsFile << " is empty";
        return;
    }

    qDebug() << "open file " << xlsFile;

    if(m_xls.isNull())
    {
        m_xls.reset(new ExcelBase);
    }

    qDebug() << "on_openfile_clicked start open";

    m_xls->open(xlsFile);

    m_xls->setCurrentSheet(1);
    m_datas.clear();//先清除
    m_xls->readAll(m_datas);

    m_xls->close(); //jdb2018-06-19

    QVariantListListModel* md = qobject_cast<QVariantListListModel*>(ui->tableView->model());

    if(md)
    {
        md->updateData();
    }
#else
    QString csvFilePath = QFileDialog::getOpenFileName(this,QString(),QString(),"csv file(*.csv)");

    if(csvFilePath.isEmpty())
    {
        qDebug() << csvFilePath << " is empty";
        return;
    }

    qDebug() << "open file " << csvFilePath;

    csvFile.setFileName(csvFilePath);

    if (csvFile.open(QIODevice::ReadWrite) < 0)
    {
        qDebug() << "can not open " << csvFilePath;
        return;
    }

    if(m_csv.isNull())
    {
        m_csv.reset(new csv);
    }

    m_csv->setcsvfile(&csvFile);
    m_csv->setcsvdataptr(&m_datas);
    m_csv->readCsvData();

    csvFile.close();

#if ITEMMODEL
    itemModel_setvalue(&m_datas);
#else
    QVariantListListModel* md = qobject_cast<QVariantListListModel*>(ui->tableView->model());

    if(md)
    {
        md->updateData();
    }
#endif
#endif
}

void formDialog::tcpconnectcash(char type)
{
    int ret;

    for(; IpIndex < IpIndexMax; IpIndex++)
    {
        formtcpclient->abortConnect();

        if(ui->tableWidget->item(IpIndex, 0)->checkState() == Qt::Checked)
        {
            ui->tableWidget->clearSelection();
            /*
             *ui->tableWidget->item(IpIndex, 2)->setSelected(true);
             */
            ui->tableWidget->selectRow(IpIndex);
            IpStr = ui->tableWidget->item(IpIndex,2)->text();//取出字符
            ui->info->setText(QString("start connection to %1").arg(IpStr));
            QCoreApplication::processEvents();//避免界面冻结

            formtcpclient->setserverip(IpStr);

            if(type == F_UPDATA)
            {
#if ITEMMODEL
                itemModel_getvalue(&m_datas);
#endif
                int rows = m_datas.size();
                int datalen, ret;

                itemindex = 0;
                senditemmax = rows - 1; //第0行为列名

                ui->progressBar->setRange(0,senditemmax);
                ui->progressBar->setValue(0);

                if(formtcpclient)
                {
                    ret = formtcpclient->newConnect2();
                    if(ret < 0)
                    {
                        continue;
                    }

                    while(itemindex < senditemmax)
                    {
                        createdata(1);
                        datalen = sendbuf[1] + 2;
                        ret = formtcpclient->writeData2(sendbuf, datalen);
                        if(ret < 0)
                        {
                            continue;
                        }

                        datalen = formtcpclient->readData2(recvbuf, 1024);
                        if(datalen < 0)
                        {
                            continue;
                        }

                        itemindex++;
                        ui->progressBar->setValue(itemindex);
                        QCoreApplication::processEvents();//避免界面冻结
                    }
                    formtcpclient->abortConnect();
                }
            }
            else if(type == F_DOWNLOAD)
            {
                int datalen, ret;

                itemindex = 0;
                senditemmax = 0;

                m_datas.clear();//先清除

                memset(sendbuf, 0, sizeof(sendbuf));

                sendbuf[0] = 'P';
                sendbuf[1] = 2;
                if(formtype == F_DEPT)
                {
                    *((unsigned short *)(sendbuf + 2)) = DEPT;
                }
                else if(formtype == F_PLU)
                {
                    *((unsigned short *)(sendbuf + 2)) = PLU1;
                }

                if(formtcpclient)
                {
                    ret = formtcpclient->newConnect2();
                    if(ret < 0) //connect failed
                    {
                        continue;
                    }

                    datalen = sendbuf[1] + 2;
                    ret = formtcpclient->writeData2(sendbuf, datalen);
                    if(ret < 0) //send data failed
                    {
                        continue;
                    }

                    datalen = formtcpclient->readData2(recvbuf, 1024);
                    if(datalen < 0) //receive data failed
                    {
                        continue;
                    }

                    itemindex = 0;
                    senditemmax = *(unsigned short *)(recvbuf + 4);
                    qDebug() << "on_download_clicked--->senditemmax = " << senditemmax;

                    ui->progressBar->setRange(0,senditemmax);
                    ui->progressBar->setValue(0);

                    while(itemindex < senditemmax)
                    {
                        createdata(1);
                        datalen = sendbuf[1] + 2;
                        ret = formtcpclient->writeData2(sendbuf, datalen);
                        if(ret < 0) //send data failed
                        {
                            break;
                        }

                        datalen = formtcpclient->readData2(recvbuf, 1024);
                        if(datalen < 0) //receive data failed
                        {
                            break;
                        }

                        dataparse(recvbuf, datalen);

                        itemindex++;
                        ui->progressBar->setValue(itemindex);
                        QCoreApplication::processEvents();//避免界面冻结
                    }

                    formtcpclient->abortConnect();

#if ITEMMODEL
                    itemModel_setvalue(&m_datas);
#else
                    QVariantListListModel* md = qobject_cast<QVariantListListModel*>(ui->tableView->model());
                    if(md)
                    {
                        md->updateData();
                    }
#endif

                    QCoreApplication::processEvents();//避免界面冻结

                    //save_xlsfile(formtype);
                    save_csvfile(formtype);
                }
            }
        }
    }
}

void formDialog::save_xlsfile(char type)
{
#if 0
    int i;
    QString filesuffix = QString("\\");

    xlsFiledir =  QDir::currentPath();
    qDebug() << "------>currentpath = " << xlsFiledir;

    QStringList Ip = IpStr.split(".");

    for(i = 0; i < Ip.size(); i++)
    {
        filesuffix += Ip.at(i);
    }

    filesuffix += QString("_");

    QString date = QDate::currentDate().toString("yyyy-MM-dd");
    QString time = QTime::currentTime().toString("hh:mm:ss");
    qDebug() << "------>date = " << date << "time = " << time;
    QStringList DateTime = date.split("-");

    for(i = 0; i < DateTime.size(); i++)
    {
        filesuffix += DateTime.at(i);
    }

    filesuffix += QString("_");

    DateTime = time.split(":");

    for(i = 0; i < DateTime.size(); i++)
    {
        filesuffix += DateTime.at(i);
    }

    filesuffix += QString(".xls");
    //filesuffix += QString(".xlsx");

    if(type == F_DEPT)
    {
        xlsFiledir += QString("/xlsfile/dept");
    }
    else if(type == F_PLU)
    {
        xlsFiledir += QString("/xlsfile/plu");
    }

    savexlsFile = xlsFiledir;
    savexlsFile += filesuffix;

    qDebug() << "savexlsfile = " << savexlsFile;

    if(m_xls.isNull())
        m_xls.reset(new ExcelBase);

    m_xls->create(savexlsFile);
    m_xls->setCurrentSheet(1);
    m_xls->writeCurrentSheet(m_datas);

    m_xls->save();

    m_xls->close();
#endif
}

void formDialog::save_csvfile(char type)
{
    int i;
    QString filesuffix = QString("\\");

    csvFiledir =  QDir::currentPath();
    qDebug() << "------>currentpath = " << csvFiledir;

    QStringList Ip = IpStr.split(".");

    for(i = 0; i < Ip.size(); i++)
    {
        filesuffix += Ip.at(i);
    }

    filesuffix += QString("_");

    QString date = QDate::currentDate().toString("yyyy-MM-dd");
    QString time = QTime::currentTime().toString("hh:mm:ss");
    qDebug() << "------>date = " << date << "time = " << time;
    QStringList DateTime = date.split("-");

    for(i = 0; i < DateTime.size(); i++)
    {
        filesuffix += DateTime.at(i);
    }

    filesuffix += QString("_");

    DateTime = time.split(":");

    for(i = 0; i < DateTime.size(); i++)
    {
        filesuffix += DateTime.at(i);
    }

    filesuffix += QString(".csv");

    if(type == F_DEPT)
    {
        csvFiledir += QString("/csvfile/dept");
    }
    else if(type == F_PLU)
    {
        csvFiledir += QString("/csvfile/plu");
    }

    savexlsFile = csvFiledir;
    savexlsFile += filesuffix;

    savexlsFile.replace('/','\\');

    qDebug() << "savexlsfile = " << savexlsFile;

    csvFile.setFileName(savexlsFile);

    if (csvFile.open(QIODevice::ReadWrite) < 0)
    {
        qDebug() << "can not create " << savexlsFile;
        return;
    }

    if(m_csv.isNull())
    {
        m_csv.reset(new csv);
    }

    m_csv->setcsvfile(&csvFile);
    m_csv->setcsvdataptr(&m_datas);
    m_csv->writeCsvData();

    csvFile.close();
}

void formDialog::on_update_clicked()
{
    IpIndexMax = ui->tableWidget->rowCount();
    IpIndex = 0;

    udflag = F_UPDATA;

    tcpconnectcash(udflag);
}

void formDialog::on_download_clicked()
{
    IpIndexMax = ui->tableWidget->rowCount();
    IpIndex = 0;

    udflag = F_DOWNLOAD;

    //xlsFiledir = QFileDialog::getExistingDirectory(this);

    tcpconnectcash(udflag);
}

void formDialog::on_tableView_doubleClicked(const QModelIndex &index)
{
    qDebug() << "row = " << index.row() << "column = " << index.column();
    QModelIndex mdidx = ui->tableView->model()->index(index.row(), index.column());
    ui->tableView->setFocus();
    ui->tableView->setCurrentIndex(mdidx);
    ui->tableView->edit(mdidx);
}
