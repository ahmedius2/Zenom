#include "controlbase.h"

#include <sys/mman.h>



using namespace std::chrono;
ControlBase::ControlBase(/*int argc, char* argv[]*/)
{
    mDataRepository = DataRepository::instance();
    //File
    logFile.open ("cblog.txt");
    logFile<<"LogFile is started"<<std::endl;
    logFile.flush();
}

ControlBase::~ControlBase()
{
    logFile << "Controlbase object is dying" << std::endl;
    logFile.flush();
    logFile.close();
}

void ControlBase::registerLogVariable(double *pVariable,
                                      const std::string& pName,
                                      unsigned int pRow,
                                      unsigned int pCol,
                                      const std::string& pDesc)
{
    mDataRepository->insertLogVariable(
                new LogVariable( pVariable, pName, pRow, pCol, pDesc )
                );
}

void ControlBase::registerLogVariable(double& pVariable,
                                      const std::string& pName,
                                      const std::string& pDesc)
{
    registerLogVariable(&pVariable, pName, 1, 1, pDesc);
}

void ControlBase::registerControlVariable(double *pVariable,
                                          const std::string& pName,
                                          unsigned int pRow,
                                          unsigned int pCol,
                                          const std::string& pDesc)
{
    mDataRepository->insertControlVariable(
                new ControlVariable( pVariable, pName, pRow, pCol, pDesc )
                );
}

void ControlBase::registerControlVariable(double& pVariable,
                                          const std::string& pName,
                                          const std::string& pDesc)
{
    registerControlVariable( &pVariable, pName, 1, 1, pDesc );
}


void ControlBase::run(int argc, char *argv[])
{
    if ( argc != 2 )
    {
        logFile << "Invalid argument" << std::endl;
        logFile.flush();
        return;
    }

    mlockall ( MCL_CURRENT | MCL_FUTURE );
	try
	{
        mDataRepository->setProjectName( argv[1] );

        mLifeCycleTask = new LifeCycleTask( this,
                                   mDataRepository->projectName() +
                                   "LifeCycleTask");
        mLifeCycleTask->runTask();
        mLifeCycleTask->join(); // wait for execution to finish
		delete mLifeCycleTask;
        logFile << "LifeCycleTask is deleted" << std::endl;
        logFile.flush();
	}
    catch ( std::exception& e)
	{
        logFile << "Life Task Error occurred: " << std::string(e.what())
                  << std::endl;
        logFile.flush();
	}
}


//============================================================================//
//		INITIALIZE OPERATIONS												  //
//============================================================================//
void ControlBase::initializeControlBase()
{

    logFile<<"initializeControlBase()"<<std::endl;
    logFile.flush();

    try
    {
        int error = initialize();	// User Function
        if( error )
        {
            logFile << "The initialize() function returned non zero: "
                      <<
                         error << std::endl;
            logFile.flush();
        }
    }
    catch( std::exception& e )
    {
        logFile << "An exception occured in the initialize() function: "
                  << e.what() << std::endl;
        logFile.flush();
    }
    catch (...)
    {
        logFile << "An unknown exception occured in the initialize()"
                     " function." << std::endl;
        logFile.flush();
    }

    mDataRepository->writeVariablesToFile();
    mDataRepository->bindMessageQueues();
    mDataRepository->sendStateRequest( R_INIT );

    StateRequest dumpState;
    while ( mDataRepository->readState( &dumpState ) < 0 )
        // false (if an error occurred or the operation timed out).
        std::this_thread::sleep_for(std::chrono::milliseconds(10));

    logFile<<"void ControlBase::initializeControlBase() dumpState : "<<dumpState<<std::endl;


    // Send message to GUI to read variables
     mDataRepository->bindMainControlHeap();

    // Control Variable degerleri heap'e kopyalanir.
    for (size_t i = 0; i < mDataRepository->controlVariables().size(); ++i)
    {
        mDataRepository->controlVariables()[i]->copyToHeap();
    }

    mDataRepository->sendStateRequest( R_INIT );

    // Send message to GUIe.flush();
    mState = STOPPED;

    logFile<<"End Of void ControlBase::initializeControlBase()"<<std::endl;
    logFile.flush();
}

