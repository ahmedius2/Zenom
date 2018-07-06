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
#include <system_error>
#include <cerrno>
#include <cstring>
#include <iostream>
#include "SharedMem.h"

SharedMem::SharedMem(const std::string &name,size_t size,znm_tools::Flags flags)
{
    std::string shmName = "/" + name;

    mode_t mode  = 0777;
    mShmfd = shm_open(shmName.c_str(), flags | O_CREAT | O_TRUNC, mode);
    if (mShmfd == -1)
        throw std::system_error(errno, std::system_category(),
                                    shmName +" SharedMem(create), shm_open");


    if (ftruncate(mShmfd, size) == -1){
        close(mShmfd);
        shm_unlink(shmName.c_str());
        throw std::system_error(errno, std::system_category(),
                                shmName + " SharedMem, ftruncate");
    }

    unsigned flags_ = 0;
    if (flags == znm_tools::Flags::READ_ONLY)
        flags_ = PROT_READ;
    else if(flags == znm_tools::Flags::READ_AND_WRITE)
        flags_ = PROT_READ | PROT_WRITE;
    else{
        close(mShmfd);
        shm_unlink(shmName.c_str());
        throw std::system_error(errno, std::system_category(),
                                shmName + " SharedMem, wrong mode");
    }

    mPtrToShMem = mmap(nullptr, size, flags_,
                       MAP_SHARED,
                       mShmfd,0);

    if(mPtrToShMem == MAP_FAILED){
        close(mShmfd);
        shm_unlink(shmName.c_str());
        throw std::system_error(errno, std::system_category(),
                                shmName + " SharedMem(create), mmap");
    }

    mName = shmName;
    mSize = size;
    mIsCreated = true;

}

SharedMem::SharedMem(const std::string &name, znm_tools::Flags flags)
{
    std::string shmName = "/" + name;

    mShmfd = shm_open(shmName.c_str(), flags, 0);
    if (mShmfd == -1)
        throw std::system_error(errno, std::system_category(),
                            shmName + " SharedMem(bind), shm_open");

    // Get size of existing shared mem
    struct stat shmMemInfo;
    if(fstat(mShmfd,&shmMemInfo) == -1){
        close(mShmfd);
        throw std::system_error(errno, std::system_category(),
                            shmName + " SharedMem, fstat");
    }

    unsigned flags_ = 0;
    if (flags == znm_tools::Flags::READ_ONLY)
        flags_ = PROT_READ;
    else if(flags == znm_tools::Flags::READ_AND_WRITE)
        flags_ = PROT_READ | PROT_WRITE;
    else{
        close(mShmfd);
        throw std::system_error(errno, std::system_category(),
                            shmName + " SharedMem, wrong mode");
    }

    mPtrToShMem = mmap(nullptr, shmMemInfo.st_size, flags_,
                       MAP_SHARED,
                       mShmfd,0);
    if(mPtrToShMem == MAP_FAILED){
        close(mShmfd);
        throw std::system_error(errno, std::system_category(),
                            shmName + " SharedMem(bind), mmap");
    }

    mName = shmName;
    mSize = shmMemInfo.st_size;
    mIsCreated = false;


}

SharedMem::~SharedMem()
{
    if( munmap(mPtrToShMem,mSize) == -1)
        std::cerr << "~SharedMem, munmap error:" << strerror(errno)<< std::endl;
    if( close(mShmfd) == -1)
        std::cerr << "~SharedMem, close error:" << strerror(errno)<< std::endl;
    if( mIsCreated && shm_unlink(mName.c_str()) == -1 && errno != ENOENT)
        std::cerr<<"~SharedMem, shm_unlink error:"<<strerror(errno)<< std::endl;
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

