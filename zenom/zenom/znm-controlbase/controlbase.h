#ifndef CONTROLBASE_H_
#define CONTROLBASE_H_

#include <vector>
#include <datarepository.h>
#include <MsgQueue.h>
#include <iostream>
#include <fstream>
#include "looptask.h"
#include "lifecycletask.h"


//#define SECOND_TO_NANO (1000000000)
//#define MILLISECOND_TO_NANO (1000000)

class ControlBase
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

    double frequency() {
       return  mDataRepository->frequency();
    }

	double period() {
		return 1.0 / mDataRepository->frequency();
	}

	double elapsedTime() {
		return mLoopTask->elapsedTimeSec();
	}

	double duration() {
		return mDataRepository->duration();
	}

	int overruns() { return mLoopTask->overruns(); }

	private:

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
	//		LOOP OPERATIONS									   			      //
	//========================================================================//
	void syncMainHeap();
	// Loop Task Elapsed Time
	void logVariables( double pSimTime );

	//========================================================================//
	//		STOP OPERATIONS														  //
    //========================================================================//
	void stopControlBase();

    //========================================================================//
	//		TERMINATE OPERATIONS												  //
    //========================================================================//
	void terminateControlBase();

	LifeCycleTask* mLifeCycleTask;
	LoopTask* mLoopTask;
	State mState;
	DataRepository* mDataRepository;



};

#endif /* CONTROLBASE_H_ */
