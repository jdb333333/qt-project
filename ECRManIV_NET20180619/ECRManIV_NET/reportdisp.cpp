#include "reportdisp.h"
#include "ui_reportdisp.h"

#include <QDebug>

reportdisp::reportdisp(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::reportdisp)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::Dialog | windowType());
}

void reportdisp::setItemModel(QStandardItemModel *tmpreportModel)
{
    reportModel = tmpreportModel;
    ui->tableView->setModel(reportModel);
    rows_display = 0;

    int width;
    int columns;
    columns = reportModel->columnCount();
    width = ui->tableView->width() / columns;
    qDebug() << "width = " << width << "columns = " << columns;

    //ui->tableView->verticalHeader()->setDefaultSectionSize(width);

#if 1
    for(int count = 0; count < columns; count++)
    {
        //ui->tableView->resizeColumnToContents(count);
        ui->tableView->setColumnWidth(count, width);
    }
#endif

    ui->tableView->horizontalHeader()->setResizeMode(columns - 1, QHeaderView::Stretch);

    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->tableView->verticalHeader()->hide();
}

reportdisp::~reportdisp()
{
    delete ui;
}

void reportdisp::getdatavalue(RData data)
{
    reportModel->insertRow(rows_display);
    reportModel->setData(reportModel->index(rows_display, 0), QString("%1").arg(data.Name));
    reportModel->setData(reportModel->index(rows_display, 1), QString("%1").arg(data.Cc));
    reportModel->setData(reportModel->index(rows_display, 2), QString("%1").arg(data.Qty));
    reportModel->setData(reportModel->index(rows_display, 3), QString("%1").arg(data.Amt));
    reportModel->setData(reportModel->index(rows_display, 4), QString("%1").arg(data.Ret));
    reportModel->setData(reportModel->index(rows_display, 5), QString("%1").arg(data.Disc));
    reportModel->setData(reportModel->index(rows_display, 6), QString("%1").arg(data.Cost));
    //ui->tableView->show();

    rows_display++;
}

void reportdisp::setcenter()
{
    int i, j;
    int rows = ui->tableView->model()->rowCount();
    int columns = ui->tableView->model()->columnCount();

    for(i = 0; i < rows; i++)
    {
        for(j = 0; j < columns; j++)
        {

        }
    }
}
