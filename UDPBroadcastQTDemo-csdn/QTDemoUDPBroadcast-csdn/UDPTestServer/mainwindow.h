#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}
class QLabel;
class QUdpSocket;
class QListWidget;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void initList();
    void addBroadcastResItem(QByteArray data, QString ip);
    void BroadcastGetIpCommand();
    void initBroadcastListener();
    QString getIp();
private:
    Ui::MainWindow *ui;
private:
    QLabel *label;
    QListWidget* mlistWidget;
       /////////////
    QUdpSocket * receiver;
    QUdpSocket * sender;
private slots:
    void processPengingDatagram();
    ///////////
};

#endif // MAINWINDOW_H
