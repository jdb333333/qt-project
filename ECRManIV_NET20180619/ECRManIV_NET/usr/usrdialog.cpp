#include "usrdialog.h"
#include "ui_usrdialog.h"

#include "usrdb.h"
#include "usrmoddialog.h"

#include <QDebug>
#include <QModelIndex>

usrDialog::usrDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::usrDialog)
{
    ui->setupUi(this);

    setWindowTitle(QString("User Management"));

    usrgroup = ORDUSRGROUP;

    //ui->UserPerm->setDisabled(true);
    //ui->UserPerm->setAttribute(Qt::WA_X11DoNotAcceptFocus);

    ui->adminedit->setReadOnly(true);
    ui->pwdedit->setReadOnly(true);

    ui->UsrNameEdit->setReadOnly(true);
    ui->UsrPwdEdit->setReadOnly(true);

    ui->adminedit->setText(QString("%1").arg(UsrDb->CUsrInfo.name));
    ui->pwdedit->setText(QString("%1").arg(UsrDb->CUsrInfo.password));

    QPalette p = this->palette();
    p.setColor(QPalette::Window, QColor(0xff,0xeb,0xcd));
    this->setPalette(p);

    ui->UserList->setColumnCount(1);

    ui->UserList->verticalHeader()->setVisible(false);
    ui->UserList->horizontalHeader()->setVisible(false);

    //设置表头字体加粗
    QFont font = ui->UserList->horizontalHeader()->font();
    font.setBold(true);
    ui->UserList->horizontalHeader()->setFont(font);

    ui->UserList->horizontalHeader()->setStretchLastSection(true); //设置充满表宽度

    ui->UserList->setAlternatingRowColors(true);
    ui->UserList->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->UserList->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->UserList->setSelectionMode(QAbstractItemView::SingleSelection);

    getusrdata();
}

usrDialog::~usrDialog()
{
    delete ui;
}

void usrDialog::on_add_clicked()
{
    if(usrgroup == ORDUSRGROUP)
    {
        memset(&UsrDb->UsrInfo, 0, sizeof(UsrDb->UsrInfo));
        UsrDb->UsrInfo.group = ORDUSR;
        UsrDb->UsrInfo.permission = REPORTPERM;
    }
    else if(usrgroup == SUPUSRGROUP)
    {
        memset(&UsrDb->UsrInfo, 0, sizeof(UsrDb->UsrInfo));
        UsrDb->UsrInfo.group = SUPUSR;
        UsrDb->UsrInfo.permission = CLERKPERM | GROUPPERM | DEPARTMENTPERM | PLUPERM | DISCOUNTPERM |
                TAXPERM | TICKETPERM | OFFERPERM | REPORTPERM | REPORTPERM;
    }

    UsrModDialog *usrmod = new UsrModDialog;
    usrmod->setWindowTitle(QString("Add User"));
    usrmod->setfunc(ADDUSR);
    usrmod->exec();

    getusrdata();
}

void usrDialog::on_OrdinaryUser_clicked()
{
    usrgroup = ORDUSRGROUP;
    getusrdata();
}

void usrDialog::on_SupevisorUser_clicked()
{
    usrgroup = SUPUSRGROUP;
    getusrdata();
}

void usrDialog::setusrlist(QString UsrName)
{
    int rows=ui->UserList->rowCount();

    qDebug() << "rows = " << rows;

    ui->UserList->insertRow(rows);

    ui->UserList->setItem(rows,0,new QTableWidgetItem(UsrName));
    ui->UserList->item(rows, 0)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
}

void usrDialog::setUsrPerm()
{
    if(UsrDb->UsrInfo.permission & GROUPPERM)
    {
        ui->groupcheckBox->setChecked(true);
    }
    else
    {
        ui->groupcheckBox->setChecked(false);
    }

    if(UsrDb->UsrInfo.permission & CLERKPERM)
    {
        ui->clerkcheckBox->setChecked(true);
    }
    else
    {
        ui->clerkcheckBox->setChecked(false);
    }

    if(UsrDb->UsrInfo.permission & DEPARTMENTPERM)
    {
        ui->departmentcheckBox->setChecked(true);
    }
    else
    {
        ui->departmentcheckBox->setChecked(false);
    }

    if(UsrDb->UsrInfo.permission & PLUPERM)
    {
        ui->plucheckBox->setChecked(true);
    }
    else
    {
        ui->plucheckBox->setChecked(false);
    }

    if(UsrDb->UsrInfo.permission & DISCOUNTPERM)
    {
        ui->discountcheckBox->setChecked(true);
    }
    else
    {
        ui->discountcheckBox->setChecked(false);
    }

    if(UsrDb->UsrInfo.permission & TAXPERM)
    {
        ui->taxcheckBox->setChecked(true);
    }
    else
    {
        ui->taxcheckBox->setChecked(false);
    }

    if(UsrDb->UsrInfo.permission & TICKETPERM)
    {
        ui->ticketcheckBox->setChecked(true);
    }
    else
    {
        ui->ticketcheckBox->setChecked(false);
    }

    if(UsrDb->UsrInfo.permission & OFFERPERM)
    {
        ui->offercheckBox->setChecked(true);
    }
    else
    {
        ui->offercheckBox->setChecked(false);
    }

    if(UsrDb->UsrInfo.permission & REPORTPERM)
    {
        ui->reportcheckBox->setChecked(true);
    }
    else
    {
        ui->reportcheckBox->setChecked(false);
    }
}

