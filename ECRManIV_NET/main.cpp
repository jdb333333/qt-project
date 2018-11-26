#include "ecrmaniv_net.h"
#include <QApplication>
#include <QDir>
#include <QIcon>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString strLibPath(QDir::toNativeSeparators(QApplication::applicationDirPath())+QDir::separator()+"plugins");
    a.addLibraryPath(strLibPath);

    //a.setWindowIcon(QIcon(":/images/icons/eutron24.png"));

    ECRManIV_NET w;
    w.show();

    return a.exec();
}
