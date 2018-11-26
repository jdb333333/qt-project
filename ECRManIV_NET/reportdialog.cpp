#include "reportdialog.h"
#include "ui_reportdialog.h"
#include "reportdb.h"
#include "tcpclient.h"
#include "itemreport.h"
#include "reportdisp.h"

#include <QDebug>
#include <QMessageBox>
#include <QStandardItemModel>

char reportname[8][32] = {
    "GRAND TOTAL",
    "DEPARTMENT",
    "TENDER",
    "DRAWER",
    "CORRECT",
    "DISCOUNT",
    "TAX",
    "PLU",
};

reportDialog::reportDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::reportDialog)
{
    ui->setupUi(this);

    MyDb = new reportdb(this);

    connect(MyDb, SIGNAL(dbstate(int)), this, SLOT(dbstate(int)));

    ZNo = 1;

    ui->reportedit->setReadOnly(true);

#if 1
    memset(reporttxt, 0, sizeof(reporttxt));
    strcpy(reporttxt, "this is a test txt\nok");
    QString TXT = QString(QLatin1String(reporttxt));

    ui->reportedit->setText(TXT);
#endif
}

reportDialog::~reportDialog()
{
    delete ui;
}

void reportDialog::on_pushButton_clicked()
{
    unsigned char datatype;
#if 0
    datatype = 0;
    if(ui->grandtotalbox->checkState() == Qt::Checked)
    {
        datatype |= GRANDTOTALREPORT;
    }
    if(ui->departmentbox->checkState() == Qt::Checked)
    {
        datatype |= DEPARTMENTREPORT;
    }
    if(ui->tenderbox->checkState() == Qt::Checked)
    {
        datatype |= TENDERREPORT;
    }
    if(ui->drawerbox->checkState() == Qt::Checked)
    {
        datatype |= DRAWERREPORT;
    }
    if(ui->correctionbox->checkState() == Qt::Checked)
    {
        datatype |= CORRECTREPORT;
    }
    if(ui->discountbox->checkState() == Qt::Checked)
    {
        datatype |= DISCOUNTREPORT;
    }
    if(ui->taxbox->checkState() == Qt::Checked)
    {
        datatype |= TAXREPORT;
    }
    if(ui->plubox->checkState() == Qt::Checked)
    {
        datatype |= PLUREPORT;
    }

    qDebug("zdatatype = %02x", datatype&0xff);
	#endif

    if(ui->xreport->checkState() == Qt::Checked)
    {
        downloaddata(datatype);
    }
}

void reportDialog::dbstate(int type)
{
    dbstat = type;
    int datalen;

    if(dbstat == WRITEDBOK)
    {
        //qDebug() << "wrtie db ok";
        //itemindex++;

        //ui->progressBar->setValue(itemindex);

        if(itemindex < senditemmax)
        {
            datalen = sendbuf[itemindex][1] + 2;
            //qDebug() << "send data len = " << datalen;
            emit senddata(sendbuf[itemindex], datalen);
        }
        else
        {
            ui->cleardbreport->setEnabled(true);
            emit unconnecthost();
        }
    }
}

void reportDialog::tcpstate(int type)
{
    tcpstat = type;
    int datalen;
    unsigned short sizelen;

    if(tcpstat == TCPCONNECTERR)
    {
        //MyDb->dbcommit();
        ui->cleardbreport->setEnabled(true);
        QMessageBox::critical(0, "tcp err",
                              "can not connection.", QMessageBox::Cancel);
    }

    if(tcpstat == TCPSENDERR)
    {
        //MyDb->dbcommit();
        ui->cleardbreport->setEnabled(true);
        QMessageBox::critical(0, "tcp err",
                              "send data time out.", QMessageBox::Cancel);
    }

    if(tcpstat == TCPRCVERR)
    {
        //MyDb->dbcommit();
        ui->cleardbreport->setEnabled(true);
        QMessageBox::critical(0, "tcp err",
                              "recv data time out.", QMessageBox::Cancel);
    }

    if(tcpstat == TCPCONNECTOK)
    {
        itemcount = 0;

        datalen = sendbuf[itemindex][1] + 2;
        //qDebug() << "datatype = " << "send data len = " << datalen;
        //MyDb->dbtransaction();
        emit senddata(sendbuf[itemindex], datalen);
    }

    if(tcpstat == TCPSENDOK)
    {
        //qDebug() << "dialog------>tcpsend ok";
        emit recvdata(recvbuf, 1024);
    }

    if(tcpstat == TCPRCVOK)
    {

        itemindex++;
        ui->progressBar->setValue(itemindex);
        QCoreApplication::processEvents();//避免界面冻结

        if(itemindex == senditemmax)
        {
            ui->cleardbreport->setEnabled(true);
        }

        //qDebug() << "dialog------->tcprcv ok";
        sizelen = *((unsigned short *)recvbuf);
        recvdataok(sizelen);
    }
}

