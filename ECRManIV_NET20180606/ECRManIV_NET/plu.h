#ifndef PLU_H
#define PLU_H

#define BCDLEN	8

#include <QList>
#include <QVariant>

#define UPDPLU	    100
#define ADDPLU	    101
#define DELPLU	    102

#define PLU1        10000

#pragma pack (1)
typedef struct
{
    unsigned char    Sign;
    unsigned char    Value[BCDLEN];
} BCD;

#pragma pack (1)
typedef struct PLURECORD {
    unsigned char    Random[7];	/* max 7 bytes is 14 digits */
    char    Name[25];	/* max 24 with terminator */
    unsigned short	OFFIndex;	// Index of OFFPrice
    unsigned char    Dept;		/* department selection max 0xff */
    unsigned char	DeptHi; 			/* High Dept Number */
    unsigned char    Price[4][5];      /* max price is 10 digits is 5 bytes */
    unsigned char    Cost[5];	      /* max 4 levels with 1 cost price */
    unsigned short	Link;				/* PLU Link */
    BCD		Inventory;	/* plu inventory */
/* scale */
/* flag */
/* inventory */
}P_PLU;
#pragma pack ()

class plu
{
public:
    plu(QList<QList<QVariant> >* ptr);
    ~plu();

    int DataCreate(int index, char *databuf);
    int DataParse(char *buf, int len);

private:
    P_PLU *Plu;
    QList<QList<QVariant> >* m_varListList;

    float BcdToFloat(char *bcd, int len, int decimal);
    void BcdToStr(char *str, char *bcd, int len);
};

#endif // PLU_H
