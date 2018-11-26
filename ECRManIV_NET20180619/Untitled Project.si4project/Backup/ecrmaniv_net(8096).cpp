#include "ecrmaniv_net.h"
#include "ui_ecrmaniv_net.h"
#include "netdialog.h"
#include "tcpclient.h"
#include "udpclient.h"
#include "reportdialog.h"
#include "formdialog.h"
#include "ticket.h"

#include "mycheckboxheader.h"

#include "formwidget.h"

#include "./usr/usrdb.h"
#include "./usr/usrdialog.h"
#include "./message/message.h"

#include "./update/updateapp.h"
#include "./RS232/rs232dialog.h"

#include <QMenu>
#include <QDebug>
#include <QPixmap>
#include <QBitmap>
#include <QSize>

#include <QFile>

ECRManIV_NET::ECRManIV_NET(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ECRManIV_NET)
{
    ui->setupUi(this);

    QPalette p = this->palette();
    p.setColor(QPalette::Window, QColor(0xff,0xeb,0xcd));
    //p.setColor(QPalette::Background, Qt::blue); //设置背景蓝色
    this->setPalette(p);

#if 0
    QPalette p1 = ui->tableWidget_2->palette();
    //p1.setColor(QPalette::Window, QColor(0xca,0xff,0x70));
    p1.setColor(QPalette::Background, QColor(0xca,0xff,0x70)); //设置背景蓝色
    ui->tableWidget_2->setPalette(p1);
#endif

    //connect(ui->tableWidget_2, SIGNAL(itemChanged(QTableWidgetItem*)), ui->tableWidget_2, SLOT(ipchange()));

    //ui->tableWidget_2->setStyleSheet(getQssContent());

#if (GETMACADDR)
    ui->tableWidget_2->setColumnCount(3);
#else
    ui->tableWidget_2->setColumnCount(2);
#endif
    ui->tableWidget_2->setRowCount(1);

#if (GETMACADDR)
    ui->tableWidget_2->setHorizontalHeaderLabels(QStringList()<<CASHNAME<<"IP"<<"MACADDR");
#else
    ui->tableWidget_2->setHorizontalHeaderLabels(QStringList()<<CASHNAME<<"IP");
#endif

    ui->tableWidget_2->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_2->setSelectionMode(QAbstractItemView::SingleSelection);

    ui->tableWidget_2->verticalHeader()->setVisible(false);

    ui->tableWidget_2->horizontalHeader()->setResizeMode(QHeaderView::Stretch);

    //ui->tableWidget_2->horizontalHeader()->setStretchLastSection(true);
    //ui->tableWidget_2->setColumnWidth(0, 150);
    //ui->tableWidget_2->setColumnWidth(1, 100);
    ui->tableWidget_2->horizontalHeader()->setResizeMode(0, QHeaderView::ResizeToContents);
    ui->tableWidget_2->horizontalHeader()->setResizeMode(1, QHeaderView::ResizeToContents);
#if (GETMACADDR)
    ui->tableWidget_2->horizontalHeader()->setResizeMode(2, QHeaderView::ResizeToContents);
#endif

    ui->tableWidget_2->setFrameShape(QFrame::NoFrame); //设置无边�?
    ui->tableWidget_2->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}");//设置表头背景�?

    ui->tableWidget_2->horizontalHeader()->setHighlightSections(false);//点击表时不对表头行光亮（获取焦点�?

#if 0
    ui->tableWidget_2->setColumnWidth(0, 80);

    QLabel *label = new QLabel();
    label->setPixmap(QPixmap(":/images/icons/LinkToPC.png"));
    label->setAlignment(Qt::AlignHCenter);
    ui->tableWidget_2->setCellWidget(0,0,label);
#else
    QString IP = QString("192.168.99.77");
    QString SHOPNAME = QString("shopname123456");

    //ui->tableWidget_2->setColumnWidth(0, 80);
    ui->tableWidget_2->setItem(0,0,new QTableWidgetItem(SHOPNAME));
    ui->tableWidget_2->item(0, 0)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    ui->tableWidget_2->setItem(0,1,new QTableWidgetItem(IP));
    ui->tableWidget_2->item(0, 1)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    ui->tableWidget_2->selectRow(0);
