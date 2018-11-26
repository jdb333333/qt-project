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
}

formDialog::~formDialog()
{
    delete PluType;
    delete m_md;
    delete ui;
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

    if(formtype == 0x01)
    {

    }
    else if(formtype == 0x02)
    {
        if(DeptType == NULL)
        {
            DeptType = new dept(&m_datas);
        }
    }
    else if(formtype == 0x03)
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

            ui->progressBar->setRange(0,senditemmax);
            ui->progressBar->setValue(0);

            createdata(1);

            int datalen = sendbuf[1] + 2;
            emit senddata(sendbuf, datalen);
        }
        else if(buf[0] == cmdUPDATE)
        {
            if(formtype == 0x02)
            {
                DeptType->DataParse(buf + 4, buf[1] - 2);
            }
            else if(formtype == 0x03)
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
        case 0x02: //dept
        if(udflag == 0x01)
        {
            qDebug() << "--->dept itemindex = " << itemindex;
            ret = DeptType->DataCreate(itemindex + 1, databuf);

            memset(sendbuf, 0, sizeof(sendbuf));

            sendbuf[0] = cmdUPDATE;
            sendbuf[1] = ret+2;
            *((unsigned short *)(sendbuf + 2)) = DEPT + itemindex + 1;
            memcpy(sendbuf + 4, databuf, ret);
        }
        else if(udflag == 0x02)
        {
            sendbuf[0] = cmdDOWNLOAD;
            sendbuf[1] = 2;
            *((unsigned short *)(sendbuf + 2)) = DEPT + itemindex + 1;
        }
            break;
        case 0x03: //plu
            if(udflag == 0x01)
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
    if(formtype == 0x02)
    {
        *((unsigned short *)(sendbuf + 2)) = DEPT;
    }
    else if(formtype == 0x03)
    {
        *((unsigned short *)(sendbuf + 2)) = PLU1;
    }

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
        qDebug() << "on_download_clicked--->senditemmax = " << senditemmax;

#if 0
        if(senditemmax > 100)
        {
            senditemmax = 100;
        }
#endif

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
    }
    else
    {
        emit connecthost();
    }
}
