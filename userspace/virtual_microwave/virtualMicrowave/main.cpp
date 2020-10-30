#include "virtualMicrowave.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    VirtualMicrowave w;
    w.show();
    return a.exec();
}
