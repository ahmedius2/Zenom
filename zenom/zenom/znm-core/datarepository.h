#ifndef DATAREPOSITORY_H
#define DATAREPOSITORY_H

#include <vector>
#include <logvariable.h>
#include <controlvariable.h>
#include <MessageQueueXn.h>

typedef std::vector<ControlVariable*> ControlVariableList;
typedef std::vector<LogVariable*> LogVariableList;

class DataRepository
{
public:

    static DataRepository* instance();

    const std::string& projectName();
    void setProjectName(const std::string& pName);

    void createMainControlHeap();
    void deleteMainControlHeap();

    void bindMainControlHeap();
    void unbindMainControlHeap();

    inline double frequency(){ return mMainControlHeapAddr[0]; }
    void setFrequency(double pFrequency) { mMainControlHeapAddr[0] = pFrequency; }

    inline double duration(){ return mMainControlHeapAddr[1]; }
    void setDuration(double pDuration) { mMainControlHeapAddr[1] = pDuration; }

    inline double elapsedTimeSecond(){ return mMainControlHeapAddr[2]; }
    void setElapsedTimeSecond(double pElapsedTime) { mMainControlHeapAddr[2] = pElapsedTime; }

    inline double overruns(){ return mMainControlHeapAddr[3]; }
    void setOverruns(double pOverruns) { mMainControlHeapAddr[3] = pOverruns; }

    void createLogVariablesHeap();
    void deleteLogVariablesHeap();

    void bindLogVariablesHeap();
    void unbindLogVariableHeap();

    void createMessageQueues();
    void deleteMessageQueues();

    void bindMessageQueues();
    void unbindMessageQueues();

    void sendStateRequest(StateRequest pRequest);
    ssize_t readState(StateRequest *pState);

    void sampleLogVariable( double pSimTimeInSec );

    void insertLogVariable(LogVariable*);
    const LogVariableList& logVariables();
    LogVariable* findLogVariable(const std::string &pName);

    void insertControlVariable(ControlVariable*);
    const ControlVariableList& controlVariables();

    void writeVariablesToFile();
    bool readVariablesFromFile();

    void clear();

private:
    static DataRepository* mInstance;

    DataRepository();

    void assignHeapAddressToVariables();

    std::string mProjectName;
    LogVariableList mLogVariables;
    ControlVariableList mControlVariables;

    HeapXn mMainControlHeap;
    double* mMainControlHeapAddr;

    MessageQueueXn mSender;
    MessageQueueXn mReceiver;
};

#endif // DATAREPOSITORY_H
