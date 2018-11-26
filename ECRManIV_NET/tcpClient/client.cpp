#include "client.h"
#include "ui_client.h"
#include <QtNetwork>

Client::Client(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Client)
{
    ui->setupUi(this);
    tcpSocket = new QTcpSocket(this);
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(readMessage()));
    connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(displayError(QAbstractSocket::SocketError)));
}

Client::~Client()
{
    delete ui;
}

void Client::newConnect()
{
    // ��ʼ�����ݴ�С��ϢΪ0
    blockSize = 0;
    // ȡ�����е�����
    tcpSocket->abort();
    tcpSocket->connectToHost(ui->hostLineEdit->text(),
                             ui->portLineEdit->text().toInt());
}

void Client::readMessage()
{
    QDataStream in(tcpSocket);
    // �����������汾������Ҫ�ͷ���������ͬ
    in.setVersion(QDataStream::Qt_4_6);
    // ����Ǹտ�ʼ��������
    if (blockSize == 0) {
        //�жϽ��յ������Ƿ�������ֽڣ�Ҳ�����ļ��Ĵ�С��Ϣ��ռ�Ŀռ�
        //������򱣴浽blockSize�����У�����ֱ�ӷ��أ�������������
        if(tcpSocket->bytesAvailable() < (int)sizeof(quint16)) return;
        in >> blockSize;
    }
    // ���û�еõ�ȫ�������ݣ��򷵻أ�������������
    if(tcpSocket->bytesAvailable() < blockSize) return;
    // �����յ������ݴ�ŵ�������
    in >> message;
    // ��ʾ���յ�������
    qDebug() << message;
    ui->messageLabel->setText(message);
}

void Client::displayError(QAbstractSocket::SocketError)
{
    qDebug() << tcpSocket->errorString();
}

// ���Ӱ�ť
void Client::on_connectButton_clicked()
{
    newConnect();
}

