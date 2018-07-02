#include "datarepository.h"
#include <fstream>
#include <iostream>
#include <system_error>

DataRepository* DataRepository::mInstance = NULL;

DataRepository* DataRepository::instance()
{
    if( !DataRepository::mInstance )
    {
        DataRepository::mInstance = new DataRepository();
    }

    return DataRepository::mInstance;
}

DataRepository::DataRepository()
    : mReceiver(nullptr)
    , mSender(nullptr)
    , mMainControlHeap(nullptr)
{
    mProjectName = "Test";
}

const std::string& DataRepository::projectName()
{
    return mProjectName;
}

void DataRepository::setProjectName(const std::string &pName)
{
    mProjectName = pName;
}
// Zenom process creates
void DataRepository::createMainControlHeap()
{
    // frequency, duration, current time, overrun
    int size = 4;

    // Control Variables
    for (unsigned int i = 0; i < mControlVariables.size(); ++i)
    {
        size += mControlVariables[i]->size();
    }

    // Log Variables
    // first double is frequency of log variable
    // second double is start time of log variable
    // third double is duration of log variable
    size += mLogVariables.size() * 3;

    mMainControlHeap = new SharedMem( mProjectName + "MainControlHeap",
                             size * sizeof(double) );
    mMainControlHeapAddr = (double*)mMainControlHeap->ptrToShMem();
    setFrequency( 1 );
    setDuration( 100 );
    setElapsedTimeSecond( 0 );
    setOverruns( 0 );
    assignHeapAddressToVariables();
}

void DataRepository::deleteMainControlHeap()
{
    delete mMainControlHeap;
    mMainControlHeap = nullptr;
}

// Control base process binds
void DataRepository::bindMainControlHeap()
{
    // first address is size
    mMainControlHeap = new SharedMem( mProjectName + "MainControlHeap");
    mMainControlHeapAddr = (double*)mMainControlHeap->ptrToShMem();

    assignHeapAddressToVariables();
}

void DataRepository::assignHeapAddressToVariables()
{
    int size = 4;
    // Control Variables Address
    for (unsigned int i = 0; i < mControlVariables.size(); ++i)
    {
        mControlVariables[i]->setMainHeapAddr( &(mMainControlHeapAddr[size]) );
        size += mControlVariables[i]->size();
    }

    // Log Variables Address
    for (unsigned int i = 0; i < mLogVariables.size(); ++i)
    {
        mLogVariables[i]->setMainHeapAddr( &(mMainControlHeapAddr[size]) );
        size += 3;
    }
}

void DataRepository::unbindMainControlHeap()
{
    delete mMainControlHeap;
    mMainControlHeap = nullptr;
}

void DataRepository::createLogVariablesHeap()
{
    try
    {
        for (unsigned int i = 0; i < mLogVariables.size(); ++i)
        {
            mLogVariables[i]->createHeap();
        }
    }
    catch( std::system_error e )
    {
        std::cout << std::string(e.what()) << std::endl;

    }
}

void DataRepository::deleteLogVariablesHeap()
{
    try
    {
        for (unsigned int i = 0; i < mLogVariables.size(); ++i)
        {
            mLogVariables[i]->deleteHeap();
        }
    }
    catch( std::system_error e )
    {
        std::cout << std::string(e.what()) << std::endl;

    }
}

void DataRepository::bindLogVariablesHeap()
{
    try
    {
        for (unsigned int i = 0; i < mLogVariables.size(); ++i)
        {
            mLogVariables[i]->bindHeap();
        }
    }
    catch( std::system_error e )
    {
        std::cout << std::string(e.what()) << std::endl;

    }
}

void DataRepository::unbindLogVariableHeap()
{
    try
    {
        for (unsigned int i = 0; i < mLogVariables.size(); ++i)
        {
            mLogVariables[i]->unbindHeap();
        }
    }
    catch( std::system_error e )
    {
        std::cout << std::string(e.what()) << std::endl;

    }
}

void DataRepository::createMessageQueues()
{
    mSender =
         new MsgQueue(mProjectName + "GuiToControl", 25,sizeof( StateRequest ));
    mReceiver =
         new MsgQueue(mProjectName + "ControlToGui", 25, sizeof( StateRequest));
}

