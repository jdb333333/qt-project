#include "ReadExcelClass.h"

#include <QString>
#include <QMessageBox>
#include <QFileInfo>
#include <QAxObject>

ReadExcelClass::ReadExcelClass():m_ExcelObject(NULL){}

ReadExcelClass::~ReadExcelClass()
{
    if(m_ExcelObject)
    {
        m_ExcelObject->clear();
        m_ExcelObject->deleteLater();
    }
}

bool ReadExcelClass::LoadExcelFile(const QString &file)
{
    QFileInfo info(file);
    if(info.exists() && info.isFile())
    {
        QAxObject* excel = new QAxObject("Excel.Application");
        if(!excel)
        {
            QMessageBox::critical(NULL,"Err","excel loss object!");
            return false;
        }

        excel->dynamicCall("SetVisible(bool)",false);
        QAxObject* workbooks = excel->querySubObject("WorkBooks");
        m_ExcelObject = workbooks->querySubObject("Open(QString,QVariant)",file);
        if(!m_ExcelObject)
        {
            QMessageBox::critical(NULL,"Err","open excel file failed!");
            return false;
        }
        return true;
    }
    return false;
}

bool ReadExcelClass::IsExcelEmpty()
{
    if(m_ExcelObject)
    {
        return m_ExcelObject->isNull();
    }
    return true;
}

int ReadExcelClass::Count()
{
    if(m_ExcelObject)
    {
        QAxObject* sheets = m_ExcelObject->querySubObject("Sheets");
        if(sheets)
            return sheets->property("Count").toInt();
    }
    return 0;
}

void ReadExcelClass::Clear()
{
    if(m_ExcelObject)
    {
        m_ExcelObject->clear();
    }
}

QList<SheetData> ReadExcelClass::AllSheets()
{
    QList<SheetData> resList;
    if(m_ExcelObject)
    {
        int nCount = Count();
        for(int i=0;i<nCount;i++)
        {
            QAxObject* sheet = m_ExcelObject->querySubObject("WorkSheets(int)",i+1);
            if(sheet)
            {
                QString name = sheet->property("Name").toString();
                resList.append(SheetData(i,name));
            }
        }
    }
    return resList;
}

bool ReadExcelClass::IsSheetEmpty(uint sheetIndex)
{
    if(m_ExcelObject)
    {
        QAxObject* sheet = m_ExcelObject->querySubObject("WorkSheets(int)",sheetIndex+1);
        if(!sheet)
            return true;
        else
            return sheet->isNull();
    }
    return true;
}

int ReadExcelClass::Rows(uint sheetIndex)
{
    if(m_ExcelObject)
    {
        QAxObject* sheet = m_ExcelObject->querySubObject("WorkSheets(int)",sheetIndex+1); //工作表第一个从1开始算起，为统一编程，sheetIndex从0开始,下同;
        if(sheet && !sheet->isNull())
        {
            QAxObject* rows = NULL;
            QAxObject* usedrange = sheet->querySubObject("UsedRange");//获取该sheet的使用范围对象;
            if(usedrange && (rows=usedrange->querySubObject("Rows")) )
                return rows->property("Count").toInt();
        }
    }
    return 0;
}

int ReadExcelClass::Columns(uint sheetIndex)
{
    if(m_ExcelObject)
    {
        QAxObject* sheet = m_ExcelObject->querySubObject("WorkSheets(int)",sheetIndex+1);
        if(sheet && !sheet->isNull())
        {
            QAxObject* columns = NULL;
            QAxObject* usedRange = sheet->querySubObject("UsedRange");//获取该sheet的使用范围对象;
            if(usedRange && (columns=usedRange->querySubObject("Columns")) )
                return columns->property("Count").toInt();
        }
    }
    return 0;
}

QList<ExcelData> ReadExcelClass::ReadAll(uint sheetIndex)
{
    QList<ExcelData> resList;
    QAxObject *sheet = NULL;
    if(m_ExcelObject && (sheet=m_ExcelObject->querySubObject("WorkSheets(int)",sheetIndex+1)) )
    {
        QAxObject *usedrange = NULL, *rows = NULL, *columns = NULL;
        if ( (usedrange = sheet->querySubObject("UsedRange"))
            && (rows = usedrange->querySubObject("Rows"))
            && (columns = usedrange->querySubObject("Columns")) )
        {
            int nRowBeg = usedrange->property("Row").toInt(); //工作表中的行起始以1开始算起;
            int nColBeg = usedrange->property("Column").toInt(); //工作表中的列起始以1开始算起;
            int nRowCount = rows->property("Count").toInt();
            int nColCount = columns->property("Count").toInt();
            if(nRowCount>0 && nColCount>0 && nRowBeg>0 && nColBeg>0 )
            {
                for(int i=nRowBeg;i<nRowBeg+nRowCount;i++)
                {
                    for(int j=nColBeg;j<nColBeg+nColCount;j++)
                    {
                        QVariant data = sheet->querySubObject("Cells(int,int)",i,j)->dynamicCall("Value2()");
                        resList.append(ExcelData(i-1,j-1,data)); //工作表中的行列起始以1开始算起,为统一编程，行列均以0开始标记;
                    }
                }
            }
        }
    }
    return resList;
}
