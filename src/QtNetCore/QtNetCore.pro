TEMPLATE = subdirs

SUBDIRS += \
    QtNetCoreEngine \
    QtNetCoreSandbox \
    QtNetCorePlugin \
    QtNetCorePluginSandbox

QtNetCoreSandbox.depends = QtNetCoreEngine
QtNetCorePlugin.depends = QtNetCoreEngine
