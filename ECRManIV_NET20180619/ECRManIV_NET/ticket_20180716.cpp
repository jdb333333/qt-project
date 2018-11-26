#include "ticket.h"
#include "ui_ticket.h"

#include "tcpclient.h"
#include "./clerk/clerk.h"
#include "./disc/disc.h"
#include "./tax/tax.h"
#include "./offer/offprice.h"
#include "./flowbill/flowbill.h"

#include <QMenu>
#include <QModelIndex>
#include <QDebug>

#include "mycheckboxheader.h"

ticket::ticket(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ticket)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::Dialog | windowType());

    this->setAttribute(Qt::WA_ShowModal, true);

    ui->header->setWordWrapMode(QTextOption::NoWrap);
    ui->trailer->setWordWrapMode(QTextOption::NoWrap);


    ui->tableWidget->setStyleSheet(getQssContent(0x02));

    myHeader = new MyCheckboxHeader(Qt::Horizontal, ui->tableWidget);
    ui->tableWidget->resizeColumnsToContents();
    ui->tableWidget->setHorizontalHeader(myHeader);
    ui->tableWidget->horizontalHeader()->setResizeMode(QHeaderView::Stretch);

    connect(myHeader, SIGNAL(signalStateTrange(int)), this, SLOT(slotsSelectAll(int)));

    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setColumnWidth(0, 80);
    ui->tableWidget->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    ui->tableWidget->horizontalHeader()->setResizeMode(0, QHeaderView::Fixed);
    ui->tableWidget->resizeColumnsToContents();

    ui->tableWidget->setAlternatingRowColors(true);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->tableWidget->horizontalHeader()->setResizeMode(1, QHeaderView::ResizeToContents);
    ui->tableWidget->horizontalHeader()->setResizeMode(2, QHeaderView::ResizeToContents);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<""<<"IP"<<"CASH");

    ui->clerkWidget->setStyleSheet(getQssContent(0x02));

    //创建菜单项
    pop_menu = new QMenu();

    ck = NULL;
    ds = NULL;
    tx = NULL;
    offer = NULL;
    ej = NULL;
}

ticket::~ticket()
{
    if(ck)
    {
        delete ck;
        ck = NULL;
    }

    if(ds)
    {
        delete ds;
        ds = NULL;
    }

    if(tx)
    {
        delete tx;
        tx = NULL;
    }

    if(offer)
    {
        delete offer;
        offer = NULL;
    }

    if(ej)
    {
        delete ej;
        ej = NULL;
    }

    delete pop_menu;
    delete myHeader;
    delete ui;
}

QString ticket::getQssContent(char type)
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

void ticket::settcpclient(tcpclient *fmtcpclient)
{
    formtcpclient = fmtcpclient;
    connect(formtcpclient, SIGNAL(tcpstate(int)), this, SLOT(tcpstate(int)));
}

void ticket::clerk_win(void)
{
    QTableWidgetItem *item;
    ui->clerkWidget->setColumnCount(4);
    ui->clerkWidget->setRowCount(5);

    win_type = CLERK_WIN;

    QStringList header;

    header << "Indx" << "Name" << "Options" << "Password";

    ui->clerkWidget->setHorizontalHeaderLabels(header);

    //设置表头字体加粗
    QFont font = ui->clerkWidget->horizontalHeader()->font();
    font.setBold(true);
    ui->clerkWidget->horizontalHeader()->setFont(font);

    ui->clerkWidget->horizontalHeader()->setStretchLastSection(true); //设置充满表宽度

    //ui->clerkWidget->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    //ui->clerkWidget->horizontalHeader()->setResizeMode(0, QHeaderView::Fixed);
    //ui->clerkWidget->resizeColumnsToContents();

    ui->clerkWidget->setAlternatingRowColors(true);
    //ui->clerkWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    //ui->clerkWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    qDebug() << "ui->clerkWidget->rowCount() = " << ui->clerkWidget->rowCount();

    for(int row = 0; row < ui->clerkWidget->rowCount(); row++)
    {
        for(int column = 0; column < ui->clerkWidget->columnCount(); column++)
        {
            if(column == 0) //indx
            {
                item = new QTableWidgetItem(QString("%1").arg(row + 1));
                item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
                item->setFlags(item->flags() & ~Qt::ItemIsEditable); //不可编辑
                ui->clerkWidget->setItem(row, column, item);
            }
            if(column == 1) //name
            {
                item = new QTableWidgetItem(QString("Clerk%1").arg(row + 1));
                item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
                ui->clerkWidget->setItem(row, column, item);
            }
            if(column == 2) //options
            {
                item = new QTableWidgetItem("");
                item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
                item->setFlags(item->flags() & ~Qt::ItemIsEditable); //不可编辑
                ui->clerkWidget->setItem(row, column, item);
            }
            if(column == 3)
            {
                item = new QTableWidgetItem("000000");
                item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
                ui->clerkWidget->setItem(row, column, item);
            }
        }
    }
}

