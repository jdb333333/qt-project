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

    QVariantListListModel* md = new QVariantListListModel(this);
    ui->tableView->setModel(md);
    md->setVariantListListPtr(&m_datas);
}

formDialog::~formDialog()
{
    delete ui;
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

void formDialog::recvdataok(int sizelen)
{
    int datalen;

    createdata(1);

    datalen = sendbuf[1] + 2;
    emit senddata(sendbuf, datalen);
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
    m_xls->readAll(m_datas);

    QVariantListListModel* md = qobject_cast<QVariantListListModel*>(ui->tableView->model());

    if(md)
    {
        md->updateData();
    }
}

void formDialog::createdata(int type)
{
    char databuf[64] = {0};
    int ret = 0;

    switch(type)
    {
        case 1: //plu
            PluType = new plu(&m_datas);
            ret = PluType->DataParse(itemindex, databuf);

            memset(sendbuf, 0, sizeof(sendbuf));

            sendbuf[0] = cmdUPDATE;
            sendbuf[1] = ret+2;
            *((unsigned short *)(sendbuf + 2)) = ADDPLU;
            memcpy(sendbuf + 4, databuf, ret);
            break;
        default:
            break;
    }
}

void formDialog::on_update_clicked()
{
    int rows = m_datas.size();

    itemindex = 0;
    senditemmax = rows - 1; //第0行为列名

    ui->progressBar->setRange(0,senditemmax);
    ui->progressBar->setValue(0);

    createdata(1);

    emit connecthost();
}
