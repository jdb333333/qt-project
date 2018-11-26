#ifndef NETDIALOG_H
#define NETDIALOG_H

#include <QDialog>

namespace Ui {
class NetDialog;
}

class NetDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NetDialog(QWidget *parent = 0);
    ~NetDialog();

    int iptype;

private:
    Ui::NetDialog *ui;

signals:
    void getipinfo(int ip1, int ip2, int ip3, int ip4);
    void setlocalip(int ip1, int ip2, int ip3, int ip4);
private slots:
    void on_buttonBox_accepted();
};

#endif // NETDIALOG_H
