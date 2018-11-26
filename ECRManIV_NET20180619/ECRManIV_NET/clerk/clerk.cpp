#include "clerk.h"


#include <QDebug>

clerk::clerk(QObject *parent) : QObject(parent)
{

}

clerk::~clerk()
{

}

int clerk::DataCreate(char *buf, QString Name, QString Options, QString Passwd)
{
    int i;
    Clerk = new C_CLERK;

    memset(Clerk, 0, sizeof(C_CLERK));

    strcpy((char *)Clerk->Name, Name.toLocal8Bit().data());
    qDebug("Clerk->Name = %s", Clerk->Name);

    Clerk->Options = 0xff;

    for(i = 0; i < Options.size(); i++)
    {
        if(Options.at(i) == QChar('1'))
        {
            //Clerk->Options &= (~(0x01 << 0));
            Clerk->Options &= (~(0x01 << 1));
        }

        if(Options.at(i) == QChar('2'))
        {
            //Clerk->Options &= (~(0x01 << 1));
            Clerk->Options &= (~(0x01 << 0));
        }

        if(Options.at(i) == QChar('3'))
        {
            Clerk->Options &= (~(0x01 << 2));
        }

        if(Options.at(i) == QChar('4'))
        {
            Clerk->Options &= (~(0x01 << 3));
        }

        if(Options.at(i) == QChar('5'))
        {
            Clerk->Options &= (~(0x01 << 4));
        }

        if(Options.at(i) == QChar('6'))
        {
            Clerk->Options &= (~(0x01 << 5));
        }

        if(Options.at(i) == QChar('7'))
        {
            Clerk->Options &= (~(0x01 << 6));
        }

        if(Options.at(i) == QChar('8'))
        {
            Clerk->Options &= (~(0x01 << 7));
        }
    }

    Clerk->Options &= 0xff;

    qDebug("Clerk->Options = %02x", Clerk->Options);

    for(int j = 2, i = 0; j >= 0 && i < Passwd.size(); i++)
    {
        if(i != 0 && i %2 == 0)
        {
            j--;
        }

        if(i % 2 == 1)
        {
            Clerk->Passwd[j] |= (Passwd.at(i).toAscii() - '0') & 0x0f;
        }

        if(i % 2 == 0)
        {
            Clerk->Passwd[j] |= ((Passwd.at(i).toAscii() - '0') << 4) & 0xf0;
        }

        Clerk->Passwd[j] &= 0xff;
        qDebug("Clerk->Passwd[%d] = %02x", j, Clerk->Passwd[j]);
    }

    memcpy(buf, Clerk, sizeof(C_CLERK));

    delete Clerk;

    return sizeof(C_CLERK);
}

QStringList clerk::DataParse(char *buf)
{
    Clerk = (C_CLERK *)buf;

    QString Name = QString((char *)Clerk->Name);
    qDebug() << "Name = " << Name;
    QString Options;

    if(!((Clerk->Options >> 7) & 0x01))
    {
        Options += QString("8");
    }
    if(!((Clerk->Options >> 6) & 0x01))
    {
        Options += QString("7");
    }
    if(!((Clerk->Options >> 5) & 0x01))
    {
        Options += QString("6");
    }
    if(!((Clerk->Options >> 4) & 0x01))
    {
        Options += QString("5");
    }
    if(!((Clerk->Options >> 3) & 0x01))
    {
        Options += QString("4");
    }
    if(!((Clerk->Options >> 2) & 0x01))
    {
        Options += QString("3");
    }
    if(!((Clerk->Options >> 1) & 0x01))
    {
        //Options += QString("2");
        Options += QString("1");
    }
    if(!((Clerk->Options >> 0) & 0x01))
    {
        //Options += QString("1");
        Options += QString("2");
    }

    qDebug() << "Options = " << Options;

    QString Passwd;

    for(int j = 2; j >= 0; j--)
    {
        Passwd += QString::number((Clerk->Passwd[j] >> 4) & 0x0f);
        Passwd += QString::number(Clerk->Passwd[j] & 0x0f);
    }
    qDebug() << "Passwd = " << Passwd;

    QStringList str;

    str << Name << Options << Passwd;

    return str;
}
