#include "basevisitor.h"

BaseVisitor::BaseVisitor(QTreeWidgetItem* pParentTreeItem, osg::Node* pParentNode)
{
	mParentTreeItem = pParentTreeItem;
	mParentNode	= pParentNode;
}

BaseVisitor::~BaseVisitor()
{

}

void BaseVisitor::analyseStateSet( osg::StateSet* pStateSet, osg::Node & )
{
	// TODO bu kisim tasinabilir.
	if ( pStateSet )
	{
		QTreeWidgetItem* nodeTreeItem = new QTreeWidgetItem( mParentTreeItem );
		nodeTreeItem->setText( 0, pStateSet->className() );

		// TODO
		/*
		ZStateSetVisitor stateSetVisitor( mTree, stateSetTreeItem, &pNode );
		osg::StateSet::AttributeList attList = pStateSet->getAttributeList();
		osg::StateSet::AttributeList::iterator iter;
		for ( iter = attList.begin(); iter != attList.end(); ++iter )
		{
			stateSetVisitor.transverse( iter->second.first );
		}
		*/
	}
}

QTreeWidgetItem* BaseVisitor::insertItem( osg::Object* pObject )
{
	QTreeWidgetItem* treeItem = new QTreeWidgetItem( mParentTreeItem );
	treeItem->setText( 0, pObject->className() );
	//treeItem->setFlags(Qt::NoItemFlags);

	return treeItem;
}

QTreeWidgetItem* BaseVisitor::insertItem( UpdateFunctor* pUpdateFunctor )
{
	NodeData* treeItem = new NodeData( mParentTreeItem );
	treeItem->setText( 0, pUpdateFunctor->name() );
	treeItem->setUpdateFunctor( pUpdateFunctor );
	treeItem->setOsgNode( mParentNode );
    //treeItem->setToolTip( 0, pUpdateFunctor->description() );
	//treeItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsUserCheckable);

	//treeItem->setData( 0, Qt::UserRole, QVariant::fromValue(nodeData) );

	return treeItem;
}
