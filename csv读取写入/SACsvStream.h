#ifndef QCSVSTREAM_H
#define QCSVSTREAM_H

class QTextStream;
class QFile;
class SACsvStreamPrivate;
#include "SALibGlobal.h"
#include <QString>
///
/// \brief дcsv�ļ���֧��
/// \author czy
/// \date 2016-08-10
///
class SALIB_EXPORT SACsvStream
{
public:
    SACsvStream(QTextStream* txt);
    SACsvStream(QFile* txt);
    virtual ~SACsvStream();
    //ת��Ϊ��ʶcsv�ַ�
    static QString toCsvString(const QString& rawStr);
    //��һ��Ҫ�ö��ŷָ����ַ���ת��Ϊһ�б�׼csv�ַ���
    static QString toCsvStringLine(const QStringList& sectionLine);
    //����һ��csv�ַ�
    static QStringList fromCsvLine(const QString &lineStr);
    SACsvStream & operator << (const QString &str);
    SACsvStream & operator << (int d);
    SACsvStream & operator << (double d);
    SACsvStream & operator << (float d);
    //����һ��
    void newLine();
    //��ȡ���������
    QTextStream* streamPtr() const;
    QTextStream& stream();
    const QTextStream& stream() const;
    //��ȡ������һ��csv�ַ���
    QStringList readCsvLine();
    //�ж��Ƿ��ļ�ĩ��
    bool atEnd() const;
private:
    static int advquoted(const QString &s, QString &fld, int i);
    static int advplain(const QString &s, QString &fld, int i);
private:

    QScopedPointer<SACsvStreamPrivate> d_p;
};
typedef SACsvStream & (*SACsvWriterFunction)(SACsvStream &);
inline SACsvStream &operator<<(SACsvStream &s, SACsvWriterFunction f)
{
    return (*f)(s);
}
SALIB_EXPORT SACsvStream &endl(SACsvStream &s);

#endif // QCSVSTREAM_H