#include "logvariableinterface.h"


LogVariableInterface::LogVariableInterface()
{
	mLogVariable = NULL;
}

void LogVariableInterface::setLogVariable( LogVariable* pLogVariable )
{
	mLogVariable = pLogVariable;
}

LogVariable* LogVariableInterface::logVariable()
{
	return mLogVariable;
}

LogVariableInterface::operator unsigned short()
{
	unsigned short us = mLogVariable->lastHeapElement()[0];
	return us;
}

LogVariableInterface::operator bool()
{
	bool b = mLogVariable->lastHeapElement()[0];
	return b;
}

LogVariableInterface::operator int()
{
	int i = mLogVariable->lastHeapElement()[0];
	return i;
}

LogVariableInterface::operator float()
{
	float f = mLogVariable->lastHeapElement()[0];
	return f;
}

LogVariableInterface::operator const osg::Vec3()
{
	osg::Vec3 vec;
	vec.x() = mLogVariable->lastHeapElement()[0];
	vec.y() = mLogVariable->lastHeapElement()[1];
	vec.z() = mLogVariable->lastHeapElement()[2];
	return vec;
}

LogVariableInterface::operator const osg::Vec3d()
{
	osg::Vec3d vec;
	vec.x() = mLogVariable->lastHeapElement()[0];
	vec.y() = mLogVariable->lastHeapElement()[1];
	vec.z() = mLogVariable->lastHeapElement()[2];
	return vec;
}

LogVariableInterface::operator const osg::Vec4()
{
	osg::Vec4 vec;
	vec.x() = mLogVariable->lastHeapElement()[0];
	vec.y() = mLogVariable->lastHeapElement()[1];
	vec.z() = mLogVariable->lastHeapElement()[2];
	vec.w() = mLogVariable->lastHeapElement()[3];
	return vec;
}

LogVariableInterface::operator const osg::Quat()
{
	osg::Quat quat;
	quat.x() = mLogVariable->lastHeapElement()[0];
	quat.y() = mLogVariable->lastHeapElement()[1];
	quat.z() = mLogVariable->lastHeapElement()[2];
	quat.w() = mLogVariable->lastHeapElement()[3];
	return quat;
}

LogVariableInterface::operator osg::Vec3Array*()
{
	osg::Vec3Array* vecs = new osg::Vec3Array();
    for ( unsigned int i = 0; i < mLogVariable->size() - 2; i = i + 3 )
	{
		vecs->push_back(osg::Vec3d(mLogVariable->lastHeapElement()[i],
			mLogVariable->lastHeapElement()[i+1], 
			mLogVariable->lastHeapElement()[i+2]));
	}

	return vecs;
}

LogVariableInterface::operator osg::Vec4Array*()
{
    osg::Vec4Array* vecs = new osg::Vec4Array();
    for ( unsigned int i = 0; i < mLogVariable->size() - 3; i = i + 4 )
    {
        vecs->push_back(osg::Vec4d(mLogVariable->lastHeapElement()[i],
            mLogVariable->lastHeapElement()[i+1],
            mLogVariable->lastHeapElement()[i+2],
            mLogVariable->lastHeapElement()[i+3]));
    }

    return vecs;
}

LogVariableInterface::operator osg::IndexArray*()
{
	osg::UIntArray* arr = new osg::UIntArray();
    for ( unsigned int i = 0; i < mLogVariable->size(); ++i )
	{
		arr->push_back(mLogVariable->lastHeapElement()[i]);
	}

	return arr;
}

LogVariableInterface::operator const osg::Matrix()
{
	osg::Matrix matrix;
	matrix.set( mLogVariable->lastHeapElement() );
	return matrix;
}

LogVariableInterface::operator GLenum()
{
    return (GLenum)mLogVariable->lastHeapElement()[0];
}

LogVariableInterface::operator osg::AutoTransform::AutoRotateMode()
{
    return (osg::AutoTransform::AutoRotateMode)mLogVariable->lastHeapElement()[0];
}

LogVariableInterface::operator osgSim::DOFTransform::MultOrder()
{
    return (osgSim::DOFTransform::MultOrder)mLogVariable->lastHeapElement()[0];
}

LogVariableInterface::operator osg::Geometry::AttributeBinding()
{
    return (osg::Geometry::AttributeBinding)mLogVariable->lastHeapElement()[0];
}

