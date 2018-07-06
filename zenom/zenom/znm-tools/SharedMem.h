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

class SharedMem
{

public:

    /**
     * @brief SharedMem constructor to bind existing shared memory
     * @param name
     * @param flags
     */
    SharedMem(const std::string& name,
              znm_tools::Flags flags = znm_tools::Flags::READ_AND_WRITE);

    /**
     * @brief SharedMem constructor to create a new shared memory
     * @param name
     * @param size
     * @param flags
     */
    SharedMem(const std::string& name,
              size_t size,
              znm_tools::Flags flags = znm_tools::Flags::READ_AND_WRITE);

    /**
     * @brief operator = do not use assignment operator
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
    ~SharedMem();

    /**
     * @brief ptrToShMem get pointer to shared memory
     * @return returns pointer to shared memory, returns nullptr if it
     * doesn't exist
     */
    void *ptrToShMem();

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
};

#endif // SHAREDMEM_H_
