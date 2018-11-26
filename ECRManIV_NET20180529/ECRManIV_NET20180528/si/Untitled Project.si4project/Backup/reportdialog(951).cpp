#include "reportdialog.h"
#include "ui_reportdialog.h"
#include "reportdb.h"
#include "tcpclient.h"
#include "itemreport.h"
#include "reportdisp.h"

#include "qvariantlistlistmodel.h"

#include "mycheckboxheader.h"

#include <QDebug>
#include <QMessageBox>
#include <QStandardItemModel>
#include <QVariantList>
#include <QModelIndex>

#include "button/switchbutton.h"

class MyPage : public QWidget
{
public:
    MyPage(QWidget *parent = 0);
    void additem(SwitchButton *btn);
private:
    QHBoxLayout *myLayout;
};

MyPage::MyPage(QWidget *parent)
    : QWidget(parent)
{
    myLayout = new QHBoxLayout;

    setLayout(myLayout);
}

void MyPage::additem(SwitchButton *btn)
{
    myLayout->addWidget(btn, 1, Qt::AlignCenter);
}

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

    XZModle = 0x01;

#if 0
    memset(reporttxt, 0, sizeof(reporttxt));
    strcpy(reporttxt, "this is a test txt\nok");
    QString TXT = QString(QLatin1String(reporttxt));

    ui->reportedit->setText(TXT);
#endif

    ui->info->clear();

    ui->tableWidget->setStyleSheet(getQssContent());

    MyCheckboxHeader *myHeader = new MyCheckboxHeader(Qt::Horizontal, ui->tableWidget);
    ui->tableWidget->resizeColumnsToContents();
    ui->tableWidget->setHorizontalHeader(myHeader);
    //ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->horizontalHeader()->setResizeMode(QHeaderView::Stretch);

    connect(myHeader, SIGNAL(signalStateTrange(int)), this, SLOT(slotsSelectAll(int)));

    ui->tableWidget->verticalHeader()->setVisible(false);   //隐藏列表�?
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setColumnWidth(0, 80);
    ui->tableWidget->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    ui->tableWidget->horizontalHeader()->setResizeMode(0, QHeaderView::Fixed);
    ui->tableWidget->resizeColumnsToContents();

    ui->tableWidget->setAlternatingRowColors(true);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows); //整行选中的方�?
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);   //禁止修改
    //ui->tableWidget->setFrameShape(QFrame::NoFrame); //设置无边�?
    //ui->tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}");//设置表头背景�?
    //ui->tableWidget->horizontalHeader()->setHighlightSections(false);//点击表时不对表头行光亮（获取焦点�?

    ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<""<<"IP");

    connect(ui->tableWidget, SIGNAL(cellChanged(int,int)), this, SLOT(changeTest(int, int)));

	zdailybtn = NULL;
	zweekbtn = NULL;
	zplubtn = NULL;
	ztimebtn = NULL;
	zclerkbtn = NULL;
	zclerkweekbtn = NULL;

	zbtnnum = 1;
	
    timebtn = new SwitchButton(this);
    timebtn->setGeometry(50, 380, 101, 31);

    connect(timebtn, SIGNAL(checkedChanged(bool)), this, SLOT(checkedChanged(bool)));

    timecount = 120;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(showTime()));
    //timer->start( 1000 );  //1000ms 表示1�?
}

reportDialog::~reportDialog()
{
	if(zdailybtn)
		delete zdailybtn;
	if(zweekbtn)
		delete zweekbtn;
	if(zplubtn)
		delete zplubtn;
	if(ztimebtn)
		delete ztimebtn;
	if(zclerkbtn)
		delete zclerkbtn;
	if(zclerkweekbtn)
		delete zclerkweekbtn;
	
	zdailybtn = NULL;
	zweekbtn = NULL;
	zplubtn = NULL;
	ztimebtn = NULL;
	zclerkbtn = NULL;
	zclerkweekbtn = NULL;
	
    delete ui;
}

