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
#include "znm-tools_global.h"
#include "znmException.h"

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

class ZNMTOOLSSHARED_EXPORT MsgQueue
{
 public:
    MsgQueue();

    /**
     * @brief operator = do not use it
     */
    MsgQueue & operator =(const MsgQueue&) = delete;

    /**
     * @brief MsgQueue do not use copy constructor
     */
    MsgQueue(const MsgQueue&) = delete;

    virtual ~MsgQueue();

    void create( const std::string& name, long maxNumOfMsgsInMQ,
                 long maxMsgSize,int flags = znm_tools::Flags::READ_AND_WRITE);

    void bind( const std::string& name,
               int flags = znm_tools::Flags::READ_AND_WRITE);

    void unbind();

    void unlink();

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
    int send(void *buf, size_t size , unsigned int priority= 0,
             struct timespec *timeout);

    /**
     * @brief receive
     * @param buf
     * @param size
     * @param timeout if nullptr, it will be a blocking call, otherwise
     * it will try to receive until timeout occurs
     * @return
     */
    ssize_t receive(void *buf, size_t size,  struct timespec *timeout);


    bool isBinded();

    bool isCreated();

private:
    int mMqfd; // Message queue file descriptor
    std::string mName;	// Name
    long mMaxMsgSize;
    long mNumMaxMsgs;
    bool mIsCreated;
    bool mIsBinded;
};


#endif // MESSAGEQUEUEXN_H_
