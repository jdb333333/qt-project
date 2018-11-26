#ifndef CONFIGURE_H
#define CONFIGURE_H

#define VAR_NAME_LEN 64
#define VAR_VALUE_LEN 64
#define VAR_GROUP_LEN 50

class QByteArray;
class QString;

typedef enum {
    DEVICENAME,
    DEVICEID,
    USERNAME,
    PASSWORD,
    CONNMODE,
    TAPPINGMODE,
    SERIALBAUDRATE,
    USBMODE,
    LPTMODE,
    TIMEOUT,
    SENDINGMODE,
    KEY,
    DFSMODE,
    CONSOLEBAUDRATE,
    APN,
    ACCGPRS,
    USERGPRS,
    PASSWDGPRS,
    WIFISSID,
    WIFIASM,
    WIFIPASSWORD,
    IPSERVER,
    PORTSERVER,
    SSINTERVAL,
    ALARM1,
    ALARM2,
    ALARM3,
    ALARM4,
    ALARM5,
    ALARM6,
    ALARM7,
    ALARM8,
    ALARM9,
    ALARM10,
    ALARM11,
    ALARM12,
    OVPNSERVICE,
    OVPNIPSERVER,
    OVPNUSER,
    OVPNPASSWD,
    PPTPSERVICE,
    PPTPIPSERVER,
    PPTPUSER,
    PPTPPASSWD,
    TELNETSERVICE,
    SSHSERVICE,
    FTPSERVICE,
    BUZZEREN,
    BUZZERFREQ,
}GROUPID;

struct consolevar{
    char name[VAR_NAME_LEN];
    char value[VAR_VALUE_LEN];
};

class configure
{
public:
    configure();
    ~configure();

    void Clear_Configure();
    void Get_Configure(QByteArray PARAMETER);
    QString Set_Configure(char *value, GROUPID varID);
    QByteArray parametervalue(GROUPID vargroupid);

private:
    int console_add(const char *str, int groupid);
    int console_init(void);

private:
    struct consolevar vargroup[VAR_GROUP_LEN];
};

#endif // CONFIGURE_H
