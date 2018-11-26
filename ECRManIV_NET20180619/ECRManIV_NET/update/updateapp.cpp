#include "updateapp.h"
#include <QFile>
#include <QFileDialog>
#include <QDebug>

updateapp::updateapp(QObject *parent) : QObject(parent)
{

}

updateapp::~updateapp()
{

}

void updateapp::openfile()
{
    //QString fileName = QFileDialog::getOpenFileName(this,"Open File",QDir::currentPath(), "*.hex");
    //QString fileName = QFileDialog::getOpenFileName(this,QString(),QString(),"hex file(*.hex)");
    /*
    QString fileName = QFileDialog::getOpenFileName(this,QString(),QString(),"csv file(*.csv)");
    QFile file(fileName);
    if(file.open(QIODevice::ReadOnly)){
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
      }
      */
}
