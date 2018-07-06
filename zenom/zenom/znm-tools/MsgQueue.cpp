//==============================================================================
// MessageQueueXn.hpp - MessageQueue services
//
// Author        :
// Version       : 2.0.01 (Temmuz 2009)
// Compatibility : POSIX, GCC
//==============================================================================



#include "MsgQueue.h"
#include<cstring>
#include <iostream>

MsgQueue::MsgQueue(const std::string &nameOfNewMsgQueue, long maxNumOfMsgsInMQ,
                   long maxMsgSize, znm_tools::Flags flags)
{
    std::string name = '/' + nameOfNewMsgQueue;

    struct mq_attr mqAttr;
    mqAttr.mq_maxmsg = maxNumOfMsgsInMQ;
    mqAttr.mq_msgsize= maxMsgSize;
    mode_t mode  = 0777;
    mMqfd = mq_open(name.c_str(), flags|O_CREAT|O_EXCL,
                    mode, &mqAttr);
    if (mMqfd == -1){
        if(errno == EEXIST){
            mq_unlink(name.c_str());
            mMqfd = mq_open(name.c_str(), flags|O_CREAT,
                            mode, &mqAttr);
        }
        if (mMqfd == -1)
            throw std::system_error(errno, std::system_category(),
                                name +" MsgQueue, mq_open");
    }

    mName = name;
    mMaxMsgSize = maxMsgSize;
    mNumMaxMsgs = maxNumOfMsgsInMQ;
    mIsCreated = true;
}

MsgQueue::MsgQueue(const std::string &nameOfMsgQueueToBind,znm_tools::Flags flags)
{
    std::string name = '/' + nameOfMsgQueueToBind;

    mMqfd = mq_open(name.c_str(), flags);
    if (mMqfd == -1)
        throw std::system_error(errno, std::system_category(),
                        name +" MsgQueue, mq_open");

    struct mq_attr mqAttr;
    if(mq_getattr(mMqfd, &mqAttr) == -1){
        mq_close(mMqfd);
        throw std::system_error(errno, std::system_category(),
                        name +" MsgQueue, mq_getattr");
    }

    mName = name;
    mMaxMsgSize = mqAttr.mq_maxmsg;
    mNumMaxMsgs = mqAttr.mq_msgsize;
    mIsCreated = false;

}

MsgQueue::~MsgQueue()
{
    if(mq_close(mMqfd) == -1)
        std::cerr << "~MsgQueue, mq_close error:"<< strerror(errno)<< std::endl;
    if(mIsCreated && mq_unlink(mName.c_str()) == -1 && errno != ENOENT)
        std::cerr << "~MsgQueue, mq_unlink error:"<<strerror(errno)<< std::endl;

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
        throw std::system_error(errno, std::system_category(),
                    mName +" MsgQueue::send");
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
        throw std::system_error(errno, std::system_category(),
                    mName +" MsgQueue::receive");
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
