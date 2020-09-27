#include "widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.setWindowTitle("养猪模拟");
    w.resize(1500,1200);
    w.show();
    return a.exec();
}
