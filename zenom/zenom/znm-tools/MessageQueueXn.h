//==============================================================================
// MessageQueueXn.hpp - Native MessageQueue services
//
// Author        :
// Version       : 2.0.01 (Temmuz 2009)
// Compatibility : POSIX, GCC
//==============================================================================

#ifndef MESSAGEQUEUEXN_H_
#define MESSAGEQUEUEXN_H_
#include <native/queue.h>
#include <string>
#include "znm-tools_global.h"
#include "znmException.h"

#define QUEUE_TIMEOUT	10000000000LL	// Default timeout 10 seconds

//==============================================================================
// class MessageQueue
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

class ZNMTOOLSSHARED_EXPORT MessageQueueXn
{
 public:
	MessageQueueXn();

    virtual ~MessageQueueXn();

	void create( const std::string& pName, size_t pPoolsize, size_t pQlimit = Q_UNLIMITED, int pMode = Q_SHARED );

	void deleteQueue();

    bool isCreated() { return mState == znm_tools::CREATED; }

	void bind( const std::string& pName, RTIME pTimeout = QUEUE_TIMEOUT);

	void unbind();

    bool isBinded() { return mState == znm_tools::BINDED; }

	int send( void *pMBuffer, size_t pSize , int pMode = Q_NORMAL );

	void* alloc( size_t size );

	ssize_t receive(void **pBufferP, RTIME pTimeout = QUEUE_TIMEOUT);

	void free ( void *pBuffer );

	int write( const void *pBuffer, size_t pSize , int mode = Q_NORMAL );

	ssize_t read ( void *pBuffer, size_t pSize , RTIME pTimeout = QUEUE_TIMEOUT );

	RT_QUEUE_INFO inquire();

private:

   RT_QUEUE queue;
   znm_tools::State mState;

   std::string mQueueName;
};


#endif // MESSAGEQUEUEXN_H_
