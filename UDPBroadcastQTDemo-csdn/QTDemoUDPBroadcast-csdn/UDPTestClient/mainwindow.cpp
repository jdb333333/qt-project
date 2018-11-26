#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QtNetwork>
#include<QLabel>
#include <QListWidget>
#include <QVBoxLayout>
#include <QListWidgetItem>
//#define GET_HOST_COMMAND "GetCYHost"
#define GET_HOST_COMMAND "GetIPAddr"
#define LOCAL_PORT 6000
#define DEST_PORT 6000

#define TRY_TIMES 1

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Client");
    initList();
    ////////////////////////////////
    initBroadcast();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initBroadcast()
{
    receiver = new QUdpSocket(this);
    /////绑定，第一个参数为端口号，第二儿表示允许其它地址链接该广播
    receiver->bind(LOCAL_PORT,QUdpSocket::ShareAddress);

    //readyRead:每当有数据报来时发送这个信号
    connect(receiver,SIGNAL(readyRead()),this,SLOT(processPengingDatagram()));

    BroadcastGetIpCommand();
}

void MainWindow::BroadcastGetIpCommand()
{
    //QByteArray datagram = "Hello World!";
    QByteArray datagram = GET_HOST_COMMAND;
    int times = TRY_TIMES;
    while(times--)
    {
        //sender->writeDatagram(datagram.data(),datagram.size(),QHostAddress::Broadcast,1066);
        receiver->writeDatagram(datagram.data(),datagram.size(),QHostAddress::Broadcast,DEST_PORT);
    }
}

void MainWindow::initList()
{
    label = new QLabel;
    label->setFixedWidth(70);
    label->setText("搜索到IP地址：");
    mlistWidget = new QListWidget;
    QVBoxLayout* layout = new QVBoxLayout;
    QListWidgetItem* lst1 = new QListWidgetItem("searched ip list:", mlistWidget);
//    QListWidgetItem* lst2 = new QListWidgetItem("decision", mlistWidget);
//    QListWidgetItem* lst3 = new QListWidgetItem("document", mlistWidget);
//    QListWidgetItem* lst4 = new QListWidgetItem("process", mlistWidget);
//    QListWidgetItem* lst5 = new QListWidgetItem("printer", mlistWidget);
    mlistWidget->insertItem(1, lst1);
//    mlistWidget->insertItem(2, lst2);
//    mlistWidget->insertItem(3, lst3);
//    mlistWidget->insertItem(4, lst4);
//    mlistWidget->insertItem(5, lst5);
    //mlistWidget->show();
    layout->addWidget(label);
    layout->addWidget(mlistWidget);


    QWidget *mainWidget = new QWidget;
    mainWidget->setLayout(layout);

    setCentralWidget(mainWidget);
}
void MainWindow::processPengingDatagram()
{
    QString s;

    //数据报不为空
    while( receiver->hasPendingDatagrams() )
    {
        QByteArray datagram;
        //datagram大小为等待处理数据报的大小才能就收数据;
        datagram.resize( receiver->pendingDatagramSize() );
        //接收数据报
        receiver->readDatagram(datagram.data(),datagram.size());
        //label->setText(datagram);
        s = datagram;
        qDebug() << "datagram = " << s;
        addIpItem(datagram);
    }
}

void MainWindow::addIpItem(QByteArray data)
{

    QListWidgetItem* lst1 = new QListWidgetItem(data, mlistWidget);
    mlistWidget->insertItem(1, lst1);
}
