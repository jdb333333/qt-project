#include "widget.h"
#include <QApplication>

#include "button/switchbutton.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
#if 1
    Widget w;
    w.show();
#else
    SwitchButton *mybtn = new SwitchButton;
    mybtn->show();
#endif

    return a.exec();
}
