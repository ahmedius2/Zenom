/*
 * LifeCycleTask.h
 *
 *  Created on: Apr 22, 2012
 *      Author: root
 */

#ifndef LIFE_CYCLE_TASK_H_
#define LIFE_CYCLE_TASK_H_

#include <TaskXn.h>

class ControlBase;

class LifeCycleTask : public TaskXn
{
public:
    LifeCycleTask( ControlBase* pControlBase , std::string name);

private:
    ControlBase* mControlBase;
    void run() override;
};

#endif /* LIFE_CYCLE_TASK_H_ */
