#ifndef NETCORE_H
#define NETCORE_H

#include <QQuickItem>
#include <QScopedPointer>

class NetCorePrivate;
class NetCore : public QQuickItem
{
    Q_OBJECT
    Q_DISABLE_COPY(NetCore)
    QScopedPointer<NetCorePrivate> const d_ptr;

public:
    NetCore(QQuickItem *parent = 0);
    ~NetCore();

    static bool CreateCoreCLR(QStringList arguements);
    static bool DestroyCoreCLR();
};

#endif // NETCORE_H
