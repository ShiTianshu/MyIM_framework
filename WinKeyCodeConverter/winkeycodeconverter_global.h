#ifndef WINKEYCODECONVERTER_GLOBAL_H
#define WINKEYCODECONVERTER_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(WINKEYCODECONVERTER_LIBRARY)
#  define WINKEYCODECONVERTERSHARED_EXPORT Q_DECL_EXPORT
#else
#  define WINKEYCODECONVERTERSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // WINKEYCODECONVERTER_GLOBAL_H
