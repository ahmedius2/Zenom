#ifndef TRANSFORMVISITOR_H
#define TRANSFORMVISITOR_H

#include <osg/AutoTransform>
#include <osg/MatrixTransform>
#include <osg/PositionAttitudeTransform>
#include <osgAnimation/Bone>
#include <osgSim/DOFTransform>

#include "basevisitor.h"

/********************** TRANSFORM VISITOR **********************/

class TransformVisitor : public BaseVisitor
{
public:
	TransformVisitor(QTreeWidgetItem* pParentTreeItem, osg::Node* pParentNode);
	void transverse(osg::Transform* pTransform);

    void anaylse(osg::Transform &);
	void anaylse(osg::AutoTransform &pTransform);
	void anaylse(osg::MatrixTransform &pTransform);
	void anaylse(osg::PositionAttitudeTransform &pTransform);
    void analyse(osgAnimation::Bone &pTransform);
    void analyse(osgSim::DOFTransform &pTransform);
};

#endif

