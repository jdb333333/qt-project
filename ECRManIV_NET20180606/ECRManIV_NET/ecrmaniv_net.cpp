#include "ecrmaniv_net.h"
#include "ui_ecrmaniv_net.h"
#include "netdialog.h"
#include "tcpclient.h"
#include "udpclient.h"
#include "exdata.h"
#include "reportdialog.h"
#include "formdialog.h"

#include "mycheckboxheader.h"

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

    ui->tableWidget_2->setColumnCount(2);
    ui->tableWidget_2->setRowCount(1);
    ui->tableWidget_2->setHorizontalHeaderLabels(QStringList()<<"CASH"<<"IP");
    ui->tableWidget_2->setSelectionBehavior(QAbstractItemView::SelectRows); //整行选中的方式
    ui->tableWidget_2->setEditTriggers(QAbstractItemView::NoEditTriggers);   //禁止修改
    ui->tableWidget_2->setSelectionMode(QAbstractItemView::SingleSelection);  //设置为可以选中单个

    QString IP = QString("192.168.99.77");
    QLabel *label = new QLabel();
    label->setPixmap(QPixmap(":/images/icons/LinkToPC.png"));
    label->setAlignment(Qt::AlignHCenter);

    ui->tableWidget_2->setCellWidget(0,0,label);
    ui->tableWidget_2->setItem(0,1,new QTableWidgetItem(IP));
    ui->tableWidget_2->item(0, 1)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    ui->tableWidget_2->verticalHeader()->setVisible(false);   //隐藏列表头
    ui->tableWidget_2->selectRow(0);

    //ui->tableWidget_2->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    ui->tableWidget_2->setColumnWidth(0, 80);
    ui->tableWidget_2->horizontalHeader()->setStretchLastSection(true);

    ui->tableWidget_2->setFrameShape(QFrame::NoFrame); //设置无边框
    ui->tableWidget_2->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}");//设置表头背景色
    //ui->tableWidget_2->setStyleSheet("selection-background-color:lightblue;"); //设置选中背景色

    ui->tableWidget_2->horizontalHeader()->setHighlightSections(false);//点击表时不对表头行光亮（获取焦点）

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

    QLabel *label = new QLabel();
    label->setPixmap(QPixmap(":/images/icons/LinkToPC.png"));
    label->setAlignment(Qt::AlignHCenter);

    ui->tableWidget_2->insertRow(rows);

    //ui->tableWidget_2->setItem(rows,0,new QTableWidgetItem("register"+QString::number(rows)));
    ui->tableWidget_2->setCellWidget(rows,0,label);
    ui->tableWidget_2->setItem(rows,1,new QTableWidgetItem(ip));
    ui->tableWidget_2->item(rows, 1)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    ui->tableWidget_2->selectRow(rows);
#if 1
    QString ipstr = ui->tableWidget_2->item(rows,1)->text();//取出字符串
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
    bool focus = ui->tableWidget_2->isItemSelected(ui->tableWidget_2->currentItem()); // 判断是否选中一行
    if(focus)
    {
        int row1 = ui->tableWidget_2->currentItem()->row(); // 当前选中行
        QString ipstr = ui->tableWidget_2->item(row1,1)->text();//取出字符串
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
            if(count == rowIndex)
            {
                QString ipstr = ui->tableWidget_2->item(count,1)->text();//取出字符串
                qDebug() << "-------->ipstr = " << ipstr;
                reportdispWin->setiplist(ipstr, true);
            }
            else
            {
                QString ipstr = ui->tableWidget_2->item(count,1)->text();//取出字符串
                qDebug() << "-------->ipstr = " << ipstr;
                reportdispWin->setiplist(ipstr, false);
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

    delete reportdispWin;
}

void ECRManIV_NET::on_clerk_clicked()
{
#if 0
    exdata *mydept = new exdata();

    connect(mydept, SIGNAL(unconnecthost()), this, SLOT(tcpunconnect()));
    connect(mydept, SIGNAL(connecthost()), this, SLOT(tcpconnect()));
    connect(mydept, SIGNAL(recvdata(char*,int)), this, SLOT(tcprecvdata(char*,int)));
    connect(mydept, SIGNAL(senddata(char*,int)), this, SLOT(tcpsenddata(char*,int)));
    connect(this->clientsocket, SIGNAL(recvdataok(int)), mydept, SLOT(recvdataok(int)));
    connect(this->clientsocket, SIGNAL(tcpstate(int)), mydept, SLOT(tcpstate(int)));

    mydept->show();
    mydept->raise();
#endif
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
        QString ipstr = ui->tableWidget_2->item(rowIndex,1)->text();//取出字符串
        clientsocket->setserverip(ipstr);
        StripToZno(ipstr);
    }
}

void ECRManIV_NET::on_plu_clicked()
{
    formDialog *myplu = new formDialog(this);
    //formDialog *myplu = new formDialog;

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
    myplu->exec();
#endif

    delete myplu;
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
    QString ip;

    ipcount = ipitem;
    ipsearchok = true;

    for(i = 0; i < ipcount; i++)
    {
        ip = QString(QLatin1String(IPGROUP[i]));
        qDebug()<<"ip = " << ip;

        rows=ui->tableWidget_2->rowCount();
        QLabel *label = new QLabel();
        label->setPixmap(QPixmap(":/images/icons/LinkToPC.png"));
        label->setAlignment(Qt::AlignHCenter);

        ui->tableWidget_2->insertRow(rows);

        ui->tableWidget_2->setCellWidget(rows,0,label);
        ui->tableWidget_2->setItem(rows,1,new QTableWidgetItem(ip));
        ui->tableWidget_2->item(rows, 1)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

        ui->tableWidget_2->selectRow(rows);

        QString ipstr = ui->tableWidget_2->item(rows,1)->text();//取出字符串
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
