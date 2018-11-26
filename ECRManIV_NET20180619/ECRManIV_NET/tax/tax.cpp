#include "tax.h"

#include <QDebug>
#include <QStringList>

tax::tax()
{

}

tax::~tax()
{

}

int tax::DataCreate(char *buf, QString Name, QString Rate, QString Options, int indx)
{
    int i, j, k;
    Tax = new T_TAX;

    memset(Tax, 0, sizeof(T_TAX));

    strcpy((char *)Tax->Name, Name.toLocal8Bit().data());
    qDebug("Tax->Name = %s", Tax->Name);

    Tax->Options |= 0x01 << 0;
    for(i = 0; i < Options.size(); i++)
    {
        if(Options.at(i) == QChar('1'))
        {
            Tax->Options |= 0x01 << 0;
        }

        if(Options.at(i) == QChar('2'))
        {
            Tax->Options |= 0x01 << 1;
        }

        if(Options.at(i) == QChar('3'))
        {
            Tax->Options |= 0x01 << 2;
        }

        if(Options.at(i) == QChar('4'))
        {
            Tax->Options |= 0x01 << 3;
        }

        if(Options.at(i) == QChar('5'))
        {
            Tax->Options |= 0x01 << 4;
        }

        if(Options.at(i) == QChar('6'))
        {
            Tax->Options |= 0x01 << 5;
        }

        if(Options.at(i) == QChar('7'))
        {
            Tax->Options |= 0x01 << 6;
        }

        if(Options.at(i) == QChar('8'))
        {
            Tax->Options |= 0x01 << 7;
        }
    }

    Tax->Options &= 0xff;

    qDebug("Tax->Options = %02x", Tax->Options);

    QStringList Rate_Value = Rate.split(".");
    QString ratevalue;
    for(k = 0; k < Rate_Value.size() && k < 2; k++)
    {
        ratevalue += Rate_Value.at(k);
    }

    if(k == 1)
    {
        ratevalue += QString("00");
    }
    else if(k > 0 && Rate_Value.at(1).size()%2)
    {
        ratevalue += QString("0");
    }
    j = (ratevalue.size()/2 - 1);
    if(ratevalue.size()%2)
    {
        ratevalue.insert(0, QString("0"));
        j++;
    }

    qDebug() << "ratevalue = " << ratevalue;

    for(i = 0; j >= 0 && i < ratevalue.size(); i++)
    {
        if(i != 0 && i %2 == 0)
        {
            j--;
        }

        if(i % 2 == 1)
        {
            Tax->Rate[j] |= (ratevalue.at(i).toAscii() - '0') & 0x0f;
        }

        if(i % 2 == 0)
        {
            Tax->Rate[j] |= ((ratevalue.at(i).toAscii() - '0') << 4) & 0xf0;
        }

        Tax->Rate[j] &= 0xff;
        qDebug("Tax->Rate[%d] = %02x", j, Tax->Rate[j]);
    }

    memcpy(buf, Tax, sizeof(T_TAX));

    delete Tax;

    return sizeof(T_TAX);
}

QStringList tax::DataParse(char *buf)
{
    int j, high, low;
    bool flag;

    Tax = (T_TAX *)buf;

    QString Name = QString((char *)Tax->Name);
    qDebug() << "Name = " << Name;
    QString Options;

    if((Tax->Options >> 4) & 0x01)
    {
        Options += QString("5");
    }
    if((Tax->Options >> 2) & 0x01)
    {
        Options += QString("3");
    }
    if((Tax->Options >> 1) & 0x01)
    {
        Options += QString("2");
    }

    qDebug() << "Options = " << Options;

    QString RateValue;

    flag = false;
    for(j = 2; j >= 0; j--)
    {
        high = (Tax->Rate[j] >> 4) & 0x0f;
        low = Tax->Rate[j] & 0x0f;

        if(flag && j == 0)
        {
            RateValue += QString(".");
        }

        if(flag || high > 0)
        {
            RateValue += QString::number(high);
            flag = true;
        }

        if(flag || low > 0)
        {
            RateValue += QString::number(low);
            flag = true;
        }
    }
    qDebug() << "RateValue = " << RateValue;

    QStringList str;

    str << Name << RateValue << Options;

    return str;
}
