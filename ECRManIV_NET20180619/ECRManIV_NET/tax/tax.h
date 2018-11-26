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
                             /* Bit0:=1,(VAT)为价内税(增值税),即:销售价格包含税;
                                     =0,(Add on)价外税(营业税),即:销售价格不包含税 */
                             /* BIT1:打印税率项(Bit0为1时有效,即打印价内税额)  */
                             /* BIT2:打印0税项(Bit0为1时有效)     */
                             /* BIT3: GST tax if set*/
                             /* BIT4:打印税额(Bit0为1时有效)     */
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
