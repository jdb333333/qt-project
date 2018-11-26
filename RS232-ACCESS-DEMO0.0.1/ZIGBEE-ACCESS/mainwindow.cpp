#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDateTime>
#include <QString>
#include <QtCore/QDebug>
//FOR RS232
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->ui_init();
    this->threadA.changeTxState(false);
    this->threadA.TxData.clear();
    connect(&this->threadA, SIGNAL(comRecive()), this, SLOT(displayRxData()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ui_init(void)
{
    // Example use QSerialPortInfo

    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        qDebug() << "Name        : " << info.portName();
        qDebug() << "Description : " << info.description();
        qDebug() << "Manufacturer: " << info.manufacturer();

        // Example use QSerialPort
        QSerialPort serial;
        serial.setPort(info);
        if (serial.open(QIODevice::ReadWrite))
        {
           ui->comboBox->addItem(info.portName());
            serial.close();
        }
    }
}

void MainWindow::on_pushButton_8_clicked()
{
//    accept();
}

void MainWindow::on_pushButton_cmopen_clicked()
{
    if(ui->comboBox->currentIndex()!=0)
    {
        //start recive thread
        threadA.startCom();
        qDebug() << "Brush:" <<"thread starting";
        threadA.setPortnum(ui->comboBox->currentText());
        threadA.changeComState(false);
        threadA.start();
        ui->textEdit_tx->append("串口打开完成");

    }else
    {
        QMessageBox::information(this,tr("Tips"),tr("请选择串口号"),QMessageBox::Yes);
    }

}

void MainWindow::on_pushButton_comclose_clicked()
{
    qDebug() << "Brush:" <<"thread1 stoping";
    threadA.stop();
    qDebug() << "Brush:" <<"com close";
    ui->textEdit_tx->append("串口关闭完成");
}

void MainWindow::on_pushButton_open_clicked()
{
    QByteArray Qarr;
    char var,tmp[100];
    char *buf;
    char cmdCloseDoor[20]={0x01,0x00,0x03,0x01,0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x31};
    QString str="open door: ";
    QDateTime *datatime=new QDateTime(QDateTime::currentDateTime());

    if(ui->radioButton_31->isChecked())cmdCloseDoor[19]=0x31;
     if(ui->radioButton_01->isChecked())cmdCloseDoor[19]=0x01;
      if(ui->radioButton_02->isChecked())cmdCloseDoor[19]=0x02;
       if(ui->radioButton_07->isChecked())cmdCloseDoor[19]=0x07;
        if(ui->radioButton_0D->isChecked())cmdCloseDoor[19]=0x0d;
         if(ui->radioButton_13->isChecked())cmdCloseDoor[19]=0x13;
          if(ui->radioButton_19->isChecked())cmdCloseDoor[19]=0x19;
           if(ui->radioButton_1F->isChecked())cmdCloseDoor[19]=0x1F;

   str+=datatime->time().toString();
   ui->textEdit_tx->append(str);
   str.clear();
   Qarr.append(cmdCloseDoor,20);

   buf=Qarr.data();
   for(var=0;var<20;var++)
   {
       ::snprintf(tmp,100, "%02X", (unsigned char)(*buf));
       buf++;
       str+=QString::fromUtf8(tmp);
       str+=" ";
   }
     ui->textEdit_tx->append(str);
     this->threadA.TxData.clear();
    this->threadA.TxData.append(cmdCloseDoor,20);
    this->threadA.changeTxState(true);

}

void MainWindow::on_pushButton_close_clicked()
{

    QByteArray Qarr;
    char var,tmp[100];
    char *buf;
    char cmdCloseDoor[20]={0x01,0x00,0x04,0x01,0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x31};
    QString str="close door: ";
    QDateTime *datatime=new QDateTime(QDateTime::currentDateTime());

    if(ui->radioButton_31->isChecked())cmdCloseDoor[19]=0x31;
     if(ui->radioButton_01->isChecked())cmdCloseDoor[19]=0x01;
      if(ui->radioButton_02->isChecked())cmdCloseDoor[19]=0x02;
       if(ui->radioButton_07->isChecked())cmdCloseDoor[19]=0x07;
        if(ui->radioButton_0D->isChecked())cmdCloseDoor[19]=0x0d;
         if(ui->radioButton_13->isChecked())cmdCloseDoor[19]=0x13;
          if(ui->radioButton_19->isChecked())cmdCloseDoor[19]=0x19;
           if(ui->radioButton_1F->isChecked())cmdCloseDoor[19]=0x1F;

   str+=datatime->time().toString();
   ui->textEdit_tx->append(str);
   str.clear();
   Qarr.append(cmdCloseDoor,20);

   buf=Qarr.data();
   for(var=0;var<20;var++)
   {
       ::snprintf(tmp,100, "%02X", (unsigned char)(*buf));
       buf++;
       str+=QString::fromUtf8(tmp);
       str+=" ";
   }
     ui->textEdit_tx->append(str);
     this->threadA.TxData.clear();
    this->threadA.TxData.append(cmdCloseDoor,20);
    this->threadA.changeTxState(true);

}

void MainWindow::on_pushButton_clear_clicked()
{
    ui->textEdit_tx->clear();
    ui->textEdit_rx->clear();
}

void MainWindow::on_pushButton_add_clicked()
{
    QByteArray Qarr;
    char var,tmp[100];
    char *buf;
    char cmdCloseDoor[20]={0x01,0x00,0x01,0x04,0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x31};
    QString str="close door: ";
    QDateTime *datatime=new QDateTime(QDateTime::currentDateTime());
    QString str1="加卡: ";
    QString card;
    QStringList cardNum;
    if(!ui->lineEdit_carnum->text().isEmpty())
    {
        str1+=datatime->time().toString();
        ui->textEdit_tx->append(str1);
     //   card=ui->lineEdit_doornum->text().trimmed();
     //   cardNum=card.split(" ");
     //   cmdCloseDoor[6]=cardNum.value(0).TO

        if(ui->radioButton_31->isChecked())cmdCloseDoor[19]=0x31;
         if(ui->radioButton_01->isChecked())cmdCloseDoor[19]=0x01;
          if(ui->radioButton_02->isChecked())cmdCloseDoor[19]=0x02;
           if(ui->radioButton_07->isChecked())cmdCloseDoor[19]=0x07;
            if(ui->radioButton_0D->isChecked())cmdCloseDoor[19]=0x0d;
             if(ui->radioButton_13->isChecked())cmdCloseDoor[19]=0x13;
              if(ui->radioButton_19->isChecked())cmdCloseDoor[19]=0x19;
               if(ui->radioButton_1F->isChecked())cmdCloseDoor[19]=0x1F;

               str.clear();
               Qarr.append(cmdCloseDoor,20);

               buf=Qarr.data();
               for(var=0;var<20;var++)
               {
                   ::snprintf(tmp,100, "%02X", (unsigned char)(*buf));
                   buf++;
                   str+=QString::fromUtf8(tmp);
                   str+=" ";
               }
                 ui->textEdit_tx->append(str);
                 this->threadA.TxData.clear();
                this->threadA.TxData.append(cmdCloseDoor,20);
                this->threadA.changeTxState(true);
    }else
    {
        QMessageBox::information(this,tr("Tips"),tr("pls input cardnum"),QMessageBox::Yes);

    }

}

void MainWindow::on_pushButton_delete_clicked()
{
    QDateTime *datatime=new QDateTime(QDateTime::currentDateTime());
    QString str1="删卡: ";
     if(!ui->lineEdit_carnum->text().isEmpty())
        {
            str1+=datatime->time().toString();
            ui->textEdit_tx->append(str1);
        }else
     {

         QMessageBox::information(this,tr("Tips"),tr("pls input card num"),QMessageBox::Yes);
     }
}

void MainWindow::on_pushButton_update_clicked()
{
    QDateTime *datatime=new QDateTime(QDateTime::currentDateTime());
    QString str1="更新门号: ";
    if(!ui->lineEdit_doornum->text().isEmpty())
    {
        str1+=datatime->time().toString();
        ui->textEdit_tx->append(str1);
    }else
    {


    }

}

void MainWindow::on_pushButton_exit_clicked()
{
    qDebug() << "Brush:" <<"thread1 stoping";
    threadA.stop();
    threadA.quit();
    threadA.exit(0);
    threadA.wait();
    qDebug() << "Brush:" <<"thread1 stoped";
}
void MainWindow::displayRxData()
{
    QString str;
    char tmp[100];
    char *buf;
    char var;
    QDateTime *datatime=new QDateTime(QDateTime::currentDateTime());
    if(threadA.requestData.size()>0)
   {
        str="收到数据: ";
        str+=datatime->time().toString();
        ui->textEdit_rx->append(str);
        str.clear();

        buf=threadA.requestData.data();
        qDebug() << "receive num:" <<threadA.requestData.size();
        for(var=0;var<threadA.requestData.size();var++)
        {
            ::snprintf(tmp,100, "%02X", (unsigned char)(*buf));
            buf++;
            str+=QString::fromUtf8(tmp);
            str+=" ";
        }
        ui->textEdit_rx->append(str);
    }
    threadA.requestData.clear();
}

void MainWindow::on_pushButton_send_clicked()
{


}


void MainWindow::on_radioButton_01_clicked()
{
    ui->lineEdit_netid->setText("00 01");
}

void MainWindow::on_radioButton_31_clicked()
{
    ui->lineEdit_netid->setText("00 31");
}

void MainWindow::on_radioButton_07_clicked()
{
    ui->lineEdit_netid->setText("00 07");
}

void MainWindow::on_radioButton_19_clicked()
{
    ui->lineEdit_netid->setText("00 19");
}

void MainWindow::on_radioButton_1F_clicked()
{
  ui->lineEdit_netid->setText("00 1F");
}

void MainWindow::on_radioButton_0D_clicked()
{
   ui->lineEdit_netid->setText("00 0D");
}

void MainWindow::on_radioButton_13_clicked()
{
   ui->lineEdit_netid->setText("00 13");
}

void MainWindow::on_radioButton_02_clicked()
{
     ui->lineEdit_netid->setText("00 02");
}

void MainWindow::on_textEdit_rx_textChanged()
{

}
