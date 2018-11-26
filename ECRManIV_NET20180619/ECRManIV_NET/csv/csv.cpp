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
            if (k < 0 ) // 没找到逗号
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

    j = s.indexOf(',', i); // 查找,
    if (j < 0) // 没找到
        j = s.length();
    fld = s.mid (i,j-i);//提取内容
    return j;
}

/// \brief 把一句csv格式的内容解析
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

/// \brief 读取一行csv文件
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

/// \brief 把字符串装换为标准csv一个单元得字符串，对应字符串原有的逗号会进行装换
///
/// csv的原则是：
///
/// - 如果字符串有逗号，把整个字符串前后用引号括起来
/// - 如果字符串有引号",引号要用两个引号表示转义""
/// \param rawStr 原有数据
/// \return 标准的csv单元字符串
QString csv::toCsvString(const QString &rawStr)
{
    //首先查找有没有引号,如果有，则把引号替换为两个引号
    QString res = rawStr;
    res.replace("\"","\"\"");
    if(res.contains(','))
    {
        //如果有逗号，在前后把整个句子用引号包含
        res = ('\"' + res + '\"');
    }
    return res;
}

/// \brief 把一行要用逗号分隔的字符串转换为一行标准csv字符串
/// \param sectionLine 如：xxx,xxxx,xxxxx 传入{'xxx','xxxx','xxxxx'}
/// \return 标准的csv字符串不带换行符
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

/// \brief 换行
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
