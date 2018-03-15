#ifndef ZSHAPEVISITOR_H
#define ZSHAPEVISITOR_H

#include <osg/Shape>
#include "basevisitor.h"

class ShapeVisitor : public osg::ShapeVisitor, public BaseVisitor
{
public:
	ShapeVisitor(QTreeWidgetItem* pParentTreeItem, osg::Node* pParentNode);
	void apply(osg::Shape& pShape);

private:
    void anaylse(osg::Shape &);
	void anaylse(osg::Box &pShape);
	void anaylse(osg::Capsule &pShape);
	void anaylse(osg::CompositeShape &pShape);
	void anaylse(osg::Cone &pShape);
	void anaylse(osg::Cylinder &pShape);
	void anaylse(osg::HeightField &pShape);	
	void anaylse(osg::InfinitePlane &pShape);
	void anaylse(osg::Sphere &pShape);	
	void anaylse(osg::TriangleMesh &pShape);
	void anaylse(osg::ConvexHull &pShape);	
};

#endif
