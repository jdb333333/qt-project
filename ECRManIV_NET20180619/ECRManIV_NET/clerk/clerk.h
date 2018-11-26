#ifndef CLERK_H
#define CLERK_H

#include <QObject>
#include <QStringList>

#define CLERK	    3000

#pragma pack (1)
typedef struct CLERKRECORD
{
    unsigned char Name[13];
    unsigned char Options;
                //BIT0: 取消限制
                //BIT1:  更改限制
                //BIT2:  取消交易
                //BIT3:  退货限制
                //BIT4:  %折扣限制
                //BIT5:  %加成限制
                //BIT6:  +-金额限制
                //BIT7: =0,training clerk
    unsigned char Passwd[3];
    unsigned char Options2;//jdb2018-05-05 增加标识
                //BIT0: 1 限制增加PLU
}C_CLERK;
#pragma pack ()

class clerk : public QObject
{
    Q_OBJECT
public:
    explicit clerk(QObject *parent = 0);
    ~clerk();

    int DataCreate(char *buf, QString Name, QString Options, QString Passwd);
    QStringList DataParse(char *buf);

private:
    C_CLERK *Clerk;

signals:

public slots:
};

#endif // CLERK_H
