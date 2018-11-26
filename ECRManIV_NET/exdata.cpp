#include "exdata.h"
#include "ui_exdata.h"
#include "excelbase.h"

#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>

#include "qvariantlistlistmodel.h"

#include "plu.h"
#include "tcpclient.h"

exdata::exdata(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::exdata),
    m_xls(NULL)
{
    ui->setupUi(this);

    QVariantListListModel* md = new QVariantListListModel(this);
    ui->tableView->setModel(md);
    md->setVariantListListPtr(&m_datas);
}

exdata::~exdata()
{
    delete ui;
}

void exdata::on_pushButton_2_clicked()
{

}

void exdata::on_openfile_clicked()
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

void exdata::on_pushButton_clicked()
{
    QString itemvalue;
    char databuf[32] = {0};

    int rows = m_datas.size();
    int columns = m_datas.at(0).size();

    for(int i = 1; i < rows; i++)
    {
        for(int j = 0; j < columns; j++)
        {
            QVariant item = m_datas.at(i).at(j);
            itemvalue = item.value<QString>();
            P_PLU plu;
            strcpy(databuf, itemvalue.toLocal8Bit().data());

            if(j == 0) //random
            {
                for(int m = 0, k = 0; m < strlen(databuf); m++, k += 2)
                {
                    plu.Random[m] = ((databuf[k] - '0') & 0x0f) | (((databuf[k + 1] - '0') >> 4) & 0xf0);
                }

                qDebug("plu.Random = %07x", plu.Random);
            }

            if(j == 1) //name
            {
                strcpy(plu.Name, databuf);

                qDebug("plu.Name = %s", plu.Name);
            }

            if(j == 2) //deptnum
            {
                plu.Dept = atoi(databuf);

                qDebug("plu.Dept = %d", plu.Dept);
            }

            if(j == 3) //cost
            {
                for(int m = 0, k = 0; m < strlen(databuf); m++, k += 2)
                {
                    plu.Cost[m] = ((databuf[k] - '0') & 0x0f) | (((databuf[k + 1] - '0') >> 4) & 0xf0);
                }

                qDebug("plu.Cost = %05x", plu.Cost);
            }

            if(j == 4) //price
            {
                for(int m = 0, k = 0; m < strlen(databuf); m++, k += 2)
                {
                    plu.Price[0][m] = ((databuf[k] - '0') & 0x0f) | (((databuf[k + 1] - '0') >> 4) & 0xf0);
                }

                qDebug("plu.Price[0] = %05x", plu.Price[0]);
            }

            if(j == 5)
            {
                for(int m = 0, k = 0; m < strlen(databuf); m++, k += 2)
                {
                    plu.Inventory.Value[m] = ((databuf[k] - '0') & 0x0f) | (((databuf[k + 1] - '0') >> 4) & 0xf0);
                }

                qDebug("plu.Inventory.Value = %08x", plu.Inventory.Value);
            }
        }


    }
}

void exdata::tcpstate(int type)
{
    int tcpstat = type;
    unsigned short sizelen;

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
        //emit senddata(sendbuf[itemindex], datalen);
    }

    if(tcpstat == TCPSENDOK)
    {
        //emit recvdata(recvbuf, 1024);
    }

    if(tcpstat == TCPRCVOK)
    {
        QCoreApplication::processEvents();//避免界面冻结

        sizelen = *((unsigned short *)recvbuf);
        recvdataok(sizelen);
    }
}

void exdata::recvdataok(int sizelen)
{

}
