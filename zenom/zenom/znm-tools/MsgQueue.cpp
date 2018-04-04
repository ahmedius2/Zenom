//==============================================================================
// MessageQueueXn.hpp - Native MessageQueue services
//
// Author        :
// Version       : 2.0.01 (Temmuz 2009)
// Compatibility : POSIX, GCC
//==============================================================================


#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>           /* For O_* constants */
#include <unistd.h>
#include <mqueue.h>
#include "MsgQueue.h"

MsgQueue::MsgQueue()
{
    mIsCreated = false;
    mIsBinded  = false;
}

MsgQueue::~MsgQueue()
{
    if(mIsCreated)
        unlink();
}

void MsgQueue::create( const std::string& name, long maxNumOfMsgsInMQ, long maxMsgSize,
             int flags = znm_tools::Flags::READ_AND_WRITE )
{
    if (mIsBinded || mIsCreated){
        if (!name.compare(mName))
            return;
        throw ZnmException("MsgQueue::create, "
                                  "already binded or created\n" );
    }

    // 0666 is default linux file permission
    struct mq_attr mqAttr;
    mqAttr.mq_maxmsg = maxNumOfMsgsInMQ;
    mqAttr.mq_msgsize= maxMsgSize;
    mMqfd = mq_open(name.c_str(), flags | O_CREAT | O_EXCL, 0666, &mqAttr);
    if (mMqfd == -1)
        throw ZnmException(name, "MsgQueue::create, mq_open", errno );

    mName = name;
    mMaxMsgSize = maxMsgSize;
    mNumMaxMsgs = maxNumOfMsgsInMQ;
    mIsCreated = true;
    mIsBinded = true;
}


void MsgQueue::bind( const std::string& name,
                           int flags = znm_tools::Flags::READ_AND_WRITE)
{
    if (mIsBinded || mIsCreated){
        if (!name.compare(mName))
            return;
        throw ZnmException("MsgQueue::bind, "
                                  "already binded or created\n" );
    }

    // 0666 is default linux file permission
    mMqfd = mq_open(name.c_str(), flags);
    if (mMqfd == -1)
        throw ZnmException(name, "MsgQueue::bind, mq_open", errno );

    struct mq_attr mqAttr;
    if(mq_getattr(mMqfd, &mqAttr) == -1){
        mq_close(mMqfd);
    }

    mName = name;
    mMaxMsgSize = mqAttr.mq_maxmsg;
    mNumMaxMsgs = mqAttr.mq_msgsize;
    mIsBinded = true;
}

void MsgQueue::unbind()
{
    if(!mIsBinded)
        return;
    if(mq_close(mMqfd) == -1)
        throw ZnmException(mName, "MsgQueue::unbind, close", errno );
    mIsBinded = false;
}

void MsgQueue::unlink()
{
    if(!mIsBinded && !mIsCreated)
        return;
    if(mIsBinded)
        unbind();
    if(mq_unlink(mName.c_str()) == -1)
        throw ZnmException(mName, "MsgQueue::unlink, shm_unlink", errno );
    mIsCreated = false;
}

int MsgQueue::send(void *buf, size_t size , unsigned int priority,
         struct timespec *timeout)
{
    int bytesSend = 0;
    if (timeout == nullptr)
        bytesSend = mq_send(mMqfd, buf, size, priority);
    else
        bytesSend = mq_timedsend(mMqfd, buf, size, priority,timeout);
    if (bytesSend == -1 && errno != ETIMEDOUT)
        throw ZnmException(mName, "MsgQueue::send", errno );
    return bytesSend;
}

ssize_t receive(void *buf, size_t size,  struct timespec *timeout)
{
    int bytesReceived = 0;
    if (timeout == nullptr)
        bytesReceived = mq_receive(mMqfd, buf, size, nullptr);
    else
        bytesReceived = mq_timedreceive(mMqfd, buf, size, nullptr,timeout);
    if (bytesReceived == -1 && errno != ETIMEDOUT)
        throw ZnmException(mName, "MsgQueue::receive", errno );
    return bytesReceived;
}

bool MsgQueue::isBinded()
{
    return mIsBinded;
}

bool MsgQueue::isCreated()
{
    return mIsCreated;
}
