//==============================================================================
// MessageQueueXn.hpp - Native MessageQueue services
//
// Author        :
// Version       : 2.0.01 (Temmuz 2009)
// Compatibility : POSIX, GCC
//==============================================================================


#include "MessageQueueXn.h"

//==============================================================================
// MessageQueueXn::MessageQueueXn
//==============================================================================
MessageQueueXn::MessageQueueXn()
{
    mState = znm_tools::NONE;
}

//==============================================================================
// MessageQueueXn::~MessageQueueXn
//==============================================================================
MessageQueueXn::~MessageQueueXn()
{

}

//==============================================================================
// MessageQueueXn::create
//==============================================================================
void MessageQueueXn::create( const std::string& pName, size_t pPoolsize, size_t pQlimit, int pMode )
{
	mQueueName = pName;
	int err;

	if( (err = rt_queue_create( &queue, pName.c_str(), pPoolsize, pQlimit, pMode )) )
	{
		throw ZnmException( mQueueName, "rt_queue_create", -err );
	}
    mState = znm_tools::CREATED;
}

//==============================================================================
// MessageQueueXn::deleteQueue
//==============================================================================
void MessageQueueXn::deleteQueue( )
{
    if ( isBinded() || isCreated() )
    {
        mState = znm_tools::NONE;

        int err;
        // Queue silinir.
        if( (err = rt_queue_delete(&queue)) )
        {
            throw ZnmException( mQueueName, "rt_queue_delete", -err );
        }
    }
}

//==============================================================================
// MessageQueueXn::bind
//==============================================================================
void MessageQueueXn::bind( const std::string& pName, RTIME pTimeout )
{
	mQueueName = pName;
	int err;

	// MessageQueue yaratilir
	if( (err = rt_queue_bind( &queue, mQueueName.c_str(), pTimeout )) )
	{
		throw ZnmException( mQueueName, "rt_queue_bind", -err );
	}
    mState = znm_tools::BINDED;
}

//==============================================================================
// MessageQueueXp::unbind
//==============================================================================
void MessageQueueXn::unbind()
{
    if ( isBinded() || isCreated() )
    {
        mState = znm_tools::NONE;

        int err;	//Hata denetim
        // MessageQueue silinir.
        if( (err = rt_queue_unbind(&queue)) )
        {
            throw ZnmException( mQueueName, "rt_queue_unbind", -err );
        }
    }
}

//==============================================================================
// MessageQueueXp::send
//==============================================================================
int MessageQueueXn::send( void *pMBuffer, size_t pSize , int pMode )
{
	int err;

	if( (err = rt_queue_send(&queue, pMBuffer, pSize, pMode )) < 0 )
	{
		throw ZnmException( mQueueName + " " + strerror(-err) );
	}

	return err;
}

//==============================================================================
// MessageQueueXn::alloc
//==============================================================================
void* MessageQueueXn::alloc( size_t pSize)
{
	void *ptr;
	if( !(ptr = rt_queue_alloc( &queue, pSize )) )
	{
		throw ZnmException( mQueueName + " alloc" );
	}

	return ptr;
}

//==============================================================================
// MessageQueueXp::receive
//==============================================================================
ssize_t MessageQueueXn::receive( void **pBufferP, RTIME pTimeout )
{
	int err = rt_queue_receive( &queue, pBufferP, pTimeout );

	if( err < 0 && err != -ETIMEDOUT && err != -EWOULDBLOCK )
	{
		throw ZnmException( mQueueName + " " + strerror(-err) );
	}

	return err;
}

//==============================================================================
// MessageQueueXn::free
//==============================================================================
void MessageQueueXn::free( void *pBuffer )
{
	int err;	//Hata denetim

 	if( (err = rt_queue_free( &queue, pBuffer )) )
	{
 		throw ZnmException( mQueueName + " " + strerror(-err) );
	}
}

//==============================================================================
// MessageQueueXp::write
//==============================================================================
int MessageQueueXn::write( const void *pBuffer,size_t pSize, int pMode )
{
	int err;

	if( (err = rt_queue_write( &queue, pBuffer, pSize, pMode )) < 0 )
	{
		throw ZnmException( mQueueName + " " + strerror(-err) );
	}

	return err;
}

//==============================================================================
// MessageQueueXp::read
//==============================================================================
ssize_t MessageQueueXn::read( void *pBuffer, size_t pSize, RTIME pTimeout )
{
    return rt_queue_read(&queue, pBuffer, pSize, pTimeout );
}

//==============================================================================
// MessageQueueXp::inquire
//==============================================================================
RT_QUEUE_INFO MessageQueueXn::inquire()
{
	RT_QUEUE_INFO info;
	int err;	//Hata denetim

	if( (err = rt_queue_inquire( &queue, &info )) )
	{
		throw ZnmException( mQueueName + " " + strerror(-err) );
	}

	return info;
}
