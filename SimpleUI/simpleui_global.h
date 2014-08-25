#ifndef SIMPLEUI_GLOBAL_H
#define SIMPLEUI_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(SIMPLEUI_LIBRARY)
#  define SIMPLEUISHARED_EXPORT Q_DECL_EXPORT
#else
#  define SIMPLEUISHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // SIMPLEUI_GLOBAL_H
