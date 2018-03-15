/*
 * LifeCycleTask.h
 *
 *  Created on: Apr 22, 2012
 *      Author: root
 */

#ifndef LIFE_CYCLE_TASK_H_
#define LIFE_CYCLE_TASK_H_

#include <TaskXn.h>
#include "controlbase.h"


class ControlBase;

class LifeCycleTask: public TaskXn
{
public:
	LifeCycleTask( ControlBase* pControlBase );

	virtual void run();

private:
	ControlBase* mControlBase;
};

#endif /* LIFE_CYCLE_TASK_H_ */
