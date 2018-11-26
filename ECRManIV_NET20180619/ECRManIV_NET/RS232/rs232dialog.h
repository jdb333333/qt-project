#ifndef RS232DIALOG_H
#define RS232DIALOG_H

#include <QDialog>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

class rs232thread;

namespace Ui {
class RS232Dialog;
}

class RS232Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit RS232Dialog(QWidget *parent = 0);
    ~RS232Dialog();

signals:
    void itempro();

private slots:
    void on_pushButton_update_clicked();

    void on_pushButton_clicked();

    void on_pushButton_port_clicked();

    void itempro_slot();
    void errState_slot(int state);

private:
    void initPort();

    int PortOpen();
    int PortWrite();
    int PortRead();
    int PortReadOneByte();
    int PortClose();

    int SendOneChar(char data);
    int ReceiveOneChar(char *data);

    unsigned char HexAcc(QByteArray Data);
    void StrToHex(QByteArray Data, char *databuf);
    int PreUpdate();
    int UpdateFirm();

private:
    Ui::RS232Dialog *ui;

    rs232thread *mythread;

    QSerialPort *myserial;
    QByteArray RxData;
    QByteArray TxData;
    QStringList number_list;

    volatile bool com_opened;
    volatile bool com_stopped;
    volatile bool tx_event;
    volatile bool rx_event;

    int onecountmax;
    int itemindex;
    int senditemmax;
};

#endif // RS232DIALOG_H