float reportDialog::BcdToFloat(char *bcd, int len, int decimal)
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

void reportDialog::recvdataok(int sizelen)
{
    //qDebug() << QString("recv %1 data!").arg(sizelen);
    if(sizelen <= 4)
    {
        return;
    }

    MyDb->setzno(ZNo);
    MyDb->datadeal(recvbuf+2, sizelen);
}

int reportDialog::downloaddata(unsigned char datatype)
{
    int count;

    itemindex = 0;
    senditemmax = 1;

    datatype = GRANDTOTALREPORT | DEPARTMENTREPORT | TENDERREPORT | DRAWERREPORT |
            CORRECTREPORT | DISCOUNTREPORT | TAXREPORT | PLUREPORT;

        if((datatype & GRANDTOTALREPORT) > 0){
        sendbuf[itemindex][0] = 0x5A;
        sendbuf[itemindex][1] = 0x02;
        sendbuf[itemindex][2] = DOWNLOAD;
        sendbuf[itemindex][3] = GRANDTOTALREPORT;
        itemindex++;
        senditemmax++;
        }

        if((datatype & DEPARTMENTREPORT) > 0){
        for(count = 1; count <= 5; count++)
        {
            memset(sendbuf[itemindex], 0, 32);
            sendbuf[itemindex][0] = 0x5A;
            sendbuf[itemindex][1] = 0x03;
            sendbuf[itemindex][2] = DOWNLOAD;
            sendbuf[itemindex][3] = DEPARTMENTREPORT;
            sendbuf[itemindex][4] = count; //deptcount
            itemindex++;
            senditemmax++;
        }
        }

        if((datatype & TENDERREPORT) > 0){
        for(count = 1; count <= 5; count++)
        {
        sendbuf[itemindex][0] = 0x5A;
        sendbuf[itemindex][1] = 0x03;
        sendbuf[itemindex][2] = DOWNLOAD;
        sendbuf[itemindex][3] = TENDERREPORT;
        sendbuf[itemindex][4] = count;
        itemindex++;
        senditemmax++;
        }
        }

        if((datatype & DRAWERREPORT) > 0){
        for(count = 1; count <= 1; count++)
        {
        sendbuf[itemindex][0] = 0x5A;
        sendbuf[itemindex][1] = 0x03;
        sendbuf[itemindex][2] = DOWNLOAD;
        sendbuf[itemindex][3] = DRAWERREPORT;
        sendbuf[itemindex][4] = count;
        itemindex++;
        senditemmax++;
        }
        }

        if((datatype & CORRECTREPORT) > 0){
        for(count = 1; count <= 4; count++)
        {
        sendbuf[itemindex][0] = 0x5A;
        sendbuf[itemindex][1] = 0x03;
        sendbuf[itemindex][2] = DOWNLOAD;
        sendbuf[itemindex][3] = CORRECTREPORT;
        sendbuf[itemindex][4] = count;
        itemindex++;
        senditemmax++;
        }
        }

        if((datatype & DISCOUNTREPORT) > 0){
        for(count = 1; count <= 10; count++)
        {
        sendbuf[itemindex][0] = 0x5A;
        sendbuf[itemindex][1] = 0x03;
        sendbuf[itemindex][2] = DOWNLOAD;
        sendbuf[itemindex][3] = DISCOUNTREPORT;
        sendbuf[itemindex][4] = count;
        itemindex++;
        senditemmax++;
        }
        }

        if((datatype & TAXREPORT) > 0){
        for(count = 1; count <= 8; count++)
        {
        sendbuf[itemindex][0] = 0x5A;
        sendbuf[itemindex][1] = 0x03;
        sendbuf[itemindex][2] = DOWNLOAD;
        sendbuf[itemindex][3] = TAXREPORT;
        sendbuf[itemindex][4] = count;
        itemindex++;
        senditemmax++;
        }
        }

        if((datatype & PLUREPORT) > 0)
        {
            sendbuf[itemindex][0] = 0x5A;
            sendbuf[itemindex][1] = 0x02;
            sendbuf[itemindex][2] = DOWNLOAD;
            sendbuf[itemindex][3] = PLUREPORT;
            itemindex++;
            senditemmax++;
        }

        tcpstat = 0;
        itemindex = 0;
        senditemmax--;

        if(senditemmax > 0)
        {
        ui->progressBar->setRange(0,senditemmax);
        ui->progressBar->setValue(0);

        ui->cleardbreport->setEnabled(false);
        emit connecthost();
        }
        else
        {
            qDebug() << "senditemmax = " << senditemmax;
            return false;
        }


    return true;
}

void reportDialog::ChToStr(char *str, char ch, int len)
{
    for(int i = 0; i < len; i++)
    {
        str[i] = ch;
    }
}

