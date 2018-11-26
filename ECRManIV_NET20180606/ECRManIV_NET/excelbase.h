#ifndef EXCELBASE_H
#define EXCELBASE_H

#include <QObject>

class ExcelBasePrivate;

class ExcelBase : public QObject
{
public:
    ExcelBase(QObject* par=NULL);
    ~ExcelBase();

private:
    Q_DISABLE_COPY(ExcelBase)
    Q_DECLARE_PRIVATE(ExcelBase)
    ExcelBasePrivate* const d_ptr;

    bool currentSheet();
    static void castVariant2ListListVariant(const QVariant& var,QList<QList<QVariant> > &res);
    QVariant readAll();

public:
    bool open(const QString& filename = QString());

    bool setCurrentSheet(int index);

    void readAll(QList<QList<QVariant> > &cells);
};

#endif // EXCELBASE_H
