#include "controlbase.h"

#include <sys/mman.h>
#include <rtdk.h>

ControlBase::ControlBase(/*int argc, char* argv[]*/)
{
    mDataRepository = DataRepository::instance();

	setFrequency( 1 );
	setDuration( 10 );
	setElapsedTime( 0 );	mElapsedTicks = 0;
	setOverruns( 0 );
}

ControlBase::~ControlBase()
{

}

void ControlBase::registerLogVariable(double *pVariable, const std::string& pName, unsigned int pRow, unsigned int pCol, const std::string& pDesc)
{
    mDataRepository->insertLogVariable( new LogVariable( pVariable, pName, pRow, pCol, pDesc ) );
}

void ControlBase::registerLogVariable(double& pVariable, const std::string& pName, const std::string& pDesc)
{
    registerLogVariable(&pVariable, pName, 1, 1, pDesc);
}

void ControlBase::registerControlVariable(double *pVariable, const std::string& pName, unsigned int pRow, unsigned int pCol, const std::string& pDesc)
{
    mDataRepository->insertControlVariable( new ControlVariable( pVariable, pName, pRow, pCol, pDesc ) );
}

void ControlBase::registerControlVariable(double& pVariable, const std::string& pName, const std::string& pDesc)
{
    registerControlVariable( &pVariable, pName, 1, 1, pDesc );
}

void ControlBase::setFrequency( double pFrequency )
{
	if ( pFrequency > 0 )
	{
		mFrequency = pFrequency;
	}
}

void ControlBase::setDuration( int pDurationInSec )
{
	if ( pDurationInSec > 0 )
	{
		mDuration = pDurationInSec;
	}
}

void ControlBase::run(int argc, char *argv[])
{
    if ( argc != 2 )
    {
        std::cout << "Invalid argument" << std::endl;
        return;
    }

    mlockall ( MCL_CURRENT | MCL_FUTURE );
    rt_print_auto_init(1);

	try
	{
        mDataRepository->setProjectName( argv[1] );

        LifeCycleTask* lifeCycleTask = new LifeCycleTask( this );
        lifeCycleTask->create( mDataRepository->projectName() + "LifeCycleTask");
		lifeCycleTask->start();
		lifeCycleTask->join();
		delete lifeCycleTask;
	}
    catch (ZnmException e)
	{
        std::cout << "Life Task Error occurred: " << std::string(e.what()) << std::endl;
	}
}


//============================================================================//
//		INITIALIZE OPERATIONS												  //
//============================================================================//
void ControlBase::initializeControlBase()
{
    try
    {
        int error = initialize();	// User Function
        if( error )
        {
            std::cerr << "The initialize() function returned non zero: " << error << std::endl;
        }
    }
    catch( std::exception& e )
    {
        std::cerr << "An exception occured in the initialize() function: " << e.what() << std::endl;
    }
    catch (...)
    {
        std::cerr << "An unknown exception occured in the initialize() function." << std::endl;
    }

    mDataRepository->writeVariablesToFile();
    mDataRepository->bindMessageQueues();
    mDataRepository->sendStateRequest( R_INIT ); // Send message to GUI to read variables
    mDataRepository->bindMainControlHeap();

    // Control Variable degerleri heap'e kopyalanir.
    for (size_t i = 0; i < mDataRepository->controlVariables().size(); ++i)
    {
        mDataRepository->controlVariables()[i]->copyToHeap();
    }

    mDataRepository->sendStateRequest( R_INIT ); // Send message to GUI to read values
    mState = STOPPED;
}

//============================================================================//
//		START OPERATIONS													  //
//============================================================================//
void ControlBase::startControlBase()
{
	if( mState != RUNNING )
    {
        setElapsedTime( 0 );
        mElapsedTicks = 0;
        setOverruns( 0 );
        mDataRepository->bindLogVariablesHeap();
        syncMainHeap();

        int error = 0;

        try
        {
            error = start();	// User Function

            // start() hata ile donerse program baslatilmaz.
            if ( error )
            {
                std::cerr << "The start() function returned non zero: " << error << std::endl;
            }
        }
        catch( std::exception& e )
        {
            error = -1;
            std::cerr << "An exception occured in the start() function: " << e.what() << std::endl;
        }
        catch (...)
        {
            error = -1;
            std::cerr << "An unknown exception occured in the start() function." << std::endl;
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

            mLoopTask = new LoopTask(this);
            mLoopTask->create( mDataRepository->projectName() + "LoopTask" );
            mLoopTask->start();
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

    mFrequency = mDataRepository->frequency();
    mDuration = mDataRepository->duration();

    mDataRepository->setElapsedTimeSecond( mElapsedTimeInSecond );
    mDataRepository->setOverruns( mOverruns );
}

void ControlBase::setElapsedTime( RTIME pElapsedTimeNano )
{
	mElapsedTicks++;
	mElapsedTimeInNano = pElapsedTimeNano;
	mElapsedTimeInMiliSecond = (double)pElapsedTimeNano / MILLISECOND_TO_NANO;
	mElapsedTimeInSecond = (double)pElapsedTimeNano / SECOND_TO_NANO;
}

void ControlBase::setOverruns( int pOverrun )
{
	mOverruns = pOverrun;
}

void ControlBase::logVariables( double pSimTime )
{
    mDataRepository->sampleLogVariable( pSimTime / SECOND_TO_NANO );
}


//============================================================================//
//		STOP OPERATIONS														  //
//============================================================================//
void ControlBase::stopControlBase()
{
    if( mState != STOPPED )
    {
        mState = STOPPED;
        mLoopTask->join();
        delete mLoopTask;

        mDataRepository->unbindLogVariableHeap();

        try
        {
            int error = stop();			// User Function
            if( error )
            {
                std::cerr << "The stop() function returned non zero: " << error << std::endl;
            }
        }
        catch( std::exception& e )
        {
            std::cerr << "An exception occured in the stop() function: " << e.what() << std::endl;
        }
        catch (...)
        {
            std::cerr << "An unknown exception occured in the stop() function." << std::endl;
        }
    }
}

//============================================================================//
//		TERMINATE OPERATIONS												  //
//============================================================================//
void ControlBase::terminateControlBase()
{
    mDataRepository->unbindMessageQueues();
    mDataRepository->unbindMainControlHeap();

    mState = TERMINATED;
	terminate();	// User Function
}

