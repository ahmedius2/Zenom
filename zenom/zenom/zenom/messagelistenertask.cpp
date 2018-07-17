#include <QMetaObject>
#include <MsgQueue.h>
#include <datarepository.h>
#include <unistd.h>
#include <iostream>

#include "messagelistenertask.h"
#include "zenom.h"

MessageListenerTask::MessageListenerTask( Zenom* pZenom )
    :  mZenom(pZenom),
       initMsgs(0),
       TaskXn("MessageListenerTask")
{

}

void MessageListenerTask::run()
{
    StateRequest stateRequest;
    while( mZenom->simulationState() != TERMINATED &&
           mZenom->simulationState() != CRASHED)
    {
        if( DataRepository::instance()->readState( &stateRequest ) > 0 )
        {
            std::cerr << "MessageListenerTask state read" << std::endl;
            switch (stateRequest)
            {

                case R_INIT:
                    std::cerr << "read state R_INIT" << std::endl;
                    mtx.lock();
                    ++initMsgs;
                    mtx.unlock();
                    condvar.notify_one();
                    break;

                case R_STOP:
                    QMetaObject::invokeMethod(mZenom, "on_stopButton_clicked");
                    std::cerr << "read state R_STOP" << std::endl;
                    break;

                default:
                    std::cout << "Message Listener Unhandled message" <<
                                 std::endl;
                    break;
            }
        }
    }
}

bool MessageListenerTask::waitForInitMessage()
{
    using namespace std::chrono;

    std::unique_lock<std::mutex> ulock(mtx);

    bool ret = condvar.wait_for(ulock,seconds(5),[this]{return initMsgs != 0;});

    if(ret)
        --initMsgs;
    else
        std::cerr << "Init message timeout..." << std::endl;

    return ret;
}
