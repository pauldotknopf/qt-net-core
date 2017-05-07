#ifndef QTNETCOREENGINE_H
#define QTNETCOREENGINE_H

#include "qtnetcoreengine_global.h"
#include <QScopedPointer>

class QtNetCoreEnginePrivate;
class QTNETCOREENGINESHARED_EXPORT QtNetCoreEngine
{
public:
  QtNetCoreEngine();
  ~QtNetCoreEngine();
   QScopedPointer<QtNetCoreEnginePrivate> const d_ptr;
   int Initialize(const int argc, const wchar_t* argv[]);
   int TearDown();
};

#endif // QTNETCOREENGINE_H
