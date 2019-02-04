/*
 * LifeCycleTask.cpp
 *
 *  Created on: Apr 22, 2012
 *      Author: root
 */

#include <iostream>
#include <datarepository.h>
#include "lifecycletask.h"
#include "controlbase.h"

LifeCycleTask::LifeCycleTask( ControlBase* pControlBase , std::string name)
    : TaskXn(name, 32)
    ,  mControlBase(pControlBase)

{

}

void LifeCycleTask::run()
{
	try
	{
        mControlBase->initializeControlBase();
        while( mControlBase->mState != TERMINATED )
        {
            StateRequest stateRequest;
            if ( DataRepository::instance()->readState( &stateRequest ) > 0 )
                // false (if an error occurred or the operation timed out).
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
                        std::cout << "R_TERMINATE message has come" << std::endl;
                        mControlBase->terminateControlBase();
                        break;

                    default:
                        std::cout << "Unhandled message" << std::endl;
                        break;
                }
            }
        }
	}
    catch (std::system_error e)
	{
        std::cerr << "Error occurred controlBase:"<< e.code() <<
                     std::string(e.what()) << std::endl;
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