#endif

    clientsocket = new tcpclient(this);
    clientsocket->setserverip(IP);

    StripToZno(IP);

    udpclientsocket = new udpclient(this);
    connect(udpclientsocket, SIGNAL(searchipok(int)), this, SLOT(searchipok(int)));

    ui->tableWidget_2->installEventFilter(this);

#if 0
    MyCheckboxHeader *myHeader = new MyCheckboxHeader(Qt::Horizontal, ui->tableWidget_2);
    ui->tableWidget_2->setHorizontalHeader(myHeader);
#endif

    //ZNo = 1;
}

ECRManIV_NET::~ECRManIV_NET()
{
    delete ui;
}

void ECRManIV_NET::permset()
{
    qDebug("CUsrInfo.permission = %d", UsrDb->CUsrInfo.permission);

    if(UsrDb->CUsrInfo.group == ADMUSR)
    {

    }
    else
    {
        ui->usrmng->setVisible(false);
        ui->label_usrmng->setVisible(false);
    }

    if(UsrDb->CUsrInfo.group == ADMUSR || UsrDb->CUsrInfo.permission & CLERKPERM)
    {

    }
    else
    {
        ui->clerk->setVisible(false);
        ui->label_clerk->setVisible(false);
    }

    if(UsrDb->CUsrInfo.group == ADMUSR || UsrDb->CUsrInfo.permission & GROUPPERM)
    {

    }
    else
    {
        ui->flowbill->setVisible(false);
        ui->label_flowbill->setVisible(false);
    }

    if(UsrDb->CUsrInfo.group == ADMUSR || UsrDb->CUsrInfo.permission & DEPARTMENTPERM)
    {

    }
    else
    {
        ui->dept->setVisible(false);
        ui->label_dept->setVisible(false);
    }

    if(UsrDb->CUsrInfo.group == ADMUSR || UsrDb->CUsrInfo.permission & PLUPERM)
    {

    }
    else
    {
        ui->plu->setVisible(false);
        ui->label_plu->setVisible(false);
    }

    if(UsrDb->CUsrInfo.group == ADMUSR || UsrDb->CUsrInfo.permission & DISCOUNTPERM)
    {

    }
    else
    {
        ui->disc->setVisible(false);
        ui->label_disc->setVisible(false);
    }

    if(UsrDb->CUsrInfo.group == ADMUSR || UsrDb->CUsrInfo.permission & TAXPERM)
    {

    }
    else
    {
        ui->tax->setVisible(false);
        ui->label_tax->setVisible(false);
    }

    if(UsrDb->CUsrInfo.group == ADMUSR || UsrDb->CUsrInfo.permission & TICKETPERM)
    {

    }
    else
    {
        ui->ticket->setVisible(false);
        ui->label_ticket->setVisible(false);
    }

    if(UsrDb->CUsrInfo.group == ADMUSR || UsrDb->CUsrInfo.permission & OFFERPERM)
    {

    }
    else
    {
        ui->system->setVisible(false);
        ui->label_offer->setVisible(false);
    }

    if(UsrDb->CUsrInfo.group == ADMUSR || UsrDb->CUsrInfo.permission & REPORTPERM)
    {

    }
    else
    {
        ui->zport->setVisible(false);
        ui->label_report->setVisible(false);
    }
}

QString ECRManIV_NET::getQssContent()
{
    QFile styleSheet("./tablewidgetstyle.txt");

    if(!styleSheet.open(QIODevice::ReadOnly))
    {
        qDebug("Can't open the style sheet file.");
        return "";
    }

    return styleSheet.readAll();
}

void ECRManIV_NET::StripToZno(QString ipstr)
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

bool ECRManIV_NET::eventFilter(QObject *o, QEvent *event)
{
    if (o == ui->tableWidget_2)
        {
            if (event->type() == QEvent::ContextMenu)
            {
                QMenu* popMenu = new QMenu(this);
                popMenu->addAction(ui->actionADD);
                popMenu->addAction(ui->actionDELETE);
                popMenu->addAction(ui->actionLOCAL);
#if 0
                if(ui->tableWidget_2->itemAt(mapFromGlobal(QCursor::pos())) != NULL)
                    {
                        popMenu->addAction(ui->actionMODI);
                    }
#endif
                popMenu->exec(QCursor::pos());
                return true;
            }
        }
    return QObject::eventFilter(o,event);
}

