#include <QCoreApplication>
#include <iostream>
#include "qtnetcoreengine.h"
#include <QThread>

int wmain(const int argc, const wchar_t *argv[])
{
    QtNetCoreEngine engine(argc, argv);



    QThread::sleep(10);
    return 0;
}
