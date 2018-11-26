#ifndef TAX_H
#define TAX_H

#include <QObject>
class QStringList;

#pragma pack (1)
typedef struct TAXRECORD
{
    unsigned char    Name[13];       /* max 12 with terminator */
    unsigned char    Rate[3];        /* rate 0.00% to 9999.00% */
    unsigned char    Options;        /* if BIT4 set not print */
                             /* Bit0:=1,(VAT)Ϊ����˰(��ֵ˰),��:���ۼ۸����˰;
                                     =0,(Add on)����˰(Ӫҵ˰),��:���ۼ۸񲻰���˰ */
                             /* BIT1:��ӡ˰����(Bit0Ϊ1ʱ��Ч,����ӡ����˰��)  */
                             /* BIT2:��ӡ0˰��(Bit0Ϊ1ʱ��Ч)     */
                             /* BIT3: GST tax if set*/
                             /* BIT4:��ӡ˰��(Bit0Ϊ1ʱ��Ч)     */
}T_TAX;
#pragma pack ()

#define TAX	    	2900

class tax
{
public:
    tax();
    ~tax();

    int DataCreate(char *buf, QString Name, QString Rate, QString Options, int indx = 1);
    QStringList DataParse(char *buf);
private:
    T_TAX *Tax;
};

#endif // TAX_H
