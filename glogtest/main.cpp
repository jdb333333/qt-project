#include "dialog.h"
#include <QApplication>

#include <QDir>
#include <QIcon>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString strLibPath(QDir::toNativeSeparators(QApplication::applicationDirPath())+QDir::separator()+"plugins");
    a.addLibraryPath(strLibPath);

    Dialog w;
    w.show();

    return a.exec();
}
