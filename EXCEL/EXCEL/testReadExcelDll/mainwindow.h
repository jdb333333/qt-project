#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

class ReadExcelClass;
class QLineEdit;
class QTabWidget;
class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    void ClearAll();
    void ReadExcel(const QString& file);
    void ShowExcelData(ReadExcelClass* re);
    void AddTabWidget(ReadExcelClass* re,uint sheetIndex,const QString& sheetName);
private:
    QLineEdit*      m_LineEdit;
    QTabWidget*     m_TabWidget;

private slots:
    void slot1();
    void slot2();
};

#endif // MAINWINDOW_H
