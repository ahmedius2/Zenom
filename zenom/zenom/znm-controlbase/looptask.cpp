/*
 * LoopTask.cpp
 *
 *  Created on: Apr 4, 2012
 *      Author: root
 */

#include <iostream>
#include "looptask.h"
#include <datarepository.h>
#include "controlbase.h"

LoopTask::LoopTask( ControlBase* pControlBase, std::string name)
    : TaskXn(name, mControlBase->period())
    , mControlBase(pControlBase)

{
}

void LoopTask::run()
{
    int error = 0;
    if( mControlBase->mState != STOPPED )
    {
        if( mControlBase->mState != PAUSED )
        {
            try
            {
                error = mControlBase->doloop();			// User Function
                if( error )
                {
                    std::cerr << "The doloop() function returned non zero: "
                              << error << std::endl;
                }
            }
            catch( std::exception& e )
            {
                error = -1;
                std::cerr << "An exception occured in the doloop() function:"
                          << e.what() << std::endl;
            }
            catch (...)
            {
                error = -1;
                std::cerr << "An unknown exception occured in the doloop()"
                             " function." << std::endl;
            }

            mControlBase->logVariables( mControlBase->mDuration );
            mControlBase->syncMainHeap();
        }
	}

    if( mControlBase->mLifeCycleTask->elapsedTimeSec()
            > mControlBase->mDuration || error )
    {
        DataRepository::instance()->sendStateRequest( R_STOP );
        this->requestPeriodicTaskTermination();
    }
}
