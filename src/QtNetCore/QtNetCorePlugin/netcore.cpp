#include "netcore.h"

QtNetCoreEngine* NetCore::netCoreEngine = NULL;

NetCore::NetCore(QQuickItem *parent):
    QQuickItem(parent)
{
    if(netCoreEngine == NULL)
    {
        qFatal("Attempting to using NetCore without calling NetCore::initialize first.");
        return;
    }
}

NetCore::~NetCore()
{
}

bool NetCore::initializeCoreEngine(const int argc, const wchar_t *argv[])
{
    if(netCoreEngine != NULL)
    {
        qWarning() << "Attempting to call initialize on an already created .NET Core engine";
        return false;
    }
    netCoreEngine = new QtNetCoreEngine(argc, argv);
}
