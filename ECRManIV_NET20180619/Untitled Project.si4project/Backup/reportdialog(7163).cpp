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
#include <QPushButton>

#include "button/switchbutton.h"
#include "./message/message.h"

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
    ui->reportedit->setWordWrapMode(QTextOption::NoWrap);

    ui->cleardbreport->setDisabled(true);

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

    ui->tableWidget->verticalHeader()->setVisible(false);   //隐藏列表???
    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setColumnWidth(0, 80);
    ui->tableWidget->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    ui->tableWidget->horizontalHeader()->setResizeMode(0, QHeaderView::Fixed);
    ui->tableWidget->resizeColumnsToContents();

    ui->tableWidget->horizontalHeader()->setResizeMode(1, QHeaderView::ResizeToContents);
    ui->tableWidget->horizontalHeader()->setResizeMode(2, QHeaderView::ResizeToContents);

    ui->tableWidget->setAlternatingRowColors(true);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows); //整行选中的方???
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);   //禁止修改
    //ui->tableWidget->setFrameShape(QFrame::NoFrame); //设置� 边???
    //ui->tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}");//设置表头背景???
    //ui->tableWidget->horizontalHeader()->setHighlightSections(false);//点击表时不对表头行光亮（获取焦点???

    qDebug() << ">>>>>>>>>>>>>>cashname = " << CASHNAME;
    ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<""<<CASHNAME<<"IP");

    connect(ui->tableWidget, SIGNAL(cellChanged(int,int)), this, SLOT(changeTest(int, int)));

    zdailybtn = NULL;
#ifdef WEEK_REPORT
    zweekbtn = NULL;
#endif
    zplubtn = NULL;
    ztimebtn = NULL;
    zclerkbtn = NULL;
#ifdef WEEK_REPORT
    zclerkweekbtn = NULL;
#endif

    zbtnnum = 1;

    timebtn = new SwitchButton(this);
    timebtn->setGeometry(50, 380, 101, 31);

    connect(timebtn, SIGNAL(checkedChanged(bool)), this, SLOT(checkedChanged(bool)));

    timecount = 120;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(showTime()));
    //timer->start( 1000 );  //1000ms 表示1???
}

reportDialog::~reportDialog()
{
    if(zdailybtn)
        delete zdailybtn;
#ifdef WEEK_REPORT
    if(zweekbtn)
        delete zweekbtn;
#endif
    if(zplubtn)
        delete zplubtn;
    if(ztimebtn)
        delete ztimebtn;
    if(zclerkbtn)
        delete zclerkbtn;
#ifdef WEEK_REPORT
    if(zclerkweekbtn)
        delete zclerkweekbtn;
#endif

    zdailybtn = NULL;
#ifdef WEEK_REPORT
    zweekbtn = NULL;
#endif
    zplubtn = NULL;
    ztimebtn = NULL;
    zclerkbtn = NULL;
#ifdef WEEK_REPORT
    zclerkweekbtn = NULL;
#endif

    delete ui;
}

void reportDialog::Delay_MSec(unsigned int msec)
{
    QTime _Timer = QTime::currentTime().addMSecs(msec);
    while( QTime::currentTime() < _Timer )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void reportDialog::showTime()
{
#if 0
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

        on_DOWNLOADDATA_clicked();
    }
#else
    QTime setime = ui->timeEdit->time();
    QTime crtime = QTime::currentTime();

    if(setime.hour() == crtime.hour() && setime.minute() == crtime.minute() && setime.second() == crtime.second())
    {
        on_DOWNLOADDATA_clicked();
    }
#endif
}

void reportDialog::zdailycheckedChanged(bool btnchecked)
{
    if(btnchecked)
    {
        qDebug("--->zdaily ON");
        zbtnnum = 1;
        DataReportType = DAILYREPORT;
#ifdef WEEK_REPORT
        zweekbtn->setChecked(false);
#endif
        zplubtn->setChecked(false);
        ztimebtn->setChecked(false);
        zclerkbtn->setChecked(false);
#ifdef WEEK_REPORT
        zclerkweekbtn->setChecked(false);
#endif

        on_DAILYBTN_clicked();
    }
    else
    {
        qDebug("--->zdaily OFF");
    }
}

