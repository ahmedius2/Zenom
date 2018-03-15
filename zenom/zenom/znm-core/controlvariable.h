/*
 * ControlVariable.h
 *
 *  Created on: Apr 9, 2012
 *      Author: root
 */

#ifndef CONTROLVARIABLE_H_
#define CONTROLVARIABLE_H_

#include "variable.h"
#include <string.h>

class ZNMCORESHARED_EXPORT ControlVariable: public Variable
{
public:
    ControlVariable(double* pAddr, const std::string& pName, unsigned int pRow = 1, unsigned int pCol = 1, const std::string& pDesc = "");
	virtual ~ControlVariable();

    void setMainHeapAddr( double* pHeapAddr );

    double heapElement(int pIndex);
    void setHeapElement(int pIndex, double pVal);

    double heapElement(int pRow, int pCol);
    void setHeapElement(int pRow, int pCol, double pVal);

    void copyToHeap();
    void copyFromHeap();

private:
    double* mMainHeapAddr;
};

#endif /* CONTROLVARIABLE_H_ */
