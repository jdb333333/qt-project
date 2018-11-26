#include "offprice.h"
#include <QDebug>
#include <QStringList>

offprice::offprice()
{

}

offprice::~offprice()
{

}

int offprice::DataCreate(char *buf, QStringList Str)
{
    int i, j, k;
    int offertype;
    OfferPrice = new O_OFFER;

    memset(OfferPrice, 0, sizeof(O_OFFER));

    QString Name, Type, DateFrom, DateTo, TimeFrom, TimeTo, WeekDay, Discount, NumItems, PriceU, PriceP;

    i = Str.size();
    if(i == 11)
    {
        Name = Str.at(0);
        Type = Str.at(1);
        DateFrom = Str.at(2);
        DateTo = Str.at(3);
        TimeFrom = Str.at(4);
        TimeTo = Str.at(5);
        WeekDay = Str.at(6);
        Discount = Str.at(7);
        NumItems = Str.at(8);
        PriceU = Str.at(9);
        PriceP = Str.at(10);
    }
    else
    {
        return -1;
    }

    strcpy((char *)OfferPrice->Name, Name.toLocal8Bit().data());
    qDebug("OfferPrice->Name = %s", OfferPrice->Name);

    OfferPrice->Type &= ~(0x03);
    offertype = 0;
    for(i = 0; i < Type.size(); i++)
    {
        if(Type.at(i) == QChar('1'))
        {
            OfferPrice->Type |= 0x01;
            offertype = 1;
        }

        if(Type.at(i) == QChar('2'))
        {
            OfferPrice->Type |= 0x02;
            offertype = 2;
        }
    }

    OfferPrice->Type &= 0xff;

    qDebug("OfferPrice->Type = %02x", OfferPrice->Type);

    QStringList Date_Value = DateFrom.split("-");
    QString datefrom;
    for(k = 0; k < Date_Value.size() && k < 2; k++)
    {
        datefrom += Date_Value.at(k);
    }

    for(j = 1, i = 0; j >= 0 && i < datefrom.size(); i++)
    {
        if(i != 0 && i %2 == 0)
        {
            j--;
        }

        if(i % 2 == 1)
        {
            OfferPrice->DateFrom[j] |= (datefrom.at(i).toAscii() - '0') & 0x0f;
        }

        if(i % 2 == 0)
        {
            OfferPrice->DateFrom[j] |= ((datefrom.at(i).toAscii() - '0') << 4) & 0xf0;
        }

        OfferPrice->DateFrom[j] &= 0xff;
        qDebug("OfferPrice->DateFrom[%d] = %02x", j, OfferPrice->DateFrom[j]);
    }

    Date_Value = DateTo.split("-");
    QString dateto;
    for(k = 0; k < Date_Value.size() && k < 2; k++)
    {
        dateto += Date_Value.at(k);
    }

    for(j = 1, i = 0; j >= 0 && i < dateto.size(); i++)
    {
        if(i != 0 && i %2 == 0)
        {
            j--;
        }

        if(i % 2 == 1)
        {
            OfferPrice->DateTo[j] |= (dateto.at(i).toAscii() - '0') & 0x0f;
        }

        if(i % 2 == 0)
        {
            OfferPrice->DateTo[j] |= ((dateto.at(i).toAscii() - '0') << 4) & 0xf0;
        }

        OfferPrice->DateTo[j] &= 0xff;
        qDebug("OfferPrice->DateTo[%d] = %02x", j, OfferPrice->DateTo[j]);
    }

    QStringList Time_Value = TimeFrom.split(":");
    QString timefrom;
    for(k = 0; k < Time_Value.size() && k < 2; k++)
    {
        timefrom += Time_Value.at(k);
    }

    for(j = 1, i = 0; j >= 0 && i < timefrom.size(); i++)
    {
        if(i != 0 && i %2 == 0)
        {
            j--;
        }

        if(i % 2 == 1)
        {
            OfferPrice->TimeFrom[j] |= (timefrom.at(i).toAscii() - '0') & 0x0f;
        }

        if(i % 2 == 0)
        {
            OfferPrice->TimeFrom[j] |= ((timefrom.at(i).toAscii() - '0') << 4) & 0xf0;
        }

        OfferPrice->TimeFrom[j] &= 0xff;
        qDebug("OfferPrice->TimeFrom[%d] = %02x", j, OfferPrice->TimeFrom[j]);
    }

    Time_Value = TimeTo.split(":");
    QString timeto;
    for(k = 0; k < Time_Value.size() && k < 2; k++)
    {
        timeto += Time_Value.at(k);
    }

    for(j = 1, i = 0; j >= 0 && i < timeto.size(); i++)
    {
        if(i != 0 && i %2 == 0)
        {
            j--;
        }

        if(i % 2 == 1)
        {
            OfferPrice->TimeTo[j] |= (timeto.at(i).toAscii() - '0') & 0x0f;
        }

        if(i % 2 == 0)
        {
            OfferPrice->TimeTo[j] |= ((timeto.at(i).toAscii() - '0') << 4) & 0xf0;
        }

        OfferPrice->TimeTo[j] &= 0xff;
        qDebug("OfferPrice->TimeTo[%d] = %02x", j, OfferPrice->TimeTo[j]);
    }

    OfferPrice->WeekDay &= ~(0xff);
    for(i = 0; i < WeekDay.size(); i++)
    {
        if(WeekDay.at(i) == QChar('1'))
        {
            OfferPrice->WeekDay |= 0x01;
        }
        if(WeekDay.at(i) == QChar('2'))
        {
            OfferPrice->WeekDay |= 0x02;
        }
        if(WeekDay.at(i) == QChar('3'))
        {
            OfferPrice->WeekDay |= 0x04;
        }
        if(WeekDay.at(i) == QChar('4'))
        {
            OfferPrice->WeekDay |= 0x08;
        }
        if(WeekDay.at(i) == QChar('5'))
        {
            OfferPrice->WeekDay |= 0x10;
        }
        if(WeekDay.at(i) == QChar('6'))
        {
            OfferPrice->WeekDay |= 0x20;
        }
        if(WeekDay.at(i) == QChar('7'))
        {
            OfferPrice->WeekDay |= 0x40;
        }
        if(WeekDay.at(i) == QChar('8'))
        {
            OfferPrice->WeekDay |= 0x80;
        }
    }

    OfferPrice->WeekDay &= 0xff;

    qDebug("OfferPrice->WeekDay = %02x", OfferPrice->WeekDay);

    if(offertype == 1)
    {
        OfferPrice->OFFVal.TYPE1.NumItems = NumItems.toInt();

        QStringList PriceU_Value = PriceU.split(".");
        QString priceu;
        for(k = 0; k < PriceU_Value.size() && k < 2; k++)
        {
            priceu += PriceU_Value.at(k);
        }
        qDebug() << "------->priceu = " << priceu;

        if(k == 1)
        {
            priceu += QString("00");
        }
        else if(k > 0 && PriceU_Value.at(1).size()%2)
        {
            priceu += QString("0");
        }
        j = (priceu.size()/2 - 1);
        if(priceu.size()%2)
        {
            priceu.insert(0, QString("0"));
            j++;
        }

        for(i = 0; j >= 0 && i < priceu.size(); i++)
        {
            if(i != 0 && i %2 == 0)
            {
                j--;
            }

            if(i % 2 == 1)
            {
                OfferPrice->OFFVal.TYPE1.PriceU[j] |= (priceu.at(i).toAscii() - '0') & 0x0f;
            }

            if(i % 2 == 0)
            {
                OfferPrice->OFFVal.TYPE1.PriceU[j] |= ((priceu.at(i).toAscii() - '0') << 4) & 0xf0;
            }

            OfferPrice->OFFVal.TYPE1.PriceU[j] &= 0xff;
            qDebug("OfferPrice->OFFVal.TYPE1.PriceU[%d] = %02x", j, OfferPrice->OFFVal.TYPE1.PriceU[j]);
        }

        QStringList PriceP_Value = PriceP.split(".");
        QString pricep;
        for(k = 0; k < PriceP_Value.size() && k < 2; k++)
        {
            pricep += PriceP_Value.at(k);
        }
        qDebug() << "------->pricep = " << pricep;

        if(k == 1)
        {
            pricep += QString("00");
        }
        else if(k > 0 && PriceP_Value.at(1).size()%2)
        {
            pricep += QString("0");
        }
        j = (pricep.size()/2 - 1);
        if(pricep.size()%2)
        {
            pricep.insert(0, QString("0"));
            j++;
        }

        for(i = 0; j >= 0 && i < pricep.size(); i++)
        {
            if(i != 0 && i %2 == 0)
            {
                j--;
            }

            if(i % 2 == 1)
            {
                OfferPrice->OFFVal.TYPE1.PriceP[j] |= (pricep.at(i).toAscii() - '0') & 0x0f;
            }

            if(i % 2 == 0)
            {
                OfferPrice->OFFVal.TYPE1.PriceP[j] |= ((pricep.at(i).toAscii() - '0') << 4) & 0xf0;
            }

            OfferPrice->OFFVal.TYPE1.PriceP[j] &= 0xff;
            qDebug("OfferPrice->OFFVal.TYPE1.PriceP[%d] = %02x", j, OfferPrice->OFFVal.TYPE1.PriceP[j]);
        }
    }
    else if(offertype == 2)
    {
        QStringList Dicount_Value = Discount.split(".");
        QString dicount;
        for(k = 0; k < Dicount_Value.size() && k < 2; k++)
        {
            dicount += Dicount_Value.at(k);
        }
        qDebug() << "------->dicount = " << dicount;

        if(k == 1)
        {
            dicount += QString("00");
        }
        else if(k > 0 && Dicount_Value.at(1).size()%2)
        {
            dicount += QString("0");
        }
        j = (dicount.size()/2 - 1);
        if(dicount.size()%2)
        {
            dicount.insert(0, QString("0"));
            j++;
        }

        for(i = 0; j >= 0 && i < dicount.size(); i++)
        {
            if(i != 0 && i %2 == 0)
            {
                j--;
            }

            if(i % 2 == 1)
            {
                OfferPrice->OFFVal.Discount[j] |= (dicount.at(i).toAscii() - '0') & 0x0f;
            }

            if(i % 2 == 0)
            {
                OfferPrice->OFFVal.Discount[j] |= ((dicount.at(i).toAscii() - '0') << 4) & 0xf0;
            }

            OfferPrice->OFFVal.Discount[j] &= 0xff;
            qDebug("OfferPrice->OFFVal.Discount[%d] = %02x", j, OfferPrice->OFFVal.Discount[j]);
        }
    }

    memcpy(buf, OfferPrice, sizeof(O_OFFER));

    delete OfferPrice;

    return sizeof(O_OFFER);
}

