#include "ticket.h"
#include "ui_ticket.h"

#include "tcpclient.h"

#include <QMessageBox>
#include <QDebug>

ticket::ticket(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ticket)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::Dialog | windowType());

    this->setAttribute(Qt::WA_ShowModal, true);
}

ticket::~ticket()
{
    delete ui;
}

void ticket::settcpclient(tcpclient *fmtcpclient)
{
    formtcpclient = fmtcpclient;
    connect(formtcpclient, SIGNAL(tcpstate(int)), this, SLOT(tcpstate(int)));
}

void ticket::tcpstate(int type)
{
    int tcpstat = type;

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
}

int ticket::txtcreate(char type)
{
    int ret, datalen;

    if(type == 0x01)
    {
        ui->header->clear();
    }
    else if(type == 0x02)
    {
        ui->trailer->clear();
    }

    for(int i = 0; i < 14; i++)
    {
        sendbuf[0] = cmdDOWNLOAD;
        sendbuf[1] = 2;

        if(type == 0x01)
        {
            if(i == 0)
            {
                *((unsigned short *)(sendbuf + 2)) = RHEAD1;
            }
            else if(i == 1)
            {
                *((unsigned short *)(sendbuf + 2)) = RHEAD2;
            }
            else if(i == 2)
            {
                *((unsigned short *)(sendbuf + 2)) = RHEAD3;
            }
            else if(i >= 3)
            {
                *((unsigned short *)(sendbuf + 2)) = RHEAD4 + i - 3;
            }
        }
        else if(type == 0x02)
        {
            if(i == 0)
            {
                *((unsigned short *)(sendbuf + 2)) = RTRAIL1;
            }
            else if(i == 1)
            {
                *((unsigned short *)(sendbuf + 2)) = RTRAIL2;
            }
            else if(i == 2)
            {
                *((unsigned short *)(sendbuf + 2)) = RTRAIL3;
            }
            else if(i >= 3)
            {
                *((unsigned short *)(sendbuf + 2)) = RTRAIL4 + i - 3;
            }
        }

        datalen = sendbuf[1] + 2;
        ret = formtcpclient->writeData2(sendbuf, datalen);
        if(ret < 0) //send data failed
        {
            return -1;
        }

        memset(recvbuf, 0, sizeof(recvbuf));
        datalen = formtcpclient->readData2(recvbuf, 1024);
        if(datalen < 0) //receive data failed
        {
            return -1;
        }

    #if 1
        qDebug() << "datalen = " << datalen;
        for(int count = 0; count < datalen; count++)
        {
            //qDebug("%c", recvbuf[count]);
            if(recvbuf[count] == 0 && (count + 1) % 43 == 0)
            {
                recvbuf[count] = '\n';
            }
            else if(recvbuf[count] == 0)
            {
                recvbuf[count] = ' ';
            }
        }
    #endif

        if(type == 0x01)
        {
            ui->header->append(QString(QLatin1String(recvbuf + 4)));
        }
        else if(type == 0x02)
        {
            ui->trailer->append(QString(QLatin1String(recvbuf + 4)));
        }

        itemindex++;
        ui->progressBar->setValue(itemindex);
        QCoreApplication::processEvents();//避免界面冻结
    }
}


void ticket::on_download_clicked()
{
    int ret;

    ret = formtcpclient->newConnect2();
    if(ret < 0) //connect failed
    {
        return;
    }

    senditemmax = 28;
    itemindex = 0;

    ui->progressBar->setRange(0,senditemmax);
    ui->progressBar->setValue(0);

    ret = txtcreate(0x01);
    if(ret < 0)
    {
        return;
    }

    ret = txtcreate(0x02);
    if(ret < 0)
    {
        return;
    }

    formtcpclient->abortConnect();
}

