#ifndef ZNMTOOLS_GLOBAL_H
#define ZNMTOOLS_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(ZNMTOOLS_LIBRARY)
#  define ZNMTOOLSSHARED_EXPORT Q_DECL_EXPORT
#else
#  define ZNMTOOLSSHARED_EXPORT Q_DECL_IMPORT
#endif

namespace znm_tools
{
    enum State
    {
        CREATED,
        BINDED,
        NONE
    };

}

#endif // ZNMTOOLS_GLOBAL_H
