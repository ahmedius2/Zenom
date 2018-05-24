#ifndef MESSAGELISTENERTASK_H_
#define MESSAGELISTENERTASK_H_

#include <TaskXn.h>
#include <QQueue>
#include "zenom.h"
class Zenom;

class MessageListenerTask: public TaskXn
{
public:
    MessageListenerTask(Zenom* pZenom);

    virtual void run();

    /*
     *
     */
    bool waitForInitMessage();

private:
    Zenom* mZenom;
    QQueue<StateRequest> mMessageQueue;
};

#endif /* MESSAGELISTENERTASK_H_ */
