#ifndef CONTROLBASE_H_
#define CONTROLBASE_H_

#include <vector>
#include <datarepository.h>
#include <MessageQueueXn.h>
#include "looptask.h"
#include "lifecycletask.h"

#include "znm-controlbase_global.h"

class LoopTask;
#define SECOND_TO_NANO (1000000000)
#define MILLISECOND_TO_NANO (1000000)

class ZNMCONTROLBASESHARED_EXPORT ControlBase
{
	friend class LoopTask;
	friend class LifeCycleTask;

public:

	ControlBase(/*int argc, char* argv[]*/);

	virtual ~ControlBase();

    /**
     * Register Functions
     */
    void registerLogVariable(double *pVariable, const std::string& pName, unsigned int pRow = 1, unsigned int pCol = 1, const std::string& pDesc= "");

    void registerLogVariable(double& pVariable, const std::string& pName, const std::string& pDesc= "");

    void registerControlVariable(double *pVariable, const std::string& pName, unsigned int pRow = 1, unsigned int pCol = 1, const std::string& pDesc= "");

    void registerControlVariable(double& pVariable, const std::string& pName, const std::string& pDesc= "");

    void run(int argc, char *argv[]);

	virtual int initialize(){return 0;}

	virtual int start(){return 0;}

    virtual int doloop(){return 0;}

	virtual int stop(){return 0;}

	virtual int terminate(){return 0;}

	double frequency() { return mFrequency; }
	void setFrequency( double pFrequency );

    double period() { return 1.0 / frequency(); }

	int duration() { return mDuration; }
	void setDuration( int pSimDurationInSec );

	RTIME simTicks() { return mElapsedTicks; }
	RTIME simTimeInNano() { return mElapsedTimeInNano; }
	double simTimeInMiliSec() { return mElapsedTimeInMiliSecond; }
	double simTimeInSec() { return mElapsedTimeInSecond; }

	int overruns() { return mOverruns; }

private:
	// Loop Task Elapsed Time
	RTIME mElapsedTicks;
	RTIME mElapsedTimeInNano;
	double mElapsedTimeInMiliSecond;	// long double ?
	double mElapsedTimeInSecond;

	int mOverruns;
	int mFrequency;
	int mDuration;

	//============================================================================//
	//		INITIALIZE OPERATIONS												  //
	//============================================================================//
	void initializeControlBase();

	//============================================================================//
	//		START OPERATIONS													  //
	//============================================================================//
	void startControlBase();
	void pauseControlBase();
	void resumeControlBase();

	//============================================================================//
	//		LOOP OPERATIONS														  //
	//============================================================================//
	void syncMainHeap();
	void setElapsedTime( RTIME pElapsedTimeNano );	// Loop Task Elapsed Time in Nano
	void setOverruns( int pOverrun );	// Loop Task Overruns
    void logVariables( double pSimTime );

	//============================================================================//
	//		STOP OPERATIONS														  //
	//============================================================================//
	void stopControlBase();

	//============================================================================//
	//		TERMINATE OPERATIONS												  //
	//============================================================================//
	void terminateControlBase();

	LoopTask* mLoopTask;
	State mState;
    DataRepository* mDataRepository;
};

#endif /* CONTROLBASE_H_ */