void reportDialog::showTime()
{
    int hour, min, sec, value;

    if(timecount != 0)
    {
        timecount--;
        hour = timecount / (60 * 60);
        value = timecount % (60 * 60);

        min = value / 60;
        sec = value % 60;

        QTime ctime(hour, min, sec);
        ui->timeEdit->setTime(ctime);
    }
    else
    {
        timer->stop();

        on_pushButton_clicked();
    }
}

void reportDialog::zdailycheckedChanged(bool btnchecked)
{
    if(btnchecked)
    {
        qDebug("--->zdaily ON");
		zbtnnum = 1;
        zweekbtn->setChecked(false);
        zplubtn->setChecked(false);
        ztimebtn->setChecked(false);
        zclerkbtn->setChecked(false);
        zclerkweekbtn->setChecked(false);
    }
    else
    {
        qDebug("--->zdaily OFF");
    }
}

void reportDialog::zweekcheckedChanged(bool btnchecked)
{
    if(btnchecked)
    {
        qDebug("--->zweek ON");
		zbtnnum = 2;
        zdailybtn->setChecked(false);
        zplubtn->setChecked(false);
        ztimebtn->setChecked(false);
        zclerkbtn->setChecked(false);
        zclerkweekbtn->setChecked(false);
    }
    else
    {
        qDebug("--->zweek OFF");
    }
}

void reportDialog::zplucheckedChanged(bool btnchecked)
{
	if(btnchecked)
    {
        qDebug("--->zplu ON");
		zbtnnum = 3;
        zdailybtn->setChecked(false);
        zweekbtn->setChecked(false);
        ztimebtn->setChecked(false);
        zclerkbtn->setChecked(false);
        zclerkweekbtn->setChecked(false);
    }
    else
    {
        qDebug("--->zplu OFF");
    }
}

void reportDialog::ztimecheckedChanged(bool btnchecked)
{
    if(btnchecked)
    {
        qDebug("--->ztime ON");
		zbtnnum = 4;
        zdailybtn->setChecked(false);
        zweekbtn->setChecked(false);
        zplubtn->setChecked(false);
        zclerkbtn->setChecked(false);
        zclerkweekbtn->setChecked(false);
    }
    else
    {
        qDebug("--->ztime OFF");
    }
}

void reportDialog::zclerkcheckedChanged(bool btnchecked)
{
	if(btnchecked)
    {
        qDebug("--->zclerk ON");
		zbtnnum = 5;
        zdailybtn->setChecked(false);
        zweekbtn->setChecked(false);
        zplubtn->setChecked(false);
        ztimebtn->setChecked(false);
        zclerkweekbtn->setChecked(false);
    }
    else
    {
        qDebug("--->zclerk OFF");
    }
}

void reportDialog::zclerkweekcheckedChanged(bool btnchecked)
{
	if(btnchecked)
    {
        qDebug("--->zclerkweek ON");
		zbtnnum = 6;
        zdailybtn->setChecked(false);
        zweekbtn->setChecked(false);
        zplubtn->setChecked(false);
        ztimebtn->setChecked(false);
        zclerkbtn->setChecked(false);
    }
    else
    {
        qDebug("--->zclerkweek OFF");
    }
}


void reportDialog::checkedChanged(bool btnchecked)
{
    if(btnchecked)
    {
        qDebug("--->time ON");
        //QTime crtime = ui->timeEdit->dateTime().time();
        QTime crtime = ui->timeEdit->time();
        timecount = crtime.hour() * 60 * 60 + crtime.minute() * 60 + crtime.second();
        qDebug() << "--->crtime" << crtime << "timecount = " << timecount;

        ui->timeEdit->setEnabled(false);
        if(timecount > 0)
        {
            timer->start( 1000 );  //1000ms 表示1�?
        }
    }
    else
    {
        qDebug("--->time OFF");
        timer->stop();
        ui->timeEdit->setEnabled(true);
    }
}

QString reportDialog::getQssContent()
{
    QFile styleSheet("./tablewidgetstyle.txt");

    if(!styleSheet.open(QIODevice::ReadOnly))
    {
        qDebug("Can't open the style sheet file.");
        return "";
    }

    return styleSheet.readAll();
}

