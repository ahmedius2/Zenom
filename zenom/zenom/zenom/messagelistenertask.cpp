#include "messagelistenertask.h"
#include <MessageQueueXn.h>
#include <datarepository.h>
#include <unistd.h>

MessageListenerTask::MessageListenerTask( Zenom* pZenom )
{
    mZenom = pZenom;
}

void MessageListenerTask::run()
{
    while( true )
    {
        StateRequest stateRequest;
        if( DataRepository::instance()->readState( &stateRequest ) >= 0 )
        {
            switch (stateRequest)
            {

                case R_INIT:
                    // All functions in QQueue are reentrant.
                    mMessageQueue.enqueue( R_INIT );
                    break;

                case R_STOP:
                    QMetaObject::invokeMethod(mZenom, "on_stopButton_clicked");
                    break;

                default:
                    std::cout << "Message Listener Unhandled message" << std::endl;
                    break;
            }
        }
    }
}

bool MessageListenerTask::waitForInitMessage()
{
    // All functions in QQueue Class are reentrant.
    int attempt = 0;
    while ( mMessageQueue.isEmpty() && attempt < 20 )
    {
        usleep( 500000 );
        ++attempt;
    }

    if( attempt < 20 )
    {
        mMessageQueue.dequeue();
        return true;
    }
    else
    {
        return false;
    }

}
