#ifndef MESSAGELISTENERTASK_H_
#define MESSAGELISTENERTASK_H_

#include <QQueue>
#include <TaskXn.h>
#include "znm-core_global.h"
class Zenom;

class MessageListenerTask: public TaskXn
{
public:
    MessageListenerTask(Zenom* pZenom);

    bool waitForInitMessage();

private:
    virtual void run();
    QQueue<StateRequest> mMessageQueue;
    Zenom* mZenom;
};

#endif /* MESSAGELISTENERTASK_H_ */