void DataRepository::deleteMessageQueues()
{
    delete mSender,
    delete mReceiver;
    mSender = mReceiver = nullptr;
}

void DataRepository::bindMessageQueues()
{
    mSender   = new MsgQueue(mProjectName + "GuiToControl");
    mReceiver = new MsgQueue(mProjectName + "ControlToGui");
}

void DataRepository::unbindMessageQueues()
{
    delete mSender,
    delete mReceiver;
    mSender = mReceiver = nullptr;
}

void DataRepository::sendStateRequest(StateRequest pRequest)
{
    mSender->send(&pRequest, sizeof(StateRequest) );
}

ssize_t DataRepository::readState(StateRequest* pState)
{
    // timeout 1 seconds
    static struct timespec to;
    to.tv_nsec = 0;
    to.tv_sec = 1;
    return mReceiver->receive( pState, sizeof(StateRequest), &to );
}

void DataRepository::sampleLogVariable(double pSimTimeInSec)
{
    for (unsigned int i = 0; i < mLogVariables.size(); ++i)
    {
        mLogVariables[i]->insertToHeap( pSimTimeInSec, frequency() );
    }
}

void DataRepository::insertLogVariable(LogVariable *pLogVariable)
{
    mLogVariables.push_back( pLogVariable );
}

const LogVariableList &DataRepository::logVariables()
{
    return mLogVariables;
}

LogVariable* DataRepository::findLogVariable(const std::string &pName)
{
    for ( unsigned int i = 0; i < mLogVariables.size(); ++i )
    {
        if ( mLogVariables[i]->name() == pName )
        {
            return mLogVariables[i];
        }
    }

    return NULL;
}

void DataRepository::insertControlVariable(ControlVariable *pControlVariable)
{
    mControlVariables.push_back( pControlVariable );
}

const ControlVariableList &DataRepository::controlVariables()
{
    return mControlVariables;
}

void DataRepository::writeVariablesToFile()
{
    std::ofstream file ("variables.txt");
    if ( !file.is_open() )
        return;

    ControlVariable* controlVariable;
    file << mControlVariables.size() << std::endl;
    for (unsigned int i = 0; i < mControlVariables.size(); ++i)
    {
        controlVariable = mControlVariables[i];
        file << controlVariable->name() << std::endl;
        file << controlVariable->row() << std::endl;
        file << controlVariable->col() << std::endl;
        file << controlVariable->description() << std::endl;
    }

    LogVariable* logVariable;
    file << mLogVariables.size() << std::endl;
    for (unsigned int i = 0; i < mLogVariables.size(); ++i)
    {
        logVariable = mLogVariables[i];
        file << logVariable->name() << std::endl;
        file << logVariable->row() << std::endl;
        file << logVariable->col() << std::endl;
        file << logVariable->description() << std::endl;
    }

    file.close();
}

bool DataRepository::readVariablesFromFile()
{
    std::ifstream file ("variables.txt");
    if ( !file.is_open() )
        return false;

     std::string countString, name, desc, row, col;
     unsigned int count;

     getline( file, countString );
     count = atoi( countString.c_str() );

    for (unsigned int i = 0; i < count; ++i)
    {
        getline( file, name );
        getline( file, row );
        getline( file, col );
        getline( file, desc );

        mControlVariables.push_back( new ControlVariable(NULL, name,
                                atoi(row.c_str()), atoi(col.c_str()), desc) );
    }

    getline( file, countString );
    count = atoi( countString.c_str() );

    for (unsigned int i = 0; i < count; ++i)
    {
        getline( file, name );
        getline( file, row );
        getline( file, col );
        getline( file, desc );

        mLogVariables.push_back( new LogVariable(NULL, name,
                       atoi(row.c_str()), atoi(col.c_str()), desc) );
    }

    file.close();

    remove( "variables.txt" );

    return true;
}

void DataRepository::clear()
{
    for (unsigned int i = 0; i < mControlVariables.size(); ++i)
    {
        delete mControlVariables[i];
    }
    mControlVariables.clear();

    for (unsigned int i = 0; i < mLogVariables.size(); ++i)
    {
        delete mLogVariables[i];
    }
    mLogVariables.clear();
}