void ECRManIV_NET::on_actionADD_triggered()
{
    NetDialog *netdialog = new NetDialog(this);
    netdialog->iptype = 1;
    netdialog->exec();
}

void ECRManIV_NET::getipitem(int ip1, int ip2, int ip3, int ip4)
{
    QString ip = QString("%1.%2.%3.%4").arg(ip1).arg(ip2).arg(ip3).arg(ip4);
    //int cols=ui->tableWidget_2->columnCount();
    int rows=ui->tableWidget_2->rowCount();

    qDebug()<<ip;

    ui->tableWidget_2->insertRow(rows);
#if 0
    QLabel *label = new QLabel();
    label->setPixmap(QPixmap(":/images/icons/LinkToPC.png"));
    label->setAlignment(Qt::AlignHCenter);

    //ui->tableWidget_2->setItem(rows,0,new QTableWidgetItem("register"+QString::number(rows)));
    ui->tableWidget_2->setCellWidget(rows,0,label);
#else
    QString name("cash");
    ui->tableWidget_2->setItem(rows,0,new QTableWidgetItem(name));
    ui->tableWidget_2->item(rows, 0)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
#endif
    ui->tableWidget_2->setItem(rows,1,new QTableWidgetItem(ip));
    ui->tableWidget_2->item(rows, 1)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    ui->tableWidget_2->selectRow(rows);
#if 1
    QString ipstr = ui->tableWidget_2->item(rows,1)->text();//取出字符�?
    clientsocket->setserverip(ipstr);
    StripToZno(ipstr);
#endif
}

void ECRManIV_NET::setlocalip(int ip1, int ip2, int ip3, int ip4)
{
    QString ip = QString("%1.%2.%3.%4").arg(ip1).arg(ip2).arg(ip3).arg(ip4);
    qDebug() << "local ip = " << ip;

    char localip[64] = {0};
    sprintf(localip, "%d.%d.%d.%d", ip1, ip2, ip3, ip4);

    udpclientsocket->BindLocalIp(localip);
}

void ECRManIV_NET::on_tableWidget_2_clicked(const QModelIndex &index)
{
    bool focus = ui->tableWidget_2->isItemSelected(ui->tableWidget_2->currentItem()); // 判断是否选中一�?
    if(focus)
    {
        int row1 = ui->tableWidget_2->currentItem()->row(); // 当前选中�?
        QString ipstr = ui->tableWidget_2->item(row1,1)->text();//取出字符�?
        clientsocket->setserverip(ipstr);
        StripToZno(ipstr);
    }
}

void ECRManIV_NET::tcpunconnect()
{
    clientsocket->abortConnect();
}

void ECRManIV_NET::tcpconnect()
{
    clientsocket->newConnect();
}

void ECRManIV_NET::tcprecvdata(char *buf, int len)
{
    clientsocket->readData(buf, len);
}

void ECRManIV_NET::tcpgetdata(char *buf, int len)
{
    clientsocket->readData(buf, len);
}

void ECRManIV_NET::tcpsenddata(char *buf, int len)
{
    clientsocket->writeData(buf, len);
}

