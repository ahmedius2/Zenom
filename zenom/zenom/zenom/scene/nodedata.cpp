#include "nodedata.h"


void NodeCallback::operator()( osg::Node* pNode, osg::NodeVisitor* pNodeVisitor )
{
    std::set<UpdateFunctor*>::iterator iter;
    for ( iter = mMethods.begin(); iter != mMethods.end(); ++iter )
    {
        if ( (*iter)->isValid() )
            (*iter)->update();
    }

    traverse(pNode, pNodeVisitor);
}

NodeData::NodeData( QTreeWidgetItem * pParent )
    : QTreeWidgetItem(pParent)
{
    mUpdateFunctor = NULL;
}

NodeData::~NodeData()
{
    delete mUpdateFunctor;
}

UpdateFunctor* NodeData::updateFunctor() const
{
    return mUpdateFunctor;
}

void NodeData::setUpdateFunctor( UpdateFunctor* pUpdateFunctor )
{
    mUpdateFunctor = pUpdateFunctor;
}

osg::Node* NodeData::osgNode() const
{
    return mOsgNode;
}

void NodeData::setOsgNode( osg::Node* pNode )
{
    mOsgNode = pNode;
}

void NodeData::unbind()
{
    // Dugumden callback fonksiyonu alinir.
    NodeCallback* callback = dynamic_cast<NodeCallback*>(mOsgNode->getUpdateCallback());
    if ( callback )
    {
        // modifier fonksiyon silinir.
        callback->mMethods.erase( mUpdateFunctor );

        // Hic modifier fonksiyon kalmadi ise dugumden callback silinir.
        if ( callback->mMethods.empty() )
        {
            mOsgNode->removeUpdateCallback( callback );
        }
    }

    setText( 0, mUpdateFunctor->name() );
    setData(0, Qt::BackgroundColorRole, QColor(255, 255, 255));

    for ( int i = 0; i < mUpdateFunctor->arity(); ++i )
        mUpdateFunctor->setArgument(i, NULL);
}

bool NodeData::bind(const QVector<LogVariable*> &pArguments)
{
    // daha once atanmis varsa silinir.
    unbind();

    if ( pArguments.size() != mUpdateFunctor->arity() )
    {
        std::cout << "pArguments.size() != mUpdateFunctor->arity()" << std::endl;
        return false;
    }

    // shows binded log variable(s).
    QString signature = mUpdateFunctor->name() + " ( ";
    for ( int i = 0; i < pArguments.size(); ++i )
    {
        LogVariable* logVariable = pArguments[i];
        Argument arg = mUpdateFunctor->argument(i);

        if( arg.size() > logVariable->size() )
        {
            std::cout << "arg.size() > logVariable->size()" << std::endl;
            return false;
        }

        mUpdateFunctor->setArgument(i, logVariable);

        signature += QString::fromStdString( logVariable->name() );
        if ( i == mUpdateFunctor->arity() - 1  )
            signature += " ) ";
        else
            signature += ", ";
    }
    setText(0, signature);
    setData(0, Qt::BackgroundColorRole, QColor(190, 200, 216));

    // Dugumden callback fonksiyonu alinir.
    NodeCallback* callback = dynamic_cast<NodeCallback*>(mOsgNode->getUpdateCallback());
    if ( !callback )
    {
        // Dugumde callback fonksiyonu yok ise eklenir.
        callback = new NodeCallback;
        mOsgNode->setUpdateCallback(callback);
    }
    callback->mMethods.insert( mUpdateFunctor );

    return true;
}




