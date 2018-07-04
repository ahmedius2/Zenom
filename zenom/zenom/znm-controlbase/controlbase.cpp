#include "controlbase.h"

#include <sys/mman.h>



using namespace std::chrono;
ControlBase::ControlBase(/*int argc, char* argv[]*/)
{
    mDataRepository = DataRepository::instance();
    myfile.open ("controlbase.log", std::ios::out);
}

ControlBase::~ControlBase()
{
    myfile.close();

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
        std::cout << "Invalid argument" << std::endl;
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
	}
    catch ( std::exception& e)
	{
        std::cout << "Life Task Error occurred: " << std::string(e.what())
                  << std::endl;
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
            std::cerr << "The initialize() function returned non zero: "
                      <<
                         error << std::endl;
        }
    }
    catch( std::exception& e )
    {
        std::cerr << "An exception occured in the initialize() function: "
                  << e.what() << std::endl;
    }
    catch (...)
    {
        std::cerr << "An unknown exception occured in the initialize()"
                     " function." << std::endl;
    }

    mDataRepository->writeVariablesToFile();
    mDataRepository->bindMessageQueues();
    myfile << "Controlbase binded to Message queues" << std::endl;
    mDataRepository->sendStateRequest( R_INIT );
    myfile << "Controlbase sent first state request" << std::endl;
    // Send message to GUI to read variables
    bool bind_success = false;
    do{
        try{
            mDataRepository->bindMainControlHeap();
            bind_success = true;
        }
        catch (std::system_error e){
            myfile << "Bind problem: " << e.what() << std::endl;
            if(e.code() == std::errc::no_such_file_or_directory){
                std::this_thread::sleep_for(std::chrono::milliseconds(5));
            }
            else
                throw e;
        }
    }while(!bind_success);

    myfile << "Controlbase binded to main heap" << std::endl;

    // Control Variable degerleri heap'e kopyalanir.
    for (size_t i = 0; i < mDataRepository->controlVariables().size(); ++i)
    {
        mDataRepository->controlVariables()[i]->copyToHeap();
    }

    myfile << "Controlbase copied variables to heap" << std::endl;

    mDataRepository->sendStateRequest( R_INIT );

    myfile << "Controlbase sent second state request" << std::endl;
    // Send message to GUI to read values
    mState = STOPPED;
}

//============================================================================//
//		START OPERATIONS													  //
//============================================================================//
void ControlBase::startControlBase()
{
    myfile << "startControlBase is called" << std::endl;
	if( mState != RUNNING )
    {
        myfile << "Controlbase starting" << std::endl;

        mDataRepository->bindLogVariablesHeap();

        myfile << "Controlbase binded to log var. heap" << std::endl;
        syncMainHeap();

        myfile << "Controlbase synced to main heap" << std::endl;

        int error = 0;

        try
        {
            myfile << "Controlbase starting user defined start" << std::endl;
            error = start();	// User Function
            myfile << "Controlbase ended user defined start" << std::endl;

            // start() hata ile donerse program baslatilmaz.
            if ( error )
            {
                std::cerr << "The start() function returned non zero: " <<
                             error << std::endl;
            }
        }
        catch( std::exception& e )
        {
            error = -1;
            std::cerr << "An exception occured in the start() function: " <<
                         e.what() << std::endl;
        }
        catch (...)
        {
            error = -1;
            std::cerr << "An unknown exception occured in the start() "
                         "function." << std::endl;
        }

        // start() hata ile donerse program baslatilmaz.
        if ( error )
        {
            myfile << "Controlbase an error occured" << std::endl;
            mState = STOPPED;
            DataRepository::instance()->sendStateRequest( R_STOP );
            myfile << "Controlbase sent request to stop" << std::endl;
            mDataRepository->unbindLogVariableHeap();
            myfile << "Controlbase unbinded log variables heap" << std::endl;
        }
        else
        {
            mState = RUNNING;
            myfile << "Controlbase creating loop task" << std::endl;
            mLoopTask = new LoopTask(
                            this,
                            std::chrono::duration<double>(
                                1.0 / mDataRepository->frequency()
                            ),
                            mDataRepository->projectName() + "LoopTask"
                        );
            myfile << "Controlbase starting loop task" << std::endl;
            mLoopTask->runTask();
            // error is probably somewhere here
            myfile << "Controlbase loop task should be running" << std::endl;
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

    mDataRepository->setElapsedTimeSecond(mLifeCycleTask->elapsedTimeSec() );
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
        mLoopTask->join();
        //...
        delete mLoopTask;

        mDataRepository->unbindLogVariableHeap();

        try
        {
            int error = stop();			// User Function
            if( error )
            {
                std::cerr << "The stop() function returned non zero: "
                          << error << std::endl;
            }
        }
        catch( std::exception& e )
        {
            std::cerr << "An exception occured in the stop() function: "
                      << e.what() << std::endl;
        }
        catch (...)
        {
            std::cerr << "An unknown exception occured in the stop() function."
                      << std::endl;
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