#ifdef WEEK_REPORT
void reportDialog::zweekcheckedChanged(bool btnchecked)
{
    if(btnchecked)
    {
        qDebug("--->zweek ON");
        zbtnnum = 2;
        DataReportType = WEEKREPORT;
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
#endif

void reportDialog::zplucheckedChanged(bool btnchecked)
{
    if(btnchecked)
    {
        qDebug("--->zplu ON");
        DataReportType = PLUDAILY;
        zbtnnum = 3;
        zdailybtn->setChecked(false);
#ifdef WEEK_REPORT
        zweekbtn->setChecked(false);
#endif
        ztimebtn->setChecked(false);
        zclerkbtn->setChecked(false);
#ifdef WEEK_REPORT
        zclerkweekbtn->setChecked(false);
#endif

        on_PLUBTN_clicked();
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
        DataReportType = ZONEREPORT;
        zbtnnum = 4;
        zdailybtn->setChecked(false);
#ifdef WEEK_REPORT
        zweekbtn->setChecked(false);
#endif
        zplubtn->setChecked(false);
        zclerkbtn->setChecked(false);
#ifdef WEEK_REPORT
        zclerkweekbtn->setChecked(false);
#endif

        on_TIMEBTN_clicked();
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
        DataReportType = CLERKDAILY;
        zbtnnum = 5;
        zdailybtn->setChecked(false);
#ifdef WEEK_REPORT
        zweekbtn->setChecked(false);
#endif
        zplubtn->setChecked(false);
        ztimebtn->setChecked(false);
#ifdef WEEK_REPORT
        zclerkweekbtn->setChecked(false);
#endif

        on_CLERKBTN_clicked();
    }
    else
    {
        qDebug("--->zclerk OFF");
    }
}

#ifdef WEEK_REPORT
void reportDialog::zclerkweekcheckedChanged(bool btnchecked)
{
    if(btnchecked)
    {
        qDebug("--->zclerkweek ON");
        DataReportType = CLERKWEEK;
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
#endif

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
            timer->start( 1000 );  //1000ms 表示1???
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

void reportDialog::setiplist(QString IP, QString SHOPNAME, bool checked)
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

    ui->tableWidget->setItem(rows,2,new QTableWidgetItem(IP));
    ui->tableWidget->item(rows, 2)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

#if 1
    ui->tableWidget->setItem(rows,1,new QTableWidgetItem(SHOPNAME));
    ui->tableWidget->item(rows, 1)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
#endif

    if(checked)
    {
        //ui->tableWidget->setCurrentCell(rows, QItemSelectionModel::Select);
        /*
         *ui->tableWidget->item(rows, 2)->setSelected(true);
         */
        ui->tableWidget->selectRow(rows);
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
    emit unconnecthost();

    recvflag = true;//jdb2018-06-20 ��?ӷ?????ǰ?????ձ?־??λ

    if(udflag == PRINT_ECR)
    {
        return;
    }

    ui->tableWidget->clearSelection();

    qDebug() << "--->IpIndex = " << IpIndex << "IpIndexMax = "  << IpIndexMax;

    for(;IpIndex < IpIndexMax; IpIndex++)
    {
        if(ui->tableWidget->item(IpIndex, 0)->checkState() == Qt::Checked)
        {
            /*
             *ui->tableWidget->item(IpIndex, 2)->setSelected(true);
             */
            ui->tableWidget->selectRow(IpIndex);
            IpStr = ui->tableWidget->item(IpIndex,2)->text();//取出字符???
            ShopName = ui->tableWidget->item(IpIndex, 1)->text(); //jdb1018-07-11 ??ȡ??????
            ui->info->setText(QString("start connection to %1").arg(IpStr));
            StripToZno(IpStr);
            QCoreApplication::processEvents();//避免界面冻结
            qDebug() << "--->set new ip";
            emit setserverip(IpStr);
            break;
        }
    }

    MyDb->SetDataTime(QDateTime::currentDateTime());

    if(IpIndex < IpIndexMax)
    {
        udflag = UPDATE_DATA;

        itemindex = 0;

        sendbuf[0][0] = 'P';
        sendbuf[0][1] = 2;
        *((unsigned short *)(sendbuf[0] + 2)) = 100;
        qDebug() << "--->connect new ip";
        emit connecthost();
    }
    else
    {
        ui->tableWidget->setEnabled(true);
        ui->DOWNLOADDATA->setEnabled(true);
        ui->xreport->setEnabled(true);
        ui->zreport->setEnabled(true);
        if(XZModle == 0x01)
        {
            ui->DAILYBTN->setEnabled(true);
            ui->PLUBTN->setEnabled(true);
            ui->TIMEBTN->setEnabled(true);
            ui->CLERKBTN->setEnabled(true);
        }
        if(XZModle == 0x02)
        {
            zdailybtn->setEnabled(true);
            zplubtn->setEnabled(true);
            ztimebtn->setEnabled(true);
            zclerkbtn->setEnabled(true);
        }
    }
}

void reportDialog::on_DOWNLOADDATA_clicked()
{
    IpIndexMax = ui->tableWidget->rowCount();
    IpIndex = 0;

    udflag = 0x0;

    if(XZModle == 0x02)
    {
        switch(zbtnnum)
        {
            case 1: //dailyreport
                if(zdailybtn->getChecked())
                    break;
                else
                    return;
#ifdef WEEK_REPORT
            case 2: //weekreport
                if(zweekbtn->getChecked())
                    break;
                else
                    return;
#endif
            case 3: //pludaily
                if(zplubtn->getChecked())
                    break;
                else
                    return;
            case 4: //time
                if(ztimebtn->getChecked())
                    break;
                else
                    return;
            case 5: //clerk
                if(zclerkbtn->getChecked())
                    break;
                else
                    return;
            default:
                break;
        }
    }

    ui->tableWidget->setEnabled(false);
    ui->DOWNLOADDATA->setEnabled(false);
    ui->xreport->setEnabled(false);
    ui->zreport->setEnabled(false);
    if(XZModle == 0x01)
    {
        ui->DAILYBTN->setEnabled(false);
        ui->PLUBTN->setEnabled(false);
        ui->TIMEBTN->setEnabled(false);
        ui->CLERKBTN->setEnabled(false);
    }
    else if(XZModle == 0x02)
    {
        zdailybtn->setEnabled(false);
        zplubtn->setEnabled(false);
        ztimebtn->setEnabled(false);
        zclerkbtn->setEnabled(false);
    }

    tcpconnectcash();
}

void reportDialog::Print_Z(void)
{
    switch(zbtnnum)
    {
        case 1: //dailyreport

            ZREPORT_PRINT(DAILYREPORT);
            on_DAILYBTN_clicked();

            //zweekbtn->setChecked(true);
            break;
#ifdef WEEK_REPORT
        case 2: //weekreport
            on_PERIODREPORT_clicked();
            //zplubtn->setChecked(true);
            break;
#endif
        case 3: //pludaily

            ZREPORT_PRINT(PLUDAILY);
            on_PLUBTN_clicked();
            //ztimebtn->setChecked(true);
            break;
        case 4: //time

            ZREPORT_PRINT(ZONEREPORT);
            on_TIMEBTN_clicked();
            break;
        case 5: //clerk
            ZREPORT_PRINT(CLERKDAILY);
            on_CLERKBTN_clicked();
            break;
        default:
            break;
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
            //ui->cleardbreport->setEnabled(true); //jdb2018-07-12 ȡ???????ݿ⹦??
            emit unconnecthost();
#else
            qDebug() << "--->start connet next";
            //ui->cleardbreport->setEnabled(true); //jdb2018-07-12 ȡ???????ݿ⹦??
            //emit unconnecthost();
            if(XZModle == 0x01)
            {
                IpIndex++;
            }

            if(XZModle == 0x02) //为Z报表，下载完后显示对应的报表
            {
#if 0
                switch(zbtnnum)
                {
                    case 1: //dailyreport

                        ZREPORT_PRINT(DAILYREPORT);
                        on_DAILYBTN_clicked();

                        //zweekbtn->setChecked(true);
                        break;
#ifdef WEEK_REPORT
                    case 2: //weekreport
                        on_PERIODREPORT_clicked();
                        //zplubtn->setChecked(true);
                        break;
#endif
                    case 3: //pludaily

                        ZREPORT_PRINT(PLUDAILY);
                        on_PLUBTN_clicked();
                        //ztimebtn->setChecked(true);
                        break;
                    case 4: //time

                        ZREPORT_PRINT(ZONEREPORT);
                        on_TIMEBTN_clicked();
                        break;
                    case 5: //clerk
                        ZREPORT_PRINT(CLERKDAILY);
                        on_CLERKBTN_clicked();
                        break;
                    default:
                        break;
                }
#else
                Print_Z();
#endif
            }
#if 0
            if(XZModle == 0x02 && zbtnnum < 4)
            {
                on_DOWNLOADDATA_clicked();
            }
            else
#endif
            {
                if(XZModle == 0x01)
                {
                    tcpconnectcash();
                }
                //tcpconnectcash();
            }
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
        //ui->cleardbreport->setEnabled(true); //jdb2018-07-12 ȡ???????ݿ⹦??
        ui->info->setText(QString("can not connection to %1").arg(IpStr));
        QCoreApplication::processEvents();//避免界面冻结
        IpIndex++;
        tcpconnectcash();
    }

    if(tcpstat == TCPSENDERR)
    {
        //ui->cleardbreport->setEnabled(true); //jdb2018-07-12 ȡ???????ݿ⹦??
        ui->info->setText(QString("send data to %1 time out.").arg(IpStr));
        IpIndex++;
        tcpconnectcash();
    }

    if(tcpstat == TCPRCVERR)
    {
        //ui->cleardbreport->setEnabled(true); //jdb2018-07-12 ȡ???????ݿ⹦??
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
        if(udflag == UPDATE_DATA) //先获取信???
        {
            //
        }
        else if(udflag == PRINT_ECR)
        {

            //控制打印
        }
        else
        {
            if(recvflag == false)
            {
                //jdb2018-06-20 ????û?н????꣬????????
            }
            else
            {
                itemindex++;
                ui->progressBar->setValue(itemindex);
                QCoreApplication::processEvents();//避免界面冻结

                if(itemindex == senditemmax)
                {
                    //emit unconnecthost();
                    //ui->cleardbreport->setEnabled(true); //jdb2018-07-12 ȡ???????ݿ⹦??
                }
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
    int datalen;

    if(strlen(recvbuf) == 0)
    {
        return;
    }

    if((recvbuf[0 + 2] & 0xff) == 0x5A && (recvbuf[2 + 2] & 0xff) == DOWNLOAD_DATA && (recvbuf[3 + 2] & 0xff) == PLUREPORT)
    {//jdb2018-06-20 plu???????ݱ???
        if((recvbuf[4 + 2] & 0xff) != 'O'  && (recvbuf[5 + 2] & 0xff) != 'K')
        {
            if(recvflag)
            {
                itemindex--;
            }

            recvflag = false;
        }
        else if((recvbuf[4 + 2] & 0xff) == 'O'  && (recvbuf[5 + 2] & 0xff) == 'K')
        {
            itemindex++;

            recvflag = true;

            memset(recvbuf, 0, sizeof(recvbuf));
            if(XZModle == 0x01)//jdb2018-06-20 x????ֻ????һ??????
            {
                IpIndex++;
                tcpconnectcash();
            }
            else
            {
                Print_Z();
            }
            return;

#if 0
            datalen = sendbuf[itemindex][1] + 2;
            memset(recvbuf, 0, sizeof(recvbuf));
            emit senddata(sendbuf[itemindex], datalen);
            return;
#endif
        }
    }

    if(sizelen == 6 && XZModle == 0x02 && recvbuf[0 + 2] == 'R' && recvbuf[4 + 2] == 'O' && recvbuf[5 + 2] == 'K') //??ӡOK
    {
        udflag = UPDATE_DATA;
        qDebug() << "z print ok";
        memset(recvbuf, 0, sizeof(recvbuf));
#if 0
        IpIndex++;
        tcpconnectcash();
#else
        Delay_MSec(20000);

        switch(zbtnnum)
        {
            case 1: //dailyreport
#ifdef WEEK_REPORT
                zweekbtn->setChecked(true);
#else
                //zplubtn->setChecked(true);
                ztimebtn->setChecked(true);
#endif
                break;
#ifdef WEEK_REPORT
            case 2: //weekreport
                zplubtn->setChecked(true);
                break;
#endif
            case 4: //time
                zclerkbtn->setChecked(true);
                break;
            case 5: //clerk
                //zdailybtn->setChecked(true);
                zplubtn->setChecked(true);
                break;
            case 3: //pludaily
                //ztimebtn->setChecked(true);
                zdailybtn->setChecked(true);
                //break;
            default:
                //emit unconnecthost();

                Delay_MSec(1000);
                IpIndex++;
                tcpconnectcash();
                return;
        }

        itemindex = 0;

        sendbuf[0][0] = 'P';
        sendbuf[0][1] = 2;
        *((unsigned short *)(sendbuf[0] + 2)) = 100;

        datalen = sendbuf[itemindex][1] + 2;
        emit senddata(sendbuf[itemindex], datalen);
        //emit connecthost();
#endif
        return;
    }

    if(sizelen <= 4)
    {
        memset(recvbuf, 0, sizeof(recvbuf));
        if(itemindex == senditemmax)
        {
            if(XZModle == 0x01)
            {
                IpIndex++;
            }

            if(XZModle == 0x02) //为Z报表，下载完后显示对应的报表
            {
#if 0
                switch(zbtnnum)
                {
                    case 1: //dailyreport

                        ZREPORT_PRINT(DAILYREPORT);
                        on_DAILYBTN_clicked();
                        //zweekbtn->setChecked(true);
                        break;
#ifdef WEEK_REPORT
                    case 2: //weekreport
                        on_PERIODREPORT_clicked();
                        //zplubtn->setChecked(true);
                        break;
#endif
                    case 3: //pludaily

                        ZREPORT_PRINT(PLUDAILY);
                        on_PLUBTN_clicked();
                        //ztimebtn->setChecked(true);
                        break;
                    case 4: //time

                        ZREPORT_PRINT(ZONEREPORT);
                        on_TIMEBTN_clicked();
                        break;
                    case 5: //clerk
                        ZREPORT_PRINT(CLERKDAILY);
                        on_CLERKBTN_clicked();
                        break;
                    default:
                        break;
                }
#else
                Print_Z();
#endif
            }
#if 0
            if(XZModle == 0x02 && zbtnnum < 4)
            {
                on_DOWNLOADDATA_clicked();
            }
            else
#endif
            {
                if(XZModle == 0x01)
                {
                    tcpconnectcash();
                }
                //tcpconnectcash();
            }
        }
        return;
    }

    if(udflag == PRINT_ECR)
    {
        //控制打印
        //emit unconnecthost();
        memset(recvbuf, 0, sizeof(recvbuf));
        return;
    }

    if(udflag == UPDATE_DATA)
    {
#if 0
        if(XZModle == 0x01)
#endif
        {
            cashid = recvbuf[7];
            udflag = DOWNLOAD_DATA; //开始下载有效数???

            downloaddata(1);
        }

        memset(recvbuf, 0, sizeof(recvbuf));
        return;
    }

    MyDb->setzno(ZNo);
    MyDb->setcashid(cashid);
    MyDb->setcaship(IpStr);
    MyDb->setcashname(ShopName); //jdb2018-07-12

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

    memset(recvbuf, 0, sizeof(recvbuf));
}

int reportDialog::downloaddata(unsigned char datatype)
{
    int count;

    itemindex = 0;
    senditemmax = 1;

    ui->reportedit->clear();

    datatype = GRANDTOTALREPORT | DEPARTMENTREPORT | TENDERREPORT | DRAWERREPORT |
        CORRECTREPORT | DISCOUNTREPORT | TAXREPORT | PLUREPORT;

    if((datatype & GRANDTOTALREPORT) > 0){
        sendbuf[itemindex][0] = 0x5A;
        sendbuf[itemindex][1] = 0x02;
        sendbuf[itemindex][2] = DOWNLOAD_DATA;
        sendbuf[itemindex][3] = GRANDTOTALREPORT;
        itemindex++;
        senditemmax++;
    }

    if((datatype & DEPARTMENTREPORT) > 0){
        for(count = 1; count <= 60; count++)
        {
            memset(sendbuf[itemindex], 0, 32);
            sendbuf[itemindex][0] = 0x5A;
            sendbuf[itemindex][1] = 0x03;
            sendbuf[itemindex][2] = DOWNLOAD_DATA;
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
            sendbuf[itemindex][2] = DOWNLOAD_DATA;
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
            sendbuf[itemindex][2] = DOWNLOAD_DATA;
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
            sendbuf[itemindex][2] = DOWNLOAD_DATA;
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
            sendbuf[itemindex][2] = DOWNLOAD_DATA;
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
            sendbuf[itemindex][2] = DOWNLOAD_DATA;
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
        sendbuf[itemindex][2] = DOWNLOAD_DATA;
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

        //ui->cleardbreport->setEnabled(false); //jdb2018-07-12 ȡ???????ݿ⹦??

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

#if 0
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
#else

void reportDialog::StrAlignment(char *buf, int buflen, char *data, int datalen, int flag)
{
    int spacelen;

    if(flag == 2) //?м?????
    {
        if(datalen < buflen)
        {
            spacelen = (buflen - datalen) / 2;
            memcpy(buf + spacelen, data, datalen);
        }
        else
        {
            memcpy(buf, data, buflen);
        }
    }
}

void reportDialog::NStrFormat(char *strs, char *str1, char *str2, char *str3, char *str4, char *str5, int len)
{
    char ch[len];
    int size1 = 0, size2 = 0, size3 = 0, size4 = 0, size5 = 0;
    int strcount = 0;
    int seclen;

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

    seclen = len / strcount;

    memset(ch, ' ', len);

    strcount = 0;
    if(size1 > 0)
    {
        StrAlignment(ch + strcount, seclen, str1, size1, 2);
        strcount += seclen;
    }
    if(size2 > 0)
    {
        StrAlignment(ch + strcount, seclen, str2, size2, 2);
        strcount += seclen;
    }
    if(size3 > 0)
    {
        StrAlignment(ch + strcount, seclen, str3, size3, 2);
        strcount += seclen;
    }
    if(size4 > 0)
    {
        StrAlignment(ch + strcount, seclen, str4, size4, 2);
        strcount += seclen;
    }
    if(size5 > 0)
    {
        StrAlignment(ch + strcount, seclen, str5, size5, 2);
        strcount += seclen;
    }
    memcpy(strs, ch, len);
}
#endif

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
        //不显???
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
                    strcpy(str1, OLDGRANDTOTAL);
                    memset(str2, 0, sizeof(str2));
                    strcpy(str2, TXTITEM.toLocal8Bit().data());
                    memset(str, 0, TXTWIDTH);
                    NStrFormat(str, str1, str2, NULL, NULL, NULL, TXTWIDTH);
                    memcpy(txtstr + strlen(txtstr), str, TXTWIDTH + 1);

                    TXTITEM = reportModel->item(i, 1)->text();
                    memset(str1, 0, sizeof(str1));
                    strcpy(str1, NEWGRANDTOTAL);
                    memset(str2, 0, sizeof(str2));
					totalaccum = TXTITEM;
                    strcpy(str2, TXTITEM.toLocal8Bit().data());
                    memset(str, 0, TXTWIDTH);
                    NStrFormat(str, str1, str2, NULL, NULL, NULL, TXTWIDTH);
                    memcpy(txtstr + strlen(txtstr), str, TXTWIDTH + 1);

                    TXTITEM = reportModel->item(i, 2)->text();
                    memset(str1, 0, sizeof(str1));
                    strcpy(str1, TOTALGROSSSALES);
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
                    strcpy(str1, TOTALGROSSSALES);
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
                        strcpy(str, RECGRANDTOTAL);
                        StrFormat(str, TXTWIDTH, 5);
                        memcpy(txtstr + strlen(txtstr), str, TXTWIDTH + 1);

                        memset(str, 0, TXTWIDTH);
                        ChToStr(str, '*', TXTWIDTH);
                        memcpy(txtstr + strlen(txtstr), str, TXTWIDTH + 1);

                        memset(str1, 0, sizeof(str1));
                        strcpy(str1, RECAMOUNT);

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
                    strcpy(str1, RECAMOUNT);
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
        strcpy(str1, RECNAME);
        memset(str2, 0, sizeof(str2));
        strcpy(str2, RECCODE);
        memset(str3, 0, sizeof(str3));
        strcpy(str3, RECQUANTITY);
        memset(str4, 0, sizeof(str4));
        strcpy(str4, RECAMOUNT);
        memset(str, 0, TXTWIDTH);
        NStrFormat(str, str1, str2, str3, str4, NULL, TXTWIDTH);
        memcpy(txtstr + strlen(txtstr), str, TXTWIDTH + 1);

        memset(str, 0, TXTWIDTH);
        ChToStr(str, '*', TXTWIDTH);
        memcpy(txtstr + strlen(txtstr), str, TXTWIDTH + 1);

        qDebug() << "--->rows = " << rows;

        for(int i = 0; i < rows; i++)
        {
            TXTITEM = reportModel->item(i, 0)->text();
            memset(str1, 0, sizeof(str1));
            strcpy(str1, TXTITEM.toLocal8Bit().data());

            TXTITEM = reportModel->item(i, 1)->text();
            memset(str2, 0, sizeof(str2));
            strcpy(str2, TXTITEM.toLocal8Bit().data());

            TXTITEM = reportModel->item(i, 3)->text();
            memset(str3, 0, sizeof(str3));
            strcpy(str3, TXTITEM.toLocal8Bit().data());

            TXTITEM = reportModel->item(i, 4)->text();
            memset(str4, 0, sizeof(str4));
            strcpy(str4, TXTITEM.toLocal8Bit().data());

            memset(str, 0, TXTWIDTH);
            NStrFormat(str, str1, str2, str3, str4, NULL, TXTWIDTH);
            memcpy(txtstr + strlen(txtstr), str, TXTWIDTH + 1);
        }
    }
    else if(reporttype & DEPARTMENTREPORT)
    {
        memset(str1, 0, sizeof(str1));
        strcpy(str1, RECDEPARTMENT);
        memset(str2, 0, sizeof(str2));
        strcpy(str2, RECQUANTITY);
        memset(str3, 0, sizeof(str3));
        strcpy(str3, RECAMOUNT);
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
            strcpy(str1, TOTALTRADE);
            memset(str2, 0, sizeof(str2));
            strcpy(str2, TXTITEM.toLocal8Bit().data());
            memset(str, 0, TXTWIDTH);
            NStrFormat(str, str1, str2, NULL, NULL, NULL, TXTWIDTH);
            memcpy(txtstr + strlen(txtstr), str, TXTWIDTH + 1);

            TXTITEM = reportModel->item(i, 3)->text();
            memset(str1, 0, sizeof(str1));
            strcpy(str1, RECAMOUNT);
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
            strcpy(str1, RECAMOUNT);
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
            strcpy(str1, RECQUANTITY);
            memset(str2, 0, sizeof(str2));
            str2[0] = '-';
            strcpy(str2 + 1, TXTITEM.toLocal8Bit().data());
            memset(str, 0, TXTWIDTH);
            NStrFormat(str, str1, str2, NULL, NULL, NULL, TXTWIDTH);
            memcpy(txtstr + strlen(txtstr), str, TXTWIDTH + 1);

            TXTITEM = reportModel->item(i, 3)->text();
            memset(str1, 0, sizeof(str1));
            strcpy(str1, RECAMOUNT);
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
            if(strstr(str, RECEXEMPT))
            {
                //不显示名???
            }
            else
            {
                memcpy(txtstr + strlen(txtstr), str, TXTWIDTH + 1);
            }

            if(strstr(str, ZERO_VAT))
            {
                memset(str1, 0, sizeof(str1));
                strcpy(str1, ZEORRATEDSALES);

                float tmpdata = reportModel->item(i, 6)->text().toDouble() - reportModel->item(i, 3)->text().toDouble();
                memset(str2, 0, sizeof(str2));
                sprintf(str2, "%.02f", tmpdata);

                memset(str, 0, TXTWIDTH);
                NStrFormat(str, str1, str2, NULL, NULL, NULL, TXTWIDTH);
                memcpy(txtstr + strlen(txtstr), str, TXTWIDTH + 1);
            }
            else if(strstr(str, RECEXEMPT))
            {
                memset(str1, 0, sizeof(str1));
                strcpy(str1, VATEXEMPTSALES);

                float tmpdata = reportModel->item(i, 6)->text().toDouble() - reportModel->item(i, 3)->text().toDouble();
                memset(str2, 0, sizeof(str2));
                sprintf(str2, "%.02f", tmpdata);

                memset(str, 0, TXTWIDTH);
                NStrFormat(str, str1, str2, NULL, NULL, NULL, TXTWIDTH);
                memcpy(txtstr + strlen(txtstr), str, TXTWIDTH + 1);

                memset(str1, 0, sizeof(str1));
                strcpy(str1, VATEXEMPTAMOUNT);

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
                strcpy(str1, GROSSSALES);

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
    char str[TXTWIDTH + 1] = {0};
    str[TXTWIDTH] = '\n';

    QStandardItemModel *reportModel = new QStandardItemModel(this);
    QStringList titles;
    if(Idx & PLUDAILY)
    {
        titles << "Name"<< "Code" << "Cc" << "Qty" << "Amt" << "Ret" << "Disc" << "Cost";
    }
    else if((Type & GRANDTOTALREPORT) && (Idx != ZONEREPORT && Idx != CLERKDAILY && Idx != CLERKWEEK))
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

#if 0
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
#endif

void reportDialog::on_cleardbreport_clicked()
{
    ui->DOWNLOADDATA->setEnabled(false);
    ui->DOWNLOADDATA->setDisabled(true);
    qDebug() << "cleardbreport ip = " << QString("%1.%2.%3.%4").arg((ZNo >> 24) & 0xff).arg((ZNo >> 16) & 0xff)
        .arg((ZNo >> 8) & 0xff).arg(ZNo & 0xff);
    MyDb->setzno(ZNo);
    MyDb->cleartable();
    ui->DOWNLOADDATA->setDisabled(false);
    ui->DOWNLOADDATA->setEnabled(true);
}

void reportDialog::ZREPORT_PRINT(char type)
{
    int datalen;
    udflag = PRINT_ECR;

    itemindex = 0;
    qDebug("--->type = %02x", type);

    sendbuf[0][0] = 'R';
    sendbuf[0][1] = 2;
    switch (type & 0xff)
    {
        case DAILYREPORT:
            sendbuf[0][2] = 0x01;
            break;
        case PLUDAILY:
            sendbuf[0][2] = 0x02;
            break;
        case ZONEREPORT:
            sendbuf[0][2] = 0x03;
            break;
        case CLERKDAILY:
            //sendbuf[0][2] = 0x04;
            sendbuf[0][2] = 0x05;//jdb2018-07-31 ER520D???????????????????????????????
            break;
        default:
            return;
    }
    sendbuf[0][3] = 0x00;

    datalen = sendbuf[itemindex][1] + 2;
    emit senddata(sendbuf[itemindex], datalen);
    //emit connecthost();
}

void reportDialog::on_TIMEBTN_clicked()
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
    MyDb->clearmaxdatatime();//jdb2018-07-31 ???????????
    creatreport(QString(GRANDTOTAL), ZONEREPORT, reportname[0], GRANDTOTALREPORT);
#endif

    ui->reportedit->append(QString(QLatin1String(reporttxt)));

#if 0
    if(XZModle == 0x02)
    {
        udflag = PRINT_ECR;

        itemindex = 0;

        sendbuf[0][0] = 'R';
        sendbuf[0][1] = 2;
        sendbuf[0][2] = 0x05;
        sendbuf[0][3] = 0x00;
        emit connecthost();
    }
#endif
}

void reportDialog::on_PLUBTN_clicked()
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
    MyDb->clearmaxdatatime();//jdb2018-07-31 ???????????
    creatreport(QString(PLU), PLUDAILY, reportname[7], PLUREPORT);
#endif

    ui->reportedit->append(QString(QLatin1String(reporttxt)));

#if 0
    if(XZModle == 0x02)
    {
        udflag = PRINT_ECR;

        itemindex = 0;

        sendbuf[0][0] = 'R';
        sendbuf[0][1] = 2;
        sendbuf[0][2] = 0x03;
        sendbuf[0][3] = 0x00;
        emit connecthost();
    }
#endif
}

void reportDialog::on_DAILYBTN_clicked()
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

    MyDb->clearmaxdatatime();//jdb2018-07-31 ???????????
    creatreport(QString(GRANDTOTAL), DAILYREPORT, reportname[0], GRANDTOTALREPORT);
    creatreport(QString(DEPARTMENT), DAILYREPORT, reportname[1], DEPARTMENTREPORT);
    creatreport(QString(TENDER), DAILYREPORT, reportname[2], TENDERREPORT);
    creatreport(QString(DRAWER), DAILYREPORT, reportname[3], DRAWERREPORT);
    creatreport(QString(CORRECT), DAILYREPORT, reportname[4], CORRECTREPORT);
    creatreport(QString(DISCOUNT), DAILYREPORT, reportname[5], DISCOUNTREPORT);
    creatreport(QString(TAX), DAILYREPORT, reportname[6], TAXREPORT);

	//jdb2018-07-31 日报表增加一项
	
	char str1[TXTWIDTH + 1] = {0};
	char str2[TXTWIDTH + 1] = {0};
	memset(str1, 0, sizeof(str1));
    strcpy(str1, TOTALACCUMULATEDSALES);
    memset(str2, 0, sizeof(str2));
    strcpy(str2, totalaccum.toLocal8Bit().data());
	totalaccum.clear();
    memset(str, 0, TXTWIDTH);
    NStrFormat(str, str1, str2, NULL, NULL, NULL, TXTWIDTH);
    memcpy(reporttxt + strlen(reporttxt), str, TXTWIDTH + 1);    
	memset(str, 0, TXTWIDTH);
    ChToStr(str, '-', TXTWIDTH);
    memcpy(reporttxt + strlen(reporttxt), str, TXTWIDTH + 1);

    ui->reportedit->append(QString(QLatin1String(reporttxt)));

#if 0
    if(XZModle == 0x02)
    {
        udflag = PRINT_ECR;

        itemindex = 0;

        sendbuf[0][0] = 'R';
        sendbuf[0][1] = 2;
        sendbuf[0][2] = 0x01;
        sendbuf[0][3] = 0x00;
        emit connecthost();
    }
#endif
}

#ifdef WEEK_REPORT
void reportDialog::on_PERIODREPORT_clicked()
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

    if(XZModle == 0x02)
    {
        udflag = PRINT_ECR;

        itemindex = 0;

        sendbuf[0][0] = 'R';
        sendbuf[0][1] = 2;
        sendbuf[0][2] = 0x02;
        sendbuf[0][3] = 0x00;
        emit connecthost();
    }
}
#endif

void reportDialog::on_CLERKBTN_clicked()
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

    for(int clerknum = 1; clerknum <= CLERKNUM; clerknum++)
    {
        memset(str, 0, TXTWIDTH);
        sprintf(str, "CLERK %d", clerknum);
        StrFormat(str, TXTWIDTH, 0);
        memcpy(reporttxt + strlen(reporttxt), str, TXTWIDTH + 1);

        memset(str, 0, TXTWIDTH);
        ChToStr(str, '=', TXTWIDTH);
        memcpy(reporttxt + strlen(reporttxt), str, TXTWIDTH + 1);

        MyDb->setclerknum(clerknum);

        MyDb->clearmaxdatatime();//jdb2018-07-31 ???????????
        creatreport(QString(GRANDTOTAL), CLERKDAILY, reportname[0], GRANDTOTALREPORT);
        creatreport(QString(TENDER), CLERKDAILY, reportname[2], TENDERREPORT);
        creatreport(QString(DRAWER), CLERKDAILY, reportname[3], DRAWERREPORT);
        creatreport(QString(CORRECT), CLERKDAILY, reportname[4], CORRECTREPORT);
        creatreport(QString(DISCOUNT), CLERKDAILY, reportname[5], DISCOUNTREPORT);
    }

    ui->reportedit->append(QString(QLatin1String(reporttxt)));
}

#ifdef WEEK_REPORT
void reportDialog::on_CLERKPERIOD_clicked()
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
#endif

void reportDialog::on_xreport_clicked()
{
    XZModle = 0x01;
    MyDb->setxzflag(XZModle);
    ui->stackedWidget->setCurrentIndex(0);

    if(zdailybtn)
        delete zdailybtn;
#ifdef WEEK_REPORT
    if(zweekbtn)
        delete zweekbtn;
#endif
    if(zplubtn)
        delete zplubtn;
    if(ztimebtn)
        delete ztimebtn;
    if(zclerkbtn)
        delete zclerkbtn;
#ifdef WEEK_REPORT
    if(zclerkweekbtn)
        delete zclerkweekbtn;
#endif

    zdailybtn = NULL;
#ifdef WEEK_REPORT
    zweekbtn = NULL;
#endif
    zplubtn = NULL;
    ztimebtn = NULL;
    zclerkbtn = NULL;
#ifdef WEEK_REPORT
    zclerkweekbtn = NULL;
#endif
}

void reportDialog::on_zreport_clicked()
{
    XZModle = 0x02;
    MyDb->setxzflag(XZModle);
    ui->stackedWidget->setCurrentIndex(1);

    qDebug() << "zbtnnum = " << zbtnnum;

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
#ifdef WEEK_REPORT
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
#endif

    //plu
    if(zplubtn)
    {
        delete zplubtn;
    }

    zplubtn = new SwitchButton(ui->stackedWidget);
#ifdef WEEK_REPORT
    zplubtn->setGeometry(40, 90, 101, 23);
#else
    zplubtn->setGeometry(40, 50, 101, 23);
#endif
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
#ifdef WEEK_REPORT
    ztimebtn->setGeometry(40, 130, 101, 23);
#else
    ztimebtn->setGeometry(40, 90, 101, 23);
#endif
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
#ifdef WEEK_REPORT
    zclerkbtn->setGeometry(40, 170, 101, 23);
#else
    zclerkbtn->setGeometry(40, 130, 101, 23);
#endif
    zclerkbtn->setButtonStyle(zclerkbtn->ButtonStyle_Image);
    zclerkbtn->setImage(QString(":/images/icons/clerkreportoff.png"), QString(":/images/icons/clerkreporton.png"));
    connect(zclerkbtn, SIGNAL(checkedChanged(bool)), this, SLOT(zclerkcheckedChanged(bool)));

    zclerkbtn->show();

    //clerkweek
#ifdef WEEK_REPORT
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
#endif

    switch (zbtnnum) {
        case 1:
            zdailybtn->setChecked(true);
            break;
#ifdef WEEK_REPORT
        case 2:
            zweekbtn->setChecked(true);
            break;
#endif
        case 3:
            zplubtn->setChecked(true);
            break;
        case 4:
            ztimebtn->setChecked(true);
            break;
        case 5:
            zclerkbtn->setChecked(true);
            break;
#ifdef WEEK_REPORT
        case 6:
            zclerkweekbtn->setChecked(true);
            break;
#endif
        default:
            break;
    }
}

void reportDialog::on_tableWidget_clicked(const QModelIndex &index)
{
    bool focus = ui->tableWidget->isItemSelected(ui->tableWidget->currentItem()); // 判断是否选中一???
    if(focus)
    {
        int row1 = ui->tableWidget->currentItem()->row(); // 当前选中???
        IpStr = ui->tableWidget->item(row1,2)->text();//取出字符???
        StripToZno(IpStr);
        emit setserverip(IpStr);
        this->setWindowTitle(IpStr);
    }
}