void ECRManIV_NET::on_zport_clicked()
{
    reportDialog *reportdispWin = new reportDialog(this);
    connect(reportdispWin, SIGNAL(unconnecthost()), this, SLOT(tcpunconnect()));
    connect(reportdispWin, SIGNAL(connecthost()), this, SLOT(tcpconnect()));
    connect(reportdispWin, SIGNAL(recvdata(char*,int)), this, SLOT(tcprecvdata(char*,int)));
    connect(reportdispWin, SIGNAL(senddata(char*,int)), this, SLOT(tcpsenddata(char*,int)));
    connect(this->clientsocket, SIGNAL(recvdataok(int)), reportdispWin, SLOT(recvdataok(int)));
    connect(this->clientsocket, SIGNAL(tcpstate(int)), reportdispWin, SLOT(tcpstate(int)));
    connect(reportdispWin, SIGNAL(setserverip(QString)), this->clientsocket, SLOT(setserverip(QString)));

    reportdispWin->setzno(ZNo);
    reportdispWin->setWindowTitle(QString("%1.%2.%3.%4").arg((ZNo >> 24) & 0xff).arg((ZNo >> 16) & 0xff)
                                  .arg((ZNo >> 8) & 0xff).arg(ZNo & 0xff));

    int rows=ui->tableWidget_2->rowCount();
    if(rows > 0)
    {
        int rowIndex = ui->tableWidget_2->currentRow();

        for(int count = 0; count < rows; count++)
        {
            QString ipstr = ui->tableWidget_2->item(count,1)->text();//取出字符�?
            qDebug() << "-------->ipstr = " << ipstr;
            QString shopname = ui->tableWidget_2->item(count, 0)->text();

            if(count == rowIndex)
            {
                reportdispWin->setiplist(ipstr, shopname, true);
            }
            else
            {
                //QString ipstr = ui->tableWidget_2->item(count,1)->text();//取出字符�?
                //qDebug() << "-------->ipstr = " << ipstr;
                reportdispWin->setiplist(ipstr, shopname, false);
            }
        }
    }

    reportdispWin->exec();

    disconnect(reportdispWin, SIGNAL(unconnecthost()), this, SLOT(tcpunconnect()));
    disconnect(reportdispWin, SIGNAL(connecthost()), this, SLOT(tcpconnect()));
    disconnect(reportdispWin, SIGNAL(recvdata(char*,int)), this, SLOT(tcprecvdata(char*,int)));
    disconnect(reportdispWin, SIGNAL(senddata(char*,int)), this, SLOT(tcpsenddata(char*,int)));
    disconnect(this->clientsocket, SIGNAL(recvdataok(int)), reportdispWin, SLOT(recvdataok(int)));
    disconnect(this->clientsocket, SIGNAL(tcpstate(int)), reportdispWin, SLOT(tcpstate(int)));
    disconnect(reportdispWin, SIGNAL(setserverip(QString)), this->clientsocket, SLOT(setserverip(QString)));

    //delete reportdispWin;
}

void ECRManIV_NET::on_clerk_clicked()
{
#if 0
    Formwidget *discwin = new Formwidget(this);

    discwin->clerk_win();

    discwin->show();
    discwin->raise();
#endif

	ticket *myticket = new ticket(this);

	myticket->setformtype(F_CLERK);

    myticket->settcpclient(this->clientsocket);
    myticket->setWindowTitle(QString("%1.%2.%3.%4").arg((ZNo >> 24) & 0xff).arg((ZNo >> 16) & 0xff)
                                  .arg((ZNo >> 8) & 0xff).arg(ZNo & 0xff));
    int rows=ui->tableWidget_2->rowCount();
    if(rows > 0)
    {
        int rowIndex = ui->tableWidget_2->currentRow();

        for(int count = 0; count < rows; count++)
        {
            QString ipstr = ui->tableWidget_2->item(count,1)->text();//取出字符�?
            qDebug() << "-------->ipstr = " << ipstr;
            QString shopname = ui->tableWidget_2->item(count, 0)->text();
            if(count == rowIndex)
            {
                myticket->setiplist(ipstr, shopname, true);
            }
            else
            {
                //QString ipstr = ui->tableWidget_2->item(count,1)->text();//取出字符�?
                //qDebug() << "-------->ipstr = " << ipstr;
                myticket->setiplist(ipstr, shopname, false);
            }
        }
    }

    myticket->show();
    myticket->raise();
}

void ECRManIV_NET::on_actionDELETE_triggered()
{
    int rowIndex = ui->tableWidget_2->currentRow();

    if (rowIndex != -1)
        ui->tableWidget_2->removeRow(rowIndex);

    //jdb2018-05-18重新设置IP
    rowIndex = ui->tableWidget_2->currentRow();
    if (rowIndex != -1)
    {
        QString ipstr = ui->tableWidget_2->item(rowIndex,1)->text();//取出字符�?
        clientsocket->setserverip(ipstr);
        StripToZno(ipstr);
    }
}

