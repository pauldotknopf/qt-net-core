#ifndef QTNETCOREENGINE_H
#define QTNETCOREENGINE_H

#include "qtnetcoreengine_global.h"
#include <QScopedPointer>
#include <QVariantList>

class QtNetCoreEnginePrivate;
class QTNETCOREENGINESHARED_EXPORT QtNetCoreEngine
{
public:
    QtNetCoreEngine(const int argc, const wchar_t *argv[]);
    ~QtNetCoreEngine();
    QScopedPointer<QtNetCoreEnginePrivate> const d_ptr;
    void InvokeStatic(QString type, QString method, QVariantList arguements);
};

#endif // QTNETCOREENGINE_H
