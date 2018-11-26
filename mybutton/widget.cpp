#include "widget.h"
#include "ui_widget.h"

#include "button/switchbutton.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    SwitchButton *mybtn = new SwitchButton(this);
    mybtn->setGeometry(50, 270, 101, 23);
    //mybtn->show();
}

Widget::~Widget()
{
    delete ui;
}