void ticket::disc_win(void)
{
    QTableWidgetItem *item;

    ui->clerkWidget->setColumnCount(5);
    ui->clerkWidget->setRowCount(6);

    win_type = DISC_WIN;

    QStringList header;

    header << "Type" << "Name" << "Options" << "FixValue" << "MaxValue";

    ui->clerkWidget->setHorizontalHeaderLabels(header);

    //设置表头字体加粗
    QFont font = ui->clerkWidget->horizontalHeader()->font();
    font.setBold(true);
    ui->clerkWidget->horizontalHeader()->setFont(font);

    //ui->clerkWidget->horizontalHeader()->setStretchLastSection(true); //设置充满表宽度

    ui->clerkWidget->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    //ui->clerkWidget->horizontalHeader()->setResizeMode(0, QHeaderView::Fixed);
    ui->clerkWidget->resizeColumnsToContents();

    ui->clerkWidget->setAlternatingRowColors(true);

    for(int row = 0; row < ui->clerkWidget->rowCount(); row++)
    {
        for(int column = 0; column < ui->clerkWidget->columnCount(); column++)
        {
            if(column == 0) //type
            {
                if(row == 0) //+%
                {
                    item = new QTableWidgetItem(QString("+%"));
                }
                else if(row == 1)
                {
                    item = new QTableWidgetItem(QString("-%"));
                }
                else if(row == 2)
                {
                    item = new QTableWidgetItem(QString("+"));
                }
                else if(row == 3)
                {
                    item = new QTableWidgetItem(QString("-"));
                }
                else if(row == 4)
                {
                    item = new QTableWidgetItem(QString("SC -%"));
                }
                else if(row == 5)
                {
                    item = new QTableWidgetItem(QString("PWD -%"));
                }

                item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
                item->setFlags(item->flags() & ~Qt::ItemIsEditable); //不可编辑
                ui->clerkWidget->setItem(row, column, item);
            }
            if(column == 1) //name
            {
                if(row == 0) //+%
                {
                    item = new QTableWidgetItem(QString("+%"));
                }
                else if(row == 1)
                {
                    item = new QTableWidgetItem(QString("-%"));
                }
                else if(row == 2)
                {
                    item = new QTableWidgetItem(QString("+NET"));
                }
                else if(row == 3)
                {
                    item = new QTableWidgetItem(QString("-NET"));
                }
                else if(row == 4)
                {
                    item = new QTableWidgetItem(QString("SC DISCOUNT"));
                }
                else if(row == 5)
                {
                    item = new QTableWidgetItem(QString("PWD DISCOUNT"));
                }

                item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
                ui->clerkWidget->setItem(row, column, item);
            }
            if(column == 2) //options
            {
                item = new QTableWidgetItem("2");
                item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
                item->setFlags(item->flags() & ~Qt::ItemIsEditable); //不可编辑
                ui->clerkWidget->setItem(row, column, item);
            }
            if(column == 3) //FixValue
            {
                item = new QTableWidgetItem("");
                item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
                ui->clerkWidget->setItem(row, column, item);
            }
            if(column == 4) //MaxValue
            {
                if(row != 2 && row != 3)
                {
                    item = new QTableWidgetItem("99");
                }
                else
                {
                    item = new QTableWidgetItem("9999");
                }

                item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
                ui->clerkWidget->setItem(row, column, item);
            }
        }
    }
}

void ticket::tax_win(void)
{
    QTableWidgetItem *item;

    ui->clerkWidget->setColumnCount(4);
    ui->clerkWidget->setRowCount(6);

    win_type = TAX_WIN;

    QStringList header;

    header << "Index" << "Name" << "Rate" << "Options";

    ui->clerkWidget->setHorizontalHeaderLabels(header);

    //设置表头字体加粗
    QFont font = ui->clerkWidget->horizontalHeader()->font();
    font.setBold(true);
    ui->clerkWidget->horizontalHeader()->setFont(font);

    ui->clerkWidget->horizontalHeader()->setStretchLastSection(true); //设置充满表宽度

    ui->clerkWidget->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    //ui->clerkWidget->horizontalHeader()->setResizeMode(0, QHeaderView::Fixed);
    ui->clerkWidget->resizeColumnsToContents();

    ui->clerkWidget->setAlternatingRowColors(true);

    for(int row = 0; row < ui->clerkWidget->rowCount(); row++)
    {
        for(int column = 0; column < ui->clerkWidget->columnCount(); column++)
        {
            if(column == 0) //index
            {
                item = new QTableWidgetItem(QString("%1").arg(row + 1));
                item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
                item->setFlags(item->flags() & ~Qt::ItemIsEditable); //不可编辑
                ui->clerkWidget->setItem(row, column, item);
            }
            if(column == 1) //Name
            {
                if(row == 0)
                {
                    item = new QTableWidgetItem(QString("TAX_A"));
                }
                else if(row == 1)
                {
                    item = new QTableWidgetItem(QString("TAX_B"));
                }
                else if(row == 2)
                {
                    item = new QTableWidgetItem(QString("TAX_C"));
                }
                else if(row == 3)
                {
                    item = new QTableWidgetItem(QString("TAX_D"));
                }
                else if(row == 4)
                {
                    item = new QTableWidgetItem(QString("TAX_E"));
                }
                else if(row == 5)
                {
                    item = new QTableWidgetItem(QString("TAX_F"));
                }

                item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
                ui->clerkWidget->setItem(row, column, item);
            }
            if(column == 2) //Rate
            {
                item = new QTableWidgetItem("");
                item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
                ui->clerkWidget->setItem(row, column, item);
            }
            if(column == 3) //Options
            {
                item = new QTableWidgetItem("");
                item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
                item->setFlags(item->flags() & ~Qt::ItemIsEditable); //不可编辑
                ui->clerkWidget->setItem(row, column, item);
            }
        }
    }
}

