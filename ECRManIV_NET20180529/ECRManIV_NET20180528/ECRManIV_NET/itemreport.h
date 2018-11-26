#ifndef ITEMREPORT_H
#define ITEMREPORT_H

#include <QWidget>

#include "reportdb.h"

namespace Ui {
class itemreport;
}

class itemreport : public QWidget
{
    Q_OBJECT

public:
    explicit itemreport(QWidget *parent = 0);
    ~itemreport();

public:
    void getdatavalue(RData data);

private:
    Ui::itemreport *ui;
};

#endif // ITEMREPORT_H
