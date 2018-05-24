#ifndef LOGVARIABLEINTERFACE_H
#define LOGVARIABLEINTERFACE_H

#include <osg/Vec3>
#include <osg/Vec4>
#include <osg/Quat>
#include <osg/Matrix>
#include <osg/Array>

#include <osg/AutoTransform>
#include <osgSim/DOFTransform>

#include <osg/Geometry>

#include <logvariable.h>

class LogVariableInterface
{
	
public:
	LogVariableInterface();

	void setLogVariable( LogVariable* pLogVariable );

	LogVariable* logVariable();
	
	operator unsigned short();

	operator bool();

	operator int();

	operator float();

	operator const osg::Vec3 ();

	operator const osg::Vec3d ();

	operator const osg::Vec4 ();

	operator const osg::Quat ();

	operator osg::Vec3Array* ();

    operator osg::Vec4Array* ();

	operator osg::IndexArray*();

	operator const osg::Matrix ();

    operator GLenum();

    operator osg::AutoTransform::AutoRotateMode();

    operator osgSim::DOFTransform::MultOrder();

    operator osg::Geometry::AttributeBinding();

private:
	LogVariable* mLogVariable;
};

#endif	// LOGVARIABLEINTERFACE_H

