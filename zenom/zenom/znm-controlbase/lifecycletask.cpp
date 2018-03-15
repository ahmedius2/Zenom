/*
 * LifeCycleTask.cpp
 *
 *  Created on: Apr 22, 2012
 *      Author: root
 */

#include "lifecycletask.h"
#include <datarepository.h>

LifeCycleTask::LifeCycleTask( ControlBase* pControlBase )
{
	mControlBase = pControlBase;
}

void LifeCycleTask::run()
{
	try
	{
        mControlBase->initializeControlBase();
        while( mControlBase->mState != TERMINATED )
        {
            StateRequest stateRequest;
            if ( DataRepository::instance()->readState( &stateRequest ) >= 0 )   // false (if an error occurred or the operation timed out).
            {
                switch (stateRequest)
                {
                    case R_START:
                        mControlBase->startControlBase();
                        break;

                    case R_PAUSE:
                        mControlBase->pauseControlBase();
                        break;

                    case R_RESUME:
                        mControlBase->resumeControlBase();
                        break;

                    case R_STOP:
                        mControlBase->stopControlBase();
                        break;

                    case R_TERMINATE:
                        mControlBase->terminateControlBase();
                        break;

                    default:
                        std::cout << "Unhandled message" << std::endl;
                        break;
                }
            }
        }
	}
    catch (ZnmException e)
	{
        std::cerr << "Error occurred controlBase:"<< e.errorNo() << std::string(e.what()) << std::endl;
	}
    catch (std::exception e)
    {
        std::cerr << "Exception occured: " << e.what() << std::endl;
    }
    catch (...)
    {
        std::cerr << "Unknown exception occured." << std::endl;
    }
}
