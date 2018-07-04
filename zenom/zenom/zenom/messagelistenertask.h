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
    void run() override;
    QQueue<StateRequest> mMessageQueue;
    Zenom* mZenom;
};

#endif /* MESSAGELISTENERTASK_H_ */
