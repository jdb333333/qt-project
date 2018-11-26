#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QtNetwork>
#include<QLabel>
#include <QListWidget>
#include <QVBoxLayout>
#include <QListWidgetItem>
//#define GET_HOST_COMMAND "GetCYHost"
#define GET_HOST_COMMAND "IP_FOUND"
//#define LOCAL_PORT 11121
#define Server_PORT 6000

#define TRY_TIMES 1

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Server");
    initList();
    ////////////////////////////////
    initBroadcastListener();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initBroadcastListener()
{
    receiver = new QUdpSocket(this);
    /////绑定，第一个参数为端口号，第二儿表示允许其它地址链接该广播
    receiver->bind(Server_PORT,QUdpSocket::ShareAddress);

    //readyRead:每当有数据报来时发送这个信号
    connect(receiver,SIGNAL(readyRead()),this,SLOT(processPengingDatagram()));

    QHostAddress client_address;
    QByteArray datagback = "IP_FOUND";
    quint16 recPort = 0;
    receiver->writeDatagram(datagback,datagback.size(),QHostAddress::Broadcast,Server_PORT);

}


void MainWindow::initList()
{
    label = new QLabel;
    label->setFixedWidth(70);
    label->setText("收到的广播源：");
    mlistWidget = new QListWidget;
    QVBoxLayout* layout = new QVBoxLayout;
    QListWidgetItem* lst1 = new QListWidgetItem("broacast command and ip list:", mlistWidget);
    mlistWidget->insertItem(1, lst1);
    layout->addWidget(label);
    layout->addWidget(mlistWidget);


    QWidget *mainWidget = new QWidget;
    mainWidget->setLayout(layout);

    setCentralWidget(mainWidget);
}
void MainWindow::processPengingDatagram()
{
    QHostAddress client_address;//声明一个QHostAddress对象用于保存发送端的信息
    //char buf[100];//声明一个字符数组用于接收发送过来的字符串
    //数据报不为空
    while( receiver->hasPendingDatagrams() )
    {
        quint16 recPort = 0;
        QByteArray datagram;
        //datagram大小为等待处理数据报的大小才能就收数据;
        datagram.resize( receiver->pendingDatagramSize() );
        //接收数据报
        receiver->readDatagram(datagram.data(),datagram.size(), &client_address, &recPort);
        //label->setText(datagram);
        QString strData= datagram;
        qDebug() << "recv data = " << strData;
            #if 0
        int ret = strData.compare(GET_HOST_COMMAND);
        if (0 == ret)
        {
            addBroadcastResItem(datagram, client_address.toString());
            QByteArray datagback = "my ip is:"+getIp().toLatin1();
            //QByteArray datagback = "my ip is:192.168.1.123";//+getIp().toLatin1();
            receiver->writeDatagram(datagback,datagback.size(),client_address,recPort);
        }
#endif
    }
}

void MainWindow::addBroadcastResItem(QByteArray data, QString ip)
{

    QListWidgetItem* lst1 = new QListWidgetItem(data + "\t" + ip, mlistWidget);
    mlistWidget->insertItem(1, lst1);
}

//得到主机的ip地址
QString MainWindow::getIp()
{
 //使用allAddresses命令获得所有的ip地址
    QList<QHostAddress> list=QNetworkInterface::allAddresses();
    foreach (QHostAddress address,list)
    {
        if(address.protocol()==QAbstractSocket::IPv4Protocol)
            return address.toString();
    }
    return 0;
}