//============================================================================//
//		START OPERATIONS													  //
//============================================================================//
void ControlBase::startControlBase()
{

    logFile<<"void ControlBase::startControlBase()"<<std::endl;
    logFile.flush();

    if( mState != RUNNING )
    {

        mDataRepository->bindLogVariablesHeap();

        int error = 0;

        try
        {
            error = start();	// User Function

            // start() hata ile donerse program baslatilmaz.
            if ( error )
            {
                logFile << "The start() function returned non zero: " <<
                             error << std::endl;
                logFile.flush();
            }
        }
        catch( std::exception& e )
        {
            error = -1;
            logFile << "An exception occured in the start() function: " <<
                         e.what() << std::endl;
            logFile.flush();
        }
        catch (...)
        {
            error = -1;
            logFile << "An unknown exception occured in the start() "
                         "function." << std::endl;
            logFile.flush();
        }

        // start() hata ile donerse program baslatilmaz.
        if ( error )
        {
            mState = STOPPED;
            DataRepository::instance()->sendStateRequest( R_STOP );
            mDataRepository->unbindLogVariableHeap();
        }
        else
        {
            mState = RUNNING;
            mLoopTask = new LoopTask(
                            this,
                            std::chrono::duration<double>(
                                1.0 / mDataRepository->frequency()
                            ),
                            mDataRepository->projectName() + "LoopTask"
                        );
            mLoopTask->runTask();
            // error is probably somewhere here
        }
    }
}

void ControlBase::pauseControlBase()
{
    mState = PAUSED;
}

void ControlBase::resumeControlBase()
{
	mState = RUNNING;
}

//============================================================================//
//		LOOP OPERATIONS														  //
//============================================================================//
void ControlBase::syncMainHeap()
{
    for (size_t i = 0; i < mDataRepository->controlVariables().size(); ++i)
    {
        mDataRepository->controlVariables()[i]->copyFromHeap();
    }

    mDataRepository->setElapsedTimeSecond(mLoopTask->elapsedTimeSec() );
    mDataRepository->setOverruns( mLoopTask->overruns() );
}


void ControlBase::logVariables( double pSimTime )
{
    mDataRepository->sampleLogVariable( pSimTime );
}


//============================================================================//
//		STOP OPERATIONS														  //
//============================================================================//
void ControlBase::stopControlBase()
{
    if( mState != STOPPED )
    {
        mState = STOPPED;
        mLoopTask->requestPeriodicTaskTermination();
        mLoopTask->join();
        //...
        delete mLoopTask;

        mDataRepository->unbindLogVariableHeap();
        logFile << "unbinded from log variable heap" << std::endl;
        logFile.flush();

        try
        {
            int error = stop();			// User Function
            if( error )
            {
                logFile << "The stop() function returned non zero: "
                          << error << std::endl;
                logFile.flush();
            }
        }
        catch( std::exception& e )
        {
            logFile << "An exception occured in the stop() function: "
                      << e.what() << std::endl;
            logFile.flush();
        }
        catch (...)
        {
            logFile << "An unknown exception occured in the stop() function."
                      << std::endl;
            logFile.flush();
        }
    }
}

//============================================================================//
//		TERMINATE OPERATIONS												  //
//============================================================================//
void ControlBase::terminateControlBase()
{
    mDataRepository->unbindMessageQueues();
    logFile << "unbinded from message queues" << std::endl;
    logFile.flush();
    mDataRepository->unbindMainControlHeap();
    logFile << "unbinded from heap" << std::endl;
    logFile.flush();


    mState = TERMINATED;
	terminate();	// User Function
}

