#include "disc.h"

#include <QDebug>
#include <QStringList>

disc::disc()
{

}

disc::~disc()
{

}

int disc::DataCreate(char *buf, QString Name, QString Options, QString FixValue, QString MaxValue, int indx)
{
    int i, j, k;
    Disc = new D_DISC;

    memset(Disc, 0, sizeof(D_DISC));

    Disc->Print = 0x0b;

    strcpy((char *)Disc->Name, Name.toLocal8Bit().data());
    qDebug("Disc->Name = %s", Disc->Name);

    switch(indx)
    {
    case 1:
        Disc->Options = 0x19;
        break;
    case 2:
        Disc->Options = 0x11;
        break;
    case 3:
        Disc->Options = 0x1d;
        break;
    case 4:
        Disc->Options = 0x15;
        break;
    #if SUBDISC
    case 5:
        Disc->Options = 0x09;
        Disc->Tax = 0xff;
        break;
    case 6:
        Disc->Options = 0x01;
        Disc->Tax = 0xff;
        break;
    case 7:
        Disc->Options = 0x0d;
        Disc->Tax = 0xff;
        break;
    case 8:
        Disc->Options = 0x05;
        Disc->Tax = 0xff;
        break;
    case 9:
        Disc->Options = 0x11;
        break;
    case 10:
        Disc->Options = 0x11;
        break;
    #else
    case 5:
        Disc->Options = 0x11;
        break;
    case 6:
        Disc->Options = 0x11;
        break;
    #endif
    }

    Disc->Options &= ~(0x03);
    for(i = 0; i < Options.size(); i++)
    {
        if(Options.at(i) == QChar('2'))
        {
            Disc->Options |= 0x01;
        }

        if(Options.at(i) == QChar('3'))
        {
            Disc->Options |= 0x02;
        }
    }

    Disc->Options &= 0xff;

    qDebug("Disc->Options = %02x", Disc->Options);

    QStringList Fix_Value = FixValue.split(".");
    QString fixvalue;
    for(k = 0; k < Fix_Value.size() && k < 2; k++)
    {
        fixvalue += Fix_Value.at(k);
    }

    if(k == 1)
    {
        fixvalue += QString("00");
    }
    else if(k > 0 && Fix_Value.at(1).size()%2)
    {
        fixvalue += QString("0");
    }
    j = (fixvalue.size()/2 - 1);
    if(fixvalue.size()%2)
    {
        fixvalue.insert(0, QString("0"));
        j++;
    }

    for(i = 0; j >= 0 && i < fixvalue.size(); i++)
    {
        if(i != 0 && i %2 == 0)
        {
            j--;
        }

        if(i % 2 == 1)
        {
            Disc->Fixed[j] |= (fixvalue.at(i).toAscii() - '0') & 0x0f;
        }

        if(i % 2 == 0)
        {
            Disc->Fixed[j] |= ((fixvalue.at(i).toAscii() - '0') << 4) & 0xf0;
        }

        Disc->Fixed[j] &= 0xff;
        qDebug("Disc->Fixed[%d] = %02x", j, Disc->Fixed[j]);
    }

    QStringList Max_Value = MaxValue.split(".");
    QString maxvalue;
    for(k = 0; k < Max_Value.size() && k < 2; k++)
    {
        maxvalue += Max_Value.at(k);
    }
    qDebug() << "------->maxvalue = " << maxvalue;

    if(k == 1)
    {
        maxvalue += QString("00");
    }
    else if(k > 0 && Max_Value.at(1).size()%2)
    {
        maxvalue += QString("0");
    }
    j = (maxvalue.size()/2 - 1);
    if(maxvalue.size()%2)
    {
        maxvalue.insert(0, QString("0"));
        j++;
    }

    for(i = 0; j >= 0 && i < maxvalue.size(); i++)
    {
        if(i != 0 && i %2 == 0)
        {
            j--;
        }

        if(i % 2 == 1)
        {
            Disc->Max[j] |= (maxvalue.at(i).toAscii() - '0') & 0x0f;
        }

        if(i % 2 == 0)
        {
            Disc->Max[j] |= ((maxvalue.at(i).toAscii() - '0') << 4) & 0xf0;
        }

        Disc->Max[j] &= 0xff;
        qDebug("Disc->Max[%d] = %02x", j, Disc->Max[j]);
    }

    memcpy(buf, Disc, sizeof(D_DISC));

    delete Disc;

    return sizeof(D_DISC);
}

QStringList disc::DataParse(char *buf)
{
    int j, high, low;
    bool flag;

    Disc = (D_DISC *)buf;

    QString Name = QString((char *)Disc->Name);
    qDebug() << "Name = " << Name;
    QString Options;

    if((Disc->Options & 0x03) == 0x00)
    {
        Options += QString("1");
    }
    else if((Disc->Options & 0x03) == 0x01)
    {
        Options += QString("2");
    }
    else if((Disc->Options & 0x03) == 0x02)
    {
        Options += QString("3");
    }

    qDebug() << "Options = " << Options;

    QString FixValue;

    flag = false;
    for(j = 2; j >= 0; j--)
    {
        high = (Disc->Fixed[j] >> 4) & 0x0f;
        low = Disc->Fixed[j] & 0x0f;

        if(flag && j == 0)
        {
            FixValue += QString(".");
        }

        if(flag || high > 0)
        {
            FixValue += QString::number(high);
            flag = true;
        }

        if(flag || low > 0)
        {
            FixValue += QString::number(low);
            flag = true;
        }
    }
    qDebug() << "FixValue = " << FixValue;

    QString MaxValue;

    flag = false;
    for(j = 3; j >= 0; j--)
    {
        high = (Disc->Max[j] >> 4) & 0x0f;
        low = Disc->Max[j] & 0x0f;

        if(flag && j == 0)
        {
            MaxValue += QString(".");
        }

        if(flag || high > 0)
        {
            MaxValue += QString::number(high);
            flag = true;
        }

        if(flag || low > 0)
        {
            MaxValue += QString::number(low);
            flag = true;
        }
    }
    qDebug() << "MaxValue = " << MaxValue;

    QStringList str;

    str << Name << Options << FixValue << MaxValue;

    return str;
}
