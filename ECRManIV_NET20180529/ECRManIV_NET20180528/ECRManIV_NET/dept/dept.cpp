#include "dept.h"
#include "../tcpclient.h"

#include <QString>
#include <QVariantList>
#include <QDebug>

D_DEPT dept_init =
{
    {0,0,0,0,0,0,0}, 	//Random
    "Dept",	//name
    01,0x0b,0xc0,0,0,
    {0,0,0,0,0},		//Price
    {0,0,0,0,0}         //PriceMax
};

dept::dept(QList<QList<QVariant> >* ptr)
{
    m_varListList = ptr;
}

dept::~dept()
{

}

void dept::BcdToStr(char *str, char *bcd, int len)
{
    int j = 0;
    bool va = false;
    bool low = false;

    int i;
    int lowv, highv;

    for(i = len - 1; i >= 0; i--)
    {
        //qDebug("--->bcd[%d] = %02x", i, bcd[i]);
        if((bcd[i] & 0xff) > 0)
        {
            va = true;
            highv = (bcd[i] >> 4) & 0x0f;
            if(highv > 0)
            {
                //
            }
            else
            {
                low = true;
            }
            break;
        }
    }

    //qDebug() << "--->i = " << i;



    for(j = 0; i >= 0; i--)
    {
        highv = (bcd[i] >> 4) & 0x0f;
        lowv = bcd[i] & 0x0f;
        //qDebug("--->highv = %d, lowv = %d", highv, lowv);

        if(low)
        {
            str[j++] = lowv + '0';
            low = false;
        }
        else
        {
            str[j++] = highv + '0';
            str[j++] = lowv + '0';
        }
    }

    //qDebug() << "--->str = " << str;
}

float dept::BcdToFloat(char *bcd, int len, int decimal)
{
    int count;
    float data = 0;
    int tmp1, tmp2;

    if(bcd[len - 1] == 0xff)
    {
        return 0;
    }

    //qDebug() << "------->len = " << len;

    for(count = 1; count <= len; count++)
    {
        data *= 100.0;
        tmp1 = bcd[len - count] & 0x0f;
        tmp2 = (bcd[len - count] >> 4) & 0x0f;
        //qDebug() << "tmp2 = " << tmp2 << "tmp1 = " << tmp1;
        data += tmp2 * 10 + tmp1;
        //qDebug() << "data = tmp2*10 + tmp1 = " << data;
    }

    for(count = 0; count < decimal; count++)
    {
        data /= 10.0;
    }

    //qDebug() << "data = " << data;

    return data;
}

int dept::DataParse(char *buf, int len)
{
    Dept = (D_DEPT *)buf;

    QVariantList deptinfo;
    char databuf[64] = {0};
    char str[64] = {0};
    float tmpdata;

    int rows = m_varListList->size();

    qDebug() << "--->rows = " << rows;

    if(rows == 0)
    {
        QVariantList tablehead;
        tablehead << "Indx" << "Name" << "Group" << "Options" << "Tax" << "Price" << "PriceMax" << "Kp";
        m_varListList->push_back(tablehead);
    }

    QString Indx, Name, Group, Options, Tax, Price, PriceMax, Kp;

    if(rows == 0)
    {
        Indx = QString::number(1, 10);
    }
    else
    {
        Indx = QString::number(rows, 10);
    }

    Name.sprintf("%s", Dept->Name);
    Group.sprintf("%d", Dept->Group + 1);

    for(int count = 7; count >= 0; count--)
    {
        if((Dept->Options >> count) & 0x01)
        {
            Options.append(QString::number(count + 1, 10));
        }
    }

    Tax = QString::number(Dept->Tax, 10);

    memset(databuf, 0, sizeof(databuf));
    memcpy(databuf, Dept->Price, 5);
    tmpdata = BcdToFloat(databuf, 5, 2);
    Price.sprintf("%0.2f", tmpdata);

    memset(databuf, 0, sizeof(databuf));
    memcpy(databuf, Dept->PriceMax, 5);
    tmpdata = BcdToFloat(databuf, 5, 2);
    PriceMax.sprintf("%0.2f", tmpdata);

    for(int count = 7; count >= 0; count--)
    {
        if((Dept->Kp >> count) & 0x01)
        {
            Kp.append(QString::number(count + 1, 10));
        }
    }

    deptinfo << Indx << Name << Group << Options << Tax << Price << PriceMax << Kp;

    m_varListList->push_back(deptinfo);

    return 0;
}

