#include "excelbaseprivate.h"
#include "excelbase.h"

#include <ActiveQt/QAxObject>
#include <QDebug>

ExcelBasePrivate::ExcelBasePrivate(ExcelBase *qptr)
    : q_ptr(qptr)
    , excel(NULL)
    , books(NULL)
    , book(NULL)
    , sheets(NULL)
    , sheet(NULL)
{

}

ExcelBasePrivate::~ExcelBasePrivate()
{
    if(excel)
    {
        if (!excel->isNull())
        {
            excel->dynamicCall("Quit()");
        }
    }

    TC_FREE(sheet );
    TC_FREE(sheets);
    TC_FREE(book  );
    TC_FREE(books );
    TC_FREE(excel );
}

void ExcelBasePrivate::construct()
{
    qDebug() << "ExcelBasePrivate::construct";
    destory();
    excel = new QAxObject(q_ptr);
    excel->setControl("Excel.Application");
    excel->setProperty("Visible",false);
    excel->setProperty("DisplayAlerts", false);//不显示任何警告信息。如果为TRUE那么在关闭是会出现类似“文件已修改，是否保存”的提示
    if (excel->isNull())
    {
        qDebug() << "excel->isNull()";
        excel->setControl("ET.Application");
    }
    if (!excel->isNull())
    {
        qDebug() << "!excel->isNull()";
        books = excel->querySubObject("Workbooks");
    }
}

void ExcelBasePrivate::destory()
{
    TC_FREE(sheet );
    TC_FREE(sheets);
    if(book != NULL && !(book->isNull()))
    {
        book->dynamicCall("Close(Boolean)", false);
    }
    TC_FREE(book );
    TC_FREE(books);
    if (excel != NULL && !(excel->isNull()))
    {
        excel->dynamicCall("Quit()");
    }
    TC_FREE(excel);
    filename  = "";
    sheetName = "";
}
