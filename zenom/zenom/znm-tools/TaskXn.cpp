//==============================================================================
// TaskXn.h - Native Task
//
// Author        :
// Version       : 2.0.01 (Temmuz 2018)
// Compatibility : POSIX, GCC
//==============================================================================

#include "TaskXn.h"

#include <iostream>
#include <chrono>
#include <pthread.h>

using namespace std::chrono::steady_clock;

TaskXn::TaskXn(string name,int priority)
    : mName(name)
    , mIsPeriodic(false)
{
    runTask(priority);
}

TaskXn::TaskXn(string name,
       int priority,
       duration period)
    : mName(name)
    , mIsPeriodic(true)
    , mPeriod(period)
{
    runTask(priority);
}

void TaskXn::runTask(int priority)
{
    mOverruns = 0;
    mWishToRun = true;
    mTask = thread(taskFunction);
    // Give RT priority to task
    sched_param sch;
    sch.__sched_priority = priority;
    if(pthread_setschedparam(mTask.native_handle(), SCHED_FIFO, &sch) == -1){
        mWishToRun = false;
        mTask.join();
        throw ZnmException(mName, "TaskXn::TaskXn,"
                                  " pthread_setschedparam", errno );
    }
}

TaskXn::~TaskXn()
{
    mWishToRun = false;
    if(mTask.joinable())
        mTask.join();

}

unsigned TaskXn::overruns()
{
    return mOverruns;
}

void TaskXn::join()
{
    mTask.join();
}

void TaskXn::detach()
{
    mTask.detach();
}

duration TaskXn::elapsedTime()
{
    return now() - mStartTime;
}

int TaskXn::maxPriority()
{
    return sched_get_priority_max(SCHED_FIFO);
}

int TaskXn::minPriority()
{
    return sched_get_priority_min(SCHED_FIFO);
}

void TaskXn::requestPeriodicTaskTermination()
{
    mWishToRun = false;
}

void TaskXn::taskFunction()
{
    mStartTime = now();
    if(mIsPeriodic){
        time_point nextStartTime = mStartTime + mPeriod;
        while(mWishToRun){
            run();
            // detect overrun
            if(nextStartTime - now() < 0){
                ++mOverruns;
            }
            std::this_thread::sleep_until(nextStartTime);
            nextStartTime += mPeriod;
        }
    }
    else{
        run();
    }
}

