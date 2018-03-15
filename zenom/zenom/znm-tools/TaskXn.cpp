//==============================================================================
// TaskXn.h - Native Task
//
// Author        :
// Version       : 2.0.01 (Temmuz 2009)
// Compatibility : POSIX, GCC
//==============================================================================

#include "TaskXn.h"

#include <iostream>
using namespace std;
//==============================================================================
// TaskXn::TaskXn
//==============================================================================
TaskXn::TaskXn()
{
    mState = znm_tools::NONE;
}

//==============================================================================
// TaskXn::~TaskXn
//==============================================================================
TaskXn::~TaskXn()
{

}

//==============================================================================
// TaskXn::create
//==============================================================================
void TaskXn::create(const std::string& pTaskName, int stksize, int prio , int mode)
{
	mTaskName = pTaskName;
	int err;

	if( (err = rt_task_create( &task, pTaskName.c_str(), stksize, prio, mode )) )
	{
		throw ZnmException(mTaskName, "rt_task_create", -err );
	}
    mState = znm_tools::CREATED;
}

//==============================================================================
// TaskXn::deleteTask
//==============================================================================
void TaskXn::deleteTask()
{
    if ( isCreated() )
    {
        mState = znm_tools::NONE;

        int err;	//Hata denetim
        if( (err = rt_task_delete(&task)) )
        {
            throw ZnmException(mTaskName, "rt_task_delete", -err );
        }
    }
}

//==============================================================================
// TaskXn::start
//==============================================================================
void TaskXn::start(void(*entry)(void *cookie), void *cookie)
{
	int err;

	if( (err = rt_task_start(&task, entry, cookie)) )
	{
		throw ZnmException(mTaskName, "rt_task_start", -err );
	}
}

//==============================================================================
// TaskXn::start
//==============================================================================
void TaskXn::start()
{
	start( TaskXn::taskRun, (void *)this );
}

void TaskXn::taskRun(void *classPtr)
{
	TaskXn *ptr = (TaskXn*) classPtr;
	ptr->run();
}

//==============================================================================
// TaskXn::setPeriodic
//==============================================================================
void TaskXn::setPeriodic(RTIME idate, RTIME period)
{
	int err;	//Hata denetim

	if( (err = rt_task_set_periodic( &task, idate, period )) )
	{
		throw ZnmException(mTaskName, "rt_task_set_periodic", -err );
	}
}

//==============================================================================
// TaskXn::waitPeriod
//==============================================================================
int TaskXn::waitPeriod( unsigned long* pOverruns )
{
    return rt_task_wait_period( pOverruns );
}

//==============================================================================
// TaskXn::suspend
//==============================================================================
void TaskXn::suspend()
{
	int err;	//Hata denetim

	if( (err = rt_task_suspend( &task )) )	// Task askiya alinir.
	{
		throw ZnmException(mTaskName, "rt_task_suspend", -err );
	}
}

//==============================================================================
// TaskXn::resume
//==============================================================================
void TaskXn::resume()
{
	int err;	//Hata denetim

	if( (err = rt_task_resume( &task )) )	// Task'a kaldigi yerden devam eder.
	{
		throw ZnmException(mTaskName, "rt_task_resume", -err );
	}
}

//==============================================================================
// TaskXn::yield
//==============================================================================
void TaskXn::yield()
{
	int err;	//Hata denetim

	if( (err = rt_task_yield()) )	// Manual round-robin.
	{
		throw ZnmException(mTaskName, "rt_task_yield", -err );
	}
}

//==============================================================================
// TaskXn::setPriority
//==============================================================================
void TaskXn::setPriority(int prio)
{
	int err;	//Hata denetim

	if( (err = rt_task_set_priority( &task, prio)) < 0 )
	{
		throw ZnmException(mTaskName, "rt_task_set_priority", -err );
	}
}

//==============================================================================
// TaskXn::self
//==============================================================================
RT_TASK* TaskXn::self()
{
	return rt_task_self();
}

//==============================================================================
// TaskXn::slice
//==============================================================================
void TaskXn::slice(RTIME quantum)
{
	int err;	//Hata denetim

	if( (err = rt_task_slice( &task, quantum )) )
	{
		throw ZnmException(mTaskName, "rt_task_slice", -err );
	}
}

//==============================================================================
// TaskXn::join
//==============================================================================
void TaskXn::join()
{
	int err;	//Hata denetim

	// Task'in islemini bitirmesi beklenir
	if( (err = rt_task_join( &task) ) )
	{
		throw ZnmException(mTaskName, "rt_task_join", -err );
	}
}

//==============================================================================
// TaskXn::inquire
//==============================================================================
RT_TASK_INFO TaskXn::inquire()
{
	RT_TASK_INFO info;
	int err;	//Hata denetim

	if( (err = rt_task_inquire(&task, &info)) )
	{
		throw ZnmException(mTaskName, "rt_task_inquire", -err );
	}

	return info;
}

