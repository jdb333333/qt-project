#ifndef CSV_H
#define CSV_H

#include <QObject>

#include <QList>
#include <QVariant>

class csvPrivate;
class QFile;
class QTextStream;

class csv : public QObject
{
    Q_OBJECT
public:
    explicit csv(QObject *parent = 0);
    ~csv();

    void setcsvfile(QFile *txt);
    void setcsvdataptr(QList<QList<QVariant> >* varListList){m_varListList = varListList;}

    void readCsvData();
    void writeCsvData();

    csv & operator << (const QString &str);

private:
    int advquoted(const QString &s, QString &fld, int i);
    int advplain(const QString &s, QString &fld, int i);
    QStringList fromCsvLine(const QString &lineStr);

    //ת��Ϊ��ʶcsv�ַ�
    QString toCsvString(const QString& rawStr);
    //��һ��Ҫ�ö��ŷָ����ַ���ת��Ϊһ�б�׼csv�ַ���
    QString toCsvStringLine(const QStringList& sectionLine);
    //����
    void newLine();

    //��ȡ���������
    QTextStream& stream();
    const QTextStream& stream() const;

    QStringList readCsvLine();
    bool atEnd() const;
private:
    QScopedPointer<csvPrivate> d_p;
    QList<QList<QVariant> >* m_varListList;

signals:

public slots:
};

#endif // CSV_H
