TEMPLATE = subdirs

SUBDIRS += \
    QtNetCoreEngine \
    QtNetCoreSandbox

QtNetCoreSandbox.depends = QtNetCoreEngine
