#include "nodevisitor.h"
#include "drawablevisitor.h"
#include "transformvisitor.h"

NodeVisitor::NodeVisitor(QTreeWidgetItem* pParentTreeItem)
	: osg::NodeVisitor(osg::NodeVisitor::TRAVERSE_ALL_CHILDREN),
    BaseVisitor(pParentTreeItem, NULL)
{

}

NodeVisitor::~NodeVisitor()
{

}

void NodeVisitor::apply( osg::Node &pNode )
{
	mParentTreeItem = insertItem( &pNode );
    mParentNode = &pNode;

	if ( osg::Geode* geode = dynamic_cast<osg::Geode*>(&pNode) )
	{
		anaylse(*geode);
	}
	else if ( osg::Transform* transform = dynamic_cast<osg::Transform*>(&pNode) )
	{
		anaylse(*transform);
	}
    else if ( osg::ClearNode* node = dynamic_cast<osg::ClearNode*>(&pNode) )
    {
        anaylse(*node);
    }
    else if ( osg::CoordinateSystemNode* node = dynamic_cast<osg::CoordinateSystemNode*>(&pNode) )
    {
        anaylse(*node);
    }
    else if ( osg::LightSource* node = dynamic_cast<osg::LightSource*>(&pNode) )
    {
        anaylse(*node);
    }
    else if ( osg::Projection* node = dynamic_cast<osg::Projection*>(&pNode) )
    {
        anaylse(*node);
    }
    else if ( osg::Switch* node = dynamic_cast<osg::Switch*>(&pNode) )
    {
        anaylse(*node);
    }
	else if ( osg::Group* node = dynamic_cast<osg::Group*>(&pNode) )
	{
		anaylse(*node);
	}	
	else
	{
		anaylse(pNode);
	}
}

void NodeVisitor::anaylse( osg::Node & )
{

}

void NodeVisitor::anaylse( osg::Geode &pNode )
{	
	for( unsigned int i = 0; i < pNode.getNumDrawables(); ++i )
	{
		QTreeWidgetItem* treeItem = insertItem( pNode.getDrawable(i) );
		DrawableVisitor drawableVisitor(treeItem, &pNode);
		drawableVisitor.transverse(	pNode.getDrawable(i) );
	}

	anaylse( static_cast<osg::Node&>(pNode) );
}

void NodeVisitor::anaylse( osg::Group &pNode )
{
    NodeVisitor nodeVisitor( mParentTreeItem );
	pNode.traverse( nodeVisitor );	

	anaylse( static_cast<osg::Node&>(pNode) );
}

void NodeVisitor::anaylse( osg::Transform &pNode )
{
	TransformVisitor transformVisitor(mParentTreeItem, &pNode);
	transformVisitor.transverse( &pNode );

	anaylse( static_cast<osg::Group&>(pNode) );
}

void NodeVisitor::anaylse( osg::ClearNode &pNode )
{
    insertItem(new UnaryUpdateFunctor<void, osg::ClearNode, bool>(&pNode, &osg::ClearNode::setRequiresClear, "setRequiresClear", "requiresClear", "bool"));
    insertItem(new UnaryUpdateFunctor<void, osg::ClearNode, const osg::Vec4&>(&pNode, &osg::ClearNode::setClearColor, "setClearColor", "color", "osg::Vec4"));
    insertItem(new UnaryUpdateFunctor<void, osg::ClearNode, GLbitfield>(&pNode, &osg::ClearNode::setClearMask, "setClearMask", "mask", "GLbitfield"));
    anaylse( static_cast<osg::Group&>(pNode) );
}

