//==============================================================================
// HeapXn.hpp - Native Heap class.
//
// Author        :
// Version       : 2.0.01 (Temmuz 2009)
// Compatibility : POSIX, GCC
//==============================================================================

#ifndef HEAPXN_H_
#define HEAPXN_H_

#include <native/heap.h>
#include <string>
#include "znm-tools_global.h"
#include "znmException.h"


//==============================================================================
// class HeapXn
//------------------------------------------------------------------------------
// \brief
// Heap objects.
// HeapXn sınıfı, tasklar için ortak kullanılabilen hafıza alanı oluşturur.
// Dinamik afıza tahsisi için uygundur.
//
// <b>Example Program:</b>
//
// \include HeapXn.t.cpp
//==============================================================================

#define HEAP_TIMEOUT 10000000000LL	// Default timeout 10 seconds
#define HEAP_MODE_C    H_SHARED     // Default creation mode

class ZNMTOOLSSHARED_EXPORT HeapXn
{

public:

	// Sadece objenin degiskenlerine atamalar yapilir.
	HeapXn();

	// Heap yaratan ise delete, heape baglanan ise unbind edilir.
    virtual ~HeapXn();

	/*
	 * Create a memory heap or a shared memory segment.
	 * pName 		the symbolic name of the heap.
	 * pHeapSize 	The size (in bytes) of the heap.
	 * pMode 		The heap creation mode. (Default H_SHARED)
	 * return
	 * throw
	 */
	void create(const std::string& pName, size_t pHeapSize, int pMode = HEAP_MODE_C);

	void* alloc(size_t pHeapSize, RTIME pTimeout = HEAP_TIMEOUT);

    bool isCreated() { return mState == znm_tools::CREATED; }

	void free(void* pBlock);

	void deleteHeap();

	void bind(const std::string& name, RTIME timeout = HEAP_TIMEOUT);

	void unbind();

    bool isBinded() { return mState == znm_tools::BINDED; }

	RT_HEAP_INFO inquire();

private:

	RT_HEAP heap;			// Heap
	std::string mHeapName;	// heap's name
    znm_tools::State mState;
};

#endif // HEAPXN_H_