void reportDialog::StrFormat(char *str, int len, int formattype)
{
    char ch[len];
    int size;

    memset(ch, ' ', len);

    size = strlen(str);

    if(formattype == 1) //中间显示
    {
        if(len - size > 0)
        {
            memcpy(ch + (len - size)/2, str, size);
        }
        else
        {
            memcpy(ch, str, size);
        }
    }
    else if(formattype == 0) //左边对齐
    {
        memcpy(ch, str, size);
    }
    else
    {
        memcpy(ch + formattype, str, size);
    }

    memcpy(str, ch, len);
}

void reportDialog::NStrFormat(char *strs, char *str1, char *str2, char *str3, char *str4, char *str5, int len)
{
    char ch[len];
    int size1 = 0, size2 = 0, size3 = 0, size4 = 0, size5 = 0, sumsize = 0;
    int strcount = 0, spacelen = 0;

    if(str1)
    {
        size1 = strlen(str1);
        strcount++;
    }

    if(str2)
    {
        size2 = strlen(str2);
        strcount++;
    }

    if(str3)
    {
        size3 = strlen(str3);
        strcount++;
    }

    if(str4)
    {
        size4 = strlen(str4);
        strcount++;
    }

    if(str5)
    {
        size5 = strlen(str5);
        strcount++;
    }

    sumsize = size1 + size2 + size3 + size4 + size5;

    memset(ch, ' ', len);

    if(sumsize < len)
    {
        spacelen = (len - sumsize)/(strcount - 1);
        strcount = 0;
        if(size1 > 0)
        {
            memcpy(ch + strcount, str1, size1);
            strcount += size1 + spacelen;
        }
        if(size2 > 0)
        {
            memcpy(ch + strcount, str2, size2);
            strcount += size2 + spacelen;
        }
        if(size3 > 0)
        {
            memcpy(ch + strcount, str3, size3);
            strcount += size3 + spacelen;
        }
        if(size4 > 0)
        {
            memcpy(ch + strcount, str4, size4);
            strcount += size4 + spacelen;
        }
        if(size5 > 0)
        {
            memcpy(ch + strcount, str5, size5);
            strcount += size5 + spacelen;
        }
        memcpy(strs, ch, len);
    }
}

