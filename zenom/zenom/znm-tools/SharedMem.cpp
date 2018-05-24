//==============================================================================
// SharedMem.cpp - Shared memory wrapper class.
//
// Author        : Ahmet Soyyigit
// Version       : 2.0.01 (2018)
// Compatibility : POSIX, GCC
//==============================================================================

#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>           /* For O_* constants */
#include <unistd.h>
#include "SharedMem.h"


SharedMem::SharedMem(const std::string &name, size_t size, znm_tools::Flags flags)
{
    mode_t mode  = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
    mShmfd = shm_open(name.c_str(), flags | O_CREAT | O_EXCL, mode);
    if (mShmfd == -1){
        if(errno == EEXIST){
            shm_unlink(name.c_str());
            mShmfd = shm_open(name.c_str(), flags | O_CREAT | O_EXCL, mode);
        }

        if (mShmfd == -1)
            throw ZnmException(name, "SharedMem::create, shm_open", errno );
    }

    if (ftruncate(mShmfd, size) == -1){
        close(mShmfd);
        shm_unlink(name.c_str());
        throw ZnmException(name, "SharedMem::create, ftruncate", errno );
    }

    unsigned flags_ = 0;
    if (flags == znm_tools::Flags::READ_ONLY)
        flags_ = PROT_READ;
    else if(flags == znm_tools::Flags::READ_AND_WRITE)
        flags_ = PROT_READ | PROT_WRITE;
    else{
        close(mShmfd);
        shm_unlink(name.c_str());
        throw ZnmException("SharedMem::create, wrong mode");
    }

    mPtrToShMem = mmap(nullptr, size, flags_,
                       MAP_SHARED | MAP_LOCKED | MAP_POPULATE,
                       mShmfd,0);
    if(mPtrToShMem == MAP_FAILED){
        close(mShmfd);
        shm_unlink(name.c_str());
        throw ZnmException(name, "SharedMem::create, mmap", errno );
    }

    mName = name;
    mSize = size;
    mIsCreated = true;
}

SharedMem::SharedMem(const std::string &name, znm_tools::Flags flags)
{
    mode_t mode  = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
    mShmfd = shm_open(name.c_str(), flags, mode);
    if (mShmfd == -1)
        throw ZnmException(name, "SharedMem::bind, open", errno );

    // Get size of existing shared mem
    struct stat shmMemInfo;
    if(fstat(mShmfd,&shmMemInfo) == -1){
        close(mShmfd);
        throw ZnmException(name, "SharedMem::bind, fstat", errno );
    }

    unsigned flags_ = 0;
    if (flags == znm_tools::Flags::READ_ONLY)
        flags_ = PROT_READ;
    else if(flags == znm_tools::Flags::READ_AND_WRITE)
        flags_ = PROT_READ | PROT_WRITE;
    else{
        close(mShmfd);
        throw ZnmException(name ,"SharedMem::bind, wrong mode");
    }

    mPtrToShMem = mmap(nullptr, shmMemInfo.st_size, flags_,
                       MAP_SHARED | MAP_LOCKED | MAP_POPULATE,
                       mShmfd,0);
    if(mPtrToShMem == MAP_FAILED){
        close(mShmfd);
        throw ZnmException(name, "SharedMem::bind, mmap", errno );
    }

    mName = name;
    mSize = shmMemInfo.st_size;
    mIsCreated = false;
}

SharedMem::~SharedMem()
{
    if( munmap(mPtrToShMem,mSize) == -1)
        throw ZnmException(mName, "SharedMem::unbind, munmap", errno );
    if( close(mShmfd) == -1)
        throw ZnmException(mName, "SharedMem::unbind, close", errno );
    if( mIsCreated){
        if( shm_unlink(mName.c_str()) == -1 && errno != ENOENT)
            throw ZnmException(mName, "SharedMem::unlink, shm_unlink", errno );
    }
}


void *SharedMem::ptrToShMem()
{
    return mPtrToShMem;
}

bool SharedMem::isBinded()
{
    return !mIsCreated;
}

bool SharedMem::isCreated()
{
    return mIsCreated;
}

