#include <QCoreApplication>
#include <iostream>
#include "qtnetcoreengine.h"

int wmain(const int argc, const wchar_t *argv[])
{
    QtNetCoreEngine engine;

    return engine.Initialize(argc, argv);
}
