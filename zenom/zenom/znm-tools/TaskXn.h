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
#include "znmException.h"

//==============================================================================
// class TaskXn
//------------------------------------------------------------------------------
// \brief
//
// <b>Example Program:</b>
//
// \include TaskXn.t.cpp
//==============================================================================

#define TASK_PRIO    50

class TaskXn
{
 public:
     TaskXn(std::string name);

     virtual ~TaskXn();

     void setPeriod();

     void setPriority( int prio );

	 void yield();

	 void join();

 protected:
     virtual void run() = 0;

 private:
     std::thread mTask;
     std::string mName;

};


#endif // TASKXN_H_
