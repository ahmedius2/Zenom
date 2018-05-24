/*
 * ControlVariable.cpp
 *
 *  Created on: Apr 9, 2012
 *      Author: root
 */

#include "controlvariable.h"

ControlVariable::ControlVariable(double* pAddr, const std::string& pName, unsigned int pRow, unsigned int pCol, const std::string& pDesc)
: Variable(pAddr, pName, pDesc, pRow, pCol)
{
    mMainHeapAddr = NULL;
}

ControlVariable::~ControlVariable()
{

}

void ControlVariable::setMainHeapAddr(double *pHeapAddr)
{
    mMainHeapAddr = pHeapAddr;
}

double ControlVariable::heapElement(int pIndex)
{
    return mMainHeapAddr[pIndex];
}

void ControlVariable::setHeapElement(int pIndex, double pVal)
{
    mMainHeapAddr[pIndex] = pVal;
}

double ControlVariable::heapElement(int pRow, int pCol)
{
    return mMainHeapAddr[pRow * col() + pCol];
}

void ControlVariable::setHeapElement(int pRow, int pCol, double pVal)
{
    mMainHeapAddr[pRow * col() + pCol] = pVal;
}

void ControlVariable::copyToHeap()
{
    memcpy( mMainHeapAddr, mVariableAddr, sizeof(double) * size() );
}

void ControlVariable::copyFromHeap()
{
    memcpy( mVariableAddr, mMainHeapAddr, sizeof(double) * size() );
}