void ticket::offer_win(void)
{
    QTableWidgetItem *item;

    ui->clerkWidget->setColumnCount(12);
    ui->clerkWidget->setRowCount(50);

    win_type = OFFER_WIN;

    QStringList header;

    header << "Indx" << "Name" << "Type" << "DateFrom" << "DateTo" << "TimeFrom" << "TimeTo"
           << "WeekDay" << "Discount" << "NumItems" << "PriceU" << "PriceP";

    ui->clerkWidget->setHorizontalHeaderLabels(header);

    //设置表头字体加粗
    QFont font = ui->clerkWidget->horizontalHeader()->font();
    font.setBold(true);
    ui->clerkWidget->horizontalHeader()->setFont(font);

    //ui->clerkWidget->horizontalHeader()->setStretchLastSection(true); //设置充满表宽度

    //ui->clerkWidget->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    //ui->clerkWidget->horizontalHeader()->setResizeMode(0, QHeaderView::Fixed);
    //ui->clerkWidget->horizontalHeader()->setResizeMode(0, QHeaderView::Stretch);
    //ui->clerkWidget->resizeColumnsToContents();

    ui->clerkWidget->setAlternatingRowColors(true);

    for(int row = 0; row < ui->clerkWidget->rowCount(); row++)
    {
        for(int column = 0; column < ui->clerkWidget->columnCount(); column++)
        {
            if(column == 0) //indx
            {
                item = new QTableWidgetItem(QString("%1").arg(row + 1));

                item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
                item->setFlags(item->flags() & ~Qt::ItemIsEditable); //不可编辑
                ui->clerkWidget->setItem(row, column, item);
            }
            if(column == 1) //name
            {
                item = new QTableWidgetItem(QString("OFFER%1").arg(row + 1));

                item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
                ui->clerkWidget->setItem(row, column, item);
            }
            if(column == 2) //type
            {
                item = new QTableWidgetItem("");
                item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
                item->setFlags(item->flags() & ~Qt::ItemIsEditable); //不可编辑
                ui->clerkWidget->setItem(row, column, item);
            }
            if(column == 3) //StartDate
            {
                item = new QTableWidgetItem("01-01");
                item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
                ui->clerkWidget->setItem(row, column, item);
            }
            if(column == 4) //EndDate
            {
                item = new QTableWidgetItem("01-01");
                item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
                ui->clerkWidget->setItem(row, column, item);
            }
            if(column == 5) //StartTime
            {
                item = new QTableWidgetItem("01:01");
                item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
                ui->clerkWidget->setItem(row, column, item);
            }
            if(column == 6) //endTime
            {
                item = new QTableWidgetItem("01:01");
                item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
                ui->clerkWidget->setItem(row, column, item);
            }
            if(column == 7) //week
            {
                item = new QTableWidgetItem("");
                item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
                item->setFlags(item->flags() & ~Qt::ItemIsEditable); //不可编辑
                ui->clerkWidget->setItem(row, column, item);
            }
            if(column == 8) //Disc
            {
                item = new QTableWidgetItem("");
                item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
                ui->clerkWidget->setItem(row, column, item);
            }
            if(column == 9) //PackQty
            {
                item = new QTableWidgetItem("");
                item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
                ui->clerkWidget->setItem(row, column, item);
            }
            if(column == 10) //UnitPrice
            {
                item = new QTableWidgetItem("");
                item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
                ui->clerkWidget->setItem(row, column, item);
            }
            if(column == 11) //FavPrice
            {
                item = new QTableWidgetItem("");
                item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
                ui->clerkWidget->setItem(row, column, item);
            }
        }
    }
}

void ticket::setformtype(char fmtype)
{
    formtype = fmtype;

    if(formtype == F_TICKET)
    {
        ui->stackedWidget->setCurrentIndex(0);
    }
    else if(formtype == F_CLERK)
    {
        ui->stackedWidget->setCurrentIndex(1);
        clerk_win();

        ck = new clerk;
    }
    else if(formtype == F_DISC)
    {
        ui->stackedWidget->setCurrentIndex(1);
        disc_win();

        ds = new disc;
    }
    else if(formtype == F_TAX)
    {
        ui->stackedWidget->setCurrentIndex(1);
        tax_win();

        tx = new tax;
    }
    else if(formtype == F_OFFER)
    {
        ui->stackedWidget->setCurrentIndex(1);
        offer_win();

        offer = new offprice;
    }
    else if(formtype == F_EJ)
    {
        ui->stackedWidget->setCurrentIndex(2);
        ui->datefrom->calendarWidget()->setLocale(QLocale(QLocale::English));
        ui->dateto->calendarWidget()->setLocale(QLocale(QLocale::English));

        ej = new flowbill;
        ui->update->setDisabled(true);
    }
}

void ticket::slotsSelectAll(int state)
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

void ticket::setiplist(QString IP, QString SHOPNAME, bool checked)
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

    ui->tableWidget->setItem(rows,2,new QTableWidgetItem(SHOPNAME));
    ui->tableWidget->item(rows, 2)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    if(checked)
    {
        ui->tableWidget->item(rows, 1)->setSelected(true);
    }
}

