#include "formdialog.h"
#include "ui_formdialog.h"

#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>

#include "excelbase.h"
#include "qvariantlistlistmodel.h"

#include "plu.h"
#include "dept/dept.h"
#include "tcpclient.h"

#include "mycheckboxheader.h"

formDialog::formDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::formDialog)
{
    ui->setupUi(this);

    m_md = new QVariantListListModel(this);
    ui->tableView->setModel(m_md);
    m_md->setVariantListListPtr(&m_datas);

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
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setColumnWidth(0, 80);
    ui->tableWidget->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    ui->tableWidget->horizontalHeader()->setResizeMode(0, QHeaderView::Fixed);
    ui->tableWidget->resizeColumnsToContents();

    ui->tableWidget->setAlternatingRowColors(true);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<""<<"IP");

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(cmpTime()));
    timer->start(1000);
}

formDialog::~formDialog()
{
    delete PluType;
    delete m_md;
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

void formDialog::setiplist(QString IP, bool checked)
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

    ui->tableWidget->setItem(rows,1,new QTableWidgetItem(IP));
    ui->tableWidget->item(rows, 1)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    if(checked)
    {
        ui->tableWidget->item(rows, 1)->setSelected(true);
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
        }
    }
    else if(formtype == F_PLU)
    {
        if(PluType == NULL)
        {
            PluType = new plu(&m_datas);
        }
    }
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

void formDialog::on_openfile_clicked()
{
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

    QVariantListListModel* md = qobject_cast<QVariantListListModel*>(ui->tableView->model());

    if(md)
    {
        md->updateData();
    }
}

void formDialog::tcpconnectcash(char type)
{
    for(; IpIndex < IpIndexMax; IpIndex++)
    {
        formtcpclient->abortConnect();

        if(ui->tableWidget->item(IpIndex, 0)->checkState() == Qt::Checked)
        {
            ui->tableWidget->clearSelection();
            ui->tableWidget->item(IpIndex, 1)->setSelected(true);
            IpStr = ui->tableWidget->item(IpIndex,1)->text();//取出字符
            ui->info->setText(QString("start connection to %1").arg(IpStr));
            QCoreApplication::processEvents();//避免界面冻结

            formtcpclient->setserverip(IpStr);

            if(type == F_UPDATA)
            {
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

                    QVariantListListModel* md = qobject_cast<QVariantListListModel*>(ui->tableView->model());
                    if(md)
                    {
                        md->updateData();
                    }

                    QCoreApplication::processEvents();//避免界面冻结

                    save_xlsfile(formtype);
                }
            }
        }
    }
}

void formDialog::save_xlsfile(char type)
{
    int i;
    QString filesuffix = QString("/");

    QStringList Ip = IpStr.split(".");

    for(i = 0; i < Ip.size(); i++)
    {
        filesuffix += Ip.at(i);
    }

#if 0
    filesuffix += QString("_");

    QString datetime = QTime::currentTime().toString("yyyy-MM-dd hh:mm:ss");
    QStringList DateTime = datetime.split(" ");

    for(i = 0; i < DateTime.size(); i++)
    {
        filesuffix += DateTime.at(i);
        filesuffix += QString("_");
    }
#endif

    filesuffix += QString(".xls");

    if(type == F_DEPT)
    {
#if 0
        savexlsFile += QString("/dept/%1").arg(filesuffix);
#else
        savexlsFile += xlsFiledir;
        savexlsFile += filesuffix;
#endif
    }
    else if(type == F_PLU)
    {
        savexlsFile += QString("/plu/%1").arg(filesuffix);
    }

    qDebug() << "savexlsfile = " << savexlsFile;

#if 0
    if(m_xls.isNull())
        m_xls.reset(new ExcelBase);

    m_xls->create(savexlsFile);
    m_xls->setCurrentSheet(1);
    m_xls->writeCurrentSheet(m_datas);
    m_xls->save();
#else
    ExcelBase *my_xls = new ExcelBase;
    my_xls->create(savexlsFile);
    my_xls->setCurrentSheet(1);
    my_xls->writeCurrentSheet(m_datas);
    my_xls->save();
#endif
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

    xlsFiledir = QFileDialog::getExistingDirectory(this);

    tcpconnectcash(udflag);
}
