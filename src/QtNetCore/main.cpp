#include <QCoreApplication>
#include "qtnetcore.h"
#include <iostream>

#include "qtnetcore.h"
#include "pal.h"
#include "utils.h"

int wmain(const int argc, const wchar_t* argv[])
{
    std::wcout << _STRINGIFY(HOST_POLICY_PKG_NAME);
    new QtNetCore();
    return 0;
}
