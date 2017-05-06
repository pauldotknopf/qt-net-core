#ifndef QTNETCORE_H
#define QTNETCORE_H

#include "qtnetcore_global.h"
#include <QScopedPointer>

class QtNetCorePrivate; ///< The PIMPL class for Foo
class QtNetCore {
  QScopedPointer<QtNetCorePrivate> const d_ptr;
public:
  QtNetCore();
  ~QtNetCore();
};

#endif // QTNETCORE_H
