#ifndef ZNMTOOLS_GLOBAL_H
#define ZNMTOOLS_GLOBAL_H

#include <fcntl.h>           /* For O_* constants */
#include <QtCore/qglobal.h>

#if defined(ZNMTOOLS_LIBRARY)
#  define ZNMTOOLSSHARED_EXPORT Q_DECL_EXPORT
#else
#  define ZNMTOOLSSHARED_EXPORT Q_DECL_IMPORT
#endif

namespace znm_tools
{
    enum Mode
    {
        READ_ONLY = O_RDONLY,
        READ_AND_WRITE = O_RDWR
    };

}

#endif // ZNMTOOLS_GLOBAL_H
