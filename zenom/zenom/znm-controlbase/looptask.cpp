/*
 * LoopTask.cpp
 *
 *  Created on: Apr 4, 2012
 *      Author: root
 */

#include "looptask.h"
#include <datarepository.h>

LoopTask::LoopTask( ControlBase* pControlBase, std::string name)
    : mControlBase(pControlBase)
    , TaskXn(name, mControlBase->period())
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

            mControlBase->logVariables( mControlBase->elapsedTime() );
            mControlBase->syncMainHeap();
        }
	}

    if( mControlBase->mElapsedTimeInSecond > mControlBase->mDuration
            || error )
    {
        DataRepository::instance()->sendStateRequest( R_STOP );
        this->requestPeriodicTaskTermination();
    }
}
