#ifndef USRDIALOG_H
#define USRDIALOG_H

#include <QDialog>

#define ORDUSRGROUP 1
#define SUPUSRGROUP 2

namespace Ui {
class usrDialog;
}

class QModelIndex;

class usrDialog : public QDialog
{
    Q_OBJECT

public:
    explicit usrDialog(QWidget *parent = 0);
    ~usrDialog();

private slots:
    void on_add_clicked();

    void on_OrdinaryUser_clicked();

    void on_SupevisorUser_clicked();

    void on_modpwd_clicked();

    void on_UserList_clicked(const QModelIndex &index);

    void on_delete_2_clicked();

    void on_setperm_clicked();

private:
    Ui::usrDialog *ui;

    int usrgroup;
    char usrdata[4096];

    void getusrdata();
    void setusrlist(QString UsrName);
    void setUsrPerm();
};

#endif // USRDIALOG_H