void reportDialog::setiplist(QString IP, bool checked)
{
    int rows=ui->tableWidget->rowCount();

    ui->tableWidget->insertRow(rows);

    QTableWidgetItem *checkBox = new QTableWidgetItem();
    //checkBox->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled );
    //checkBox->setTextAlignment(Qt::AlignVCenter);
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
        //ui->tableWidget->setCurrentCell(rows, QItemSelectionModel::Select);
        ui->tableWidget->item(rows, 1)->setSelected(true);

    }
}

void reportDialog::slotsSelectAll(int state)
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

void reportDialog::changeTest(int row, int col)
{
    qDebug("row = %d, col = %d", row, col);
#if 1
    if(ui->tableWidget->item(row, col)->checkState() == Qt::Checked)
    {
        qDebug("checked");
    }
    else
    {
        qDebug("unchecked");
    }
#endif
}

void reportDialog::StripToZno(QString ipstr)
{
    char ch[64] = {0};
    char tmpdata[16] = {0};
    QString IP = ipstr;
    qDebug() << "ipstr = " << IP;

    strcpy(ch, IP.toLocal8Bit().data());

    char *tmpp, *tmpq;
    int ip[4], ipcount = 0;
    tmpq = ch;

    qDebug("ch = %s", ch);

    while(tmpp = strstr(tmpq, "."))
    {
        memset(tmpdata, 0, sizeof(tmpdata));
        memcpy(tmpdata, tmpq, tmpp - tmpq);
        ip[ipcount++] = atoi(tmpdata);
        tmpp++;
        tmpq = tmpp;
    }
    ip[ipcount++] = atoi(tmpq);

    qDebug("---> ip = %d.%d.%d.%d", ip[0], ip[1], ip[2], ip[3]);

    ZNo = (ip[0] << 24)&0xff000000 | (ip[1] << 16)&0x00ff0000 | (ip[2] << 8)&0x0000ff00 | ip[3]&0xff;
    qDebug("ZNo = %04x", ZNo);
}

void reportDialog::tcpconnectcash()
{
    if(udflag == 0x03)
    {
        return;
    }

    ui->tableWidget->clearSelection();

    for(;IpIndex < IpIndexMax; IpIndex++)
    {
        if(ui->tableWidget->item(IpIndex, 0)->checkState() == Qt::Checked)
        {
            ui->tableWidget->item(IpIndex, 1)->setSelected(true);
            IpStr = ui->tableWidget->item(IpIndex,1)->text();//取出字符�?
            ui->info->setText(QString("start connection to %1").arg(IpStr));
            StripToZno(IpStr);
            QCoreApplication::processEvents();//避免界面冻结
            emit setserverip(IpStr);
            break;
        }
    }

    if(IpIndex < IpIndexMax)
    {
        udflag = 0x02;

        itemindex = 0;

        sendbuf[0][0] = 'P';
        sendbuf[0][1] = 2;
        *((unsigned short *)(sendbuf[0] + 2)) = 100;
        emit connecthost();
    }
}

