//==============================================================================
// MessageQueue.hpp -  MessageQueue services
//
// Author        :
// Version       : 2.0.01 (Temmuz 2009)
// Compatibility : POSIX, GCC
//==============================================================================

// man mq_overview
#ifndef MESSAGEQUEUEXN_H_
#define MESSAGEQUEUEXN_H_
#include <string>
#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>           /* For O_* constants */
#include <unistd.h>
#include <mqueue.h>
#include <cerrno>
#include <system_error>
#include "znm-tools_global.h"

//==============================================================================
// class MsgQueue
//------------------------------------------------------------------------------
// \brief
// MessageQueue services
// MessageQueue sınıfı, processlerin iletisim kurmasını sağlar.Processler
// MessageQueue kullanarak mesaj gönderip, kuyruktan mesaj alırlar.
// MessageQueue bir process tarafından oluşturulur, diğer processler
// oluşturulan kuyruğa bağlanır.
//
// <b>Ornek Program:</b>
//
// \include MessageQueueXn.t.cpp
//==============================================================================

class MsgQueue
{
 public:

    /**
     * @brief MsgQueue creating constructor
     * @param name
     * @param maxNumOfMsgsInMQ
     * @param maxMsgSize
     * @param flags
     */
    MsgQueue(const std::string& nameOfNewMsgQueue,
             long maxNumOfMsgsInMQ,
             long maxMsgSize,
             znm_tools::Flags flags = znm_tools::Flags::READ_AND_WRITE);

    /**
     * @brief MsgQueue binding constructor
     * @param name
     * @param flags
     */
    MsgQueue(const std::string& nameOfMsgQueueToBind,
             znm_tools::Flags flags = znm_tools::Flags::READ_AND_WRITE);

    ~MsgQueue();

    /**
     * @brief operator = do not use assignment operator
     */
    MsgQueue & operator =(const MsgQueue&) = delete;

    /**
     * @brief MsgQueue do not use copy constructor
     */
    MsgQueue(const MsgQueue&) = delete;


    /**
     * @brief send
     * @param buf
     * @param size
     * @param size
     * @param priority
     * @param timeout if nullptr, it will be a blocking call, otherwise
     * it will try to send until timeout occurs
     * @return
     */
    int send(void *buf, size_t size , unsigned int priority= 31,
             struct timespec *timeout = nullptr);

    /**
     * @brief receive
     * @param buf
     * @param size
     * @param timeout if nullptr, it will be a blocking call, otherwise
     * it will try to receive until timeout occurs
     * @return
     */
    ssize_t receive(void *buf, size_t size,  struct timespec *timeout = nullptr);


    bool isBinded();

    bool isCreated();

private:
    mqd_t mMqfd; // Message queue file descriptor
    std::string mName;	// Name
    long mMaxMsgSize;
    long mNumMaxMsgs;
    bool mIsCreated;
};


#endif // MESSAGEQUEUEXN_H_
