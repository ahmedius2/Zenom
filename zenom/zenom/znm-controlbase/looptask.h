/*
 * LoopTask.h
 *
 *  Created on: Apr 4, 2012
 *      Author: root
 */

#ifndef LOOP_TASK_H_
#define LOOP_TASK_H_

#include <TaskXn.h>


class ControlBase;

class LoopTask: public TaskXn
{
public:
    LoopTask( ControlBase* pControlBase , std::string name);

private:
    void run();
	ControlBase* mControlBase;
};

#endif /* LOOP_TASK_H_ */
