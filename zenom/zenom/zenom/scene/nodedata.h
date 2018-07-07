#ifndef NODEDATA_H
#define NODEDATA_H

#include <QTreeWidgetItem>
#include <set>
#include <osg/Node>
#include <osg/NodeCallback>

#include "updatefunctor.h"

class NodeCallback : public osg::NodeCallback
{
public:

    virtual void operator()(osg::Node* pNode, osg::NodeVisitor* pNodeVisitor);

    std::set<UpdateFunctor*> mMethods;
};

class NodeData : public QTreeWidgetItem
{
public:
    NodeData( QTreeWidgetItem * pParent = NULL );
    ~NodeData();

    UpdateFunctor* updateFunctor() const;
    void setUpdateFunctor( UpdateFunctor* pUpdateFunctor );

    osg::Node* osgNode() const;
    void setOsgNode( osg::Node* pNode );

    bool bind(const QVector<LogVariable*>& pArguments );
    void unbind();

private:
    UpdateFunctor* mUpdateFunctor;
    osg::Node* mOsgNode;
};

Q_DECLARE_METATYPE(NodeData);

#endif // NODEDATA_H
