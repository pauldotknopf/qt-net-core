#ifndef NETCORE_H
#define NETCORE_H

#include <QQuickItem>
#include "qtnetcoreengine.h"

class NetCore : public QQuickItem
{
    Q_OBJECT
    Q_DISABLE_COPY(NetCore)

public:
    NetCore(QQuickItem *parent = 0);
    ~NetCore();
private:
    QtNetCoreEngine* netCoreEngine;
};

#endif // NETCORE_H
