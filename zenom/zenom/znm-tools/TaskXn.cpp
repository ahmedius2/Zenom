//==============================================================================
// TaskXn.h - Native Task
//
// Author        :
// Version       : 2.0.01 (Temmuz 2009)
// Compatibility : POSIX, GCC
//==============================================================================

#include "TaskXn.h"

#include <iostream>
#include <chrono>

using namespace std;

TaskXn::TaskXn()
{

}

TaskXn::~TaskXn()
{

}

void TaskXn::setPeriod()
{

}

int TaskXn::waitForPeriodToFinish()
{

}

void TaskXn::yield()
{
    std::this_thread::yield();
}

void TaskXn::join()
{
    if(mTask.joinable())
        mTask.join();
}

