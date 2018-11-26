#ifndef RS232THREAD_H
#define RS232THREAD_H

#include <QThread>
#include <QString>

class QSerialPort;

class rs232thread : public QThread
{
    Q_OBJECT
public:
    rs232thread();
    ~rs232thread();

    void setPortnum(QString number)
    {
        portnumber = number;
    }
    void closemyserial()
    {
        serialcloseflag = true;
    }
    void getconfig()
    {
        configflag = true;
    }
    void setconfig(QByteArray Parameter)
    {
        ParameterData = Parameter;
        setconfigflag = true;
    }
    void startlogin();

private:
    int rcvackinfo(QSerialPort *myserial, const char *ackstr, const char *rcvstr1 = NULL,
                   const char *rcvstr2 = NULL, const char *rcvstr3 = NULL, const char *rcvstr4 = NULL);

protected:
    void run();

private:
    QString portnumber;
    QByteArray RxData;
    QByteArray TxData;
    QByteArray ParameterData;
    volatile bool serialcloseflag;
    volatile bool loginstate;
    volatile bool configflag;//true 获取配置参数 false 不获取配置参数
    volatile bool setconfigflag;//true 设置配置参数 false 不设置配置参数
    volatile bool loginflag;

signals:
    void comRx(QByteArray rcvData);
    void errState(int state);
};

#endif // RS232THREAD_H
