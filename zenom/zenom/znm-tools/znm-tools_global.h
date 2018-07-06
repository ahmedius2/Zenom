#ifndef ZNMTOOLS_GLOBAL_H
#define ZNMTOOLS_GLOBAL_H

#include <fcntl.h>           /* For O_* constants */

namespace znm_tools
{
    enum Flags
    {
        READ_ONLY = O_RDONLY,
        READ_AND_WRITE = O_RDWR,
        WRITE_ONLY = O_WRONLY
    };

}

#endif // ZNMTOOLS_GLOBAL_H
