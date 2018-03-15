/*
 * LoopTask.cpp
 *
 *  Created on: Apr 4, 2012
 *      Author: root
 */

#include "looptask.h"
#include <datarepository.h>

LoopTask::LoopTask( ControlBase* pControlBase )
{
	mControlBase = pControlBase;
}

void LoopTask::run()
{
    int error = 0;
	RTIME now, previous;
	RTIME elapsedTime = 0;
    unsigned long totalOverruns = 0;
    unsigned long overruns;
	double frequency = mControlBase->mFrequency;
	double duration = mControlBase->mDuration;

	this->setPeriodic( TM_NOW , SECOND_TO_NANO / frequency );
	previous = rt_timer_read();

    while( mControlBase->mState != STOPPED )
    {
        waitPeriod( &overruns );
        totalOverruns += overruns;
        mControlBase->setOverruns( totalOverruns );

        if( mControlBase->mState != PAUSED )
        {
            try
            {
                error = mControlBase->doloop();			// User Function
                if( error )
                {
                    std::cerr << "The doloop() function returned non zero: " << error << std::endl;
                }
            }
            catch( std::exception& e )
            {
                error = -1;
                std::cerr << "An exception occured in the doloop() function: " << e.what() << std::endl;
            }
            catch (...)
            {
                error = -1;
                std::cerr << "An unknown exception occured in the doloop() function." << std::endl;
            }

            mControlBase->logVariables( elapsedTime );
            mControlBase->syncMainHeap();

            now = rt_timer_read();
            elapsedTime += (now - previous);
            mControlBase->setElapsedTime( elapsedTime );
            previous = now;
        }
        else
        {
            now = rt_timer_read();
            previous = now;
        }

        if( mControlBase->mElapsedTimeInSecond > duration || error )
        {
            DataRepository::instance()->sendStateRequest( R_STOP );
            break;
        }
	}
}
