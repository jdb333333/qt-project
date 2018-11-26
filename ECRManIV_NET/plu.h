#ifndef PLU_H
#define PLU_H

#define BCDLEN	8

#include <QList>
#include <QVariant>

#define UPDPLU	    100
#define ADDPLU	    101
#define DELPLU	    102

typedef struct
{
    unsigned char    Sign;
    unsigned char    Value[BCDLEN];
} BCD;

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

class plu
{
public:
    plu(QList<QList<QVariant> >* ptr);
    ~plu();

    int DataParse(int index, char *databuf);

private:
    P_PLU Plu;
    QList<QList<QVariant> >* m_varListList;
};

#endif // PLU_H
