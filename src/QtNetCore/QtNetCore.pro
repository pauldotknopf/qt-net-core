TEMPLATE = subdirs

SUBDIRS += \
    QtNetCoreEngine \
    QtNetCoreSandbox \
    QtNetCorePluginSandbox

QtNetCoreSandbox.depends = QtNetCoreEngine
QtNetCorePlugin.depends = QtNetCoreEngine