QStringList offprice::DataParse(char *buf)
{
    int j, high, low;
    bool flag;
    int offertype;

    OfferPrice = (O_OFFER *)buf;

    QString Name = QString((char *)OfferPrice->Name);
    qDebug() << "Name = " << Name;

    QString Type;

    offertype = 0;
    if(!((OfferPrice->Type >> 0) & 0x03))
    {
        Type += QString("0");
    }
    if((OfferPrice->Type >> 1) & 0x01)
    {
        Type += QString("2");
        offertype = 2;
    }
    if((OfferPrice->Type >> 0) & 0x01)
    {
        Type += QString("1");
        offertype = 1;
    }

    qDebug() << "Type = " << Type;

    QString DateFrom;

    flag = true;
    for(j = 1; j >= 0; j--)
    {
        high = (OfferPrice->DateFrom[j] >> 4) & 0x0f;
        low = OfferPrice->DateFrom[j] & 0x0f;

        if(j == 0)
        {
            DateFrom += QString("-");
        }

        if(flag || high > 0)
        {
            DateFrom += QString::number(high);
        }

        if(flag || low > 0)
        {
            DateFrom += QString::number(low);
        }
    }
    qDebug() << "DateFrom = " << DateFrom;

    QString DateTo;

    flag = true;
    for(j = 1; j >= 0; j--)
    {
        high = (OfferPrice->DateTo[j] >> 4) & 0x0f;
        low = OfferPrice->DateTo[j] & 0x0f;

        if(j == 0)
        {
            DateTo += QString("-");
        }

        if(flag || high > 0)
        {
            DateTo += QString::number(high);
        }

        if(flag || low > 0)
        {
            DateTo += QString::number(low);
        }
    }
    qDebug() << "DateTo = " << DateTo;

    QString TimeFrom;

    flag = true;
    for(j = 1; j >= 0; j--)
    {
        high = (OfferPrice->TimeFrom[j] >> 4) & 0x0f;
        low = OfferPrice->TimeFrom[j] & 0x0f;

        if(j == 0)
        {
            TimeFrom += QString(":");
        }

        if(flag || high > 0)
        {
            TimeFrom += QString::number(high);
        }

        if(flag || low > 0)
        {
            TimeFrom += QString::number(low);
        }
    }
    qDebug() << "TimeFrom = " << TimeFrom;

    QString TimeTo;

    flag = true;
    for(j = 1; j >= 0; j--)
    {
        high = (OfferPrice->TimeTo[j] >> 4) & 0x0f;
        low = OfferPrice->TimeTo[j] & 0x0f;

        if(j == 0)
        {
            TimeTo += QString(":");
        }

        if(flag || high > 0)
        {
            TimeTo += QString::number(high);
        }

        if(flag || low > 0)
        {
            TimeTo += QString::number(low);
        }
    }
    qDebug() << "TimeTo = " << TimeTo;

    QString WeekDay;

    if((OfferPrice->WeekDay >> 0) & 0x01)
    {
        WeekDay += QString("1");
    }
    if((OfferPrice->WeekDay >> 1) & 0x01)
    {
        WeekDay += QString("2");
    }
    if((OfferPrice->WeekDay >> 2) & 0x01)
    {
        WeekDay += QString("3");
    }
    if((OfferPrice->WeekDay >> 3) & 0x01)
    {
        WeekDay += QString("4");
    }
    if((OfferPrice->WeekDay >> 4) & 0x01)
    {
        WeekDay += QString("5");
    }
    if((OfferPrice->WeekDay >> 5) & 0x01)
    {
        WeekDay += QString("6");
    }
    if((OfferPrice->WeekDay >> 6) & 0x01)
    {
        WeekDay += QString("7");
    }
    if((OfferPrice->WeekDay >> 7) & 0x01)
    {
        WeekDay += QString("8");
    }

    qDebug() << "WeekDay = " << WeekDay;

    QString Discount, NumItems, PriceU, PriceP;
    if(offertype == 2)
    {
        flag = false;
        for(j = 8; j >= 0; j--)
        {
            high = (OfferPrice->OFFVal.Discount[j] >> 4) & 0x0f;
            low = OfferPrice->OFFVal.Discount[j] & 0x0f;

            if(flag && j == 0)
            {
                Discount += QString(".");
            }

            if(flag || high > 0)
            {
                Discount += QString::number(high);
                flag = true;
            }

            if(flag || low > 0)
            {
                Discount += QString::number(low);
                flag = true;
            }
        }
        qDebug() << "Discount = " << Discount;
    }
    else if(offertype == 1)
    {
        NumItems = QString("%1").arg(OfferPrice->OFFVal.TYPE1.NumItems);
        qDebug() << "NumItems = " << NumItems;

        flag = false;
        for(j = 3; j >= 0; j--)
        {
            high = (OfferPrice->OFFVal.TYPE1.PriceU[j] >> 4) & 0x0f;
            low = OfferPrice->OFFVal.TYPE1.PriceU[j] & 0x0f;

            if(flag && j == 0)
            {
                PriceU += QString(".");
            }

            if(flag || high > 0)
            {
                PriceU += QString::number(high);
                flag = true;
            }

            if(flag || low > 0)
            {
                PriceU += QString::number(low);
                flag = true;
            }
        }
        qDebug() << "PriceU = " << PriceU;

        flag = false;
        for(j = 3; j >= 0; j--)
        {
            high = (OfferPrice->OFFVal.TYPE1.PriceP[j] >> 4) & 0x0f;
            low = OfferPrice->OFFVal.TYPE1.PriceP[j] & 0x0f;

            if(flag && j == 0)
            {
                PriceP += QString(".");
            }

            if(flag || high > 0)
            {
                PriceP += QString::number(high);
                flag = true;
            }

            if(flag || low > 0)
            {
                PriceP += QString::number(low);
                flag = true;
            }
        }
        qDebug() << "PriceP = " << PriceP;
    }

    QStringList str;

    str << Name << Type << DateFrom << DateTo << TimeFrom << TimeTo << WeekDay << Discount << NumItems << PriceU << PriceP;

    return str;
}
