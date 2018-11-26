#ifndef DEPT_H
#define DEPT_H

#include <QObject>

#include <QList>
#include <QVariant>

#define DEPT	    5000
#define DEPTITEMS 8

#pragma pack (1)
typedef struct DEPTRECORD
{
    unsigned char    Random[7];  /* max 7 bytes is 14 digits */
    char    Name[25];   /* max 24 with terminator */
    unsigned char    Group;  /* group selection max 0xff also for print bill,=0 not allon to a group */
    unsigned char    Print;  /* print lay-out */
    unsigned char    Options;
    unsigned char    Tax;    /* Tax selection max 8 */
    unsigned char    Kp;     /* Kp aansturing max 8 */
    unsigned char    Price[5];
    unsigned char    PriceMax[5];
}D_DEPT;
#pragma pack ()

class dept
{
public:
    dept(QList<QList<QVariant> >* ptr);
    ~dept();

    int DataCreate(int index, char *databuf);
    int DataParse(char *buf, int len);

private:
    D_DEPT *Dept;
    QList<QList<QVariant> >* m_varListList;

    float BcdToFloat(char *bcd, int len, int decimal);
    void BcdToStr(char *str, char *bcd, int len);
};

#endif // DEPT_H
