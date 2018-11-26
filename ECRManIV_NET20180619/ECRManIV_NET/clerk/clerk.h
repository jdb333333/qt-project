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
                //BIT0: ȡ������
                //BIT1:  ��������
                //BIT2:  ȡ������
                //BIT3:  �˻�����
                //BIT4:  %�ۿ�����
                //BIT5:  %�ӳ�����
                //BIT6:  +-�������
                //BIT7: =0,training clerk
    unsigned char Passwd[3];
    unsigned char Options2;//jdb2018-05-05 ���ӱ�ʶ
                //BIT0: 1 ��������PLU
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
