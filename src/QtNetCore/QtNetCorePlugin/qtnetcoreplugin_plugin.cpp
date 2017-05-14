#include "qtnetcoreplugin_plugin.h"
#include "netcore.h"

#include <qqml.h>

void QtNetCorePluginPlugin::registerTypes(const char *uri)
{
    // @uri QtNetCore
    qmlRegisterType<NetCore>(uri, 1, 0, "NetCore");
}