void ECRManIV_NET::on_plu_clicked()
{
    formDialog *myplu = new formDialog(this);
    //formDialog *myplu = new formDialog;

    myplu->setformtype(0x03);

#if 0
    connect(myplu, SIGNAL(unconnecthost()), this, SLOT(tcpunconnect()));
    connect(myplu, SIGNAL(connecthost()), this, SLOT(tcpconnect()));
    connect(myplu, SIGNAL(recvdata(char*,int)), this, SLOT(tcprecvdata(char*,int)));
    connect(myplu, SIGNAL(senddata(char*,int)), this, SLOT(tcpsenddata(char*,int)));
    connect(this->clientsocket, SIGNAL(recvdataok(int)), myplu, SLOT(recvdataok(int)));
    connect(this->clientsocket, SIGNAL(tcpstate(int)), myplu, SLOT(tcpstate(int)));
    connect(myplu, SIGNAL(resetserver()), this->clientsocket, SLOT(resetserver()));

    myplu->setWindowTitle(QString("%1.%2.%3.%4").arg((ZNo >> 24) & 0xff).arg((ZNo >> 16) & 0xff)
                                  .arg((ZNo >> 8) & 0xff).arg(ZNo & 0xff));
    myplu->exec();

    disconnect(myplu, SIGNAL(unconnecthost()), this, SLOT(tcpunconnect()));
    disconnect(myplu, SIGNAL(connecthost()), this, SLOT(tcpconnect()));
    disconnect(myplu, SIGNAL(recvdata(char*,int)), this, SLOT(tcprecvdata(char*,int)));
    disconnect(myplu, SIGNAL(senddata(char*,int)), this, SLOT(tcpsenddata(char*,int)));
    disconnect(this->clientsocket, SIGNAL(recvdataok(int)), myplu, SLOT(recvdataok(int)));
    disconnect(this->clientsocket, SIGNAL(tcpstate(int)), myplu, SLOT(tcpstate(int)));
    disconnect(myplu, SIGNAL(resetserver()), this->clientsocket, SLOT(resetserver()));
#else
    myplu->settcpclient(this->clientsocket);
    myplu->setWindowTitle(QString("%1.%2.%3.%4").arg((ZNo >> 24) & 0xff).arg((ZNo >> 16) & 0xff)
                                  .arg((ZNo >> 8) & 0xff).arg(ZNo & 0xff));

    int rows=ui->tableWidget_2->rowCount();
    if(rows > 0)
    {
        int rowIndex = ui->tableWidget_2->currentRow();

        for(int count = 0; count < rows; count++)
        {
            QString ipstr = ui->tableWidget_2->item(count,1)->text();//取出字符�?
            qDebug() << "-------->ipstr = " << ipstr;
            QString shopname = ui->tableWidget_2->item(count, 0)->text();
            if(count == rowIndex)
            {
                myplu->setiplist(ipstr, shopname, true);
            }
            else
            {
                //QString ipstr = ui->tableWidget_2->item(count,1)->text();//取出字符�?
                //qDebug() << "-------->ipstr = " << ipstr;
                myplu->setiplist(ipstr, shopname, false);
            }
        }
    }

    myplu->exec();
#endif

    //delete myplu;
}

void ECRManIV_NET::on_pushButton_clicked()
{
#if 0
    int rowIndex;

    for(rowIndex = 0; rowIndex < ui->tableWidget_2->rowCount(); rowIndex++)
    {
        ui->tableWidget_2->removeRow(rowIndex);
    }
#else
    ui->tableWidget_2->clearContents();
    ui->tableWidget_2->setRowCount(0);
#endif

    memset(IPGROUP, 0, sizeof(IPGROUP));
    ipsearchok = false;
    ipcount = udpclientsocket->BroadcastGetIpCommand(IPGROUP);
}