void reportDialog::ReportToTxt(QStandardItemModel *reportModel, char *txtstr, char *Titel, char reporttype, char reportmod)
{
    char str[TXTWIDTH + 1] = {0};
    char str1[32] = {0};
    char str2[32] = {0};
    char str3[32] = {0};
    char str4[32] = {0};
    char str5[32] = {0};

    str[TXTWIDTH] = '\n';

    memset(str, 0, TXTWIDTH);
    strcpy(str, Titel);
    StrFormat(str, TXTWIDTH, 5);

    memcpy(txtstr + strlen(txtstr), str, TXTWIDTH + 1);

    memset(str, 0, TXTWIDTH);
    ChToStr(str, '*', TXTWIDTH);
    memcpy(reporttxt + strlen(reporttxt), str, TXTWIDTH + 1);

    QString TXTITEM;

    int rows = reportModel->rowCount();
    qDebug() << "--->reportModel rows = " << rows;
    int columns = reportModel->columnCount();
    qDebug() << "--->reportModel columns = " << columns;

    if(reporttype & GRANDTOTALREPORT)
    {
        if(columns == 3)
        {
            if(reportmod & DAILYREPORT)
            {
            for(int i = 0; i < rows; i++)
            {
                TXTITEM = reportModel->item(i, 0)->text();
                memset(str1, 0, sizeof(str1));
                strcpy(str1, "OLD GRAND TOTAL");
                memset(str2, 0, sizeof(str2));
                strcpy(str2, TXTITEM.toLocal8Bit().data());
                memset(str, 0, TXTWIDTH);
                NStrFormat(str, str1, str2, NULL, NULL, NULL, TXTWIDTH);
                memcpy(txtstr + strlen(txtstr), str, TXTWIDTH + 1);

                TXTITEM = reportModel->item(i, 1)->text();
                memset(str1, 0, sizeof(str1));
                strcpy(str1, "NEW GRAND TOTAL");
                memset(str2, 0, sizeof(str2));
                strcpy(str2, TXTITEM.toLocal8Bit().data());
                memset(str, 0, TXTWIDTH);
                NStrFormat(str, str1, str2, NULL, NULL, NULL, TXTWIDTH);
                memcpy(txtstr + strlen(txtstr), str, TXTWIDTH + 1);

                TXTITEM = reportModel->item(i, 2)->text();
                memset(str1, 0, sizeof(str1));
                strcpy(str1, "TOTAL GROSS SALES");
                memset(str2, 0, sizeof(str2));
                strcpy(str2, TXTITEM.toLocal8Bit().data());
                memset(str, 0, TXTWIDTH);
                NStrFormat(str, str1, str2, NULL, NULL, NULL, TXTWIDTH);
                memcpy(txtstr + strlen(txtstr), str, TXTWIDTH + 1);
            }
            }
            else if(reportmod & WEEKREPORT)
            {
                for(int i = 0; i < rows; i++)
                {
                TXTITEM = reportModel->item(i, 2)->text();
                memset(str1, 0, sizeof(str1));
                strcpy(str1, "TOTAL GROSS SALES");
                memset(str2, 0, sizeof(str2));
                strcpy(str2, TXTITEM.toLocal8Bit().data());
                memset(str, 0, TXTWIDTH);
                NStrFormat(str, str1, str2, NULL, NULL, NULL, TXTWIDTH);
                memcpy(txtstr + strlen(txtstr), str, TXTWIDTH + 1);
                }
            }
        }
        else
        {
            for(int i = 0; i < rows; i++)
            {
            TXTITEM = reportModel->item(i, 3)->text();
            memset(str1, 0, sizeof(str1));
            strcpy(str1, "AMOUNT");
            memset(str2, 0, sizeof(str2));
            strcpy(str2, TXTITEM.toLocal8Bit().data());
            memset(str, 0, TXTWIDTH);
            NStrFormat(str, str1, str2, NULL, NULL, NULL, TXTWIDTH);
            memcpy(txtstr + strlen(txtstr), str, TXTWIDTH + 1);
            }
        }
    }
    else if(reporttype & DEPARTMENTREPORT)
    {
        memset(str1, 0, sizeof(str1));
        strcpy(str1, "DEPARTMENT");
        memset(str2, 0, sizeof(str2));
        strcpy(str2, "QUANTITY");
        memset(str3, 0, sizeof(str3));
        strcpy(str3, "AMOUNT");
        memset(str, 0, TXTWIDTH);
        NStrFormat(str, str1, str2, str3, NULL, NULL, TXTWIDTH);
        memcpy(txtstr + strlen(txtstr), str, TXTWIDTH + 1);

        for(int i = 0; i < rows; i++)
        {
            TXTITEM = reportModel->item(i, 0)->text();
            memset(str1, 0, sizeof(str1));
            strcpy(str1, TXTITEM.toLocal8Bit().data());

            TXTITEM = reportModel->item(i, 2)->text();
            memset(str2, 0, sizeof(str2));
            strcpy(str2, TXTITEM.toLocal8Bit().data());

            TXTITEM = reportModel->item(i, 3)->text();
            memset(str3, 0, sizeof(str3));
            strcpy(str3, TXTITEM.toLocal8Bit().data());

            memset(str, 0, TXTWIDTH);
            NStrFormat(str, str1, str2, str3, NULL, NULL, TXTWIDTH);
            memcpy(txtstr + strlen(txtstr), str, TXTWIDTH + 1);
        }
    }
    else if(reporttype & TENDERREPORT)
    {
        for(int i = 0; i < rows; i++)
        {
            TXTITEM = reportModel->item(i, 0)->text();
            memset(str, 0, TXTWIDTH);
            strcpy(str, TXTITEM.toLocal8Bit().data());
            StrFormat(str, TXTWIDTH, 0);
            memcpy(txtstr + strlen(txtstr), str, TXTWIDTH + 1);

            TXTITEM = reportModel->item(i, 1)->text();
            memset(str1, 0, sizeof(str1));
            strcpy(str1, "TOTAL TRADE");
            memset(str2, 0, sizeof(str2));
            strcpy(str2, TXTITEM.toLocal8Bit().data());
            memset(str, 0, TXTWIDTH);
            NStrFormat(str, str1, str2, NULL, NULL, NULL, TXTWIDTH);
            memcpy(txtstr + strlen(txtstr), str, TXTWIDTH + 1);

            TXTITEM = reportModel->item(i, 3)->text();
            memset(str1, 0, sizeof(str1));
            strcpy(str1, "AMOUNT");
            memset(str2, 0, sizeof(str2));
            strcpy(str2, TXTITEM.toLocal8Bit().data());
            memset(str, 0, TXTWIDTH);
            NStrFormat(str, str1, str2, NULL, NULL, NULL, TXTWIDTH);
            memcpy(txtstr + strlen(txtstr), str, TXTWIDTH + 1);
        }
    }
    else if(reporttype & DRAWERREPORT)
    {
        for(int i = 0; i < rows; i++)
        {
            TXTITEM = reportModel->item(i, 0)->text();
            memset(str, 0, TXTWIDTH);
            strcpy(str, TXTITEM.toLocal8Bit().data());
            StrFormat(str, TXTWIDTH, 0);
            memcpy(txtstr + strlen(txtstr), str, TXTWIDTH + 1);

            TXTITEM = reportModel->item(i, 3)->text();
            memset(str1, 0, sizeof(str1));
            strcpy(str1, "AMOUNT");
            memset(str2, 0, sizeof(str2));
            strcpy(str2, TXTITEM.toLocal8Bit().data());
            memset(str, 0, TXTWIDTH);
            NStrFormat(str, str1, str2, NULL, NULL, NULL, TXTWIDTH);
            memcpy(txtstr + strlen(txtstr), str, TXTWIDTH + 1);
        }
    }
    else if(reporttype & CORRECTREPORT)
    {
        for(int i = 0; i < rows; i++)
        {
            TXTITEM = reportModel->item(i, 0)->text();
            memset(str, 0, TXTWIDTH);
            strcpy(str, TXTITEM.toLocal8Bit().data());
            StrFormat(str, TXTWIDTH, 0);
            memcpy(txtstr + strlen(txtstr), str, TXTWIDTH + 1);

            TXTITEM = reportModel->item(i, 2)->text();
            memset(str1, 0, sizeof(str1));
            strcpy(str1, "QUANTITY");
            memset(str2, 0, sizeof(str2));
            str2[0] = '-';
            strcpy(str2 + 1, TXTITEM.toLocal8Bit().data());
            memset(str, 0, TXTWIDTH);
            NStrFormat(str, str1, str2, NULL, NULL, NULL, TXTWIDTH);
            memcpy(txtstr + strlen(txtstr), str, TXTWIDTH + 1);

            TXTITEM = reportModel->item(i, 3)->text();
            memset(str1, 0, sizeof(str1));
            strcpy(str1, "AMOUNT");
            memset(str2, 0, sizeof(str2));
            str2[0] = '-';
            strcpy(str2 + 1, TXTITEM.toLocal8Bit().data());
            memset(str, 0, TXTWIDTH);
            NStrFormat(str, str1, str2, NULL, NULL, NULL, TXTWIDTH);
            memcpy(txtstr + strlen(txtstr), str, TXTWIDTH + 1);
        }
    }
    else if(reporttype & DISCOUNTREPORT)
    {
        for(int i = 0; i < rows; i++)
        {
            TXTITEM = reportModel->item(i, 0)->text();
            memset(str1, 0, sizeof(str1));
            strcpy(str1, TXTITEM.toLocal8Bit().data());

            TXTITEM = reportModel->item(i, 3)->text();
            memset(str2, 0, sizeof(str2));
            if(strstr(str1, "-%"))
            {
                str2[0] = '-';
                strcpy(str2 + 1, TXTITEM.toLocal8Bit().data());
            }
            else
            {
                strcpy(str2, TXTITEM.toLocal8Bit().data());
            }
            memset(str, 0, TXTWIDTH);
            NStrFormat(str, str1, str2, NULL, NULL, NULL, TXTWIDTH);
            memcpy(txtstr + strlen(txtstr), str, TXTWIDTH + 1);
        }
    }
    else if(reporttype & TAXREPORT)
    {
        for(int i = 0; i < rows; i++)
        {
            TXTITEM = reportModel->item(i, 0)->text();
            memset(str, 0, TXTWIDTH);
            strcpy(str, TXTITEM.toLocal8Bit().data());
            StrFormat(str, TXTWIDTH, 0);
            if(strstr(str, "EXEMPT_"))
            {
                //不显示名称
            }
            else
            {
                memcpy(txtstr + strlen(txtstr), str, TXTWIDTH + 1);
            }

            if(strstr(str, "ZERO_VAT"))
            {
                memset(str1, 0, sizeof(str1));
                strcpy(str1, "ZEOR RATED SALES");

                float tmpdata = reportModel->item(i, 6)->text().toDouble() - reportModel->item(i, 3)->text().toDouble();
                memset(str2, 0, sizeof(str2));
                sprintf(str2, "%.02f", tmpdata);

                memset(str, 0, TXTWIDTH);
                NStrFormat(str, str1, str2, NULL, NULL, NULL, TXTWIDTH);
                memcpy(txtstr + strlen(txtstr), str, TXTWIDTH + 1);
            }
            else if(strstr(str, "EXEMPT_"))
            {
                memset(str1, 0, sizeof(str1));
                strcpy(str1, "VAT EXEMPT SALES");

                float tmpdata = reportModel->item(i, 6)->text().toDouble() - reportModel->item(i, 3)->text().toDouble();
                memset(str2, 0, sizeof(str2));
                sprintf(str2, "%.02f", tmpdata);

                memset(str, 0, TXTWIDTH);
                NStrFormat(str, str1, str2, NULL, NULL, NULL, TXTWIDTH);
                memcpy(txtstr + strlen(txtstr), str, TXTWIDTH + 1);

                memset(str1, 0, sizeof(str1));
                strcpy(str1, "VAT EXEMPT AMOUNT");

                tmpdata = 0 - reportModel->item(i, 3)->text().toDouble();
                memset(str2, 0, sizeof(str2));
                sprintf(str2, "%.02f", tmpdata);

                memset(str, 0, TXTWIDTH);
                NStrFormat(str, str1, str2, NULL, NULL, NULL, TXTWIDTH);
                memcpy(txtstr + strlen(txtstr), str, TXTWIDTH + 1);
            }
            else
            {
                memset(str1, 0, sizeof(str1));
                strcpy(str1, "GROSS SALES");

                float tmpdata = reportModel->item(i, 3)->text().toDouble();
                memset(str2, 0, sizeof(str2));
                sprintf(str2, "%.02f", tmpdata);

                memset(str, 0, TXTWIDTH);
                NStrFormat(str, str1, str2, NULL, NULL, NULL, TXTWIDTH);
                memcpy(txtstr + strlen(txtstr), str, TXTWIDTH + 1);
            }
        }
    }

    memset(str, 0, TXTWIDTH);
    ChToStr(str, '-', TXTWIDTH);
    memcpy(reporttxt + strlen(reporttxt), str, TXTWIDTH + 1);
}