void ticket::txtparse(char type)
{
    QString txtstr;
    char tmpdata[4096] = {0};
    int count, k = 0, m = 0, items = 0, i = 0;
    int datalen;

    if(type == 0x01)
    {
        txtstr = ui->header->toPlainText();
    }
    else if(type == 0x02)
    {
        txtstr = ui->trailer->toPlainText();
    }

    if(txtstr.size() < sizeof(tmpdata))
    {
        strcpy(tmpdata, txtstr.toLocal8Bit().data());
    }
    else
    {
        strncpy(tmpdata, txtstr.toLocal8Bit().data(), sizeof(tmpdata) - 1);
    }

    memset(sendbuf, 0, sizeof(sendbuf));

    m = 4;

    for(count = 0; count < strlen(tmpdata); count++)
    {
        qDebug("[%d]--->%02x", count, tmpdata[count]);

        if(tmpdata[count] == '\n')
        {
            qDebug() << "count = " << count;

            if(k < 42) //一行的字节小于42个字节
            {
                for(int i = 0; i < 42 - k; i++)
                {
                    sendbuf[m++] = ' '; //补齐42字节
                    qDebug("[%d]%02x", m - 4, sendbuf[m-1]);
                }
                sendbuf[m++] = 0;
            }
            else
            {
                sendbuf[m++] = 0;
            }

            k = 0;
            items++;

            if(items < 3) //3行
            {
            }
            else
            {
                goto next;
            }

            qDebug("[%d]%02x", m - 4, sendbuf[m-1]);
            continue;
        }
        else //没有回车
        {
            if(k == 42) //一行的字节大于42个字节
            {
                //sendbuf[m++] = 0; //截断

                //items++;
            }
            else if(k < 42)
            {
                sendbuf[m++] = tmpdata[count];
            }
        }
        k++;

next:
        qDebug("[%d]%02x", m - 4, sendbuf[m-1]);
        qDebug() << "m = " << m << "k = " << k;
        qDebug() << "items = " << items;

        if(items < 3 && count + 1 == strlen(tmpdata))//不足3行补齐
        {
            m = 3 * 43 + 4;
            items = 3;
        }

        if(items == 3) //3行
        {
            sendbuf[0] = cmdUPDATE;
            sendbuf[1] = (m - 4 + 2) & 0xff;
            if(type == 0x01)
            {
                if(i == 0)
                {
                    *((unsigned short *)(sendbuf + 2)) = RHEAD1;
                }
                else if(i == 1)
                {
                    *((unsigned short *)(sendbuf + 2)) = RHEAD2;
                }
                else if(i == 2)
                {
                    *((unsigned short *)(sendbuf + 2)) = RHEAD3;
                }
                else if(i >= 3)
                {
                    *((unsigned short *)(sendbuf + 2)) = RHEAD4 + i - 3;
                }
            }
            else if(type == 0x02)
            {
                if(i == 0)
                {
                    *((unsigned short *)(sendbuf + 2)) = RTRAIL1;
                }
                else if(i == 1)
                {
                    *((unsigned short *)(sendbuf + 2)) = RTRAIL2;
                }
                else if(i == 2)
                {
                    *((unsigned short *)(sendbuf + 2)) = RTRAIL3;
                }
                else if(i >= 3)
                {
                    *((unsigned short *)(sendbuf + 2)) = RTRAIL4 + i - 3;
                }
            }

            i++;

            datalen = (sendbuf[1] + 2) & 0xff;
            qDebug() << "datalen = " << datalen;
            memcpy(itemsbuf[i - 1 + senditemmax], sendbuf, datalen);
            itemslen[i - 1 + senditemmax] = datalen;

            if(i == 14)
            {
                break;
            }

            items = 0;
            m = 4;
        }
    }

    senditemmax += i;
}

void ticket::on_update_clicked()
{
    int ret, datalen;

    senditemmax = 0;

    txtparse(0x01);
    txtparse(0x02);

	ret = formtcpclient->newConnect2();
    if(ret < 0) //connect failed
    {
     	return;
    }        

	ui->progressBar->setRange(0,senditemmax);
    ui->progressBar->setValue(0);
	
	for(itemindex = 0; itemindex < senditemmax; )
	{
    qDebug("itemsbuf[%d].datalen = %d", itemindex, itemslen[itemindex]);
			datalen = itemslen[itemindex];
			qDebug() << "datalen = " << datalen;
			memcpy(sendbuf, itemsbuf[itemindex], datalen);
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

			itemindex++;
			ui->progressBar->setValue(itemindex);
            QCoreApplication::processEvents();//避免界面冻结
	}

	formtcpclient->abortConnect();
}
