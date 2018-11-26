#ifndef OFFPRICE_H
#define OFFPRICE_H

#include <QObject>

class QStringList;

#define OFFER		3100

#pragma pack (1)
typedef struct OFFRECORD
{
    unsigned char    Name[25];
    unsigned char    Type;
    unsigned char    DateFrom[2];
    unsigned char    DateTo[2];
    unsigned char    TimeFrom[2];
    unsigned char    TimeTo[2];
    unsigned char    WeekDay;
    union
    {
        unsigned char    Discount[9];
        struct
        {
            unsigned char    NumItems;
            unsigned char    PriceU[4];
            unsigned char    PriceP[4];
        }   TYPE1;
    } OFFVal;
}O_OFFER;
#pragma pack ()

class offprice
{
public:
    offprice();
    ~offprice();

    int DataCreate(char *buf, QStringList Str);
    QStringList DataParse(char *buf);

private:
    O_OFFER *OfferPrice;
};

#endif // OFFPRICE_H
