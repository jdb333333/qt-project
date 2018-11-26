#ifndef RS232THREAD_H
#define RS232THREAD_H

#include <QThread>
#include <QStringList>
#include <QString>
#include <QObject>

#define OPENFAILED 0x01
#define NODATA 0x02
#define DATAERR 0x03
#define DATATIMEOUT 0x04

class rs232thread : public QThread
{
    Q_OBJECT
public:
    rs232thread();
    ~rs232thread();

    void setMessage(QStringList str_list)
    {
        messageStrList = str_list;
    }

    void setPortnum(QString number)
    {
        portnumber = number;
    }
    void changeComState(bool stat)
    {
        com_opened=stat;
    }
    void stop()
    {
       stopped=true;
    }

    void setitemcount(int count)
    {
        itemcount = count;
    }

protected:
    void run();

private:
    QString portnumber;
    QByteArray RxData;
    QByteArray TxData;
    QStringList messageStrList;

    int itemcount;

    volatile bool com_opened;
    volatile bool stopped;

signals:
    void comTx();
    void errState(int state);
};

#endif // RS232THREAD_H
