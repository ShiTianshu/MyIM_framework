#ifndef TABLETRANSLATOR_GLOBAL_H
#define TABLETRANSLATOR_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(TABLETRANSLATOR_LIBRARY)
#  define TABLETRANSLATORSHARED_EXPORT Q_DECL_EXPORT
#else
#  define TABLETRANSLATORSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // TABLETRANSLATOR_GLOBAL_H