//#define DISPTABLE

void reportDialog::creatreport(QString suffixname, char Idx, char * Titel, char Type)
{
    QStandardItemModel *reportModel = new QStandardItemModel(this);
    QStringList titles;
    if((Type & GRANDTOTALREPORT) && (Idx != ZONEREPORT && Idx != CLERKDAILY && Idx != CLERKWEEK))
    {
        titles << "OLD GRAND TOTAL" << "NEW GRAND TOTAL" << "TOTAL GROSS SALES";
    }
    else
    {
        //titles << "Name"<< "Qty" << "Amt" << "Ret" << "Disc" << "Cost";
        titles << "Name"<< "Cc" << "Qty" << "Amt" << "Ret" << "Disc" << "Cost";
    }

    reportModel->setHorizontalHeaderLabels(titles);

#ifdef DISPTABLE
    reportdisp *deptdisp = new reportdisp(this);
    deptdisp->setItemModel(reportModel);
#endif

    MyDb->readtable(suffixname, Idx, ZNo, NULL, reportModel, Type);
	QString IPADDR = QString("%1.%2.%3.%4").arg((ZNo >> 24) & 0xff).arg((ZNo >> 16) & 0xff)
		.arg((ZNo >> 8) & 0xff).arg(ZNo & 0xff);
	qDebug() << "--------------->IPADDR = " << IPADDR;

    //memset(reporttxt, 0, sizeof(reporttxt));
    ReportToTxt(reportModel, reporttxt, Titel, Type, Idx);
    //ui->reportedit->append(QString(QLatin1String(reporttxt)));

#ifdef DISPTABLE
    if(Idx & DAILYREPORT)
    {
        deptdisp->setWindowTitle(QString("DAILY REPORT--->%1").arg(QString(QLatin1String(Titel))));
    }
    else if(Idx & WEEKREPORT)
    {
        deptdisp->setWindowTitle(QString("PERIOD REPORT--->%1").arg(QString(QLatin1String(Titel))));
    }
    else if(Idx & CLERKDAILY)
    {
        deptdisp->setWindowTitle(QString("CLERK DAILY--->%1").arg(QString(QLatin1String(Titel))));
    }
    else if(Idx & CLERKWEEK)
    {
        deptdisp->setWindowTitle(QString("CLERK PERIOD--->%1").arg(QString(QLatin1String(Titel))));
    }
    else if(Idx & PLUDAILY)
    {
        deptdisp->setWindowTitle(QString("PERIOD PLU--->%1").arg(QString(QLatin1String(Titel))));
    }

    deptdisp->setcenter();
    deptdisp->show();
    deptdisp->raise();
    if(!deptdisp->isActiveWindow())
    {
        deptdisp->activateWindow();
    }
#endif
}

