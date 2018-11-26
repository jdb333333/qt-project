#ifndef ECRMANIV_NET_H
#define ECRMANIV_NET_H

#include <QWidget>
#include <QModelIndex>

class reportdisp;
class tcpclient;
class udpclient;

#define IPMAX 100

namespace Ui {
class ECRManIV_NET;
}

class ECRManIV_NET : public QWidget
{
    Q_OBJECT

public:
    explicit ECRManIV_NET(QWidget *parent = 0);
    ~ECRManIV_NET();

    char IPGROUP[IPMAX][64];

private slots:
    void on_actionADD_triggered();

private:
    Ui::ECRManIV_NET *ui;

    tcpclient *clientsocket;
    udpclient *udpclientsocket;
    int ipcount;
    bool ipsearchok;
    int ZNo;

protected:
    bool eventFilter(QObject *, QEvent *);

private slots:
    void getipitem(int ip1, int ip2, int ip3, int ip4);
    void setlocalip(int ip1, int ip2, int ip3, int ip4);
    void searchipok(int ipitem);
    void on_tableWidget_2_clicked(const QModelIndex &index);
    void tcpunconnect();
    void tcpconnect();
    void tcprecvdata(char *buf, int len);
    void tcpsenddata(char *buf, int len);
    void on_zport_clicked();
    void on_clerk_clicked();
    void on_actionDELETE_triggered();

    void on_plu_clicked();

    void on_pushButton_clicked();

    void on_actionLOCAL_triggered();

public:
    void tcpgetdata(char *buf, int len);
    void StripToZno(QString ipstr);
};

#endif // ECRMANIV_NET_H
