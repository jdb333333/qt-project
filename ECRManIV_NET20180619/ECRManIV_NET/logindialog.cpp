#include "logindialog.h"
#include "ui_logindialog.h"

#include "./usr/usrdb.h"

#include <QMessageBox>
#include <QDebug>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);

    setWindowTitle(QString("User Login"));
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_login_clicked()
{
    int ret = 0;

    // �ж��û����������Ƿ���ȷ��
    // ��������򵯳�����Ի���
    memset(&UsrDb->CUsrInfo, 0, sizeof(USRINFO));

    QString Name = ui->usredit->text().trimmed();
    strcpy(UsrDb->CUsrInfo.name, Name.toLocal8Bit().data());

    ret = UsrDb->selecttable(&UsrDb->CUsrInfo);

    qDebug() << "ret = " << ret;

    if(ret < 0)
    {
        QMessageBox::warning(this, tr("Warning!"),
                    tr("username is not exist!"),
                    QMessageBox::Yes);
        // ������ݲ���λ���
        ui->usredit->clear();
        ui->pwdedit->clear();
        ui->usredit->setFocus();

        return;
    }

    QString USRPWD = QString("%1").arg(UsrDb->CUsrInfo.password);
    QString INPUTPWD = ui->pwdedit->text();

    if(INPUTPWD == USRPWD)
    {
       accept();
    } else {
       QMessageBox::warning(this, tr("Warning!"),
                   tr("password err!"),
                   QMessageBox::Yes);
       // ������ݲ���λ���
       ui->usredit->clear();
       ui->pwdedit->clear();
       ui->usredit->setFocus();
    }
}
