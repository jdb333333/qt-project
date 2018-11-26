#ifndef COMM_H
#define COMM_H


class comm
{
public:
    comm();
    ~comm();

    static int OneBCDToInt(char bcd);
    static int BCDToInt(unsigned char *bcd, int len);
    static float BcdToFloat(char *bcd, int len, int decimal);

    static void ChToStr(char *str, char ch, int len);
    static void StrFormat(char *str, int len, int formattype);
    static void NStrFormat(char *strs, char *str1, char *str2, char *str3, char *str4, char *str5, int len);

private:
    static void StrAlignment(char *buf, int buflen, char *data, int datalen, int flag);
};

#endif // COMM_H
