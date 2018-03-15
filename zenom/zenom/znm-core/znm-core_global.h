#ifndef ZNMCORE_GLOBAL_H
#define ZNMCORE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(ZNMCORE_LIBRARY)
#  define ZNMCORESHARED_EXPORT Q_DECL_EXPORT
#else
#  define ZNMCORESHARED_EXPORT Q_DECL_IMPORT
#endif

enum State
{
    RUNNING,
    PAUSED,
    STOPPED,
    TERMINATED,
    CRASHED
};

enum StateRequest
{
    R_INIT,
    R_START,
    R_PAUSE,
    R_RESUME,
    R_STOP,
    R_TERMINATE
};

#endif // ZNMCORE_GLOBAL_H
