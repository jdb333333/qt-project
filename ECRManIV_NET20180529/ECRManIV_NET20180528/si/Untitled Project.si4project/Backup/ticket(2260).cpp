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

void ticket::on_download_clicked()
{
    int ret, datalen;

    ui->header->clear();

    for(int i = 0; i < 4; i++)
    {
        sendbuf[0] = cmdDOWNLOAD;
        sendbuf[1] = 2;
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

        memset(recvbuf, 0, sizeof(recvbuf));
        datalen = formtcpclient->readData2(recvbuf, 1024);
        if(datalen < 0) //receive data failed
        {
            return;
        }

    #if 1
        qDebug() << "datalen = " << datalen;
        for(int count = 0; count < datalen; count++)
        {
            //qDebug("%c", recvbuf[count]);
            if(recvbuf[count] == 0)
            {
                recvbuf[count] = '\n';
            }
        }
    #endif

        ui->header->append(QString(QLatin1String(recvbuf + 4)));
    }

    formtcpclient->abortConnect();
}

void ticket::on_update_clicked()
{
    int count, k = 0, m = 0, items = 0, i = 0;
    QString header;
    int ret, datalen;

    header = ui->header->toPlainText();

    char tmpdata[4096] = {0};

    if(header.size() < sizeof(tmpdata))
    {
        strcpy(tmpdata, header.toLocal8Bit().data());
    }
    else
    {
        strncpy(tmpdata, header.toLocal8Bit().data(), sizeof(tmpdata) - 1);
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
            i++;

            ret = formtcpclient->newConnect2();
            if(ret < 0) //connect failed
            {
                return;
            }

            datalen = (sendbuf[1] + 2) & 0xff;
            ret = formtcpclient->writeData2(sendbuf, datalen);
            if(ret < 0) //send data failed
            {
                return;
            }

            formtcpclient->abortConnect();

            items = 0;
            m = 4;
            memset(sendbuf, 0, sizeof(sendbuf));
        }
    }

#if 0
    recvbuf[m] = 0;

    for(count = 0; count < m; count++)
    {
        if(recvbuf[count] == 0)
        {
            recvbuf[count] = '\n';
        }
    }

    ui->trailer->append(QString(QLatin1String(recvbuf)));
#endif
}
