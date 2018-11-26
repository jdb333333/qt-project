#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

namespace Ui {
class Dialog;
}

class rs232thread;
class configure;
class SwitchButton;

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
private slots:
    void on_pushButton_port_clicked();

private:
    void initPort();

    int PortOpen();
    int PortWrite();
    int PortRead();
    int PortClose();

    void ParameterDisplay();
    QString ParameterSet();
    void SignalDisplay(QByteArray sigData);
    void AlarmDisplay(QByteArray alarmData);
    void FileDataDisplay(QByteArray FileData);

private:
    Ui::Dialog *ui;
    QSerialPort *myserial;
    QByteArray RxData;
    QByteArray TxData;

    rs232thread *mythread;

    configure *myconfigure;

    SwitchButton *powerbtn;
    SwitchButton *serialbtn;
    SwitchButton *parallelbtn;
    SwitchButton *usbbtn;
    SwitchButton *batterybtn;
    SwitchButton *sdbtn;

    volatile bool com_opened;
    volatile bool com_stopped;
    volatile bool tx_event;
    volatile bool rx_event;

    volatile bool usbstate;
    volatile bool serialstate;
    volatile bool parallelstate;
    volatile bool powerstate;

private slots:
    void comRx(QByteArray rcvData);
    void on_radioButton_usb_toggled(bool checked);
    void on_radioButton_serial_toggled(bool checked);
    void on_radioButton_parallel_toggled(bool checked);
    void on_radioButton_gsm_toggled(bool checked);
    void on_radioButton_wifi_toggled(bool checked);
    void on_checkBox_ovpn_toggled(bool checked);
    void on_checkBox_pptp_toggled(bool checked);
    void on_pushButton_download_clicked();
    void on_pushButton_update_clicked();
    void on_pushButton_login_clicked();
};

#endif // DIALOG_H
