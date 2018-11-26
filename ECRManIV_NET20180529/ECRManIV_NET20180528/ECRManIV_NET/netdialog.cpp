#include "netdialog.h"
#include "ui_netdialog.h"

#include <QDebug>

NetDialog::NetDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NetDialog)
{
    ui->setupUi(this);

    QRegExp rx("^((2[0-4]\\d|25[0-5]|[01]?\\d\\d?)\\.){3}(2[0-4]\\d|25[0-5]|[01]?\\d\\d?)$");
    QRegExpValidator *m_IPValidator = new QRegExpValidator(rx, this);
    ui->lineEdit->setValidator(m_IPValidator);

    connect(this, SIGNAL(getipinfo(int,int,int,int)), parent, SLOT(getipitem(int,int,int,int)));
    connect(this, SIGNAL(setlocalip(int,int,int,int)), parent, SLOT(setlocalip(int,int,int,int)));

    iptype = 0;
}

NetDialog::~NetDialog()
{
    delete ui;
}

void NetDialog::on_buttonBox_accepted()
{
    int ip1, ip2, ip3, ip4;
    int k;
    QStringList ip_info = ui->lineEdit->text().split(".");

    k = ip_info.size();
    //qDebug() << "ipnum = " << k;

    if(k == 4)
    {
        ip1 = ip_info.at(0).toInt();
        ip2 = ip_info.at(1).toInt();
        ip3 = ip_info.at(2).toInt();
        ip4 = ip_info.at(3).toInt();

        //QString IP = QString("%1.%2.%3.%4").arg(ip1).arg(ip2).arg(ip3).arg(ip4);

        //qDebug() << IP;

        if(iptype == 1)
        {
            emit getipinfo(ip1, ip2, ip3, ip4);
        }
        else if(iptype == 2)
        {
            emit setlocalip(ip1, ip2, ip3, ip4);
        }
    }
}
