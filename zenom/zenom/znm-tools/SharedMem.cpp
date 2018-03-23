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

SharedMem::SharedMem()
{
    mIsCreated = false;
    mIsBinded  = false;
    mPtrToShMem = nullptr;
    mSize = 0;
}

SharedMem::~SharedMem()
{
    if(mIsCreated)
        unlink();
}

int SharedMem::create(const std::string &name,
                           size_t size,
                           znm_tools::Mode mode)
{
    if (mIsBinded || mIsCreated)
        return -1;
    // 0666 is default linux file permission
    mShmfd = shm_open(name.c_str(), mode | O_CREAT | O_EXCL, 0666);
    if (mShmfd == -1)
        return -1;

    if (ftruncate(mShmfd, size) == -1)
        return -1;

    if (mode == znm_tools::Mode::READ_ONLY)
        mPtrToShMem = mmap(nullptr, size, PROT_READ,
                           MAP_SHARED | MAP_LOCKED | MAP_POPULATE,
                           mShmfd,0);
    else if(mode == znm_tools::Mode::READ_AND_WRITE)
        mPtrToShMem = mmap(nullptr, size, PROT_READ | PROT_WRITE,
                           MAP_SHARED | MAP_LOCKED | MAP_POPULATE,
                           mShmfd,0);
    else
        return -1;

    if(mPtrToShMem == MAP_FAILED)
        return -1;

    mSize = size;
    mIsCreated = true;
    mIsBinded = true;
    return 0;
}


int SharedMem::bind(const std::string &name,
                                 znm_tools::Mode mode)
{
    if (mIsBinded || mIsCreated)
        return -1;
    // 0666 is default linux file permission
    mShmfd = shm_open(name.c_str(), mode, 0666);
    if (mShmfd == -1)
        return -1;

    struct stat shmMemInfo;
    fstat(mShmfd,&shmMemInfo);

    if (mode == znm_tools::Mode::READ_ONLY)
        mPtrToShMem = mmap(nullptr, shmMemInfo.st_size, PROT_READ,
                           MAP_SHARED | MAP_LOCKED | MAP_POPULATE,
                           mShmfd,0);
    else if(mode == znm_tools::Mode::READ_AND_WRITE)
        mPtrToShMem = mmap(nullptr, shmMemInfo.st_size, PROT_READ | PROT_WRITE,
                           MAP_SHARED | MAP_LOCKED | MAP_POPULATE,
                           mShmfd,0);
    else
        return -1;

    if(mPtrToShMem == MAP_FAILED)
        return -1;

    mSize = shmMemInfo.st_size;
    mIsBinded = true;
    return 0;
}

int SharedMem::unbind()
{
    if(!mIsBinded)
        return -1;
    int ret = munmap(mPtrToShMem,mSize);
    ret += close(mShmfd);
    if (ret == 0){
        mIsBinded = false;
        mSize = 0;
        mPtrToShMem = nullptr;
    }
    return ret;
}

void *SharedMem::ptrToShMem()
{
    return mIsBinded ? nullptr : mPtrToShMem;
}

int SharedMem::unlink()
{
    if(mIsBinded)
        unbind();
    int ret = shm_unlink(mName.c_str());
    if(ret == 0)
        mIsCreated = false;
    return ret;
}

bool SharedMem::isBinded()
{
    return mIsBinded;
}

bool SharedMem::isCreated()
{
    return mIsCreated;
}




