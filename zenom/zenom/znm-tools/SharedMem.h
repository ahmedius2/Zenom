//==============================================================================
// SharedMem.hpp - Native Heap class.
//
// Author        :
// Version       : 2.0.01 (Temmuz 2009)
// Compatibility : POSIX, GCC
//==============================================================================

#ifndef SHAREDMEM_H_
#define SHAREDMEM_H_

#include <string>
#include "znm-tools_global.h"
#include "znmException.h"


//==============================================================================
// class SharedMem
//------------------------------------------------------------------------------
// \brief
// Heap objects.
// SharedMem sınıfı, tasklar için ortak kullanılabilen hafıza alanı oluşturur.
// Dinamik hafıza tahsisi için uygundur.
//
// <b>Example Program:</b>
//
// \include SharedMem.t.cpp
//==============================================================================

class ZNMTOOLSSHARED_EXPORT SharedMem
{

public:

    /**
     * @brief SharedMem constructs an empty SharedMem object
     */
    SharedMem();

    /**
     * @brief operator = do not use it
     */
    SharedMem & operator =(const SharedMem&) = delete;

    /**
     * @brief SharedMem do not use copy constructor
     */
    SharedMem(const SharedMem&) = delete;

    /**
     * @brief ~SharedMem destructs shared memory object and unlinks the
     * shared memory if created by this object
     */
    virtual ~SharedMem();

    /**
     * @brief SharedMem::create creates a new shared memory object if there
     * isn't already one with the name and binds to it
     * @param name name of the shared memory
     * @param size size of the shared memory
     * @param mode read only or read-write
     */
    void create(const std::string& name,
                    size_t size,
                    znm_tools::Flags flags = znm_tools::Flags::READ_AND_WRITE);

    /**
     * @brief SharedMem::bind
     * bind to an existing shared memory, if it doesn't exist returns -1
     * a creator cannot bind again after unbind. it must unlink before
     * binding
     * @param   name  name of the shared memory
     * @param   mode  Read only or read-write
     */
    void  bind(const std::string& name,
                   znm_tools::Flags flags = znm_tools::Flags::READ_AND_WRITE);

    /**
     * @brief ptrToShMem get pointer to shared memory
     * @return returns pointer to shared memory, returns nullptr if it
     * doesn't exist
     */
    void *ptrToShMem();

    /**
     * @brief unbind from already binded shared memory
     * @return 0 on success and -1 on error
     */
    void unbind();


    /**
     * @brief unlink unlink the shared memory by hand
     */
    void unlink();

    /**
     * @brief isBinded
     * @return true if binded, false otherwise
     */
    bool isBinded();

    /**
     * @brief isCreated
     * @return true if created, false otherwise
     */
    bool isCreated();

private:
    int mShmfd; // Shared memory file descriptor
    void *mPtrToShMem; // Pointer to shared memory
    std::string mName;	// Name
    unsigned mSize;
    bool mIsCreated;
    bool mIsBinded;
};

#endif // SHAREDMEM_H_