void reportDialog::on_grandtotal_clicked()
{
    creatreport(QString(GRANDTOTAL), DAILYREPORT, reportname[0], GRANDTOTALREPORT);
}

void reportDialog::on_department_clicked()
{
    creatreport(QString(DEPARTMENT), DAILYREPORT, reportname[1], DEPARTMENTREPORT);
}

void reportDialog::on_tender_clicked()
{
    creatreport(QString(TENDER), DAILYREPORT, reportname[2], TENDERREPORT);
}

void reportDialog::on_drawer_clicked()
{
    creatreport(QString(DRAWER), DAILYREPORT, reportname[3], DRAWERREPORT);
}

void reportDialog::on_correction_clicked()
{
    creatreport(QString(CORRECT), DAILYREPORT, reportname[4], CORRECTREPORT);
}

void reportDialog::on_discount_clicked()
{
    creatreport(QString(DISCOUNT), DAILYREPORT, reportname[5], DISCOUNTREPORT);
}

void reportDialog::on_tax_clicked()
{
    creatreport(QString(TAX), DAILYREPORT, reportname[6], TAXREPORT);
}

void reportDialog::on_grandtotal_2_clicked()
{
    creatreport(QString(GRANDTOTAL), WEEKREPORT, reportname[0], GRANDTOTALREPORT);
}