void ECRManIV_NET::searchipok(int ipitem)
{
    int i, rows;
    QString MACADDR;

    ipcount = ipitem;
    ipsearchok = true;

    for(i = 0; i < ipcount; i++)
    {
        QString ip;
        QString shopname;

        QStringList shopinfo = QString("%1").arg(IPGROUP[i]).split(':');

        ip = shopinfo.at(0);
        if(shopinfo.size() > 1)
        {
            shopname = shopinfo.at(1);
        }

        if(shopinfo.size() > 2)
        {
            MACADDR = shopinfo.at(2);
            qDebug() << ">>>>>>>>>>MACADDR = " << MACADDR;
        }

        //ip = QString(QLatin1String(IPGROUP[i]));
        qDebug()<<"ip = " << ip;
        qDebug() << "shopname = " << shopname;

        rows=ui->tableWidget_2->rowCount();
        ui->tableWidget_2->insertRow(rows);
#if 0
        QLabel *label = new QLabel();
        label->setPixmap(QPixmap(":/images/icons/LinkToPC.png"));
        label->setAlignment(Qt::AlignHCenter);

        ui->tableWidget_2->setCellWidget(rows,0,label);
#else
        ui->tableWidget_2->setItem(rows,0,new QTableWidgetItem(shopname));
        ui->tableWidget_2->item(rows, 0)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
#endif
        ui->tableWidget_2->setItem(rows,1,new QTableWidgetItem(ip));
        ui->tableWidget_2->item(rows, 1)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

#if (GETMACADDR)
        ui->tableWidget_2->setItem(rows,2,new QTableWidgetItem(MACADDR));
        ui->tableWidget_2->item(rows, 2)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
#else
#endif

        ui->tableWidget_2->selectRow(rows);

        QString ipstr = ui->tableWidget_2->item(rows,1)->text();//取出字符�?
        clientsocket->setserverip(ipstr);
        StripToZno(ipstr);
    }
}

void ECRManIV_NET::on_actionLOCAL_triggered()
{
    NetDialog *netdialog = new NetDialog(this);
    netdialog->iptype = 2;
    netdialog->exec();
}

void ECRManIV_NET::on_dept_clicked()
{
    formDialog *mydept = new formDialog(this);

    mydept->setformtype(0x02);

    mydept->settcpclient(this->clientsocket);
    mydept->setWindowTitle(QString("%1.%2.%3.%4").arg((ZNo >> 24) & 0xff).arg((ZNo >> 16) & 0xff)
                                  .arg((ZNo >> 8) & 0xff).arg(ZNo & 0xff));

    int rows=ui->tableWidget_2->rowCount();
    if(rows > 0)
    {
        int rowIndex = ui->tableWidget_2->currentRow();

        for(int count = 0; count < rows; count++)
        {
            QString ipstr = ui->tableWidget_2->item(count,1)->text();//取出字符�?
            qDebug() << "-------->ipstr = " << ipstr;
            QString shopname = ui->tableWidget_2->item(count, 0)->text();
            if(count == rowIndex)
            {
                mydept->setiplist(ipstr, shopname, true);
            }
            else
            {
                //QString ipstr = ui->tableWidget_2->item(count,1)->text();//取出字符�?
                //qDebug() << "-------->ipstr = " << ipstr;
                mydept->setiplist(ipstr, shopname, false);
            }
        }
    }

    mydept->exec();

    //delete mydept;
    //mydept = NULL;
}

void ECRManIV_NET::on_ticket_clicked()
{
    ticket *myticket = new ticket(this);

	myticket->setformtype(F_TICKET);

    myticket->settcpclient(this->clientsocket);
    myticket->setWindowTitle(QString("%1.%2.%3.%4").arg((ZNo >> 24) & 0xff).arg((ZNo >> 16) & 0xff)
                                  .arg((ZNo >> 8) & 0xff).arg(ZNo & 0xff));
    int rows=ui->tableWidget_2->rowCount();
    if(rows > 0)
    {
        int rowIndex = ui->tableWidget_2->currentRow();

        for(int count = 0; count < rows; count++)
        {
            QString ipstr = ui->tableWidget_2->item(count,1)->text();//取出字符�?
            qDebug() << "-------->ipstr = " << ipstr;
            QString shopname = ui->tableWidget_2->item(count, 0)->text();
            if(count == rowIndex)
            {
                myticket->setiplist(ipstr, shopname, true);
            }
            else
            {
                //QString ipstr = ui->tableWidget_2->item(count,1)->text();//取出字符�?
                //qDebug() << "-------->ipstr = " << ipstr;
                myticket->setiplist(ipstr, shopname, false);
            }
        }
    }

    myticket->show();
    myticket->raise();
}

