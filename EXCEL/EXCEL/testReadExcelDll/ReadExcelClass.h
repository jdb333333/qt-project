#ifndef READEXCELCLASS_H
#define READEXCELCLASS_H

//#include "readexcelclass_global.h"

#include <QtCore/qglobal.h>

#if defined(READEXCELCLASS_LIBRARY)
#  define READEXCELCLASSSHARED_EXPORT Q_DECL_EXPORT
#else
#  define READEXCELCLASSSHARED_EXPORT Q_DECL_IMPORT
#endif

#include <QVariant>
#include <QString>

struct SheetData
{
    SheetData():Index(0),Name(""){}
    SheetData(uint index,const QString& name)
    {
        Index = index; Name = name;
    }
    uint    Index;
    QString Name;
};
struct ExcelData
{
    ExcelData():Row(0),Col(0),Data(QVariant()){}
    ExcelData(uint row,uint col,const QVariant& data)
    {
        Row = row; Col = col; Data = data;
    }
    uint Row;
    uint Col;
    QVariant Data;
};

class QAxObject;
class READEXCELCLASSSHARED_EXPORT ReadExcelClass
{
public:
    ReadExcelClass();
    ~ReadExcelClass();

public: //about excel;
    bool                LoadExcelFile(const QString& file); //加载excel文件;
    bool                IsExcelEmpty(); //excel文件是否为空;
    int                 Count(); //excel文件中有多少个sheet;
    void                Clear(); //清空excel对象;
    QList<SheetData>    AllSheets(); //获取所有sheet的名称;
public: //about sheet;
    bool                IsSheetEmpty(uint sheetIndex); //判断sheet是否为空;
    int                 Rows(uint sheetIndex); //sheetIndex从0开始,表示第几个工作表(sheet)共有多少行;
    int                 Columns(uint sheetIndex); //sheetIndex从0开始，表示第几个工作表(sheet)共有多少列;
    QList<ExcelData>    ReadAll(uint sheetIndex);//sheetIndex从0开始;表示读取第几个表单/工作表(sheet)的所有内容;
private:
    QAxObject*      m_ExcelObject; //excel对象;
};

#endif // READEXCELCLASS_H