void reportDialog::on_department_2_clicked()
{
    creatreport(QString(DEPARTMENT), WEEKREPORT, reportname[1], DEPARTMENTREPORT);
}

void reportDialog::on_tender_2_clicked()
{
    creatreport(QString(TENDER), WEEKREPORT, reportname[2], TENDERREPORT);
}

void reportDialog::on_drawer_2_clicked()
{
    creatreport(QString(DRAWER), WEEKREPORT, reportname[3], DRAWERREPORT);
}

void reportDialog::on_correction_2_clicked()
{
    creatreport(QString(CORRECT), WEEKREPORT, reportname[4], CORRECTREPORT);
}

void reportDialog::on_discount_2_clicked()
{
    creatreport(QString(DISCOUNT), WEEKREPORT, reportname[5], DISCOUNTREPORT);
}

void reportDialog::on_tax_2_clicked()
{
    creatreport(QString(TAX), WEEKREPORT, reportname[6], TAXREPORT);
}

void reportDialog::on_grandtotal_3_clicked()
{
    creatreport(QString(GRANDTOTAL), CLERKDAILY, reportname[0], GRANDTOTALREPORT);
}

void reportDialog::on_tender_3_clicked()
{
    creatreport(QString(TENDER), CLERKDAILY, reportname[2], TENDERREPORT);
}

void reportDialog::on_drawer_3_clicked()
{
    creatreport(QString(DRAWER), CLERKDAILY, reportname[3], DRAWERREPORT);
}

void reportDialog::on_correction_3_clicked()
{
    creatreport(QString(CORRECT), CLERKDAILY, reportname[4], CORRECTREPORT);
}

void reportDialog::on_discount_3_clicked()
{
    creatreport(QString(DISCOUNT), CLERKDAILY, reportname[5], DISCOUNTREPORT);
}

void reportDialog::on_grandtotal_4_clicked()
{
    creatreport(QString(GRANDTOTAL), CLERKWEEK, reportname[0], GRANDTOTALREPORT);
}

void reportDialog::on_tender_4_clicked()
{
    creatreport(QString(TENDER), CLERKWEEK, reportname[2], TENDERREPORT);
}

void reportDialog::on_correction_4_clicked()
{
    creatreport(QString(CORRECT), CLERKWEEK, reportname[4], CORRECTREPORT);
}

void reportDialog::on_discount_4_clicked()
{
    creatreport(QString(DISCOUNT), CLERKWEEK, reportname[5], DISCOUNTREPORT);
}

void reportDialog::on_cleardbreport_clicked()
{
    ui->pushButton->setEnabled(false);
    ui->pushButton->setDisabled(true);
	qDebug() << "cleardbreport ip = " << QString("%1.%2.%3.%4").arg((ZNo >> 24) & 0xff).arg((ZNo >> 16) & 0xff)
                .arg((ZNo >> 8) & 0xff).arg(ZNo & 0xff);
	MyDb->setzno(ZNo);
    MyDb->cleartable();
    ui->pushButton->setDisabled(false);
    ui->pushButton->setEnabled(true);
}

void reportDialog::on_correction_5_clicked()
{
    #if 0
    creatreport(QString(GRANDTOTAL), ZONEREPORT, reportname[0], GRANDTOTALREPORT);
    #endif
}

void reportDialog::on_grandtotal_5_clicked()
{
#if 0
    creatreport(QString(PLU), PLUDAILY, reportname[7], PLUREPORT);
#endif
}

void reportDialog::on_pushButton_2_clicked()
{
    memset(reporttxt, 0, sizeof(reporttxt));
    ui->reportedit->clear();

    char str[TXTWIDTH + 1] = {0};
    str[TXTWIDTH] = '\n';
    memset(str, 0, TXTWIDTH);
    strcpy(str, "DAILY REPORT");
    StrFormat(str, TXTWIDTH, 1);
    memcpy(reporttxt + strlen(reporttxt), str, TXTWIDTH + 1);

    memset(str, 0, TXTWIDTH);
    ChToStr(str, '-', TXTWIDTH);
    memcpy(reporttxt + strlen(reporttxt), str, TXTWIDTH + 1);

    memset(str, 0, TXTWIDTH);
    ChToStr(str, '-', TXTWIDTH);
    memcpy(reporttxt + strlen(reporttxt), str, TXTWIDTH + 1);

    creatreport(QString(GRANDTOTAL), DAILYREPORT, reportname[0], GRANDTOTALREPORT);
    creatreport(QString(DEPARTMENT), DAILYREPORT, reportname[1], DEPARTMENTREPORT);
    creatreport(QString(TENDER), DAILYREPORT, reportname[2], TENDERREPORT);
    creatreport(QString(DRAWER), DAILYREPORT, reportname[3], DRAWERREPORT);
    creatreport(QString(CORRECT), DAILYREPORT, reportname[4], CORRECTREPORT);
    creatreport(QString(DISCOUNT), DAILYREPORT, reportname[5], DISCOUNTREPORT);
    creatreport(QString(TAX), DAILYREPORT, reportname[6], TAXREPORT);

    ui->reportedit->append(QString(QLatin1String(reporttxt)));
}

