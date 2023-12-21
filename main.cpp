#include "mynotepad.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Mynotepad w;
    w.show();
    return a.exec();
}