void usrDialog::getusrdata()
{
    USRINFO usrinfo;
    int datalen, indx, maxnum;

    int usrlen = sizeof(USRINFO);

    if(usrgroup == ORDUSRGROUP)
    {
        usrinfo.group = ORDUSR;
    }
    else if(usrgroup == SUPUSRGROUP)
    {
        usrinfo.group = SUPUSR;
    }

    datalen = UsrDb->selectgrouptable(usrinfo, usrdata);

    maxnum = datalen/usrlen;
    qDebug() << "maxnum = " << maxnum;

    ui->UserList->setRowCount(0);
    ui->UserList->clearContents();
    for(indx = 0; indx < maxnum; indx++)
    {
        memcpy(&usrinfo, usrdata + indx * usrlen, usrlen);
        qDebug() << "usrinfo.name = " << usrinfo.name;
        setusrlist(QString("%1").arg(usrinfo.name));
    }

    ui->UsrNameEdit->clear();
    ui->UsrPwdEdit->clear();
    if(ui->UserList->rowCount() > 0)
    {
        ui->UserList->item(0, 0)->setSelected(true);
        ui->UserList->setFocus();

        memcpy(&UsrDb->UsrInfo, usrdata, usrlen);

        ui->UsrNameEdit->setText(QString("%1").arg(UsrDb->UsrInfo.name));
        ui->UsrPwdEdit->setText(QString("%1").arg(UsrDb->UsrInfo.password));
        setUsrPerm();
    }
}

void usrDialog::on_modpwd_clicked()
{
    memcpy(&UsrDb->UsrInfo, &UsrDb->CUsrInfo, sizeof(UsrDb->UsrInfo));

    UsrModDialog *usrmod = new UsrModDialog;
    usrmod->setWindowTitle(QString("Mod Admin"));
    usrmod->setfunc(MODPWD);
    usrmod->exec();

    ui->adminedit->setText(QString("%1").arg(UsrDb->CUsrInfo.name));
    ui->pwdedit->setText(QString("%1").arg(UsrDb->CUsrInfo.password));
}

void usrDialog::on_UserList_clicked(const QModelIndex &index)
{
    int row = index.row();
    int col = index.column();

    QString UsrName = ui->UserList->item(row, col)->text();

    memset(&UsrDb->UsrInfo, 0, sizeof(USRINFO));

    strcpy(UsrDb->UsrInfo.name, UsrName.toLocal8Bit().data());

    UsrDb->selecttable(&UsrDb->UsrInfo);

    ui->UsrNameEdit->setText(QString("%1").arg(UsrDb->UsrInfo.name));
    ui->UsrPwdEdit->setText(QString("%1").arg(UsrDb->UsrInfo.password));
    setUsrPerm();
}

void usrDialog::on_delete_2_clicked()
{
    QString UsrName;
    int row = ui->UserList->currentRow();
    int col = ui->UserList->currentColumn();

    UsrName = ui->UserList->item(row, col)->text();

    USRINFO usrinfo;

    strcpy(usrinfo.name, UsrName.toLocal8Bit().data());

    UsrDb->deleteusr(usrinfo);

    getusrdata();
}

void usrDialog::on_setperm_clicked()
{
    USRINFO newusrinfo;

    memcpy(&newusrinfo, &UsrDb->UsrInfo, sizeof(USRINFO));

    newusrinfo.permission = 0;

    if(usrgroup == ORDUSRGROUP)
    {
        if(ui->clerkcheckBox->checkState())
        {
            newusrinfo.permission |= CLERKPERM;
        }

        if(ui->groupcheckBox->checkState())
        {
            newusrinfo.permission |= GROUPPERM;
        }

        if(ui->departmentcheckBox->checkState())
        {
            newusrinfo.permission |= DEPARTMENTPERM;
        }

        if(ui->plucheckBox->checkState())
        {
            newusrinfo.permission |= PLUPERM;
        }

        if(ui->discountcheckBox->checkState())
        {
            newusrinfo.permission |= DISCOUNTPERM;
        }

        if(ui->taxcheckBox->checkState())
        {
            newusrinfo.permission |= TAXPERM;
        }

        if(ui->ticketcheckBox->checkState())
        {
            newusrinfo.permission |= TICKETPERM;
        }

        if(ui->offercheckBox->checkState())
        {
            newusrinfo.permission |= OFFERPERM;
        }

        if(ui->reportcheckBox->checkState())
        {
            newusrinfo.permission |= REPORTPERM;
        }

        UsrDb->modusr(UsrDb->UsrInfo, newusrinfo);
    }
}
