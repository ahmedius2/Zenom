#include "datarepository.h"
#include <fstream>

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
    size += mLogVariables.size() * 3;

    mMainControlHeap.create( mProjectName + "MainControlHeap", size * sizeof(double) );
    mMainControlHeapAddr = (double*)mMainControlHeap.alloc( size * sizeof(double) );

    setFrequency( 1 );
    setDuration( 100 );
    setElapsedTimeSecond( 0 );
    setOverruns( 0 );
    assignHeapAddressToVariables();
}

void DataRepository::deleteMainControlHeap()
{
    if( mMainControlHeap.isCreated() )
    {
        mMainControlHeap.free( mMainControlHeapAddr );
        mMainControlHeap.deleteHeap();
    }
}

void DataRepository::bindMainControlHeap()
{
    // first address is size
    mMainControlHeap.bind( mProjectName + "MainControlHeap" );
    mMainControlHeapAddr = (double*)mMainControlHeap.alloc( 0 );

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
    if( mMainControlHeap.isBinded() )
    {
        mMainControlHeap.unbind();
    }
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
    catch( ZnmException e )
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
    catch( ZnmException e )
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
    catch( ZnmException e )
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
    catch( ZnmException e )
    {
        std::cout << std::string(e.what()) << std::endl;

    }
}

void DataRepository::createMessageQueues()
{
    mSender.create( mProjectName + "GuiToControl", sizeof( StateRequest ) * 25, Q_UNLIMITED, Q_SHARED );
    mReceiver.create( mProjectName + "ControlToGui", sizeof( StateRequest ) * 25, Q_UNLIMITED, Q_SHARED );
}

void DataRepository::deleteMessageQueues()
{
    mSender.deleteQueue();
    mReceiver.deleteQueue();
}

void DataRepository::bindMessageQueues()
{
    mSender.bind( mProjectName + "ControlToGui" );
    mReceiver.bind( mProjectName + "GuiToControl" );
}

void DataRepository::unbindMessageQueues()
{
    mSender.unbind();
    mReceiver.unbind();
}

void DataRepository::sendStateRequest(StateRequest pRequest)
{
    mSender.write( &pRequest, sizeof(StateRequest) );
}

ssize_t DataRepository::readState(StateRequest* pState)
{
    return mReceiver.read( pState, sizeof(StateRequest), 1000000000LL ); // timeout 1 seconds
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

        mControlVariables.push_back( new ControlVariable(NULL, name, atoi(row.c_str()), atoi(col.c_str()), desc) );
    }

    getline( file, countString );
    count = atoi( countString.c_str() );

    for (unsigned int i = 0; i < count; ++i)
    {
        getline( file, name );
        getline( file, row );
        getline( file, col );
        getline( file, desc );

        mLogVariables.push_back( new LogVariable(NULL, name, atoi(row.c_str()), atoi(col.c_str()), desc) );
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
