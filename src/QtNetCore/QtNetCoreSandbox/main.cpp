#include <QCoreApplication>
#include <iostream>
#include "qtnetcoreengine.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    new QtNetCoreEngine();

    std::cout << "test\n";

    return a.exec();
}
