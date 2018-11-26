#include "SACsvStream.h"
#include <QTextStream>
#include <QFile>
class SACsvStreamPrivate
{
    SACsvStream* Parent;
    QTextStream* m_txt;
    QScopedPointer<QTextStream> m_pfile;
    bool m_isStartLine;
public:
    SACsvStreamPrivate(SACsvStream* p):Parent(p)
      ,m_txt(nullptr)
      ,m_pfile(nullptr)
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



SACsvStream::SACsvStream(QTextStream* txt)
    :d_p(new SACsvStreamPrivate(this))
{
    d_p->setTextStream(txt);
}

SACsvStream::SACsvStream(QFile *txt)
    :d_p(new SACsvStreamPrivate(this))
{
    d_p->setFile(txt);
}

SACsvStream::~SACsvStream()
{

}
///
/// \brief ���ַ���װ��Ϊ��׼csvһ����Ԫ���ַ�������Ӧ�ַ���ԭ�еĶ��Ż����װ��
///
/// csv��ԭ���ǣ�
///
/// - ����ַ����ж��ţ��������ַ���ǰ��������������
/// - ����ַ���������",����Ҫ���������ű�ʾת��""
/// \param rawStr ԭ������
/// \return ��׼��csv��Ԫ�ַ���
///
QString SACsvStream::toCsvString(const QString &rawStr)
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
///
/// \brief ��һ��Ҫ�ö��ŷָ����ַ���ת��Ϊһ�б�׼csv�ַ���
/// \param sectionLine �磺xxx,xxxx,xxxxx ����{'xxx','xxxx','xxxxx'}
/// \return ��׼��csv�ַ����������з�
///
QString SACsvStream::toCsvStringLine(const QStringList &sectionLine)
{
    QString res;
    int size = sectionLine.size();
    for(int i=0;i<size;++i)
    {
        if(0 == i)
        {
            res += SACsvStream::toCsvString(sectionLine[i]);
        }
        else
        {
            res += ("," + SACsvStream::toCsvString(sectionLine[i]));
        }
    }
    return res;
}
///
/// \brief ��һ��csv��ʽ�����ݽ���
/// \param lineStr
/// \return
///
QStringList SACsvStream::fromCsvLine(const QString &lineStr)
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
///
/// \brief дcsv�ļ����ݣ��ַ����Զ�ת��Ϊcsv�ļ�֧�ֵ��ַ���������Ҫת��
///
/// ����csv�ļ���
/// \par
/// 12,txt,23,34
/// 45,num,56,56
/// д��ķ���Ϊ��
/// \code
/// .....
/// QCsvWriter csv(&textStream);
/// csv<<"12"<<"txt"<<"23";
/// csv.endLine("34");
/// csv<<"45"<<"num"<<"56";
/// csv.endLine("56");
/// \endcode
///
/// \param str ��Ҫд���csv�ļ�һ����Ԫ���ַ���
/// \return
///
SACsvStream &SACsvStream::operator <<(const QString &str)
{
    d_p->formatTextStream()<<toCsvString(str);
    return *this;
}

SACsvStream &SACsvStream::operator <<(int d)
{
    d_p->formatTextStream()<<d;
    return *this;
}

SACsvStream &SACsvStream::operator <<(double d)
{
    d_p->formatTextStream()<<d;
    return *this;
}

SACsvStream &SACsvStream::operator <<(float d)
{
    d_p->formatTextStream()<<d;
    return *this;
}

///
/// \brief ����
///
void SACsvStream::newLine()
{
    d_p->setStartLine(true);
    d_p->stream()<<endl;
}

QTextStream *SACsvStream::streamPtr() const
{
    return d_p->streamPtr();
}

QTextStream &SACsvStream::stream()
{
    return d_p->stream();
}


const QTextStream &SACsvStream::stream() const
{
    return d_p->stream();
}
///
/// \brief ��ȡһ��csv�ļ�
/// \return
///
QStringList SACsvStream::readCsvLine()
{
    return fromCsvLine(stream().readLine());
}

bool SACsvStream::atEnd() const
{
    return stream().atEnd();
}

int SACsvStream::advquoted(const QString &s, QString &fld, int i)
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

int SACsvStream::advplain(const QString &s, QString &fld, int i)
{
    int j;

    j = s.indexOf(',', i); // ����,
    if (j < 0) // û�ҵ�
        j = s.length();
    fld = s.mid (i,j-i);//��ȡ����
    return j;
}

///
/// \brief endl
/// \param s
/// \return
///
SACsvStream &endl(SACsvStream &s)
{
    s.newLine();
    return s;
}