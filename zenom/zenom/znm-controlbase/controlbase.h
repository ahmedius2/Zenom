#ifndef CONTROLBASE_H_
#define CONTROLBASE_H_

#include <vector>
#include <datarepository.h>
#include <MsgQueue.h>
#include "looptask.h"
#include "lifecycletask.h"

#include "znm-controlbase_global.h"

#define SECOND_TO_NANO (1000000000)
#define MILLISECOND_TO_NANO (1000000)

class ZNMCONTROLBASESHARED_EXPORT ControlBase
{
    friend class LifeCycleTask;
	friend class LoopTask;

public:

	ControlBase(/*int argc, char* argv[]*/);

	virtual ~ControlBase();

    /**
     * Register Functions
     */
    void registerLogVariable(double *pVariable,
                             const std::string& pName,
                             unsigned int pRow = 1,
                             unsigned int pCol = 1,
                             const std::string& pDesc= "");

    void registerLogVariable(double& pVariable,
                             const std::string& pName,
                             const std::string& pDesc= "");

    void registerControlVariable(double *pVariable,
                                 const std::string& pName,
                                 unsigned int pRow = 1,
                                 unsigned int pCol = 1,
                                 const std::string& pDesc= "");

    void registerControlVariable(double& pVariable,
                                 const std::string& pName,
                                 const std::string& pDesc= "");

    void run(int argc, char *argv[]);

	virtual int initialize(){return 0;}

	virtual int start(){return 0;}

    virtual int doloop(){return 0;}

	virtual int stop(){return 0;}

	virtual int terminate(){return 0;}

    //std::chrono::steady_clock::duration period() { return mPeriod; }

    //std::chrono::steady_clock::duration elapsedTime() {
    //    return mLifeCycleTask->elapsedTimeSec();
    //}

    //int overruns() { return mLoopTask->overruns(); }

private:
    // Duration of simulation, it will end at this time.
    std::chrono::seconds<double> mDuration;


    //========================================================================//
    //		INITIALIZE OPERATIONS											  //
    //========================================================================//
	void initializeControlBase();

    //========================================================================//
    //		START OPERATIONS                                                  //
    //========================================================================//
	void startControlBase();
	void pauseControlBase();
	void resumeControlBase();

    //========================================================================//
    //		LOOP OPERATIONS												  //
	//============================================================================//
	void syncMainHeap();
    // Loop Task Elapsed Time
    void logVariables( std::chrono::duration pSimTime );

	//============================================================================//
	//		STOP OPERATIONS														  //
	//============================================================================//
	void stopControlBase();

	//============================================================================//
	//		TERMINATE OPERATIONS												  //
	//============================================================================//
	void terminateControlBase();

    LifeCycleTask* mLifeCycleTask;
	LoopTask* mLoopTask;
	State mState;
    DataRepository* mDataRepository;
};

#endif /* CONTROLBASE_H_ */
