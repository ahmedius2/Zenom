//==============================================================================
// TaskXn.h - Native Task
//
// Author        :
// Version       : 2.0.01 (Temmuz 2018)
// Compatibility : POSIX, GCC
//==============================================================================

#include <iostream>
#include <pthread.h>
#include <system_error>
#include "TaskXn.h"


TaskXn::TaskXn(std::string name,int priority)
    : mName(name)
    , mPriority(priority)
    , mOverruns(0)
    , mIsPeriodic(false)
    , mWishToRun(false)
{
}

TaskXn::TaskXn(std::string name,
       std::chrono::duration<double> period,
       int priority)
    : mName(name)
    , mPriority(priority)
    , mOverruns(0)
    , mIsPeriodic(true)
    , mWishToRun(false)
{
    mPeriod =
        std::chrono::duration_cast<std::chrono::steady_clock::duration>(period);
}



TaskXn::~TaskXn()
{
    mWishToRun = false;
    if(mTask.joinable())
        mTask.join();
}

void TaskXn::runTask()
{
    if(mWishToRun){
        std::cerr << "Task " + mName + " is already running..." << std::endl;
        return;
    }
    mWishToRun = true;
    mTask = std::thread(&TaskXn::taskFunction, this);
    // Give RT priority to task
    sched_param sch;
    sch.__sched_priority = mPriority;
    if(pthread_setschedparam(mTask.native_handle(), SCHED_FIFO, &sch) == -1){
        mWishToRun = false;
        mTask.join();
        throw std::system_error(errno, std::system_category(),
                        mName +" TaskXn, mq_open");
    }
}

unsigned TaskXn::overruns()
{
    return mOverruns;
}

void TaskXn::join()
{
    // if you don't request periodic task termination before
    // calling this function, it wil block indefinetlyS
    mTask.join();
}

void TaskXn::detach()
{
    mTask.detach();
}

double TaskXn::elapsedTimeSec()
{
    return std::chrono::duration_cast<std::chrono::duration<double>>
                      (std::chrono::steady_clock::now() - mStartTime).count();
}

double TaskXn::period()
{
    return std::chrono::duration_cast<std::chrono::duration<double>>(
                                                           mPeriod
                                                           ).count();
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
    mStartTime = std::chrono::steady_clock::now();
    if(mIsPeriodic){

        auto nextStartTime = mStartTime + mPeriod;
        while(mWishToRun){
            run();
            // count overrun
            if((nextStartTime - std::chrono::steady_clock::now()).count() < 0){
                ++mOverruns;
                //std::cerr << "Task " << mName << " overrun: " << mOverruns <<
                //             " !" << std::endl;
            }
            std::this_thread::sleep_until(nextStartTime);
            nextStartTime += mPeriod;
        }
    }
    else{
        run();
        mWishToRun = false;
    }
}

