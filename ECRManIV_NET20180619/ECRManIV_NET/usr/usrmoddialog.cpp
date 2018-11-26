#include "usrmoddialog.h"
#include "ui_usrmoddialog.h"

#include "./usr/usrdb.h"

#include <QMessageBox>

UsrModDialog::UsrModDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UsrModDialog)
{
    ui->setupUi(this);
}

UsrModDialog::~UsrModDialog()
{
    delete ui;
}

void UsrModDialog::setfunc(int indx)
{
    ui->stackedWidget->setCurrentIndex(indx);

    if(indx == ADDUSR)
    {
        ui->usernameedit->setFocus();
    }
    if(indx == MODPWD)
    {
        ui->NewNameEdit->setFocus();
    }
}

void UsrModDialog::on_okbtn_clicked()
{
    int ret;
    int indx = ui->stackedWidget->currentIndex();

    USRINFO newusrinfo;

    memset(&newusrinfo, 0, sizeof(newusrinfo));

    if(indx == 0)
    {
        QString NewUserName = ui->usernameedit->text().trimmed();

        if(NewUserName.size() > 0)
        {
            QString Pwd1 = ui->Password1edit->text();
            QString Pwd2 = ui->Password2edit->text();

            if(Pwd1.size() > 0 && Pwd1 == Pwd2)
            {
                memcpy(&newusrinfo, &UsrDb->UsrInfo, sizeof(UsrDb->UsrInfo));

                memset(newusrinfo.name, 0, sizeof(newusrinfo.name));
                strcpy(newusrinfo.name, NewUserName.toLocal8Bit().data());

                memset(newusrinfo.password, 0, sizeof(newusrinfo.password));
                strcpy(newusrinfo.password, Pwd1.toLocal8Bit().data());

                ret = UsrDb->checkusr(NewUserName);
                if(ret < 0)
                {
                    QMessageBox::warning(this, tr("Warning!"),
                                tr("user is exist!"),
                                QMessageBox::Yes);
                    ui->usernameedit->clear();
                    ui->Password1edit->clear();
                    ui->Password2edit->clear();
                    ui->usernameedit->setFocus();
                }
                else
                {
                    UsrDb->inserttable(newusrinfo);
                    accept();
                }
            }
            else
            {
                QMessageBox::warning(this, tr("Warning!"),
                            tr("new password set err!"),
                            QMessageBox::Yes);
                ui->usernameedit->clear();
                ui->Password1edit->clear();
                ui->Password2edit->clear();
                ui->usernameedit->setFocus();
            }
        }
        else
        {
            QMessageBox::warning(this, tr("Warning!"),
                        tr("user name set err!"),
                        QMessageBox::Yes);
            ui->usernameedit->clear();
            ui->Password1edit->clear();
            ui->Password2edit->clear();
            ui->usernameedit->setFocus();
        }
    }

    if(indx == 1)
    {
        QString NewName = ui->NewNameEdit->text().trimmed();
        if(NewName.size() == 0)
        {
            QMessageBox::warning(this, tr("Warning!"),
                        tr("new name set err!"),
                        QMessageBox::Yes);
            ui->NewNameEdit->clear();
            ui->OldPwdedit->clear();
            ui->NewPwd1edit->clear();
            ui->NewPwd2edit->clear();
            ui->NewNameEdit->setFocus();
        }
        else
        {
            QString OldPwd = ui->OldPwdedit->text();
            QString UserPwd = QString("%1").arg(UsrDb->UsrInfo.password);
            if(UserPwd == OldPwd)
            {
                QString NewPwd1 = ui->NewPwd1edit->text();
                QString NewPwd2 = ui->NewPwd2edit->text();

                if(NewPwd1.size() > 0 && NewPwd1 == NewPwd2)
                {
                    memcpy(&newusrinfo, &UsrDb->UsrInfo, sizeof(UsrDb->UsrInfo));

                    memset(newusrinfo.name, 0, sizeof(newusrinfo.name));
                    strcpy(newusrinfo.name, NewName.toLocal8Bit().data());

                    memset(newusrinfo.password, 0, sizeof(newusrinfo.password));
                    strcpy(newusrinfo.password, NewPwd1.toLocal8Bit().data());

                    UsrDb->modusr(UsrDb->UsrInfo, newusrinfo);
                    memcpy(&UsrDb->CUsrInfo, &newusrinfo, sizeof(USRINFO));
                    accept();
                }
                else
                {
                    QMessageBox::warning(this, tr("Warning!"),
                                tr("new password set err!"),
                                QMessageBox::Yes);
                    ui->NewNameEdit->clear();
                    ui->OldPwdedit->clear();
                    ui->NewPwd1edit->clear();
                    ui->NewPwd2edit->clear();
                    ui->NewNameEdit->setFocus();
                }
            }
            else
            {
                QMessageBox::warning(this, tr("Warning!"),
                            tr("old password err!"),
                            QMessageBox::Yes);
                ui->NewNameEdit->clear();
                ui->OldPwdedit->clear();
                ui->NewPwd1edit->clear();
                ui->NewPwd2edit->clear();
                ui->NewNameEdit->setFocus();
            }
        }
    }
}
