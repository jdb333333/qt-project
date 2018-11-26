#include "plu.h"
#include <QString>
#include <QVariantList>

#include <QDebug>

plu::plu(QList<QList<QVariant> >* ptr)
{
    m_varListList = ptr;
}

plu::~plu()
{

}

void plu::BcdToStr(char *str, char *bcd, int len)
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

float plu::BcdToFloat(char *bcd, int len, int decimal)
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

int plu::DataParse(char *buf, int len)
{
    Plu = (P_PLU *)buf;

    QVariantList pluinfo;
    char databuf[64] = {0};
    char str[64] = {0};
    float tmpdata;

#if 0
    qDebug() << "=================================";
    for(int j = 0; j < len; j++)
    {
        qDebug("buf[%d] = %02x", j, buf[j]);
    }
    qDebug() << "=================================";
#endif

    int rows = m_varListList->size();

    qDebug() << "--->rows = " << rows;

    if(rows == 0)
    {
        QVariantList tablehead;
        tablehead << "Random" << "Name" << "Dept" << "Cost" << "Price" << "Inventory" << "Offer";
        m_varListList->push_back(tablehead);
    }

    QString Random, Name, Dept, Price, Cost, Inventory, Offer;

#if 0
    if(rows >= 80 && rows < 100)
    {
        for(int count = 0; count < 7; count++)
        {
            qDebug("%02x", Plu->Random[count]);
        }
    }
#endif

    memset(databuf, 0, sizeof(databuf));
    memcpy(databuf, Plu->Random, 7);
    BcdToStr(str, databuf, 7);
    Random.sprintf("%s", str);

    Name.sprintf("%s", Plu->Name);
    Dept.sprintf("%d", Plu->Dept + 1);

    memset(databuf, 0, sizeof(databuf));
    memcpy(databuf, Plu->Price[0], 5);
    tmpdata = BcdToFloat(databuf, 5, 2);
    Price.sprintf("%0.2f", tmpdata);

    memset(databuf, 0, sizeof(databuf));
    memcpy(databuf, Plu->Cost, 5);
    tmpdata = BcdToFloat(databuf, 5, 2);
    Cost.sprintf("%0.2f", tmpdata);

    memset(databuf, 0, sizeof(databuf));
    memcpy(databuf, Plu->Inventory.Value, 8);
#if 0
    qDebug("------>Plu->Inventory.Sign = %02x", Plu->Inventory.Sign);
    for(int k = 0; k < 8; k++)
    {
        qDebug("-------->databuf[%d] = %02x", k, databuf[k]);
    }
#endif
    tmpdata = BcdToFloat(databuf, 8, Plu->Inventory.Sign);
    Inventory.sprintf("%0.2f", tmpdata);

	Offer.sprintf("%d", Plu->OFFIndex);

    pluinfo << Random << Name << Dept << Cost << Price << Inventory << Offer;

    m_varListList->push_back(pluinfo);

    return 0;
}

int plu::DataCreate(int index, char *buf)
{
    QString itemvalue;
    char databuf[64];
    int i = index;

    Plu = (P_PLU *)buf;

    int columns = m_varListList->at(0).size();

    memset(Plu, 0, sizeof(P_PLU));

    for(int j = 0; j < columns; j++)
    {
        QVariant item = m_varListList->at(i).at(j);
        itemvalue = item.value<QString>();

        memset(databuf, 0, 64);
        strcpy(databuf, itemvalue.toLocal8Bit().data());

        if(j == 0) //random
        {
            //qDebug("%s", databuf);
            for(int m = 0, k = strlen(databuf) - 1; k >= 0; m++)
            {
                Plu->Random[m] = (databuf[k--] - '0') & 0x0f;
                if(k < 0)
                {
                    //qDebug("Plu.Random[%d] = %02x", m, Plu->Random[m]);
                    break;
                }
                Plu->Random[m] |= ((databuf[k--] - '0') << 4) & 0xf0;
                //qDebug("Plu.Random[%d] = %02x", m, Plu->Random[m]);
            }
        }

        if(j == 1) //name
        {
            strcpy(Plu->Name, databuf);

            //qDebug("Plu.Name = %s", Plu->Name);
        }

        if(j == 2) //deptnum
        {
            Plu->Dept = item.value<int>() - 1;

            //qDebug("Plu.Dept = %d", Plu->Dept);
        }

        if(j == 3) //cost
        {
            //qDebug("%s", databuf);

            int tmpdata = item.value<float>() * 100;
            QString dd;
            dd.sprintf("%d", tmpdata);

            memset(databuf, 0, sizeof(databuf));
            strcpy(databuf, dd.toLocal8Bit());
            //qDebug("%s", databuf);
            for(int m = 0, k = strlen(databuf) - 1; k >= 0; m++)
            {
                Plu->Cost[m] = (databuf[k--] - '0') & 0x0f;
                if(k < 0)
                {
                    //qDebug("Plu.Cost[%d] = %02x", m, Plu->Cost[m]);
                    break;
                }
                Plu->Cost[m] |= ((databuf[k--] - '0') << 4) & 0xf0;
                //qDebug("Plu.Cost[%d] = %02x", m, Plu->Cost[m]);
            }
        }

        if(j == 4) //price
        {
            int tmpdata = item.value<float>() * 100;
            QString dd;
            dd.sprintf("%d", tmpdata);

            memset(databuf, 0, sizeof(databuf));
            strcpy(databuf, dd.toLocal8Bit());

            //qDebug("%s", databuf);
            for(int m = 0, k = strlen(databuf) - 1; k >= 0; m++)
            {
                Plu->Price[0][m] = (databuf[k--] - '0') & 0x0f;
                if(k < 0)
                {
                    //qDebug("Plu.Price[0][%d] = %02x", m, Plu->Price[0][m]);
                    break;
                }
                Plu->Price[0][m] |= ((databuf[k--] - '0') << 4) & 0xf0;
                //qDebug("Plu.Price[0][%d] = %02x", m, Plu->Price[0][m]);
            }
        }

        if(j == 5)
        {
            int tmpdata = item.value<float>() * 100;
            QString dd;
            dd.sprintf("%d", tmpdata);

            memset(databuf, 0, sizeof(databuf));
            strcpy(databuf, dd.toLocal8Bit());
            //qDebug("%s", databuf);
            for(int m = 0, k = strlen(databuf) - 1; k >= 0; m++)
            {
                Plu->Inventory.Value[m] = (databuf[k--] - '0') & 0x0f;
                if(k < 0)
                {
                    //qDebug("Plu.Price[0][%d] = %02x", m, Plu->Inventory.Value[m]);
                    break;
                }
                Plu->Inventory.Value[m] |= ((databuf[k--] - '0') << 4) & 0xf0;
                //qDebug("Plu.Price[0][%d] = %02x", m, Plu->Inventory.Value[m]);
            }
            Plu->Inventory.Sign = 0x02;
        }

		if(j == 6)
		{
			Plu->OFFIndex = item.value<int>();
		}
    }

    return sizeof(P_PLU);
}
