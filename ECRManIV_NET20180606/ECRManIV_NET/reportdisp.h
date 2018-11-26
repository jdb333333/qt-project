#ifndef REPORTDISP_H
#define REPORTDISP_H

#include <QWidget>
#include <QStandardItemModel>

#include "reportdb.h"

namespace Ui {
class reportdisp;
}

class reportdisp : public QWidget
{
    Q_OBJECT

public:
    explicit reportdisp(QWidget *parent = 0);
    void setItemModel(QStandardItemModel *tmpreportModel);
    ~reportdisp();

private:
    Ui::reportdisp *ui;

    int rows_display;

    QStandardItemModel *reportModel;

public:
    void getdatavalue(RData data);
    void setcenter();
};

#endif // REPORTDISP_H
