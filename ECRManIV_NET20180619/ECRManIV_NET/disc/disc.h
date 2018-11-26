#ifndef DISC_H
#define DISC_H

#include <QObject>

#define DISC	    500
#define SUBDISC     1

class QStringList;

#pragma pack (1)
typedef struct DISCRECORD
{
    unsigned char    Print;
    unsigned char    Options;
    unsigned char    Fixed[3];
    unsigned char    Tax;
    unsigned char    Max[4];
    unsigned char    Name[13];       /* max 12 with terminator */
}D_DISC;
#pragma pack ()

class disc
{
public:
    disc();
    ~disc();

    int DataCreate(char *buf, QString Name, QString Options, QString FixValue, QString MaxValue, int indx = 1);
    QStringList DataParse(char *buf);

private:
    D_DISC *Disc;
};

#endif // DISC_H
