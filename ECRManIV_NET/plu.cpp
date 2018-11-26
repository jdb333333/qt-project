#include "plu.h"

plu::plu(QList<QList<QVariant> >* ptr)
{
    m_varListList = ptr;
}

plu::~plu()
{

}

int plu::DataParse(int index, char *buf)
{
    QString itemvalue;
    char databuf[64];
    int i = index;

    int columns = m_varListList->at(0).size();

    for(int j = 0; j < columns; j++)
    {
        QVariant item = m_varListList->at(i).at(j);
        itemvalue = item.value<QString>();

        memset(&Plu, 0, sizeof(Plu));

        strcpy(databuf, itemvalue.toLocal8Bit().data());

        if(j == 0) //random
        {
            for(int m = 0, k = 0; m < strlen(databuf); m++, k += 2)
            {
                Plu.Random[m] = ((databuf[k] - '0') & 0x0f) | (((databuf[k + 1] - '0') >> 4) & 0xf0);
            }

            qDebug("Plu.Random = %07x", Plu.Random);
        }

        if(j == 1) //name
        {
            strcpy(Plu.Name, databuf);

            qDebug("Plu.Name = %s", Plu.Name);
        }

        if(j == 2) //deptnum
        {
            Plu.Dept = atoi(databuf);

            qDebug("Plu.Dept = %d", Plu.Dept);
        }

        if(j == 3) //cost
        {
            for(int m = 0, k = 0; m < strlen(databuf); m++, k += 2)
            {
                Plu.Cost[m] = ((databuf[k] - '0') & 0x0f) | (((databuf[k + 1] - '0') >> 4) & 0xf0);
            }

            qDebug("Plu.Cost = %05x", Plu.Cost);
        }

        if(j == 4) //price
        {
            for(int m = 0, k = 0; m < strlen(databuf); m++, k += 2)
            {
                Plu.Price[0][m] = ((databuf[k] - '0') & 0x0f) | (((databuf[k + 1] - '0') >> 4) & 0xf0);
            }

            qDebug("Plu.Price[0] = %05x", Plu.Price[0]);
        }

        if(j == 5)
        {
            for(int m = 0, k = 0; m < strlen(databuf); m++, k += 2)
            {
                Plu.Inventory.Value[m] = ((databuf[k] - '0') & 0x0f) | (((databuf[k + 1] - '0') >> 4) & 0xf0);
            }

            qDebug("Plu.Inventory.Value = %08x", Plu.Inventory.Value);
        }
    }

    memcpy(buf, &Plu, sizeof(Plu));

    return sizeof(Plu);
}
