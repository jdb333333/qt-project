#include "comm.h"

#include <QString>

comm::comm()
{

}

comm::~comm()
{

}

int comm::OneBCDToInt(char bcd)
{
    int data;
    int high, low;

    high = (bcd >> 4) & 0x0f;

    low = bcd & 0x0f;

    data = high * 10 + low;

    return data;
}

int comm::BCDToInt(unsigned char *bcd, int len)
{
    int count;
    float data = 0;
    int tmp1, tmp2;

    if(bcd[len - 1] == 0xff)
    {
        return 0;
    }

    for(count = 1; count <= len; count++)
    {
        data *= 100.0;
        tmp1 = bcd[len - count] & 0x0f;
        tmp2 = (bcd[len - count] >> 4) & 0x0f;

        data += tmp2 * 10 + tmp1;
    }

    return data;
}

float comm::BcdToFloat(char *bcd, int len, int decimal)
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

void comm::ChToStr(char *str, char ch, int len)
{
    for(int i = 0; i < len; i++)
    {
        str[i] = ch;
    }
}

void comm::StrFormat(char *str, int len, int formattype)
{
    char ch[len];
    int size;

    memset(ch, ' ', len);

    size = strlen(str);

    if(formattype == 1) //§æ§ª?§ë?§¥§è?§°§é?§¬
    {
        if(len - size > 0)
        {
            memcpy(ch + (len - size)/2, str, size);
        }
        else
        {
            memcpy(ch, str, size);
        }
    }
    else if(formattype == 0) //§ç§©?§ê§°§«§ç?§«§ë§¯?
    {
        memcpy(ch, str, size);
    }
    else
    {
        memcpy(ch + formattype, str, size);
    }

    memcpy(str, ch, len);
}

void comm::StrAlignment(char *buf, int buflen, char *data, int datalen, int flag)
{
    int spacelen;

    if(flag == 2) //?§Ñ§®?????
    {
        if(datalen < buflen)
        {
            spacelen = (buflen - datalen) / 2;
            memcpy(buf + spacelen, data, datalen);
        }
        else
        {
            memcpy(buf, data, buflen);
        }
    }
}

void comm::NStrFormat(char *strs, char *str1, char *str2, char *str3, char *str4, char *str5, int len)
{
    char ch[len];
    int size1 = 0, size2 = 0, size3 = 0, size4 = 0, size5 = 0;
    int strcount = 0;
    int seclen;

    if(str1)
    {
        size1 = strlen(str1);
        strcount++;
    }

    if(str2)
    {
        size2 = strlen(str2);
        strcount++;
    }

    if(str3)
    {
        size3 = strlen(str3);
        strcount++;
    }

    if(str4)
    {
        size4 = strlen(str4);
        strcount++;
    }

    if(str5)
    {
        size5 = strlen(str5);
        strcount++;
    }

    seclen = len / strcount;

    memset(ch, ' ', len);

    strcount = 0;
    if(size1 > 0)
    {
        StrAlignment(ch + strcount, seclen, str1, size1, 2);
        strcount += seclen;
    }
    if(size2 > 0)
    {
        StrAlignment(ch + strcount, seclen, str2, size2, 2);
        strcount += seclen;
    }
    if(size3 > 0)
    {
        StrAlignment(ch + strcount, seclen, str3, size3, 2);
        strcount += seclen;
    }
    if(size4 > 0)
    {
        StrAlignment(ch + strcount, seclen, str4, size4, 2);
        strcount += seclen;
    }
    if(size5 > 0)
    {
        StrAlignment(ch + strcount, seclen, str5, size5, 2);
        strcount += seclen;
    }
    memcpy(strs, ch, len);
}