void reportDialog::on_pushButton_clicked()
{
    IpIndexMax = ui->tableWidget->rowCount();
    IpIndex = 0;

    udflag = 0x0;

    tcpconnectcash();
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

        qDebug("itemindex = %d, senditemmax = %d", itemindex, senditemmax);
        if(itemindex < senditemmax)
        {
            datalen = sendbuf[itemindex][1] + 2;
            //qDebug() << "send data len = " << datalen;
            emit senddata(sendbuf[itemindex], datalen);
        }
        else
        {
#if 0
            ui->cleardbreport->setEnabled(true);
            emit unconnecthost();
#else
            qDebug() << "--->start connet next";
            ui->cleardbreport->setEnabled(true);
            emit unconnecthost();
            IpIndex++;
            tcpconnectcash();
#endif
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
        ui->cleardbreport->setEnabled(true);
        ui->info->setText(QString("can not connection to %1").arg(IpStr));
        QCoreApplication::processEvents();//避免界面冻结
        IpIndex++;
        tcpconnectcash();
    }

    if(tcpstat == TCPSENDERR)
    {
        ui->cleardbreport->setEnabled(true);
        ui->info->setText(QString("send data to %1 time out.").arg(IpStr));
        IpIndex++;
        tcpconnectcash();
    }

    if(tcpstat == TCPRCVERR)
    {
        ui->cleardbreport->setEnabled(true);
        ui->info->setText(QString("recv data from %1 time out.").arg(IpStr));
        IpIndex++;
        tcpconnectcash();
    }

    if(tcpstat == TCPCONNECTOK)
    {
        ui->info->setText(QString("connection to %1 success.").arg(IpStr));
        QCoreApplication::processEvents();//避免界面冻结
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
        if(udflag == 0x02) //先获取信�?
        {
            //
        }
        else if(udflag == 0x03)
        {

            //控制打印
        }
        else
        {
            itemindex++;
            ui->progressBar->setValue(itemindex);
            QCoreApplication::processEvents();//避免界面冻结

            if(itemindex == senditemmax)
            {
                emit unconnecthost();
                ui->cleardbreport->setEnabled(true);
            }
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
        if(itemindex == senditemmax)
        {
            IpIndex++;
            tcpconnectcash();
        }
        return;
    }

    if(udflag == 0x03)
    {
        //控制打印
        emit unconnecthost();
        return;
    }

    if(udflag == 0x02)
    {
    #if 0
        if(XZModle == 0x01)
	#endif
        {
            cashid = recvbuf[7];
            udflag = 0x01; //开始下载有效数�?

            downloaddata(1);
        }

        return;
    }

    MyDb->setzno(ZNo);
    MyDb->setcashid(cashid);
    MyDb->setcaship(IpStr);
	
	if(XZModle == 0x01)
	{
		MyDb->SetDataType(0x0);
		MyDb->datadeal(recvbuf+2, sizelen);
	}
	else if(XZModle == 0x02)
	{
		MyDb->SetDataType(DataReportType);
    	MyDb->datadeal(recvbuf+2, sizelen);
	}
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

#if 0
        emit connecthost();
#else
        int datalen = sendbuf[itemindex][1] + 2;
        emit senddata(sendbuf[itemindex], datalen);
#endif
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

    if((reportmod & ZONEREPORT) || (reporttype & PLUREPORT))
    {
        //不显�?
    }
    else
    {
        memset(str, 0, TXTWIDTH);
        strcpy(str, Titel);
        StrFormat(str, TXTWIDTH, 5);

        memcpy(txtstr + strlen(txtstr), str, TXTWIDTH + 1);

        memset(str, 0, TXTWIDTH);
        ChToStr(str, '*', TXTWIDTH);
        memcpy(txtstr + strlen(txtstr), str, TXTWIDTH + 1);
    }

    QString TXTITEM;

    int rows = reportModel->rowCount();
    qDebug() << "--->reportModel rows = " << rows;
    int columns = reportModel->columnCount();
    qDebug() << "--->reportModel columns = " << columns;

    if(reporttype & GRANDTOTALREPORT)
    {
        qDebug() << "--->columns = " << columns;
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
            if(reportmod & ZONEREPORT)
            {
                qDebug() << "--->ZONEREPORT";
                for(int i = 0; i < rows; i++)
                {
                memset(str, 0, TXTWIDTH);
                TXTITEM = reportModel->item(i, 0)->text();
                strcpy(str, TXTITEM.toLocal8Bit().data());
                StrFormat(str, TXTWIDTH, 0);
                memcpy(txtstr + strlen(txtstr), str, TXTWIDTH + 1);

                memset(str, 0, TXTWIDTH);
                ChToStr(str, '=', TXTWIDTH);
                memcpy(txtstr + strlen(txtstr), str, TXTWIDTH + 1);

                if(reportModel->item(i, 3)->text().toDouble() > 0)
                {
                    qDebug() << "AMOUNT = " << reportModel->item(i, 3)->text().toDouble();
                    memset(str, 0, TXTWIDTH);
                    strcpy(str, "GRAND TOTAL");
                    StrFormat(str, TXTWIDTH, 5);
                    memcpy(txtstr + strlen(txtstr), str, TXTWIDTH + 1);

                    memset(str, 0, TXTWIDTH);
                    ChToStr(str, '*', TXTWIDTH);
                    memcpy(txtstr + strlen(txtstr), str, TXTWIDTH + 1);

                    memset(str1, 0, sizeof(str1));
                    strcpy(str1, "AMOUNT");

                    TXTITEM = reportModel->item(i, 3)->text();
                    memset(str2, 0, sizeof(str2));
                    strcpy(str2, TXTITEM.toLocal8Bit().data());

                    memset(str, 0, TXTWIDTH);
                    NStrFormat(str, str1, str2, NULL, NULL, NULL, TXTWIDTH);
                    memcpy(txtstr + strlen(txtstr), str, TXTWIDTH + 1);

                    memset(str, 0, TXTWIDTH);
                    ChToStr(str, '-', TXTWIDTH);
                    memcpy(txtstr + strlen(txtstr), str, TXTWIDTH + 1);
                }
                }
            }
            else
            {
                qDebug() << "---> NOT ZONEREPORT";
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
    }
    else if(reporttype & PLUREPORT)
    {
        memset(str1, 0, sizeof(str1));
        strcpy(str1, "PLU");
        memset(str2, 0, sizeof(str2));
        strcpy(str2, "QUANTITY");
        memset(str3, 0, sizeof(str3));
        strcpy(str3, "AMOUNT");
        memset(str, 0, TXTWIDTH);
        NStrFormat(str, str1, str2, str3, NULL, NULL, TXTWIDTH);
        memcpy(txtstr + strlen(txtstr), str, TXTWIDTH + 1);

        memset(str, 0, TXTWIDTH);
        ChToStr(str, '*', TXTWIDTH);
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
                //不显示名�?
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
    if(XZModle == 0x01)
    {
        memset(reporttxt, 0, sizeof(reporttxt));
        ui->reportedit->clear();

        char str[TXTWIDTH + 1] = {0};
        str[TXTWIDTH] = '\n';
        memset(str, 0, TXTWIDTH);
        strcpy(str, "TIME ZONE");
        StrFormat(str, TXTWIDTH, 1);
        memcpy(reporttxt + strlen(reporttxt), str, TXTWIDTH + 1);

        memset(str, 0, TXTWIDTH);
        ChToStr(str, '=', TXTWIDTH);
        memcpy(reporttxt + strlen(reporttxt), str, TXTWIDTH + 1);

    #if 1
        creatreport(QString(GRANDTOTAL), ZONEREPORT, reportname[0], GRANDTOTALREPORT);
    #endif

        ui->reportedit->append(QString(QLatin1String(reporttxt)));
    }

    if(XZModle == 0x02)
    {
        ui->reportedit->clear();
        udflag = 0x03;

        itemindex = 0;

        sendbuf[0][0] = 'R';
        sendbuf[0][1] = 2;
        sendbuf[0][2] = 0x05;
        sendbuf[0][3] = 0x00;
        emit connecthost();
    }
}

void reportDialog::on_grandtotal_5_clicked()
{
    if(XZModle == 0x01)
    {
        memset(reporttxt, 0, sizeof(reporttxt));
        ui->reportedit->clear();

        char str[TXTWIDTH + 1] = {0};
        str[TXTWIDTH] = '\n';
        memset(str, 0, TXTWIDTH);
        strcpy(str, "PLU REPORT");
        StrFormat(str, TXTWIDTH, 1);
        memcpy(reporttxt + strlen(reporttxt), str, TXTWIDTH + 1);

        memset(str, 0, TXTWIDTH);
        ChToStr(str, '=', TXTWIDTH);
        memcpy(reporttxt + strlen(reporttxt), str, TXTWIDTH + 1);

    #if 1
        creatreport(QString(PLU), PLUDAILY, reportname[7], PLUREPORT);
    #endif

        ui->reportedit->append(QString(QLatin1String(reporttxt)));
    }

    if(XZModle == 0x02)
    {
        ui->reportedit->clear();
        udflag = 0x03;

        itemindex = 0;

        sendbuf[0][0] = 'R';
        sendbuf[0][1] = 2;
        sendbuf[0][2] = 0x03;
        sendbuf[0][3] = 0x00;
        emit connecthost();
    }
}

void reportDialog::on_pushButton_2_clicked()
{
    if(XZModle == 0x01)
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
        ChToStr(str, '=', TXTWIDTH);
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

    if(XZModle == 0x02)
    {
        ui->reportedit->clear();
        udflag = 0x03;

        itemindex = 0;

        sendbuf[0][0] = 'R';
        sendbuf[0][1] = 2;
        sendbuf[0][2] = 0x01;
        sendbuf[0][3] = 0x00;
        emit connecthost();
    }
}

void reportDialog::on_pushButton_3_clicked()
{
    if(XZModle == 0x01)
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
        ChToStr(str, '=', TXTWIDTH);
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

    if(XZModle == 0x02)
    {
        ui->reportedit->clear();
        udflag = 0x03;

        itemindex = 0;

        sendbuf[0][0] = 'R';
        sendbuf[0][1] = 2;
        sendbuf[0][2] = 0x02;
        sendbuf[0][3] = 0x00;
        emit connecthost();
    }
}

void reportDialog::on_pushButton_4_clicked()
{
    if(XZModle == 0x01)
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
        ChToStr(str, '=', TXTWIDTH);
        memcpy(reporttxt + strlen(reporttxt), str, TXTWIDTH + 1);

        creatreport(QString(GRANDTOTAL), CLERKDAILY, reportname[0], GRANDTOTALREPORT);
        creatreport(QString(TENDER), CLERKDAILY, reportname[2], TENDERREPORT);
        creatreport(QString(DRAWER), CLERKDAILY, reportname[3], DRAWERREPORT);
        creatreport(QString(CORRECT), CLERKDAILY, reportname[4], CORRECTREPORT);
        creatreport(QString(DISCOUNT), CLERKDAILY, reportname[5], DISCOUNTREPORT);

        ui->reportedit->append(QString(QLatin1String(reporttxt)));
    }

    if(XZModle == 0x02)
    {
        ui->reportedit->clear();
    }
}

void reportDialog::on_pushButton_5_clicked()
{
    if(XZModle == 0x01)
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
        ChToStr(str, '=', TXTWIDTH);
        memcpy(reporttxt + strlen(reporttxt), str, TXTWIDTH + 1);

        creatreport(QString(GRANDTOTAL), CLERKWEEK, reportname[0], GRANDTOTALREPORT);
        creatreport(QString(TENDER), CLERKWEEK, reportname[2], TENDERREPORT);
        creatreport(QString(CORRECT), CLERKWEEK, reportname[4], CORRECTREPORT);
        creatreport(QString(DISCOUNT), CLERKWEEK, reportname[5], DISCOUNTREPORT);

        ui->reportedit->append(QString(QLatin1String(reporttxt)));
    }

    if(XZModle == 0x02)
    {
        ui->reportedit->clear();
    }
}

void reportDialog::on_xreport_clicked()
{
    XZModle = 0x01;
    ui->stackedWidget->setCurrentIndex(0);

	if(zdailybtn)
		delete zdailybtn;
	if(zweekbtn)
		delete zweekbtn;
	if(zplubtn)
		delete zplubtn;
	if(ztimebtn)
		delete ztimebtn;
	if(zclerkbtn)
		delete zclerkbtn;
	if(zclerkweekbtn)
		delete zclerkweekbtn;
	
	zdailybtn = NULL;
	zweekbtn = NULL;
	zplubtn = NULL;
	ztimebtn = NULL;
	zclerkbtn = NULL;
	zclerkweekbtn = NULL;
}

void reportDialog::on_zreport_clicked()
{
    XZModle = 0x02;
    ui->stackedWidget->setCurrentIndex(1);

	//daily
    if(zdailybtn)
    {
        delete zdailybtn;
    }

    zdailybtn = new SwitchButton(ui->stackedWidget);
    zdailybtn->setGeometry(40, 10, 101, 23);
    zdailybtn->setButtonStyle(zdailybtn->ButtonStyle_Image);
    zdailybtn->setImage(QString(":/images/icons/dailyreportoff.png"), QString(":/images/icons/dailyreporton.png"));
    connect(zdailybtn, SIGNAL(checkedChanged(bool)), this, SLOT(zdailycheckedChanged(bool)));

    zdailybtn->show();

	//week
	if(zweekbtn)
    {
        delete zweekbtn;
    }

    zweekbtn = new SwitchButton(ui->stackedWidget);
    zweekbtn->setGeometry(40, 50, 101, 23);
    zweekbtn->setButtonStyle(zweekbtn->ButtonStyle_Image);
    zweekbtn->setImage(QString(":/images/icons/weekreportoff.png"), QString(":/images/icons/weekreporton.png"));
    connect(zweekbtn, SIGNAL(checkedChanged(bool)), this, SLOT(zweekcheckedChanged(bool)));

    zweekbtn->show();

	//plu
	if(zplubtn)
    {
        delete zplubtn;
    }

    zplubtn = new SwitchButton(ui->stackedWidget);
    zplubtn->setGeometry(40, 90, 101, 23);
    zplubtn->setButtonStyle(zplubtn->ButtonStyle_Image);
    zplubtn->setImage(QString(":/images/icons/plureportoff.png"), QString(":/images/icons/plureporton.png"));
    connect(zplubtn, SIGNAL(checkedChanged(bool)), this, SLOT(zplucheckedChanged(bool)));

    zplubtn->show();

	//time
	if(ztimebtn)
    {
        delete ztimebtn;
    }

    ztimebtn = new SwitchButton(ui->stackedWidget);
    ztimebtn->setGeometry(40, 130, 101, 23);
    ztimebtn->setButtonStyle(ztimebtn->ButtonStyle_Image);
    ztimebtn->setImage(QString(":/images/icons/timereportoff.png"), QString(":/images/icons/timereporton.png"));
    connect(ztimebtn, SIGNAL(checkedChanged(bool)), this, SLOT(ztimecheckedChanged(bool)));

    ztimebtn->show();

	//clerk
	if(zclerkbtn)
    {
        delete zclerkbtn;
    }

    zclerkbtn = new SwitchButton(ui->stackedWidget);
    zclerkbtn->setGeometry(40, 170, 101, 23);
    zclerkbtn->setButtonStyle(zclerkbtn->ButtonStyle_Image);
    zclerkbtn->setImage(QString(":/images/icons/clerkreportoff.png"), QString(":/images/icons/clerkreporton.png"));
    connect(zclerkbtn, SIGNAL(checkedChanged(bool)), this, SLOT(zclerkcheckedChanged(bool)));

    zclerkbtn->show();

	//clerkweek
	if(zclerkweekbtn)
    {
        delete zclerkweekbtn;
    }

    zclerkweekbtn = new SwitchButton(ui->stackedWidget);
    zclerkweekbtn->setGeometry(40, 210, 101, 23);
    zclerkweekbtn->setButtonStyle(zclerkweekbtn->ButtonStyle_Image);
    zclerkweekbtn->setImage(QString(":/images/icons/clerkweekreportoff.png"), QString(":/images/icons/clerkweekreporton.png"));
    connect(zclerkweekbtn, SIGNAL(checkedChanged(bool)), this, SLOT(zclerkweekcheckedChanged(bool)));

    zclerkweekbtn->show();

    switch (zbtnnum) {
    case 1:
        zdailybtn->setChecked(true);
        break;
    case 2:
        zweekbtn->setChecked(true);
    case 3:
        zplubtn->setChecked(true);
    case 4:
        ztimebtn->setChecked(true);
    case 5:
        zclerkbtn->setChecked(true);
    case 6:
        zclerkweekbtn->setChecked(true);
    default:
        break;
    }
}

void reportDialog::on_tableWidget_clicked(const QModelIndex &index)
{
    bool focus = ui->tableWidget->isItemSelected(ui->tableWidget->currentItem()); // 判断是否选中一�?
    if(focus)
    {
        int row1 = ui->tableWidget->currentItem()->row(); // 当前选中�?
        IpStr = ui->tableWidget->item(row1,1)->text();//取出字符�?
        StripToZno(IpStr);
        emit setserverip(IpStr);
        this->setWindowTitle(IpStr);
    }
}
