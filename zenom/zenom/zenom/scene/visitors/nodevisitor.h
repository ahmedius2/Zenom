#ifndef NODEVISITOR_H
#define NODEVISITOR_H

#include <osg/NodeVisitor>
#include <osg/Geode>
#include <osg/Transform>

#include <osg/ClearNode>
#include <osg/CoordinateSystemNode>
#include <osg/LightSource>
#include <osg/Projection>
#include <osg/Switch>

#include "basevisitor.h"

class NodeVisitor : public osg::NodeVisitor, public BaseVisitor
{
public:
    NodeVisitor(QTreeWidgetItem* pParent);

	~NodeVisitor();

	virtual void apply(osg::Node &pNode);

private:
    void anaylse(osg::Node &);
	void anaylse(osg::Geode &pNode);
	void anaylse(osg::Group &pNode);
	void anaylse(osg::Transform &pNode);

    void anaylse(osg::ClearNode& pNode);
    void anaylse(osg::CoordinateSystemNode& pNode);
    void anaylse(osg::LightSource& pNode);
    void anaylse(osg::Projection& pNode);
    void anaylse(osg::Switch& pNode);
};

#endif // NODEVISITOR_H
