/*
 * Variable.cpp
 *
 *  Created on: Mar 26, 2012
 *      Author: root
 */

#include "variable.h"

//==============================================================================
// Variable::Variable
//==============================================================================
Variable::Variable(double* pAddr, const std::string& pName, const std::string& pDesc , unsigned int pRow , unsigned int pCol)
{
    mVariableAddr = pAddr;
    mName = pName;
    mDescription = pDesc;
    mRow = pRow;
    mCol = pCol;
}

//==============================================================================
// Variable::~Variable
//==============================================================================
Variable::~Variable()
{

}

