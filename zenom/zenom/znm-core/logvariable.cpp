/*
 * LogVariable.cpp
 *
 *  Created on: Mar 26, 2012
 *      Author: root
 */

#include "logvariable.h"
#include <iostream>

LogVariable::LogVariable(double* pAddr,
                         const std::string& pName,
                         unsigned int pRow,
                         unsigned int pCol,
                         const std::string& pDesc)
 : Variable(pAddr, pName, pDesc, pRow, pCol)
{
    mHeap = nullptr;
    mHeapBeginAddr = nullptr;
    mMainHeapAddr = nullptr;
}

LogVariable::~LogVariable()
{

}

void LogVariable::setMainHeapAddr(double *pHeapAddr)
{
    mMainHeapAddr = pHeapAddr;
    mMainHeapAddr[0] = 1;      // frequency
    mMainHeapAddr[1] = 0;      // start time
    mMainHeapAddr[2] = 100;    // duration
}

double LogVariable::frequency()
{
    return mMainHeapAddr[0];
}

void LogVariable::setFrequency(double pFrequency)
{
    mMainHeapAddr[0] = pFrequency;
}

double LogVariable::startTime()
{
    return mMainHeapAddr[1];
}

void LogVariable::setStartTime(double pStartTime)
{
    mMainHeapAddr[1] = pStartTime;
}

double LogVariable::duration()
{
    return mMainHeapAddr[2];
}

void LogVariable::setDuration(double pDuration)
{
    mMainHeapAddr[2] = pDuration;
}

void LogVariable::createHeap()
{
    // (size + Time Stamp) * frequency * duration + index
    int heapSize = ((size() + 1) * frequency() * duration() + 1)*sizeof(double);

    mHeap = new SharedMem( mName, heapSize );
    mHeapBeginAddr = (double*)mHeap->ptrToShMem();

	// Heap was created successfully.
    mHeapBeginAddr[0] = 0;      // size
    mHeapAddr = mHeapBeginAddr + 1;

    mLogCounter = 0;
}

void LogVariable::deleteHeap()
{

    if(mHeap != nullptr){
        delete mHeap;
        mHeap = nullptr;
        mHeapBeginAddr = nullptr;
        mHeapAddr = nullptr;
    }
}

void LogVariable::insertToHeap(double pTimeInSec, double pMainFreq)
{

    // TODO duration ondalik sayı olmasin.
    if( startTime() <= pTimeInSec && pTimeInSec < (startTime() + duration()) )
	{
        mLogCounter += frequency(); // increment counter

        if ( mLogCounter >= pMainFreq )
        {
            mLogCounter -= pMainFreq;   // reset counter;

            unsigned int num = size();
            std::memcpy( mHeapAddr, mVariableAddr, sizeof(double) * num );
            // copy variable
            mHeapAddr[num] = pTimeInSec;			// copy time stamp

            mHeapAddr += (num + 1);	// set next address
            ++(*mHeapBeginAddr);	// Increase index
        }
	}
}

void LogVariable::bindHeap()
{
    // first address is size address.
    mHeap = new SharedMem( mName );
    mHeapBeginAddr = (double*)mHeap->ptrToShMem();
    mHeapAddr = mHeapBeginAddr + 1;

    mLogCounter = 0;
}

void LogVariable::unbindHeap()
{
    if(mHeap != nullptr){
        delete mHeap;
        mHeap = nullptr;
    }
}

bool LogVariable::isHeapValid()
{
    return (mHeap != nullptr) && heapSize();
}

int LogVariable::heapSize()
{
    return static_cast<int>( mHeapBeginAddr[0] );
}

double* LogVariable::heapElement(int pIndex)
{
    return &(mHeapBeginAddr[ pIndex * (size() + 1) + 1 ]);
}

double LogVariable::heapElement(int pIndex, int pVariableIndex)
{
	return heapElement(pIndex)[pVariableIndex];
}

double LogVariable::heapElement(int pIndex, int pRow, int pCol)
{
	return heapElement(pIndex, pRow * col() + pCol);
}

double* LogVariable::lastHeapElement()
{
	int index = heapSize() - 1;	// Last element index
	return heapElement(index);
}

double LogVariable::lastHeapElement(int pVariableIndex)
{
	return lastHeapElement()[pVariableIndex];
}

double LogVariable::lastHeapElement(int pRow, int pCol)
{
	return lastHeapElement(pRow * col() + pCol);
}





