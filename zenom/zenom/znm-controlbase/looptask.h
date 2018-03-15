/*
 * LoopTask.h
 *
 *  Created on: Apr 4, 2012
 *      Author: root
 */

#ifndef LOOP_TASK_H_
#define LOOP_TASK_H_

#include <TaskXn.h>
#include "controlbase.h"
#include <native/timer.h>

class ControlBase;

class LoopTask: public TaskXn
{
public:
	LoopTask( ControlBase* pControlBase );

	void run();

private:
	ControlBase* mControlBase;
};

#endif /* LOOP_TASK_H_ */
