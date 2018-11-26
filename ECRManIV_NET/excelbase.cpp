#include "excelbase.h"
#include "excelbaseprivate.h"

#include <QDebug>

ExcelBase::ExcelBase(QObject* par):QObject(par)
  ,d_ptr(new ExcelBasePrivate(this))
{

}

ExcelBase::~ExcelBase()
{

}

bool ExcelBase::open(const QString& filename)
{
    bool ret = false;

    qDebug() << "ExcelBase::open " <<filename;

    Q_D(ExcelBase);
    d->construct();
    if ( d->books != NULL && ! d->books->isNull() )
    {
        d->book = d->books->querySubObject("Open(QString, QVariant)", filename, 0);
        ret = d->book != NULL && ! d->book->isNull();
        if ( ret )
        {
            d->sheets = d->book->querySubObject("WorkSheets");
            d->filename = filename;
            currentSheet();
        }
    }

    return ret;
}

bool ExcelBase::currentSheet()
{
    bool ret = false;

    Q_D(ExcelBase);
    TC_FREE(d->sheet);
    if (d->excel != NULL && !d->excel->isNull())
    {
        TC_FREE(d->sheet);
        d->sheet = d->excel->querySubObject("ActiveWorkBook");
        ret = d->sheet != NULL && !d->sheet->isNull();
        d->sheetName = ret ? d->sheet->property("Name").toString() : "";
    }

    return ret;
}

bool ExcelBase::setCurrentSheet(int index)
{
    bool ret = false;
    Q_D(ExcelBase);
    if (d->sheets != NULL && !d->sheets->isNull())
    {
        TC_FREE(d->sheet);
        d->sheet = d->sheets->querySubObject("Item(int)", index);
        ret = d->sheet != NULL && ! d->sheet->isNull();
        if(ret)
        {
            d->sheet->dynamicCall("Activate(void)");
        }
        d->sheetName = ret ? d->sheet->property("Name").toString() : "";
    }
    return ret;
}

void ExcelBase::castVariant2ListListVariant(const QVariant &var, QList<QList<QVariant> > &res)
{
    QVariantList varRows = var.toList();
    if(varRows.isEmpty())
    {
        return;
    }
    const int rowCount = varRows.size();
    QVariantList rowData;
    for(int i=0;i<rowCount;++i)
    {
        rowData = varRows[i].toList();
        res.push_back(rowData);
    }
}

QVariant ExcelBase::readAll()
{
    QVariant var;
    Q_D(ExcelBase);
    if (d->sheet != NULL && ! d->sheet->isNull())
    {
        QAxObject *usedRange = d->sheet->querySubObject("UsedRange");
        if(NULL == usedRange || usedRange->isNull())
        {
            return var;
        }
        var = usedRange->dynamicCall("Value");
        delete usedRange;
    }

    return var;
}

void ExcelBase::readAll(QList<QList<QVariant> > &cells)
{
    castVariant2ListListVariant(readAll(),cells);
}