void ECRManIV_NET::on_disc_clicked()
{
    ticket *myticket = new ticket(this);

    myticket->setformtype(F_DISC);

    myticket->settcpclient(this->clientsocket);
    myticket->setWindowTitle(QString("%1.%2.%3.%4").arg((ZNo >> 24) & 0xff).arg((ZNo >> 16) & 0xff)
                                  .arg((ZNo >> 8) & 0xff).arg(ZNo & 0xff));
    int rows=ui->tableWidget_2->rowCount();
    if(rows > 0)
    {
        int rowIndex = ui->tableWidget_2->currentRow();

        for(int count = 0; count < rows; count++)
        {
            QString ipstr = ui->tableWidget_2->item(count,1)->text();//取出字符�?
            qDebug() << "-------->ipstr = " << ipstr;
            QString shopname = ui->tableWidget_2->item(count, 0)->text();
            if(count == rowIndex)
            {
                myticket->setiplist(ipstr, shopname, true);
            }
            else
            {
                //QString ipstr = ui->tableWidget_2->item(count,1)->text();//取出字符�?
                //qDebug() << "-------->ipstr = " << ipstr;
                myticket->setiplist(ipstr, shopname, false);
            }
        }
    }

    myticket->show();
    myticket->raise();
}

void ECRManIV_NET::on_tax_clicked()
{
    ticket *myticket = new ticket(this);

    myticket->setformtype(F_TAX);

    myticket->settcpclient(this->clientsocket);
    myticket->setWindowTitle(QString("%1.%2.%3.%4").arg((ZNo >> 24) & 0xff).arg((ZNo >> 16) & 0xff)
                                  .arg((ZNo >> 8) & 0xff).arg(ZNo & 0xff));
    int rows=ui->tableWidget_2->rowCount();
    if(rows > 0)
    {
        int rowIndex = ui->tableWidget_2->currentRow();

        for(int count = 0; count < rows; count++)
        {
            QString ipstr = ui->tableWidget_2->item(count,1)->text();//取出字符�?
            qDebug() << "-------->ipstr = " << ipstr;
            QString shopname = ui->tableWidget_2->item(count, 0)->text();
            if(count == rowIndex)
            {
                myticket->setiplist(ipstr, shopname, true);
            }
            else
            {
                //QString ipstr = ui->tableWidget_2->item(count,1)->text();//取出字符�?
                //qDebug() << "-------->ipstr = " << ipstr;
                myticket->setiplist(ipstr, shopname, false);
            }
        }
    }

    myticket->show();
    myticket->raise();
}

void ECRManIV_NET::on_system_clicked()
{
	ticket *myticket = new ticket(this);

    myticket->setformtype(F_OFFER);

    myticket->settcpclient(this->clientsocket);
    myticket->setWindowTitle(QString("%1.%2.%3.%4").arg((ZNo >> 24) & 0xff).arg((ZNo >> 16) & 0xff)
                                  .arg((ZNo >> 8) & 0xff).arg(ZNo & 0xff));
    int rows=ui->tableWidget_2->rowCount();
    if(rows > 0)
    {
        int rowIndex = ui->tableWidget_2->currentRow();

        for(int count = 0; count < rows; count++)
        {
            QString ipstr = ui->tableWidget_2->item(count,1)->text();//取出字符�?
            qDebug() << "-------->ipstr = " << ipstr;
            QString shopname = ui->tableWidget_2->item(count, 0)->text();
            if(count == rowIndex)
            {
                myticket->setiplist(ipstr, shopname, true);
            }
            else
            {
                //QString ipstr = ui->tableWidget_2->item(count,1)->text();//取出字符�?
                //qDebug() << "-------->ipstr = " << ipstr;
                myticket->setiplist(ipstr, shopname, false);
            }
        }
    }

    myticket->show();
    myticket->raise();
}