void reportDialog::on_pushButton_3_clicked()
{
    memset(reporttxt, 0, sizeof(reporttxt));
    ui->reportedit->clear();

    char str[TXTWIDTH + 1] = {0};
    str[TXTWIDTH] = '\n';
    memset(str, 0, TXTWIDTH);
    strcpy(str, "PERIOD REPORT");
    StrFormat(str, TXTWIDTH, 1);
    memcpy(reporttxt + strlen(reporttxt), str, TXTWIDTH + 1);

    memset(str, 0, TXTWIDTH);
    ChToStr(str, '-', TXTWIDTH);
    memcpy(reporttxt + strlen(reporttxt), str, TXTWIDTH + 1);

    memset(str, 0, TXTWIDTH);
    ChToStr(str, '-', TXTWIDTH);
    memcpy(reporttxt + strlen(reporttxt), str, TXTWIDTH + 1);

    creatreport(QString(GRANDTOTAL), WEEKREPORT, reportname[0], GRANDTOTALREPORT);
    creatreport(QString(DEPARTMENT), WEEKREPORT, reportname[1], DEPARTMENTREPORT);
    creatreport(QString(TENDER), WEEKREPORT, reportname[2], TENDERREPORT);
    creatreport(QString(DRAWER), WEEKREPORT, reportname[3], DRAWERREPORT);
    creatreport(QString(CORRECT), WEEKREPORT, reportname[4], CORRECTREPORT);
    creatreport(QString(DISCOUNT), WEEKREPORT, reportname[5], DISCOUNTREPORT);
    creatreport(QString(TAX), WEEKREPORT, reportname[6], TAXREPORT);

    ui->reportedit->append(QString(QLatin1String(reporttxt)));
}

void reportDialog::on_pushButton_4_clicked()
{
    memset(reporttxt, 0, sizeof(reporttxt));
    ui->reportedit->clear();

    char str[TXTWIDTH + 1] = {0};
    str[TXTWIDTH] = '\n';
    memset(str, 0, TXTWIDTH);
    strcpy(str, "CLERK DAILY");
    StrFormat(str, TXTWIDTH, 1);
    memcpy(reporttxt + strlen(reporttxt), str, TXTWIDTH + 1);

    memset(str, 0, TXTWIDTH);
    ChToStr(str, '-', TXTWIDTH);
    memcpy(reporttxt + strlen(reporttxt), str, TXTWIDTH + 1);

    memset(str, 0, TXTWIDTH);
    ChToStr(str, '-', TXTWIDTH);
    memcpy(reporttxt + strlen(reporttxt), str, TXTWIDTH + 1);

    creatreport(QString(GRANDTOTAL), CLERKDAILY, reportname[0], GRANDTOTALREPORT);
    creatreport(QString(TENDER), CLERKDAILY, reportname[2], TENDERREPORT);
    creatreport(QString(DRAWER), CLERKDAILY, reportname[3], DRAWERREPORT);
    creatreport(QString(CORRECT), CLERKDAILY, reportname[4], CORRECTREPORT);
    creatreport(QString(DISCOUNT), CLERKDAILY, reportname[5], DISCOUNTREPORT);

    ui->reportedit->append(QString(QLatin1String(reporttxt)));
}

void reportDialog::on_pushButton_5_clicked()
{
    memset(reporttxt, 0, sizeof(reporttxt));
    ui->reportedit->clear();

    char str[TXTWIDTH + 1] = {0};
    str[TXTWIDTH] = '\n';
    memset(str, 0, TXTWIDTH);
    strcpy(str, "CLERK PERIOD");
    StrFormat(str, TXTWIDTH, 1);
    memcpy(reporttxt + strlen(reporttxt), str, TXTWIDTH + 1);

    memset(str, 0, TXTWIDTH);
    ChToStr(str, '-', TXTWIDTH);
    memcpy(reporttxt + strlen(reporttxt), str, TXTWIDTH + 1);

    memset(str, 0, TXTWIDTH);
    ChToStr(str, '-', TXTWIDTH);
    memcpy(reporttxt + strlen(reporttxt), str, TXTWIDTH + 1);

    creatreport(QString(GRANDTOTAL), CLERKWEEK, reportname[0], GRANDTOTALREPORT);
    creatreport(QString(TENDER), CLERKWEEK, reportname[2], TENDERREPORT);
    creatreport(QString(CORRECT), CLERKWEEK, reportname[4], CORRECTREPORT);
    creatreport(QString(DISCOUNT), CLERKWEEK, reportname[5], DISCOUNTREPORT);

    ui->reportedit->append(QString(QLatin1String(reporttxt)));
}
