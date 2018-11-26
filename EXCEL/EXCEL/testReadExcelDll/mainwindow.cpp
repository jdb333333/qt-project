#include "mainwindow.h"

#include <QLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QFileDialog>
#include <QTabWidget>
#include <QTableWidget>
#include <QTableWidgetItem>

#include <QMessageBox>
#include "ReadExcelClass.h"

MainWindow::MainWindow(QWidget *parent)  : QWidget(parent)
{
    m_LineEdit = new QLineEdit(this);
    m_TabWidget = new QTabWidget();
    QPushButton* openBtn = new QPushButton("Open...",this);

    QVBoxLayout* mainLayout = new QVBoxLayout;
    QHBoxLayout* hLayout = new QHBoxLayout;
    hLayout->addWidget(m_LineEdit);
    hLayout->addWidget(openBtn);
    mainLayout->addWidget(m_TabWidget);
    mainLayout->addLayout(hLayout);
    mainLayout->setMargin(0);
    mainLayout->setSpacing(5);
    this->setLayout(mainLayout);

    connect(openBtn,SIGNAL(clicked()),this, SLOT(slot1()));

    connect(m_LineEdit,SIGNAL(returnPressed()), this, SLOT(slot2()));

    this->resize(500,350);
}

MainWindow::~MainWindow()
{

}

void MainWindow::slot1()
{
    QString file = QFileDialog::getOpenFileName(this,"load excel file",".","Excel(*.xls *.xlsx)");
    if(!file.isEmpty())
    {
        m_LineEdit->setText(file);
        ReadExcel(file);
    }
}

void MainWindow::slot2()
{
    QString file = m_LineEdit->text();
    if(!file.trimmed().isEmpty())
    {
        ReadExcel(file);
    }
}

void MainWindow::ReadExcel(const QString &file)
{
    ReadExcelClass re;
    if(re.LoadExcelFile(file))
    {
        ClearAll();
        ShowExcelData(&re);
    }
}

void MainWindow::ClearAll()
{
    if(m_TabWidget && m_TabWidget->count()>0)
    {
        m_TabWidget->clear();
    }
}

void MainWindow::ShowExcelData(ReadExcelClass *re)
{
    QList<SheetData> sheetList = re->AllSheets();
    if(sheetList.count()>0)
    {
        for(int i=0;i<sheetList.count();i++)
        {
            SheetData data = sheetList[i];
            AddTabWidget(re,data.Index,data.Name);
        }
    }
}

void MainWindow::AddTabWidget(ReadExcelClass *re, uint sheetIndex,const QString& sheetName)
{
    int rows = re->Rows(sheetIndex);
    int cols = re->Columns(sheetIndex);
    QList<ExcelData> dataList = re->ReadAll(sheetIndex);
    int nCount = dataList.count();
    if(nCount>0)
    {
        QTableWidget *wdt = new QTableWidget(rows,cols);
        wdt->setEditTriggers(QAbstractItemView::NoEditTriggers); //禁止编辑;
        wdt->setSelectionBehavior(QAbstractItemView::SelectRows);//整行选择;
        wdt->setSelectionMode(QAbstractItemView::ExtendedSelection);//设置为可以选中多个目标;
        for(int i=0;i<nCount;i++)
        {
            ExcelData data = dataList[i];
            QTableWidgetItem* item = new QTableWidgetItem;
            item->setData(Qt::DisplayRole,data.Data);
            wdt->setItem(data.Row,data.Col,item);
        }
        m_TabWidget->addTab(wdt,sheetName);
    }
}