#if 0
void ECRManIV_NET::on_group_clicked()
{
#if 0
#if 1
    ticket *myticket = new ticket(this);

    myticket->setformtype(F_EJ);

    myticket->settcpclient(this->clientsocket);
    myticket->setWindowTitle(QString("%1.%2.%3.%4").arg((ZNo >> 24) & 0xff).arg((ZNo >> 16) & 0xff)
                                  .arg((ZNo >> 8) & 0xff).arg(ZNo & 0xff));
    int rows=ui->tableWidget_2->rowCount();
    if(rows > 0)
    {
        int rowIndex = ui->tableWidget_2->currentRow();

        for(int count = 0; count < rows; count++)
        {
            QString ipstr = ui->tableWidget_2->item(count,1)->text();//取出字符�?
            qDebug() << "-------->ipstr = " << ipstr;
            QString shopname = ui->tableWidget_2->item(count, 0)->text();
            if(count == rowIndex)
            {
                myticket->setiplist(ipstr, shopname, true);
            }
            else
            {
                //QString ipstr = ui->tableWidget_2->item(count,1)->text();//取出字符�?
                //qDebug() << "-------->ipstr = " << ipstr;
                myticket->setiplist(ipstr, shopname, false);
            }
        }
    }

    myticket->show();
    myticket->raise();
#else
    usrDialog *usrmng = new usrDialog;
    usrmng->exec();
#endif
#endif
}
#endif

void ECRManIV_NET::on_usrmng_clicked()
{
    usrDialog *usrmng = new usrDialog;
    usrmng->exec();
}

void ECRManIV_NET::on_flowbill_clicked()
{
    ticket *myticket = new ticket(this);

    myticket->setformtype(F_EJ);

    myticket->settcpclient(this->clientsocket);
    myticket->setWindowTitle(QString("%1.%2.%3.%4").arg((ZNo >> 24) & 0xff).arg((ZNo >> 16) & 0xff)
                                  .arg((ZNo >> 8) & 0xff).arg(ZNo & 0xff));
    int rows=ui->tableWidget_2->rowCount();
    if(rows > 0)
    {
        int rowIndex = ui->tableWidget_2->currentRow();

        for(int count = 0; count < rows; count++)
        {
            QString ipstr = ui->tableWidget_2->item(count,1)->text();//取出字符�?
            qDebug() << "-------->ipstr = " << ipstr;
            QString shopname = ui->tableWidget_2->item(count, 0)->text();
            if(count == rowIndex)
            {
                myticket->setiplist(ipstr, shopname, true);
            }
            else
            {
                //QString ipstr = ui->tableWidget_2->item(count,1)->text();//取出字符�?
                //qDebug() << "-------->ipstr = " << ipstr;
                myticket->setiplist(ipstr, shopname, false);
            }
        }
    }

    myticket->show();
    myticket->raise();
}

void ECRManIV_NET::on_update_clicked()
{
    RS232Dialog *myupdate = new RS232Dialog(this);
    myupdate->exec();

#if 0
    QString fileName = QFileDialog::getOpenFileName(this,QString(),QString(),"hex file(*.hex)");
    QFile file(fileName);
    if(file.open(QIODevice::ReadOnly)){
#if 0
            QDataStream in(&file);
            while(!in.atEnd())
            {
                unsigned int a1;
                signed short a2,a3;
                short a4;
                in.readRawData((char*)&a1, 4);
                in.readRawData((char*)&a2, 2);
                in.readRawData((char*)&a3, 2);
                in.readRawData((char*)&a4, 4);
                qDebug() << a1;
            }
#else
        QTextStream data(&file);
        QStringList fonts;
        QString line;
        while (!data.atEnd())//���ж�ȡ�ı�����ȥ��ÿ�еĻس�
        {
            fonts.clear();
            line = data.readLine();
            fonts<<line;
            qDebug() << fonts;
        }
#endif
      }
#endif
}
