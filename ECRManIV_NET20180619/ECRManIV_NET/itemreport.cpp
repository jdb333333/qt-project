#include "itemreport.h"
#include "ui_itemreport.h"

itemreport::itemreport(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::itemreport)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::Dialog | windowType());

    ui->CcValue->setFocusPolicy(Qt::NoFocus);
    ui->QtyValue->setFocusPolicy(Qt::NoFocus);
    ui->AmtValue->setFocusPolicy(Qt::NoFocus);
    ui->RetValue->setFocusPolicy(Qt::NoFocus);
    ui->DiscValue->setFocusPolicy(Qt::NoFocus);
    ui->CostValue->setFocusPolicy(Qt::NoFocus);
}

void itemreport::getdatavalue(RData data)
{
    this->setWindowTitle(QString("DAILY REPORT"));

    ui->ReportName->setText(QString(QLatin1String(data.Name)));
    ui->CcValue->setText(QString("%1").arg(data.Cc));
    ui->QtyValue->setText(QString("%1").arg(data.Qty));
    ui->AmtValue->setText(QString("%1").arg(data.Amt));
    ui->RetValue->setText(QString("%1").arg(data.Ret));
    ui->DiscValue->setText(QString("%1").arg(data.Disc));
    ui->CostValue->setText(QString("%1").arg(data.Cost));
}

itemreport::~itemreport()
{
    delete ui;
}
