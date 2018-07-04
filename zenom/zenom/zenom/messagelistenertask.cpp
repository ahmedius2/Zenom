#include <QMetaObject>
#include <MsgQueue.h>
#include <datarepository.h>
#include <unistd.h>
#include <iostream>

#include "messagelistenertask.h"
#include "zenom.h"

MessageListenerTask::MessageListenerTask( Zenom* pZenom )
    :  TaskXn("MessageListenerTask")
    , mZenom(pZenom)
{
}

void MessageListenerTask::run()
{
    StateRequest stateRequest;
    while( true )
    {
        //std::cerr << "MessageListenerTask waiting for state message" << std::endl;
        if( DataRepository::instance()->readState( &stateRequest ) >= 0 )
        {
            std::cerr << "MessageListenerTask state read" << std::endl;
            switch (stateRequest)
            {

                case R_INIT:
                    // All functions in QQueue are reentrant.
                    mMessageQueue.enqueue( R_INIT );
                    std::cerr << "read state R_INIT" << std::endl;
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
    // All functions in QQueue Class are reentrant.
    int attempt = 0;
    while ( mMessageQueue.isEmpty() && attempt < 40 )
    {
        std::cerr << "waiting for init message" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        ++attempt;
    }

    if( attempt < 40 )
    {
        mMessageQueue.dequeue();
        return true;
    }
    else
    {
        return false;
    }

}
