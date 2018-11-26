#ifndef EXCELBASEPRIVATE_H
#define EXCELBASEPRIVATE_H

#include <QAxObject>

#define TC_FREE(x)  {delete x; x=NULL;}

class ExcelBase;

class ExcelBasePrivate
{
    Q_DECLARE_PUBLIC(ExcelBase)
public:
    explicit ExcelBasePrivate(ExcelBase* qptr);
    ~ExcelBasePrivate();

    void construct();
    void destory();

    ExcelBase*  const q_ptr;

    QAxObject*  excel;
    QAxObject*  books;
    QAxObject*  book;
    QAxObject*  sheets;
    QAxObject*  sheet;

    QString     filename;
    QString     sheetName;
};

#endif // EXCELBASEPRIVATE_H