void ticket::tcpstate(int type)
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
        for(int count = 4; count < datalen; count++)
        {
            qDebug("[%d]%c", count, recvbuf[count]);
            //if(recvbuf[count] == 0 && (count + 1) % 43 == 0)
			if((count + 1 - 4) % 43 == 0)
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

    return 0;
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

void ticket::ticket_download(void)
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

void ticket::ticket_update(void)
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

void ticket::clerk_update(void)
{
    int ret, datalen;

    QString Name, Options, Passwd;

#if 1
    ret = formtcpclient->newConnect2();
    if(ret < 0) //connect failed
    {
        return;
    }
#endif

    itemindex = 0;
    senditemmax = ui->clerkWidget->rowCount();

    ui->progressBar->setRange(0,senditemmax);
    ui->progressBar->setValue(0);

    for(int row = 0; row < ui->clerkWidget->rowCount(); row++)
    {
        Name = ui->clerkWidget->item(row, 1)->text();
        Options = ui->clerkWidget->item(row, 2)->text();
        Passwd = ui->clerkWidget->item(row, 3)->text();

        qDebug() << "Name = " << Name << "Options = " << Options << "Passwd = " << Passwd;

        sendbuf[0] = cmdUPDATE;
        *((unsigned short *)(sendbuf + 2)) = CLERK + row + 1;

        datalen = ck->DataCreate(sendbuf + 4, Name, Options, Passwd);

        sendbuf[1] = 2 + datalen;

        datalen += 4;

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

#if 1
    formtcpclient->abortConnect();
#endif
}

void ticket::clerk_download(void)
{
    int ret, datalen;
    int column;
    QStringList strlist;

#if 1
    ret = formtcpclient->newConnect2();
    if(ret < 0) //connect failed
    {
        return;
    }
#endif

    itemindex = 0;
    senditemmax = ui->clerkWidget->rowCount();

    ui->progressBar->setRange(0,senditemmax);
    ui->progressBar->setValue(0);

    for(int row = 0; row < ui->clerkWidget->rowCount(); row++)
    {
        sendbuf[0] = cmdDOWNLOAD;
        sendbuf[1] = 2;
        *((unsigned short *)(sendbuf + 2)) = CLERK + row + 1;

        datalen = 4;

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

        strlist = ck->DataParse(recvbuf + 4);

        //qDebug() << "strlist = " << strlist;
        for(column = 1; column < ui->clerkWidget->columnCount(); column++)
        {
            ui->clerkWidget->item(row, column)->setText(strlist.at(column - 1));
        }

        itemindex++;
        ui->progressBar->setValue(itemindex);
        QCoreApplication::processEvents();//避免界面冻结
    }

#if 1
    formtcpclient->abortConnect();
#endif
}

void ticket::disc_update(void)
{
    int ret, datalen;

    QString Name, Options, FixValue, MaxValue;

#if 1
    ret = formtcpclient->newConnect2();
    if(ret < 0) //connect failed
    {
        return;
    }
#endif

    itemindex = 0;
    senditemmax = ui->clerkWidget->rowCount();

    ui->progressBar->setRange(0,senditemmax);
    ui->progressBar->setValue(0);

    for(int row = 0; row < ui->clerkWidget->rowCount(); row++)
    {
        Name = ui->clerkWidget->item(row, 1)->text();
        Options = ui->clerkWidget->item(row, 2)->text();
        FixValue = ui->clerkWidget->item(row, 3)->text();
        MaxValue = ui->clerkWidget->item(row, 4)->text();

        qDebug() << "Name = " << Name << "Options = " << Options << "FixValue = "
                 << FixValue << "MaxValue = " << MaxValue;

        sendbuf[0] = cmdUPDATE;
        if(row < 4)
        {
            *((unsigned short *)(sendbuf + 2)) = DISC + row + 1;
        }
        else{
            *((unsigned short *)(sendbuf + 2)) = DISC + row + 1 + 4;
        }

        datalen = ds->DataCreate(sendbuf + 4, Name, Options, FixValue, MaxValue, row + 1);

        sendbuf[1] = 2 + datalen;

        datalen += 4;

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

#if 1
    formtcpclient->abortConnect();
#endif
}

void ticket::disc_download(void)
{
    int ret, datalen;
    int column;
    QStringList strlist;

#if 1
    ret = formtcpclient->newConnect2();
    if(ret < 0) //connect failed
    {
        return;
    }
#endif

    itemindex = 0;
    senditemmax = ui->clerkWidget->rowCount();

    ui->progressBar->setRange(0,senditemmax);
    ui->progressBar->setValue(0);

    for(int row = 0; row < ui->clerkWidget->rowCount(); row++)
    {
        sendbuf[0] = cmdDOWNLOAD;
        sendbuf[1] = 2;
        if(row < 4)
        {
            *((unsigned short *)(sendbuf + 2)) = DISC + row + 1;
        }
        else //SC PWD
        {
            *((unsigned short *)(sendbuf + 2)) = DISC + 4 + row + 1;
        }

        datalen = 4;

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

        strlist = ds->DataParse(recvbuf + 4);

        //qDebug() << "strlist = " << strlist;
        for(column = 1; column < ui->clerkWidget->columnCount(); column++)
        {
            ui->clerkWidget->item(row, column)->setText(strlist.at(column - 1));
        }

        itemindex++;
        ui->progressBar->setValue(itemindex);
        QCoreApplication::processEvents();//避免界面冻结
    }

#if 1
    formtcpclient->abortConnect();
#endif
}

void ticket::tax_update(void)
{
    int ret, datalen;

    QString Name, Options, Rate;

#if 1
    ret = formtcpclient->newConnect2();
    if(ret < 0) //connect failed
    {
        return;
    }
#endif

    itemindex = 0;
    senditemmax = ui->clerkWidget->rowCount();

    ui->progressBar->setRange(0,senditemmax);
    ui->progressBar->setValue(0);

    for(int row = 0; row < ui->clerkWidget->rowCount(); row++)
    {
        Name = ui->clerkWidget->item(row, 1)->text();
        Rate = ui->clerkWidget->item(row, 2)->text();
        Options = ui->clerkWidget->item(row, 3)->text();

        qDebug() << "Name = " << Name << "Rate = " << Rate << "Options = " << Options;

        sendbuf[0] = cmdUPDATE;
        *((unsigned short *)(sendbuf + 2)) = TAX + row + 1;

        datalen = tx->DataCreate(sendbuf + 4, Name, Rate, Options);

        sendbuf[1] = 2 + datalen;

        datalen += 4;

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

#if 1
    formtcpclient->abortConnect();
#endif
}

void ticket::tax_download(void)
{
    int ret, datalen;
    int column;
    QStringList strlist;

#if 1
    ret = formtcpclient->newConnect2();
    if(ret < 0) //connect failed
    {
        return;
    }
#endif

    itemindex = 0;
    senditemmax = ui->clerkWidget->rowCount();

    ui->progressBar->setRange(0,senditemmax);
    ui->progressBar->setValue(0);

    for(int row = 0; row < ui->clerkWidget->rowCount(); row++)
    {
        sendbuf[0] = cmdDOWNLOAD;
        sendbuf[1] = 2;

        *((unsigned short *)(sendbuf + 2)) = TAX + row + 1;

        datalen = 4;

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

        strlist = tx->DataParse(recvbuf + 4);

        //qDebug() << "strlist = " << strlist;
        for(column = 1; column < ui->clerkWidget->columnCount(); column++)
        {
            ui->clerkWidget->item(row, column)->setText(strlist.at(column - 1));
        }

        itemindex++;
        ui->progressBar->setValue(itemindex);
        QCoreApplication::processEvents();//避免界面冻结
    }

#if 1
    formtcpclient->abortConnect();
#endif
}

void ticket::offer_update(void)
{
    int ret, datalen;

    QString Name, Type, DateFrom, DateTo, TimeFrom, TimeTo, WeekDay, Discount, NumItems, PriceU, PriceP;

#if 1
    ret = formtcpclient->newConnect2();
    if(ret < 0) //connect failed
    {
        return;
    }
#endif

    itemindex = 0;
    senditemmax = ui->clerkWidget->rowCount();

    ui->progressBar->setRange(0,senditemmax);
    ui->progressBar->setValue(0);

    for(int row = 0; row < ui->clerkWidget->rowCount(); row++)
    {
        Name = ui->clerkWidget->item(row, 1)->text();
        Type = ui->clerkWidget->item(row, 2)->text();
        DateFrom = ui->clerkWidget->item(row, 3)->text();
        DateTo = ui->clerkWidget->item(row, 4)->text();
        TimeFrom = ui->clerkWidget->item(row, 5)->text();
        TimeTo = ui->clerkWidget->item(row, 6)->text();
        WeekDay = ui->clerkWidget->item(row, 7)->text();
        Discount = ui->clerkWidget->item(row, 8)->text();
        NumItems = ui->clerkWidget->item(row, 9)->text();
        PriceU = ui->clerkWidget->item(row, 10)->text();
        PriceP = ui->clerkWidget->item(row, 11)->text();

        //qDebug() << "Name = " << Name << "Rate = " << Rate << "Options = " << Options;

        sendbuf[0] = cmdUPDATE;
        *((unsigned short *)(sendbuf + 2)) = OFFER + row + 1;

        QStringList Str;
        Str << Name << Type << DateFrom << DateTo << TimeFrom
            << TimeTo << WeekDay << Discount << NumItems << PriceU << PriceP;
        datalen = offer->DataCreate(sendbuf + 4, Str);

        sendbuf[1] = 2 + datalen;

        datalen += 4;

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

#if 1
    formtcpclient->abortConnect();
#endif
}

void ticket::offer_download(void)
{
    int ret, datalen;
    int column;
    QStringList strlist;

#if 1
    ret = formtcpclient->newConnect2();
    if(ret < 0) //connect failed
    {
        return;
    }
#endif

    itemindex = 0;
    senditemmax = ui->clerkWidget->rowCount();

    ui->progressBar->setRange(0,senditemmax);
    ui->progressBar->setValue(0);

    for(int row = 0; row < ui->clerkWidget->rowCount(); row++)
    {
        sendbuf[0] = cmdDOWNLOAD;
        sendbuf[1] = 2;

        *((unsigned short *)(sendbuf + 2)) = OFFER + row + 1;

        datalen = 4;

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


        strlist = offer->DataParse(recvbuf + 4);

#if 1
        //qDebug() << "strlist = " << strlist;
        for(column = 1; column < ui->clerkWidget->columnCount(); column++)
        {
            ui->clerkWidget->item(row, column)->setText(strlist.at(column - 1));
        }
#endif

        itemindex++;
        ui->progressBar->setValue(itemindex);
        QCoreApplication::processEvents();//避免界面冻结
    }

#if 1
    formtcpclient->abortConnect();
#endif
}

void ticket::ej_download(void)
{
    int ret, datalen;
    WORD size;

    qDebug() << "--->ej download";

    ret = formtcpclient->newConnect2();
    if(ret < 0) //connect failed
    {
        return;
    }

    sendbuf[0] = cmdFLOWDATA;
    sendbuf[1] = 2;
    *((WORD *)(sendbuf+2)) = 0;//发送功能码0,要收款机发送其编号数据

    datalen = 4;

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

    if(recvbuf[0] & 0xff == cmdANSWER)
    {
        qDebug() << "--->flowbill recv break!";
        formtcpclient->abortConnect();
        return;
    }

    size = *((WORD *)(recvbuf + 2));//获取流水顺序号(逻辑编号)

    qDebug() << "size = " << size;

    ej->setipstr(IpStr);

    for(;;)
    {
        size++;
        sendbuf[0] = cmdFLOWDATA;
        sendbuf[1] = 2;
        *((WORD *)(sendbuf+2)) = size;//提取下一个流水记录

        datalen = 4;

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

        if(recvbuf[0] & 0xff == cmdANSWER)
        {
            qDebug() << "--->flowbill recv break!";
            break;
        }

        size = *((WORD *)(recvbuf + 2));//获取流水顺序号(逻辑编号)
        qDebug() << "--->size = " << size;

        if(size == 0)
        {
            qDebug("--->recvbuf[0] = %02x", recvbuf[0]);
            break;
        }

        ej->DataParse(recvbuf + 4);
    }

    formtcpclient->abortConnect();
}

void ticket::tcpconnectcash(char type)
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
                if(formtype == F_TICKET)
                {
                    ticket_update();
                }
                else if(formtype == F_CLERK)
                {
                    clerk_update();
                }
                else if(formtype == F_DISC)
                {
                    disc_update();
                }
                else if(formtype == F_TAX)
                {
                    tax_update();
                }
                else if(formtype == F_OFFER)
                {
                    offer_update();
                }
            }
            else if(type == F_DOWNLOAD)
            {
                if(formtype == F_TICKET)
                {
                    ticket_download();
                }
                else if(formtype == F_CLERK)
                {
                    clerk_download();
                }
                else if(formtype == F_DISC)
                {
                    disc_download();
                }
                else if(formtype == F_TAX)
                {
                    tax_download();
                }
                else if(formtype == F_OFFER)
                {
                    offer_download();
                }
                else if(formtype == F_EJ)
                {
                    ej_download();
                }
            }
        }
    }
}

void ticket::on_download_clicked()
{
    IpIndexMax = ui->tableWidget->rowCount();
    IpIndex = 0;

    udflag = F_DOWNLOAD;

    tcpconnectcash(udflag);
}

void ticket::on_update_clicked()
{
    IpIndexMax = ui->tableWidget->rowCount();
    IpIndex = 0;

    udflag = F_UPDATA;

    tcpconnectcash(udflag);
}

#if 0
void ticket::on_header_textChanged()
{
    QString textContent = ui->header->toPlainText();

    int length = textContent.count();

    int maxLength = 43; // 最大字符数

    if(length > maxLength) {
        int position = ui->header->textCursor().position();

        QTextCursor textCursor = ui->header->textCursor();

        textContent.remove(position - (length - maxLength), length - maxLength);

        ui->header->setText(textContent);

        textCursor.setPosition(position - (length - maxLength));

        ui->header->setTextCursor(textCursor);

    }
}
#endif

void ticket::clerk_option_deal()
{
    QString optiondata;
    optiondata += ui->actionTrain_Clerk->isChecked() ? QString("8") : QString("");
    optiondata += ui->actionAmount_Discount_Need_Password->isChecked() ? QString("7") : QString("");
    optiondata += ui->actionPercentage_Addition_Need_Password->isChecked() ? QString("6") : QString("");
    optiondata += ui->actionPercentage_Discount_Need_Password->isChecked() ? QString("5") : QString("");
    optiondata += ui->actionReturn_Need_Password->isChecked() ? QString("4") : QString("");
    optiondata += ui->actionCancel_Need_Password->isChecked() ? QString("3") : QString("");
    optiondata += ui->actionCorr_Need_Password->isChecked() ? QString("2") : QString("");
    optiondata += ui->actionVoid_Need_Password->isChecked() ? QString("1") : QString("");
    ui->clerkWidget->currentItem()->setText(optiondata);

    pop_menu->exec(currpos);
}

void ticket::clerk_option_menu()
{
    pop_menu->clear(); //清除原有菜单

    ui->actionVoid_Need_Password->setChecked(false);
    ui->actionCorr_Need_Password->setChecked(false);
    ui->actionCancel_Need_Password->setChecked(false);
    ui->actionReturn_Need_Password->setChecked(false);
    ui->actionPercentage_Discount_Need_Password->setChecked(false);
    ui->actionPercentage_Addition_Need_Password->setChecked(false);
    ui->actionAmount_Discount_Need_Password->setChecked(false);
    ui->actionTrain_Clerk->setChecked(false);

    QString str = ui->clerkWidget->currentItem()->text();

    for(int i = 0; i < str.size(); i++)
    {
        if(str.at(i) == QChar('1'))
        {
            ui->actionVoid_Need_Password->setChecked(true);
        }

        if(str.at(i) == QChar('2'))
        {
            ui->actionCorr_Need_Password->setChecked(true);
        }

        if(str.at(i) == QChar('3'))
        {
            ui->actionCancel_Need_Password->setChecked(true);
        }

        if(str.at(i) == QChar('4'))
        {
            ui->actionReturn_Need_Password->setChecked(true);
        }

        if(str.at(i) == QChar('5'))
        {
            ui->actionPercentage_Discount_Need_Password->setChecked(true);
        }

        if(str.at(i) == QChar('6'))
        {
            ui->actionPercentage_Addition_Need_Password->setChecked(true);
        }

        if(str.at(i) == QChar('7'))
        {
            ui->actionAmount_Discount_Need_Password->setChecked(true);
        }

        if(str.at(i) == QChar('8'))
        {
            ui->actionTrain_Clerk->setChecked(true);
        }
    }

    pop_menu->addAction(ui->actionVoid_Need_Password);
    pop_menu->addAction(ui->actionCorr_Need_Password);
    pop_menu->addAction(ui->actionCancel_Need_Password);
    pop_menu->addAction(ui->actionReturn_Need_Password);
    pop_menu->addAction(ui->actionPercentage_Discount_Need_Password);
    pop_menu->addAction(ui->actionPercentage_Addition_Need_Password);
    pop_menu->addAction(ui->actionAmount_Discount_Need_Password);
    pop_menu->addAction(ui->actionTrain_Clerk);

    //菜单出现的位置为当前鼠标的位置
    currpos = QCursor::pos();
    pop_menu->exec(currpos);
}

void ticket::disc_option_deal()
{
    QString optiondata;
    optiondata += ui->actionFixed_Float->isChecked() ? QString("3") : QString("");
    optiondata += ui->actionFload->isChecked() ? QString("2") : QString("");
    optiondata += ui->actionFixed->isChecked() ? QString("1") : QString("");
    ui->clerkWidget->currentItem()->setText(optiondata);

    //pop_menu->exec(currpos);
}

void ticket::disc_option_menu()
{
    pop_menu->clear(); //清除原有菜单

    ui->actionFixed->setChecked(false);
    ui->actionFload->setChecked(false);
    ui->actionFixed_Float->setChecked(false);

    QString str = ui->clerkWidget->currentItem()->text();

    for(int i = 0; i < str.size(); i++)
    {
        if(str.at(i) == QChar('1'))
        {
            ui->actionFixed->setChecked(true);
        }

        if(str.at(i) == QChar('2'))
        {
            ui->actionFload->setChecked(true);
        }

        if(str.at(i) == QChar('3'))
        {
            ui->actionFixed_Float->setChecked(true);
        }
    }

    pop_menu->addAction(ui->actionFixed);
    pop_menu->addAction(ui->actionFload);
    pop_menu->addAction(ui->actionFixed_Float);

    //菜单出现的位置为当前鼠标的位置
    currpos = QCursor::pos();
    pop_menu->exec(currpos);
}

void ticket::tax_option_deal()
{
    QString optiondata;
    optiondata += ui->actionPrint_Tax->isChecked() ? QString("5") : QString("");
    optiondata += ui->actionPrint_Zero->isChecked() ? QString("3") : QString("");
    optiondata += ui->actionPrint_Vat->isChecked() ? QString("2") : QString("");
    ui->clerkWidget->currentItem()->setText(optiondata);

    pop_menu->exec(currpos);
}

void ticket::tax_option_menu()
{
    pop_menu->clear(); //清除原有菜单

    ui->actionPrint_Vat->setChecked(false);
    ui->actionPrint_Zero->setChecked(false);
    ui->actionPrint_Tax->setChecked(false);

    QString str = ui->clerkWidget->currentItem()->text();

    for(int i = 0; i < str.size(); i++)
    {
        if(str.at(i) == QChar('2'))
        {
            ui->actionPrint_Vat->setChecked(true);
        }

        if(str.at(i) == QChar('3'))
        {
            ui->actionPrint_Zero->setChecked(true);
        }

        if(str.at(i) == QChar('5'))
        {
            ui->actionPrint_Tax->setChecked(true);
        }
    }

    pop_menu->addAction(ui->actionPrint_Vat);
    pop_menu->addAction(ui->actionPrint_Zero);
    pop_menu->addAction(ui->actionPrint_Tax);

    //菜单出现的位置为当前鼠标的位置
    currpos = QCursor::pos();
    pop_menu->exec(currpos);
}

void ticket::offer_option_deal()
{
    int column = ui->clerkWidget->currentColumn();

    QString optiondata;

    if(column == 2)
    {
        optiondata += ui->actionNo_Discount->isChecked() ? QString("0") : QString("");
        optiondata += ui->actionOffer_Price->isChecked() ? QString("1") : QString("");
        optiondata += ui->actionDiscount->isChecked() ? QString("2") : QString("");
    }
    else if(column == 7)
    {
        optiondata += ui->actionMonday->isChecked() ? QString("1") : QString("");
        optiondata += ui->actionTuesday->isChecked() ? QString("2") : QString("");
        optiondata += ui->actionWednesday->isChecked() ? QString("3") : QString("");
        optiondata += ui->actionThursday->isChecked() ? QString("4") : QString("");
        optiondata += ui->actionFriday->isChecked() ? QString("5") : QString("");
        optiondata += ui->actionSaturday->isChecked() ? QString("6") : QString("");
        optiondata += ui->actionSunday->isChecked() ? QString("7") : QString("");
    }

    ui->clerkWidget->currentItem()->setText(optiondata);

    if(column == 7)
    {
        pop_menu->exec(currpos);
    }
}

void ticket::offer_option_menu()
{
    int column = ui->clerkWidget->currentColumn();

    pop_menu->clear(); //清除原有菜单

    if(column == 2)
    {
        ui->actionNo_Discount->setChecked(false);
        ui->actionOffer_Price->setChecked(false);
        ui->actionDiscount->setChecked(false);

        QString str = ui->clerkWidget->currentItem()->text();

        for(int i = 0; i < str.size(); i++)
        {
            if(str.at(i) == QChar('1'))
            {
                ui->actionOffer_Price->setChecked(true);
            }

            if(str.at(i) == QChar('2'))
            {
                ui->actionDiscount->setChecked(true);
            }

            if(str.at(i) == QChar('0'))
            {
                ui->actionNo_Discount->setChecked(true);
            }
        }

        pop_menu->addAction(ui->actionNo_Discount);
        pop_menu->addAction(ui->actionOffer_Price);
        pop_menu->addAction(ui->actionDiscount);
    }
    else if(column == 7)
    {
        ui->actionMonday->setChecked(false);
        ui->actionTuesday->setChecked(false);
        ui->actionWednesday->setChecked(false);
        ui->actionThursday->setChecked(false);
        ui->actionFriday->setChecked(false);
        ui->actionSaturday->setChecked(false);
        ui->actionSunday->setChecked(false);

        QString str = ui->clerkWidget->currentItem()->text();

        for(int i = 0; i < str.size(); i++)
        {
            if(str.at(i) == QChar('1'))
            {
                ui->actionMonday->setChecked(true);
            }
            if(str.at(i) == QChar('2'))
            {
                ui->actionTuesday->setChecked(true);
            }
            if(str.at(i) == QChar('3'))
            {
                ui->actionWednesday->setChecked(true);
            }
            if(str.at(i) == QChar('4'))
            {
                ui->actionThursday->setChecked(true);
            }
            if(str.at(i) == QChar('5'))
            {
                ui->actionFriday->setChecked(true);
            }
            if(str.at(i) == QChar('6'))
            {
                ui->actionSaturday->setChecked(true);
            }
            if(str.at(i) == QChar('7'))
            {
                ui->actionSunday->setChecked(true);
            }
        }

        pop_menu->addAction(ui->actionMonday);
        pop_menu->addAction(ui->actionTuesday);
        pop_menu->addAction(ui->actionWednesday);
        pop_menu->addAction(ui->actionThursday);
        pop_menu->addAction(ui->actionFriday);
        pop_menu->addAction(ui->actionSaturday);
        pop_menu->addAction(ui->actionSunday);
    }

    //菜单出现的位置为当前鼠标的位置
    currpos = QCursor::pos();
    pop_menu->exec(currpos);
}

void ticket::on_clerkWidget_clicked(const QModelIndex &index)
{
    if(win_type == CLERK_WIN)
    {
        if(index.column() == 2)
        {
            clerk_option_menu();
        }
    }
    else if(win_type == DISC_WIN)
    {
        if(index.column() == 2)
        {
            disc_option_menu();
        }
    }
    else if(win_type == TAX_WIN)
    {
        if(index.column() == 3)
        {
            tax_option_menu();
        }
    }
    else if(win_type == OFFER_WIN)
    {
        if(index.column() == 2 || index.column() == 7)
        {
            offer_option_menu();
        }
    }
}

void ticket::on_actionVoid_Need_Password_triggered()
{
    clerk_option_deal();
}

void ticket::on_actionCorr_Need_Password_triggered()
{
    clerk_option_deal();
}

void ticket::on_actionCancel_Need_Password_triggered()
{
    clerk_option_deal();
}

void ticket::on_actionReturn_Need_Password_triggered()
{
    clerk_option_deal();
}

void ticket::on_actionPercentage_Discount_Need_Password_triggered()
{
    clerk_option_deal();
}

void ticket::on_actionPercentage_Addition_Need_Password_triggered()
{
    clerk_option_deal();
}

void ticket::on_actionAmount_Discount_Need_Password_triggered()
{
    clerk_option_deal();
}

void ticket::on_actionTrain_Clerk_triggered()
{
    clerk_option_deal();
}
#if 1
void ticket::on_actionFixed_triggered()
{
    disc_option_deal();
}

void ticket::on_actionFload_triggered()
{
    disc_option_deal();
}

void ticket::on_actionFixed_Float_triggered()
{
    disc_option_deal();
}
#endif
void ticket::on_actionFixed_toggled(bool arg1)
{
    if(arg1)
    {
        ui->actionFload->setChecked(false);
        ui->actionFixed_Float->setChecked(false);
    }
}

void ticket::on_actionFload_toggled(bool arg1)
{
    if(arg1)
    {
        ui->actionFixed->setChecked(false);
        ui->actionFixed_Float->setChecked(false);
    }
}

void ticket::on_actionFixed_Float_toggled(bool arg1)
{
    if(arg1)
    {
        ui->actionFixed->setChecked(false);
        ui->actionFload->setChecked(false);
    }
}

void ticket::on_actionPrint_Vat_triggered()
{
    tax_option_deal();
}

void ticket::on_actionPrint_Zero_triggered()
{
    tax_option_deal();
}

void ticket::on_actionPrint_Tax_triggered()
{
    tax_option_deal();
}

void ticket::on_actionNo_Discount_triggered()
{
    offer_option_deal();
}

void ticket::on_actionOffer_Price_triggered()
{
    offer_option_deal();
}

void ticket::on_actionDiscount_triggered()
{
    offer_option_deal();
}

void ticket::on_actionNo_Discount_toggled(bool arg1)
{
    if(arg1)
    {
        ui->actionOffer_Price->setChecked(false);
        ui->actionDiscount->setChecked(false);
    }
}

void ticket::on_actionOffer_Price_toggled(bool arg1)
{
    if(arg1)
    {
        ui->actionNo_Discount->setChecked(false);
        ui->actionDiscount->setChecked(false);
    }
}

void ticket::on_actionDiscount_toggled(bool arg1)
{
    if(arg1)
    {
        ui->actionNo_Discount->setChecked(false);
        ui->actionOffer_Price->setChecked(false);
    }
}

void ticket::on_actionMonday_triggered()
{
    offer_option_deal();
}

void ticket::on_actionTuesday_triggered()
{
    offer_option_deal();
}

void ticket::on_actionWednesday_triggered()
{
    offer_option_deal();
}

void ticket::on_actionThursday_triggered()
{
    offer_option_deal();
}

void ticket::on_actionFriday_triggered()
{
    offer_option_deal();
}

void ticket::on_actionSaturday_triggered()
{
    offer_option_deal();
}

void ticket::on_actionSunday_triggered()
{
    offer_option_deal();
}
