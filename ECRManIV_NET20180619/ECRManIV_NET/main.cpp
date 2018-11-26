#include "ecrmaniv_net.h"
#include "logindialog.h"

#include <QApplication>
#include <QDir>
#include <QIcon>

#include "./usr/usrdb.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString strLibPath(QDir::toNativeSeparators(QApplication::applicationDirPath())+QDir::separator()+"plugins");
    a.addLibraryPath(strLibPath);

    //a.setWindowIcon(QIcon(":/images/icons/eutron24.png"));

    usrdb *myusrdb = new usrdb;

    ECRManIV_NET w;

    LoginDialog dlg;
    if (dlg.exec() == QDialog::Accepted)
    {
        w.permset();
        w.show();

        return a.exec();
    }
    else
        return 0;
}
