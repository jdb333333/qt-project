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
    bool create(const QString& filename = QString());
    bool open(const QString& filename = QString());

    bool setCurrentSheet(int index);

    void readAll(QList<QList<QVariant> > &cells);

    void saveAs(const QString& filename);
    void save();

    void close();

    static QString to26AlphabetString(int data);
    static void convertToColName(int data, QString &res);
    static void castListListVariant2Variant(const QList<QList<QVariant> > &cells,QVariant& res);
    bool writeCurrentSheet(const QList<QList<QVariant> > &cells);
};

#endif // EXCELBASE_H
