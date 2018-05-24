#ifndef BASEVISITOR_H
#define BASEVISITOR_H

#include <QTreeWidgetItem>
#include <QVariant>
#include <osg/Node>

#include "../nodedata.h"


class BaseVisitor
{
public:
	BaseVisitor(QTreeWidgetItem* pParentTreeItem, osg::Node* pParentNode);
	~BaseVisitor();

protected:

	QTreeWidgetItem* insertItem( osg::Object* pObject );

	QTreeWidgetItem* insertItem( UpdateFunctor* pUpdateFunctor );

    void analyseStateSet( osg::StateSet* pStateSet, osg::Node & );

	QTreeWidgetItem* mParentTreeItem;
	osg::Node* mParentNode;
};

#endif // BASEVISITOR_H
