#include "excelbase.h"
#include "excelbaseprivate.h"

#include <QDebug>

ExcelBase::ExcelBase(QObject* par):QObject(par)
  ,d_ptr(new ExcelBasePrivate(this))
{

}

ExcelBase::~ExcelBase()
{
    close();
    delete d_ptr;
}

void ExcelBase::close()
{
    Q_D(ExcelBase);
    d->destory();
}

bool ExcelBase::create(const QString& filename)
{
    bool ret = false;
    Q_D(ExcelBase);
    d->construct();
    if (d->books != NULL && ! d->books->isNull())
    {
        d->books->dynamicCall("Add");
        d->book   = d->excel->querySubObject("ActiveWorkBook");
        d->sheets = d->book->querySubObject("WorkSheets");
        currentSheet();
        d->filename = filename;
        ret = true;
    }

    return ret;
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
        ret = d->book != NULL && !(d->book->isNull());
        if(ret)
        {
            d->sheets = d->book->querySubObject("WorkSheets");
            d->filename = filename;
            currentSheet();
        }
    }

    return ret;
}

void ExcelBase::saveAs(const QString& filename)
{
    Q_D(ExcelBase);
    if (d->book != NULL && !(d->book->isNull()))
    {
        d->filename = filename;
        QString strPath = d->filename;
        strPath = strPath.replace('/','\\');
        qDebug()<<strPath;
        d->book->dynamicCall("SaveAs(const QString&,int,const QString&,const QString&,bool,bool)", strPath
                             ,56,QString(""),QString(""),false,false);
    }
}

void ExcelBase::save()
{
    Q_D(ExcelBase);
    if(d->filename.isEmpty())
        return;

    saveAs(d->filename);
}

bool ExcelBase::currentSheet()
{
    bool ret = false;

    Q_D(ExcelBase);
    TC_FREE(d->sheet);
    if (d->excel != NULL && !(d->excel->isNull()))
    {
        TC_FREE(d->sheet);
        d->sheet = d->excel->querySubObject("ActiveWorkBook");
        ret = d->sheet != NULL && !(d->sheet->isNull());
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
        ret = d->sheet != NULL && !(d->sheet->isNull());
        if(ret)
        {
            d->sheet->dynamicCall("Activate(void)");
        }
        d->sheetName = ret ? d->sheet->property("Name").toString() : "";
    }
    return ret;
}

void ExcelBase::castListListVariant2Variant(const QList<QList<QVariant> > &cells, QVariant &res)
{
    QVariantList vars;
    const int rows = cells.size();
    for(int i=0;i<rows;++i)
    {
        vars.append(QVariant(cells[i]));
    }
    res = QVariant(vars);
}

QString ExcelBase::to26AlphabetString(int data)
{
    QChar ch = data + 0x40; //A¶ÔÓ¦0x41
    return QString(ch);
}

void ExcelBase::convertToColName(int data, QString &res)
{
    Q_ASSERT(data>0 && data<65535);
    int tempData = data / 26;
    if(tempData > 0)
    {
        int mode = data % 26;
        convertToColName(mode,res);
        convertToColName(tempData,res);
    }
    else
    {
        res=(to26AlphabetString(data)+res);
    }
}

bool ExcelBase::writeCurrentSheet(const QList<QList<QVariant> > &cells)
{
    Q_D(ExcelBase);
    if(cells.size() <= 0)
        return false;

    if(NULL == d->sheet || d->sheet->isNull())
        return false;

    int row = cells.size();
    int col = cells.at(0).size();

    //qDebug() << "------>row = " << row << "col = " << col;

    QString rangStr;
    convertToColName(col,rangStr);
    //qDebug() << "------>rangStr = " << rangStr;
    rangStr += QString::number(row);
    //qDebug() << "------>rangStr = " << rangStr;
    rangStr = "A1:" + rangStr;
    qDebug()<<rangStr;
    QAxObject *range = d->sheet->querySubObject("Range(const QString&)",rangStr);
    //QAxObject *range = d->sheet->querySubObject("Cells(int,int)", 1, 1);
    if(NULL == range || range->isNull())
    {
        return false;
    }

    bool succ = false;
    QVariant var;
    castListListVariant2Variant(cells,var);
    //qDebug() << "------>var = " << var;
    //succ = range->setProperty("Value", var);
    //succ = range->setProperty("Value", "this is a test");
    //range->dynamicCall("Value", "write data test");
    range->dynamicCall("SetValue(const QVariant&)", var);

    delete range;
    return succ;
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
    if(d->sheet != NULL && !(d->sheet->isNull()))
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
