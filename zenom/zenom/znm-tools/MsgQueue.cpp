//==============================================================================
// MessageQueueXn.hpp - Native MessageQueue services
//
// Author        :
// Version       : 2.0.01 (Temmuz 2009)
// Compatibility : POSIX, GCC
//==============================================================================



#include "MsgQueue.h"

MsgQueue::MsgQueue(const std::string &nameOfNewMsgQueue, long maxNumOfMsgsInMQ,
                   long maxMsgSize, znm_tools::Flags flags)
{
    struct mq_attr mqAttr;
    mqAttr.mq_maxmsg = maxNumOfMsgsInMQ;
    mqAttr.mq_msgsize= maxMsgSize;
    mode_t mode  = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
    mMqfd = mq_open(nameOfNewMsgQueue.c_str(), flags | O_CREAT | O_EXCL, mode, &mqAttr);
    if (mMqfd == -1){
        if(errno == EEXIST){
            mq_unlink(nameOfNewMsgQueue.c_str());
            mMqfd = mq_open(nameOfNewMsgQueue.c_str(), flags|O_CREAT, mode, &mqAttr);
        }
        if (mMqfd == -1)
            throw ZnmException(name, "MsgQueue::create, mq_open" );
    }

    mName = nameOfNewMsgQueue;
    mMaxMsgSize = maxMsgSize;
    mNumMaxMsgs = maxNumOfMsgsInMQ;
    mIsCreated = true;
}

MsgQueue::MsgQueue(const std::string &nameOfMsgQueueToBind, znm_tools::Flags flags)
{
    // 0666 is default linux file permission
    mMqfd = mq_open(nameOfMsgQueueToBind.c_str(), flags);
    if (mMqfd == -1)
        throw ZnmException(name, "MsgQueue::bind, mq_open" );

    struct mq_attr mqAttr;
    if(mq_getattr(mMqfd, &mqAttr) == -1){
        mq_close(mMqfd);
        throw ZnmException(name, "MsgQueue::bind, mq_getattr" );
    }

    mName = nameOfMsgQueueToBind;
    mMaxMsgSize = mqAttr.mq_maxmsg;
    mNumMaxMsgs = mqAttr.mq_msgsize;
    mIsCreated = false;
}

MsgQueue::~MsgQueue()
{
    if(mIsCreated){
        if(mq_unlink(mName.c_str()) == -1 && errno != ENOENT)
            throw ZnmException(mName, "MsgQueue::unlink, mq_unlink" );
    }
    else{ // unbind
        if(mq_close(mMqfd) == -1)
            throw ZnmException(mName, "MsgQueue::unbind, mq_close" );
    }
}


int MsgQueue::send(void *buf, size_t size , unsigned int priority,
         struct timespec *timeout)
{
    int bytesSend = 0;
    if (timeout == nullptr)
        bytesSend = mq_send(mMqfd, (const char*)buf, size, priority);
    else
        bytesSend = mq_timedsend(mMqfd, (const char*)buf, size, priority,timeout);
    if (bytesSend == -1 && errno != ETIMEDOUT)
        throw ZnmException(mName, "MsgQueue::send" );
    return bytesSend;
}

ssize_t MsgQueue::receive(void *buf, size_t size,  struct timespec *timeout)
{
    int bytesReceived = 0;
    if (timeout == nullptr)
        bytesReceived = mq_receive(mMqfd, (char*)buf, size, nullptr);
    else
        bytesReceived = mq_timedreceive(mMqfd,(char*)buf, size, nullptr,timeout);
    if (bytesReceived == -1 && errno != ETIMEDOUT)
        throw ZnmException(mName, "MsgQueue::receive" );
    return bytesReceived;
}

bool MsgQueue::isBinded()
{
    return !mIsCreated;
}

bool MsgQueue::isCreated()
{
    return mIsCreated;
}
