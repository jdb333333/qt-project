#include "formdialog.h"
#include "ui_formdialog.h"

#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>

#include "excelbase.h"
#include "qvariantlistlistmodel.h"

#include "plu.h"
#include "tcpclient.h"

formDialog::formDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::formDialog)
{
    ui->setupUi(this);

    m_md = new QVariantListListModel(this);
    ui->tableView->setModel(m_md);
    m_md->setVariantListListPtr(&m_datas);

    udflag = 0;

    PluType = new plu(&m_datas);

    ui->tableView->setAlternatingRowColors(true);

    ui->tableView->setStyleSheet(getQssContent());

    formtcpclient = NULL;
}

formDialog::~formDialog()
{
    delete PluType;
    delete m_md;
    delete ui;
}

void formDialog::settcpclient(tcpclient *fmtcpclient)
{
    formtcpclient = fmtcpclient;
    connect(formtcpclient, SIGNAL(tcpstate(int)), this, SLOT(tcpstate(int)));
}

QString formDialog::getQssContent()
{
    QFile styleSheet("./tableviewstyle.txt");

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
    int datalen = 0;
    unsigned short sizelen = 0;

    if(tcpstat == TCPCONNECTERR)
    {
        QMessageBox::critical(0, "tcp err",
                              "can not connection.", QMessageBox::Cancel);
    }

    if(tcpstat == TCPSENDERR)
    {
        QMessageBox::critical(0, "tcp err",
                              "send data time out.", QMessageBox::Cancel);
    }

    if(tcpstat == TCPRCVERR)
    {
        QMessageBox::critical(0, "tcp err",
                              "recv data time out.", QMessageBox::Cancel);
    }

    if(formtcpclient)
    {

    }
    else
    {
        if(tcpstat == TCPCONNECTOK)
        {
            datalen = sendbuf[1] + 2;
            emit senddata(sendbuf, datalen);
        }

        if(tcpstat == TCPSENDOK)
        {
            emit recvdata(recvbuf, 1024);
        }

        if(tcpstat == TCPRCVOK)
        {
            itemindex++;
            ui->progressBar->setValue(itemindex);
            QCoreApplication::processEvents();//避免界面冻结

            sizelen = *((unsigned short *)recvbuf);
            recvdataok(sizelen);
        }
    }
}

void formDialog::dataparse(char *buf, int len)
{
    //qDebug("---->type = %02x, udflag = %02x", buf[0], udflag);
    if(udflag == 0x01)
    {
        return;
    }
    else if(udflag == 0x02)
    {
        //qDebug("---->type = %02x", buf[0]);
        if(buf[0] == 'P')
        {
            int pluitems = *(unsigned short *)(buf + 4);
            //qDebug() << "pluitems = " << pluitems;
            itemindex = 0;
            senditemmax = pluitems;

#if 0
            if(senditemmax > 10)
            {
                senditemmax = 10;
            }
#endif

            ui->progressBar->setRange(0,senditemmax);
            ui->progressBar->setValue(0);

            createdata(1);

            int datalen = sendbuf[1] + 2;
            emit senddata(sendbuf, datalen);
        }
        else if(buf[0] == cmdUPDATE)
        {
#if 0
            P_PLU *Plu = (P_PLU *)(buf + 4);

            qDebug("Random = %02x%02x%02x%02x%02x%02x%02x", Plu->Random[0], Plu->Random[1], Plu->Random[2],
                    Plu->Random[3], Plu->Random[4], Plu->Random[5], Plu->Random[6]);
            qDebug("Name = %s", Plu->Name);
            qDebug("Dept = %d", Plu->Dept + 1);
            qDebug("Price = %02x%02x%02x%02x%02x", Plu->Price[0][0], Plu->Price[0][1], Plu->Price[0][2],
                    Plu->Price[0][3], Plu->Price[0][4]);
            qDebug("Cost = %02x%02x%02x%02x%02x", Plu->Cost[0], Plu->Cost[1], Plu->Cost[2],
                    Plu->Cost[3], Plu->Cost[4]);
#endif
            PluType->DataParse(buf + 4, buf[1] - 2);
        }
    }
}

void formDialog::createdata(int type)
{
    char databuf[128] = {0};
    int ret = 0;

    switch(type)
    {
        case 1: //plu
            if(udflag == 0x01)
            {
                qDebug() << "--->plu itemindex = " << itemindex;
                ret = PluType->DataCreate(itemindex + 1, databuf);

                memset(sendbuf, 0, sizeof(sendbuf));

                sendbuf[0] = cmdUPDATE;
                sendbuf[1] = ret+2;
                *((unsigned short *)(sendbuf + 2)) = ADDPLU;
                memcpy(sendbuf + 4, databuf, ret);
            }
            else if(udflag == 0x02)
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
        if(udflag == 0x02)
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

void formDialog::on_update_clicked()
{
    int rows = m_datas.size();
    int datalen, ret;

    udflag = 0x01;

    itemindex = 0;
    senditemmax = rows - 1; //第0行为列名
    //senditemmax = rows;

    ui->progressBar->setRange(0,senditemmax);
    ui->progressBar->setValue(0);

    if(formtcpclient)
    {
        ret = formtcpclient->newConnect2();
        if(ret < 0)
        {
            return;
        }

        while(itemindex < senditemmax)
        {
            createdata(1);
            datalen = sendbuf[1] + 2;
            ret = formtcpclient->writeData2(sendbuf, datalen);
            if(ret < 0)
            {
                return;
            }

            datalen = formtcpclient->readData2(recvbuf, 1024);
            if(datalen < 0)
            {
                return;
            }

            itemindex++;
            ui->progressBar->setValue(itemindex);
            QCoreApplication::processEvents();//避免界面冻结
        }
    }
    else
    {
        createdata(1);

        emit connecthost();
    }
}

void formDialog::on_download_clicked()
{
    int datalen, ret;

    udflag = 0x02;
    itemindex = 0;
    senditemmax = 0;

    m_datas.clear();//先清除

    memset(sendbuf, 0, sizeof(sendbuf));

    sendbuf[0] = 'P';
    sendbuf[1] = 2;
    *((unsigned short *)(sendbuf + 2)) = PLU1;

    if(formtcpclient)
    {
        ret = formtcpclient->newConnect2();
        if(ret < 0) //connect failed
        {
            return;
        }

        datalen = sendbuf[1] + 2;
        ret = formtcpclient->writeData2(sendbuf, datalen);
        if(ret < 0) //send data failed
        {
            return;
        }

        datalen = formtcpclient->readData2(recvbuf, 1024);
        if(datalen < 0) //receive data failed
        {
            return;
        }

        itemindex = 0;
        senditemmax = *(unsigned short *)(recvbuf + 4);

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
    }
    else
    {
        emit connecthost();
    }
}
