#ifndef DRAWABLEVISITOR_H
#define DRAWABLEVISITOR_H

#include <osg/Geometry>
#include <osg/ShapeDrawable>
#include <osg/Shape>

#include "basevisitor.h"

class DrawableVisitor : public BaseVisitor
{
public:
	DrawableVisitor(QTreeWidgetItem* pParentTreeItem, osg::Node* pParentNode);

	~DrawableVisitor();

	void transverse(osg::Drawable* pDrawable);

private:
	void anaylse( osg::Drawable &pDrawable );
	void anaylse( osg::ShapeDrawable &pDrawable );
	void anaylse( osg::Geometry &pDrawable );
};

#endif // DRAWABLEVISITOR_H
