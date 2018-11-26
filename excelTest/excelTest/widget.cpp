#include "widget.h"
#include "ui_widget.h"

#include <QFileDialog>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    QString FilePath = QFileDialog :: getOpenFileName(this, NULL, NULL, "All File(*.*)");
    if(FilePath!=""){
        eetest.Open(FilePath,1,false);
        eetest.ReadDataToTable(ui->tableWidget);
    }
}

void Widget::on_pushButton_2_clicked()
{
//    eetest.Open("a.xlsx",1,false);
    eetest.SaveDataFrTable(ui->tableWidget);
}
