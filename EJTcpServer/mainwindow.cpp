#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDataStream>
#include<QByteArray>
#include<QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_tcpserver = new QTcpServer(this);
    m_tcpsocket = new QTcpSocket(this);
    m_tcpserver->listen(QHostAddress::Any,6666);//�����Ķ˿ں�
    connect(m_tcpserver,SIGNAL(newConnection()), this,SLOT(newConnect()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newConnect()
{
    ui->label_txtShow->setText("new client connected!!!");
    m_tcpsocket = m_tcpserver->nextPendingConnection();//���ü���
    connect(m_tcpsocket,SIGNAL(readyRead()),
            this,SLOT(readMessage())); //���������տͻ��˵���Ϣ
    connect(m_tcpsocket,SIGNAL(disconnected()),
                m_tcpsocket,SLOT(deleteLater()));
}

void MainWindow::readMessage()
{

    QString res;
    res+=m_tcpsocket->readAll();
    ui->textEdit->setText(res);
}

void MainWindow::sendMessage()
{

    QTextStream out(m_tcpsocket);
    out<<ui->lineEdit->text()<<endl;
}

void MainWindow::on_Btn_send_clicked()//--------�˺�����ͨ����ui�ļ���ת����ֱ�����ɵ�
{
    sendMessage();//---���ɺ���Ӵ˾�
}