int dept::DataCreate(int index, char *buf)
{
    QString itemvalue;
    char databuf[64];
    int i = index;
    int tmpindx;

    Dept = (D_DEPT *)buf;

    int columns = m_varListList->at(0).size();

    memset(Dept, 0, sizeof(D_DEPT));
    Dept->Print = 0x0b;

    for(int j = 1; j < columns; j++)
    {
        QVariant item = m_varListList->at(i).at(j);
        itemvalue = item.value<QString>();

        memset(databuf, 0, 64);
        strcpy(databuf, itemvalue.toLocal8Bit().data());

        if(j == 1) //Name
        {
            strcpy(Dept->Name, databuf);

            qDebug("Dept->Name = %s", Dept->Name);
        }

        if(j == 2) //Group
        {
            Dept->Group = item.value<int>() - 1;

            qDebug("Dept->Group = %d", Dept->Group);
        }

        if(j == 3) //Options
        {
            for(int count = 0; count < strlen(databuf); count++)
            {
                tmpindx = databuf[count] - '0';

                if(tmpindx)
                {
                    Dept->Options |= 0x01 << (tmpindx - 1);
                }
            }

            qDebug("Dept->Options = %02x", Dept->Options);
        }

        if(j == 4) //Tax
        {
            tmpindx = databuf[0] - '0';

            if(tmpindx < 7 && tmpindx > 0)
            {
                Dept->Tax = tmpindx;
            }

            qDebug("Dept->Tax = %d", Dept->Tax);
        }

        if(j == 5) //Price
        {
            int tmpdata = item.value<float>() * 100;
            QString dd;
            dd.sprintf("%d", tmpdata);

            memset(databuf, 0, sizeof(databuf));
            strcpy(databuf, dd.toLocal8Bit());

            //qDebug("%s", databuf);
            for(int m = 0, k = strlen(databuf) - 1; k >= 0; m++)
            {
                Dept->Price[m] = (databuf[k--] - '0') & 0x0f;
                if(k < 0)
                {
                    //qDebug("Plu.Price[0][%d] = %02x", m, Plu->Price[0][m]);
                    break;
                }
                Dept->Price[m] |= ((databuf[k--] - '0') << 4) & 0xf0;
                qDebug("Dept.Price[%d] = %02x", m, Dept->Price[m]);
            }
        }

        if(j == 6) //PriceMax
        {
            int tmpdata = item.value<float>() * 100;
            QString dd;
            dd.sprintf("%d", tmpdata);

            memset(databuf, 0, sizeof(databuf));
            strcpy(databuf, dd.toLocal8Bit());

            //qDebug("%s", databuf);
            for(int m = 0, k = strlen(databuf) - 1; k >= 0; m++)
            {
                Dept->PriceMax[m] = (databuf[k--] - '0') & 0x0f;
                if(k < 0)
                {
                    //qDebug("Plu.Price[0][%d] = %02x", m, Plu->Price[0][m]);
                    break;
                }
                Dept->PriceMax[m] |= ((databuf[k--] - '0') << 4) & 0xf0;
                qDebug("Plu.PriceMax[%d] = %02x", m, Dept->PriceMax[m]);
            }
        }

        if(j == 7) //Kp
        {
            for(int count = 0; count < strlen(databuf); count++)
            {
                tmpindx = databuf[count] - '0';

                if(tmpindx > 0 && tmpindx < 9)
                {
                    Dept->Kp |= 0x01 << (tmpindx - 1);
                }
            }

            qDebug("Dept->Kp = %02x", Dept->Kp);
        }
    }

    return sizeof(D_DEPT);
}

