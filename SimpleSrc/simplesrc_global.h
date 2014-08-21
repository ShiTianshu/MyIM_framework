#ifndef SIMPLESRC_GLOBAL_H
#define SIMPLESRC_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(SIMPLESRC_LIBRARY)
#  define SIMPLESRCSHARED_EXPORT Q_DECL_EXPORT
#else
#  define SIMPLESRCSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // SIMPLESRC_GLOBAL_H
