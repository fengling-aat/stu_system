#include "system.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    System w;
    w.sys_read();
    w.show();
    return a.exec();
}
