//==============================================================================
// TaskXn.hpp - Native Task class.
//
// Author        :
// Version       : 2.0.01 (Temmuz 2009)
// Compatibility : POSIX, GCC
//==============================================================================

#ifndef TASKXN_H_
#define TASKXN_H_

#include <native/task.h>
#include <string>
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

#define TASK_TIMEOUT 10000000000LL  // Varsayilan zaman asimi olarak 10sn
#define TASK_MODE_C    T_JOINABLE      // Varsayilan yarailma modu
#define TASK_PRIO    50
#define TASK_STACK_SIZE  0

class ZNMTOOLSSHARED_EXPORT TaskXn
{
 public:
	 TaskXn();

     virtual ~TaskXn();

	 void create(const std::string& pTaskName, int stksize = TASK_STACK_SIZE, int prio = TASK_PRIO, int mode = TASK_MODE_C);

	 void deleteTask();

     bool isCreated() { return mState == znm_tools::CREATED; }

	 void start(void(*entry)(void *cookie), void *cookie);

	 void start();

	 void setPeriodic(RTIME idate, RTIME period);

     int waitPeriod( unsigned long* pOverruns = NULL );

	 void suspend();

	 void resume();

	 void yield();

	 void setPriority( int prio );

	 RT_TASK* self();

	 void slice(RTIME quantum);

	 void join();

	 RT_TASK_INFO inquire();

 protected:
	 virtual void run() {};

 private:
	 static void taskRun(void *classPtr);

  	 RT_TASK task;

  	 std::string mTaskName;
     znm_tools::State mState;
};


#endif // TASKXN_H_
