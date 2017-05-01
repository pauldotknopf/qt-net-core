#ifndef QTNETCORE_GLOBAL_H
#define QTNETCORE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(QTNETCORE_LIBRARY)
#  define QTNETCORESHARED_EXPORT Q_DECL_EXPORT
#else
#  define QTNETCORESHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // QTNETCORE_GLOBAL_H