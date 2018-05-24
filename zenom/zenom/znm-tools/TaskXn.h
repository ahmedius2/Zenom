//==============================================================================
// TaskXn.hpp - Task class.
//
// Author        :
// Version       : 2.0.01 (Temmuz 2009)
// Compatibility : POSIX, GCC
//==============================================================================

#ifndef TASKXN_H_
#define TASKXN_H_

#include <string>
#include <thread>
#include <chrono>
#include "znm-tools_global.h"

//==============================================================================
// class TaskXn
//------------------------------------------------------------------------------
// \brief
//
// <b>Example Program:</b>
//
// \include TaskXn.t.cpp
//==============================================================================

/**
 * @brief The TaskXn class is an abstract class that needs to be extended
 * in order to write and run a task
 */
class TaskXn
{
 public:
    /**
     * @brief TaskXn non periodic task constructor
     * @param name
     * @param priority
     */
    TaskXn(std::string name, int priority = 16);

    /**
     * @brief TaskXn the thread needs to be started after creation
     * by calling the start function
     * @param name
     * @param period default is 16
     * @param priority nanosconds on x86 linux
     */
    TaskXn(std::string name,
           std::chrono::steady_clock::duration period,
           int priority = 16);

    /**
     * @brief operator = do not use it
     */
    TaskXn & operator =(const TaskXn&) = delete;

    /**
     * @brief TaskXn do not use copy constructor
     */
    TaskXn(const TaskXn&) = delete;

    /**
     * @brief ~TaskXn to stop thread, it must be destructed
     */
    virtual ~TaskXn();

//    void setOverrunLimit(unsigned ovrLimit);

    unsigned overruns();

    void join();

    void detach();

    std::chrono::duration<double> elapsedTimeSec();

    static int maxPriority();

    static int minPriority();

 protected:
    virtual void run() = 0;
    void requestPeriodicTaskTermination();
 private:
    void taskFunction();
    void runTask(int priority);

    std::string mName;
    std::thread mTask;
    std::chrono::steady_clock::duration mPeriod;
    std::chrono::steady_clock::time_point mStartTime;
    std::atomic<unsigned> mOverruns, mOverrunLimit;
    std::atomic<bool> mWishToRun, mIsPeriodic;
};


#endif // TASKXN_H_
