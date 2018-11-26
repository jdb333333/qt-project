#include "configure.h"

#include <QString>
#include <QByteArray>

configure::configure()
{
    console_init();
}

configure::~configure()
{

}

void configure::Clear_Configure()
{
    for(int i; i < VAR_GROUP_LEN; i++)
    {
        memset(vargroup[i].value, 0, VAR_VALUE_LEN);
    }
}

QString configure::Set_Configure(char *value, GROUPID varID)
{
    int ret;
    char prefix1[] = "<\0";
    char suffix1[] = ">\0";
    char prefix2[] = "</\0";
    char suffix2[] = ">\0";
    QString setvar;

    setvar.clear();

    qDebug("value = %s, vargroup.value = %s", value, vargroup[varID].value);
    ret = strncmp(value, vargroup[varID].value,
                  strlen(value) > strlen(vargroup[varID].value) ? strlen(value) : strlen(vargroup[varID].value));
    if(ret != 0){
        setvar.append(prefix1);
        setvar.append(vargroup[varID].name);
        setvar.append(suffix1);

        setvar.append(value);

        setvar.append(prefix2);
        setvar.append(vargroup[varID].name);
        setvar.append(suffix2);

        memset(vargroup[varID].value, 0, sizeof(vargroup[varID].value));
        memcpy(vargroup[varID].value, value, strlen(value));
    }

    return setvar;
}

void configure::Get_Configure(QByteArray PARAMETER)
{
    char *p, *q;
    char prefix1[] = "<\0";
    char suffix1[] = ">\0";
    char prefix2[] = "</\0";
    char suffix2[] = ">\n\0";
    int i;
    char tmpname[VAR_NAME_LEN];
    bool modflag;
    bool usermodflag;
    bool passmodflag;

    char buffer[4096];

    memcpy(buffer, PARAMETER.data(), PARAMETER.size());
    buffer[PARAMETER.size()] = 0;

    modflag = false;
    usermodflag = false;
    passmodflag = false;

    for(i = 0; i < VAR_GROUP_LEN; i++){
        memset(tmpname, '\0', sizeof(tmpname));
        strcat(tmpname, prefix1);
        strcat(tmpname, vargroup[i].name);
        strcat(tmpname, suffix1);
        qDebug("tmpgname = %s", tmpname);
        if(p = strstr(buffer, tmpname)){
            qDebug("tmpgname = %s", tmpname);
            modflag = true;
            p = strstr(p, suffix1);
            p++;
            if(q = strstr(p, prefix2)){
                memset(vargroup[i].value, '\0', sizeof(vargroup[i].value));
                memcpy(vargroup[i].value, p, (char *)q - (char *)p);
                qDebug("value = %s", vargroup[i].value);
            }
        }
    }
}

int configure::console_add(const char *str, int groupid)
{
    memset(vargroup[groupid-1].name, '\0', 128);
    strcat(vargroup[groupid-1].name, str);

    qDebug("vargroup.name = %s", vargroup[groupid-1].name);

    return 0;
}

QByteArray configure::parametervalue(GROUPID vargroupid)
{
    QByteArray varvalue;
    varvalue.append(vargroup[vargroupid].value);
    return varvalue;
}

int configure::console_init(void)
{
    memset(&vargroup, 0, sizeof(vargroup));
    console_add("DEVICE NAME", 1);
    console_add("DEVICE ID", 2);
    console_add("USERNAME", 3);
    console_add("PASSWORD", 4);
    console_add("CONNMODE", 5);
    console_add("TAPPINGMODE", 6);
    console_add("SERIALBAUDRATE", 7);
    console_add("USBMODE", 8);
    console_add("LPTMODE", 9);
    console_add("TIMEOUT", 10);
    console_add("SENDINGMODE", 11);
    console_add("KEY", 12);
    console_add("DFSMODE", 13);
    console_add("CONSOLEBAUDRATE", 14);
    console_add("APN", 15);
    console_add("ACCGPRS", 16);
    console_add("USERGPRS", 17);
    console_add("PASSWDGPRS", 18);
    console_add("WIFISSID", 19);
    console_add("WIFIASM", 20);
    console_add("WIFIPASSWORD", 21);
    console_add("IPSERVER", 22);
    console_add("PORTSERVER", 23);
    console_add("SSINTERVAL", 24);
    console_add("ALARM1", 25);
    console_add("ALARM2", 26);
    console_add("ALARM3", 27);
    console_add("ALARM4", 28);
    console_add("ALARM5", 29);
    console_add("ALARM6", 30);
    console_add("ALARM7", 31);
    console_add("ALARM8", 32);
    console_add("ALARM9", 33);
    console_add("ALARM10", 34);
    console_add("ALARM11", 35);
    console_add("ALARM12", 36);
    console_add("OVPNSERVICE", 37);
    console_add("OVPNIPSERVER", 38);
    console_add("OVPNUSER", 39);
    console_add("OVPNPASSWD", 40);
    console_add("PPTPSERVICE", 41);
    console_add("PPTPIPSERVER", 42);
    console_add("PPTPUSER", 43);
    console_add("PPTPPASSWD", 44);
    console_add("TELNETSERVICE", 45);
    console_add("SSHSERVICE", 46);
    console_add("FTPSERVICE", 47);
    console_add("BUZZEREN", 48);
    console_add("BUZZERFREQ", 49);

    return 0;
}
