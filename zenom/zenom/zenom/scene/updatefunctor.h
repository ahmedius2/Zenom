#ifndef UPDATEFUNCTOR_H
#define UPDATEFUNCTOR_H

#include "logvariableinterface.h"
#include <vector>
#include <QString>
#include <functional>

struct Argument 
{
	Argument(const QString& pName, const QString& pType);

    // minimum required size of log variable
    unsigned int size();

	QString mName;
	QString mType;
	LogVariableInterface mVariant;
};

/*
* Base function object class
*
*
*/
class UpdateFunctor
{
public:
    UpdateFunctor( const QString& pName );

    virtual ~UpdateFunctor();

	int arity() const;

	virtual void update() = 0;

	void setArgument(int pIndex, LogVariable* pLogVariable);

	Argument argument( int pIndex ) const;

	QString name() const;
	
	QString description() const;

    bool isValid();

protected:
	std::vector<Argument> mArguments;
	QString mName;
};


/*
* Unary function object class
*
*
*/
template<class R, class Object,
         typename Arg,
         typename Cast_Type = Arg>
class UnaryUpdateFunctor : public UpdateFunctor
{
    typedef R (Object::*Function)(Arg);
public:
	UnaryUpdateFunctor( Object* pObject, Function pFunction, 
        const QString& pName,
        const QString& pArgName, const QString& pArgType )
        : UpdateFunctor( pName ), mObject( pObject ), mFunction( pFunction )
	{
        mArguments.push_back( Argument( pArgName, pArgType ) );
	}

	virtual void update()
	{        
        (mObject->*mFunction)( static_cast<Cast_Type>(mArguments[0].mVariant) );
	}

private:
	Object* mObject;
	Function mFunction;
};

/*
* Binary function object class
*
*
*/
template<class R, class Object,
         typename Arg1, typename Arg2,
         typename Cast_Type1 = Arg1, typename Cast_Type2 = Arg2>
class BinaryUpdateFunctor : public UpdateFunctor
{
    typedef R (Object::*Function)(Arg1, Arg2);
public:
	BinaryUpdateFunctor( Object* pObject, Function pFunction, 
        const QString& pName,
        const QString& pArg1Name, const QString& pArg1Type,
        const QString& pArg2Name, const QString& pArg2Type )
        : UpdateFunctor( pName ), mObject( pObject ), mFunction( pFunction )
	{
        mArguments.push_back( Argument( pArg1Name, pArg1Type ) );
        mArguments.push_back( Argument( pArg2Name, pArg2Type ) );
	}

	virtual void update()
	{
        (mObject->*mFunction)( static_cast<Cast_Type1>(mArguments[0].mVariant), static_cast<Cast_Type2>(mArguments[1].mVariant) );
	}

private:
	Object* mObject;
	Function mFunction;
};

/*
* Ternary function object class
*
*
*/
template<class R, class Object,
         typename Arg1, typename Arg2, typename Arg3,
         typename Cast_Type1 = Arg1, typename Cast_Type2 = Arg2, typename Cast_Type3 = Arg3>
class TernaryUpdateFunctor : public UpdateFunctor
{
    typedef R (Object::*Function)(Arg1, Arg2, Arg3);
public:
	TernaryUpdateFunctor( Object* pObject, Function pFunction,
        const QString& pName,
        const QString& pArg1Name, const QString& pArg1Type,
        const QString& pArg2Name, const QString& pArg2Type,
        const QString& pArg3Name, const QString& pArg3Type )
        : UpdateFunctor( pName ), mObject( pObject ), mFunction( pFunction )
	{
        mArguments.push_back( Argument( pArg1Name, pArg1Type ) );
        mArguments.push_back( Argument( pArg2Name, pArg2Type ) );
        mArguments.push_back( Argument( pArg3Name, pArg3Type ) );
	}

	virtual void update()
	{
        (mObject->*mFunction)( static_cast<Cast_Type1>(mArguments[0].mVariant),
            static_cast<Cast_Type2>(mArguments[1].mVariant),
            static_cast<Cast_Type3>(mArguments[2].mVariant) );
	}

private:
	Object* mObject;
	Function mFunction;
};
#endif // UPDATEFUNCTOR_H
