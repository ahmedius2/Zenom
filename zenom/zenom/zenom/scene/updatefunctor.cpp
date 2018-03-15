#include "updatefunctor.h"
#include <cxxabi.h>

Argument::Argument(const QString& pName, const QString& pType)
    : mName(pName), mType(pType)
{
    /*
    int     status;
    char   *realname;
    realname = abi::__cxa_demangle(pType.toStdString().c_str(), 0, 0, &status);
    mType = QString(realname);
    free(realname);
    */
}

unsigned int Argument::size()
{
    unsigned int ret = 0;
    if ( mType == "int" || mType == "float" || mType == "double" )
    {
        ret = 1;
    }
    else if ( mType == "osg::Vec2" || mType == "osg::Vec2b" || mType == "osg::Vec2d" ||
        mType == "osg::Vec2f" || mType == "osg::Vec2s" )
    {
        ret = 2;
    }
    else if ( mType == "osg::Vec3" || mType == "osg::Vec3b" || mType == "osg::Vec3d" ||
              mType == "osg::Vec3f" || mType == "osg::Vec3s" || mType == "osg::Vec3Array" )
    {
        ret = 3;
    }
    else if ( mType == "osg::Vec4" || mType == "osg::Vec4b" || mType == "osg::Vec4d" ||
              mType == "osg::Vec4f" || mType == "osg::Vec4s" || mType == "osg::Quat" ||
              mType == "osg::Vec4Array" )
    {
        ret = 4;
    }
    else if ( mType == "osg::Matrix" || mType == "osg::Matrixd" || mType == "osg::Matrixf" )
    {
        ret = 16;
    }

    return ret;
}

UpdateFunctor::UpdateFunctor( const QString& pName )
    : mName( pName )
{

}

UpdateFunctor::~UpdateFunctor()
{

}

int UpdateFunctor::arity() const
{
	return mArguments.size();
}

void UpdateFunctor::setArgument( int pIndex, LogVariable* pLogVariable )
{
	mArguments[pIndex].mVariant.setLogVariable( pLogVariable );
}

Argument UpdateFunctor::argument( int pIndex ) const
{
	return mArguments[pIndex];
}

QString UpdateFunctor::name() const
{
	return mName;
}

bool UpdateFunctor::isValid()
{
    bool valid = true;
    for ( unsigned int i = 0; i < mArguments.size(); ++i )
    {
        valid = valid && mArguments[i].mVariant.logVariable()->isHeapValid();
    }

    return valid;
}
