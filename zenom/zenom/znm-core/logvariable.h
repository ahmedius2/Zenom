/*
 * LogVariable.h
 *
 *  Created on: Mar 26, 2012
 *      Author: Cuneyt AY
 */

#ifndef LOGVARIABLE_H_
#define LOGVARIABLE_H_

#include "variable.h"
#include <HeapXn.h>

class ZNMCORESHARED_EXPORT LogVariable: public Variable
{
public:
    LogVariable(double* pAddr, const std::string& pName, unsigned int pRow = 1, unsigned int pCol = 1, const std::string& pDesc = "");

	virtual ~LogVariable();

    void setMainHeapAddr( double* pHeapAddr );

    /**
     * Log degiskeni frekansini getirir.
     * @return Degisken frekansi
     */
    double frequency();

    /**
     * Log degiskeni frekansini gunceller.
     * @param Logfrequency  Yeni frekans
     */
    void setFrequency(double pFrequency);

    /**
     * Log degiskenin baslayacagi sureyi getirir.
     * @return Degiskenin baslangic zamani
     */
    double startTime();

    /**
     * Log degiskenin baslayacagi sureyi gunceller.
     * @param logStartTime  Yeni baslangic zamani
     */
    void setStartTime(double pStartTime);

    /**
     * Log degiskeninin devam edecegi sureyi getirir.
     * @return Degisken süreci
     */
    double duration();

    /**
     * Log degiskeninin devam edecegi sureyi gunceller.
     * @param logDuration  Yeni sürec
     */
    void setDuration(double pDuration);

    // Write Data
    void createHeap();

    void deleteHeap();

    void insertToHeap(double pTimeStamp, double pMainFreq);

    // Read Data
    void bindHeap();

    void unbindHeap();

    bool isHeapValid();

    int heapSize();

    double* heapElement(int pIndex);

    double heapElement(int pIndex, int pVariableIndex);

    double heapElement(int pIndex, int pRow, int pCol);

    double* lastHeapElement();

    double lastHeapElement(int pVariableIndex);

    double lastHeapElement(int pRow, int pCol);

protected:

    HeapXn mHeap;
    double* mHeapBeginAddr;
    double* mHeapAddr;

    double* mMainHeapAddr;

    double mLogCounter;
};

#endif /* LOGVARIABLE_H_ */
