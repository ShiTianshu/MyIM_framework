#ifndef MYCORE_GLOBAL_H
#define MYCORE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(MYCORE_LIBRARY)
#  define MYCORESHARED_EXPORT Q_DECL_EXPORT
#else
#  define MYCORESHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // MYCORE_GLOBAL_H
