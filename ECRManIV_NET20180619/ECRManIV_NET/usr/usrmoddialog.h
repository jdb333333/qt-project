#ifndef USRMODDIALOG_H
#define USRMODDIALOG_H

#include <QDialog>

#define ADDUSR 0
#define MODPWD 1

namespace Ui {
class UsrModDialog;
}

class UsrModDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UsrModDialog(QWidget *parent = 0);
    ~UsrModDialog();

    void setfunc(int flag);

private slots:
    void on_okbtn_clicked();

private:
    Ui::UsrModDialog *ui;
};

#endif // USRMODDIALOG_H
