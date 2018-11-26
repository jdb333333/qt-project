#include "csv.h"
#include <QTextStream>
#include <QFile>
#include <QString>
#include <QDebug>
#include <QStringList>

class csvPrivate
{
    csv* Parent;
    QTextStream* m_txt;
    QScopedPointer<QTextStream> m_pfile;
    bool m_isStartLine;
public:
    csvPrivate(csv* p):Parent(p)
      ,m_txt(NULL)
      ,m_pfile(NULL)
      ,m_isStartLine(true)
    {

    }
    void setTextStream(QTextStream* st)
    {
        m_txt = st;
    }
    QTextStream* streamPtr()
    {
        return m_txt;
    }
    QTextStream& stream()
    {
        return (*m_txt);
    }
    const QTextStream& stream() const
    {
        return (*m_txt);
    }
    bool isStartLine() const
    {
        return m_isStartLine;
    }
    void setStartLine(bool on)
    {
        m_isStartLine = on;
    }

    void setFile(QFile *txt)
    {
        m_pfile.reset(new QTextStream(txt));
        m_txt = m_pfile.data();
    }

    QTextStream& formatTextStream()
    {
        if(!isStartLine())
        {
            stream()<<',';
        }
        else
        {
            setStartLine(false);
        }
        return stream();
    }
};

csv::csv(QObject *parent) : QObject(parent)
    ,d_p(new csvPrivate(this))
{

}

csv::~csv()
{

}

void csv::setcsvfile(QFile *txt)
{
    d_p->setFile(txt);
}

int csv::advquoted(const QString &s, QString &fld, int i)
{
    int j;

    fld = "";
    for (j = i; j < s.length()-1; j++)
    {
        if (s[j] == '\"' && s[++j] != '\"')
        {
            int k = s.indexOf (',', j);
            if (k < 0 ) // û�ҵ�����
                k = s.length();
            for (k -= j; k-- > 0; )
                fld += s[j++];
            break;
        }
        fld += s[j];
    }
    return j;
}

int csv::advplain(const QString &s, QString &fld, int i)
{
    int j;

    j = s.indexOf(',', i); // ����,
    if (j < 0) // û�ҵ�
        j = s.length();
    fld = s.mid (i,j-i);//��ȡ����
    return j;
}

/// \brief ��һ��csv��ʽ�����ݽ���
/// \param lineStr
/// \return
QStringList csv::fromCsvLine(const QString &lineStr)
{
    if(lineStr.isEmpty())
    {
        return QStringList();
    }
    QStringList res;
    QString str;
    int i, j=0;
    int col = 0;
    i = 0;
    do {
        if (i < lineStr.length() && lineStr[i] == '\"')
            j = advquoted(lineStr, str, ++i); // skip quote
        else
            j = advplain(lineStr, str, i);
        res.push_back (str);
        ++col;
        i = j + 1;
    } while (j < lineStr.length());
    return res;
}

QTextStream &csv::stream()
{
    return d_p->stream();
}

const QTextStream &csv::stream() const
{
    return d_p->stream();
}

bool csv::atEnd() const
{
    return stream().atEnd();
}

/// \brief ��ȡһ��csv�ļ�
/// \return
QStringList csv::readCsvLine()
{
    return fromCsvLine(stream().readLine());
}

void csv::readCsvData()
{
    QStringList datalist;

    m_varListList->clear();

    while(1)
    {
        if(atEnd())
        {
            break;
        }

        datalist = readCsvLine();
        qDebug() << "--->datalist = " << datalist;
        QVariantList varlist;
        for(int i = 0; i < datalist.size(); i++)
        {
            varlist << datalist.at(i);
        }

        m_varListList->push_back(varlist);
    }
}

/// \brief ���ַ���װ��Ϊ��׼csvһ����Ԫ���ַ�������Ӧ�ַ���ԭ�еĶ��Ż����װ��
///
/// csv��ԭ���ǣ�
///
/// - ����ַ����ж��ţ��������ַ���ǰ��������������
/// - ����ַ���������",����Ҫ���������ű�ʾת��""
/// \param rawStr ԭ������
/// \return ��׼��csv��Ԫ�ַ���
QString csv::toCsvString(const QString &rawStr)
{
    //���Ȳ�����û������,����У���������滻Ϊ��������
    QString res = rawStr;
    res.replace("\"","\"\"");
    if(res.contains(','))
    {
        //����ж��ţ���ǰ����������������Ű���
        res = ('\"' + res + '\"');
    }
    return res;
}

/// \brief ��һ��Ҫ�ö��ŷָ����ַ���ת��Ϊһ�б�׼csv�ַ���
/// \param sectionLine �磺xxx,xxxx,xxxxx ����{'xxx','xxxx','xxxxx'}
/// \return ��׼��csv�ַ����������з�
QString csv::toCsvStringLine(const QStringList &sectionLine)
{
    QString res;
    int size = sectionLine.size();
    for(int i=0;i<size;++i)
    {
        if(0 == i)
        {
            res += toCsvString(sectionLine[i]);
        }
        else
        {
            res += ("," + toCsvString(sectionLine[i]));
        }
    }
    return res;
}

csv &csv::operator <<(const QString &str)
{
    d_p->formatTextStream()<<toCsvString(str);
    return *this;
}

/// \brief ����
void csv::newLine()
{
    d_p->setStartLine(true);
    d_p->stream()<<endl;
}

void csv::writeCsvData()
{
    int rows = m_varListList->size();

    for(int row = 0; row < rows; row++)
    {
        int cols = m_varListList->at(row).size();

        QStringList datalist;
        for(int col = 0; col < cols; col++)
        {
            datalist << m_varListList->at(row).at(col).toString();
        }

        QString datastr = toCsvStringLine(datalist);

        d_p->formatTextStream()<<datastr;
        newLine();
    }
}
