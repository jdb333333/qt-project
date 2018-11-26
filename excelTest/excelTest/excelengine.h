#ifndef EXCELENGINE_H
#define EXCELENGINE_H

#include <QAxObject>
#include <QDebug>
#include <QString>
#include <QTableWidget>
#include <QStringList>
#include "qt_windows.h"
#include <QFile>
class ExcelEngine
{
public:
    ExcelEngine();
    ExcelEngine(QString xlsFile);
    ~ExcelEngine();
    bool Open(UINT nSheet, bool visible);
    bool Open(QString xlsFile, UINT nSheet, bool visible);
    void Save();
    void Close();
    void Clear();
    bool SaveDataFrTable(QTableWidget *tableWidget);
    bool ReadDataToTable(QTableWidget *tableWidget);
    QVariant GetCellData(UINT row, UINT column);
    bool SetCellData(UINT row, UINT column, QVariant data);
    bool IsOpen();
    bool IsValid();
    UINT GetRowCount()const;
    UINT GetColumnCount()const;
private:
    QAxObject* pExcel;
    QAxObject* pWorkbooks;
    QAxObject* pWorkbook;
    QAxObject* pWorksheet;
    QString sXlsFile;
    int nRowCount;
    int nColumnCount;
    int nStartRow;
    int nStartColumn;
    int nCurrSheet;
    bool bIsOpen;
    bool bIsValid;
    bool bIsANewFile;
    bool bIsSaveAlready;
    bool bIsVisible;


};

#endif // EXCELENGINE_H