void NodeVisitor::anaylse( osg::CoordinateSystemNode &pNode )
{
    osg::EllipsoidModel* ellipsoidModel = pNode.getEllipsoidModel();
    if (ellipsoidModel)
    {
        insertItem(new UnaryUpdateFunctor<void, osg::EllipsoidModel, double>(ellipsoidModel, &osg::EllipsoidModel::setRadiusEquator, "setRadiusEquator", "radius", "double"));
        insertItem(new UnaryUpdateFunctor<void, osg::EllipsoidModel, double>(ellipsoidModel, &osg::EllipsoidModel::setRadiusPolar, "setRadiusPolar", "radius", "double"));
    }

    anaylse( static_cast<osg::Group&>(pNode) );
}

void NodeVisitor::anaylse( osg::LightSource &pNode )
{
    osg::Light* light = pNode.getLight();
    if (light)
    {
        insertItem(new UnaryUpdateFunctor<void, osg::Light, int>(light, &osg::Light::setLightNum, "setLightNum", "num", "int"));
        insertItem(new UnaryUpdateFunctor<void, osg::Light, const osg::Vec4&>(light, &osg::Light::setAmbient, "setAmbient", "ambient", "osg::Vec4"));
        insertItem(new UnaryUpdateFunctor<void, osg::Light, const osg::Vec4&>(light, &osg::Light::setDiffuse, "setDiffuse", "diffuse", "osg::Vec4"));
        insertItem(new UnaryUpdateFunctor<void, osg::Light, const osg::Vec4&>(light, &osg::Light::setSpecular, "setSpecular", "specular", "osg::Vec4"));
        insertItem(new UnaryUpdateFunctor<void, osg::Light, const osg::Vec4&>(light, &osg::Light::setPosition, "setPosition", "position", "osg::Vec4"));
        insertItem(new UnaryUpdateFunctor<void, osg::Light, const osg::Vec3&>(light, &osg::Light::setDirection, "setDirection", "direction", "osg::Vec3"));
        insertItem(new UnaryUpdateFunctor<void, osg::Light, float>(light, &osg::Light::setConstantAttenuation, "setConstantAttenuation", "constant_attenuation", "float"));
        insertItem(new UnaryUpdateFunctor<void, osg::Light, float>(light, &osg::Light::setLinearAttenuation, "setLinearAttenuation", "linear_attenuation", "float"));
        insertItem(new UnaryUpdateFunctor<void, osg::Light, float>(light, &osg::Light::setQuadraticAttenuation, "setQuadraticAttenuation", "quadratic_attenuation", "float"));
        insertItem(new UnaryUpdateFunctor<void, osg::Light, float>(light, &osg::Light::setSpotExponent, "setSpotExponent", "spot_exponent", "float"));
        insertItem(new UnaryUpdateFunctor<void, osg::Light, float>(light, &osg::Light::setSpotCutoff, "setSpotCutoff", "spot_cutoff", "float"));
    }

    anaylse( static_cast<osg::Group&>(pNode) );
}

void NodeVisitor::anaylse( osg::Projection &pNode )
{
    insertItem(new UnaryUpdateFunctor<void, osg::Projection, const osg::Matrix&>(&pNode, &osg::Projection::setMatrix, "setMatrix", "matrix", "osg::Matrix"));
    insertItem(new UnaryUpdateFunctor<void, osg::Projection, const osg::Matrix&>(&pNode, &osg::Projection::preMult, "preMult", "matrix", "osg::Matrix"));
    insertItem(new UnaryUpdateFunctor<void, osg::Projection, const osg::Matrix&>(&pNode, &osg::Projection::postMult, "postMult", "matrix", "osg::Matrix"));

    anaylse( static_cast<osg::Group&>(pNode) );
}


void NodeVisitor::anaylse( osg::Switch &pNode )
{
    insertItem(new BinaryUpdateFunctor<void, osg::Switch, unsigned int, bool>(&pNode, &osg::Switch::setValue, "setValue", "pos", "unsigned int", "value", "bool"));
    insertItem(new UnaryUpdateFunctor<bool, osg::Switch, unsigned int>(&pNode, &osg::Switch::setSingleChildOn, "setSingleChildOn", "pos", "unsigned int"));

    anaylse( static_cast<osg::Group&>(pNode) );
}
