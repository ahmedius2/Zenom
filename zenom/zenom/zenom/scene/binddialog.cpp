#include "binddialog.h"
#include "ui_binddialog.h"

#include "visitors/nodevisitor.h"

BindDialog::BindDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BindDialog)
{
    ui->setupUi(this);

    // Set argument dialog
    mSetArgumentDialog = new SetArgumentDialog(this);
    connect(mSetArgumentDialog, SIGNAL(binded(NodeData*, const QVector<LogVariable*>)), SLOT(bindedSlot(NodeData*, const QVector<LogVariable*>)) );
    connect(mSetArgumentDialog, SIGNAL(unbinded(NodeData*)), SLOT(unbindedSlot(NodeData*)) );
}

BindDialog::~BindDialog()
{
    delete ui;
}

void BindDialog::setSceneData(osg::ref_ptr<osg::Node> pModel)
{
    NodeVisitor visitor( ui->nodeTree->invisibleRootItem() );
    pModel->accept(visitor);
    ui->nodeTree->expandAll();
}

void BindDialog::setLogVariableList(const LogVariableList &pLogVariableList)
{
    mSetArgumentDialog->setLogVariableList(pLogVariableList);
}

void BindDialog::saveSettings( QSettings& pSettings )
{
    pSettings.setValue("size", mBindedElements.size());
    int count = 0;
    foreach (NodeData* pFunctor, mBindedElements)
    {
        pSettings.beginGroup( QString("SceneBindedElement") + QString::number(count) );
        QString functorPath = childToRoot(pFunctor);
        pSettings.setValue("functorPath", functorPath);
        for ( int i = 0; i < pFunctor->updateFunctor()->arity(); ++i )
        {
            Argument arg = pFunctor->updateFunctor()->argument(i);
            pSettings.setValue( QString("Arg") + QString::number(i), arg.mVariant.logVariable()->name().c_str() );
        }
        pSettings.endGroup();
        ++count;
    }
}

void BindDialog::loadSettings( QSettings& pSettings )
{
    int size = pSettings.value("size", 0).toInt();
    for ( int i = 0; i < size; ++i )
    {
        pSettings.beginGroup( QString("SceneBindedElement") + QString::number(i) );

        QString functorPath = pSettings.value("functorPath").toString();
        NodeData* functor = dynamic_cast<NodeData*>( rootToChild( functorPath ) );
        if ( functor )
        {
            QVector<LogVariable*> arguments;
            for ( int j = 0; j < functor->updateFunctor()->arity(); ++j )
            {
                QString logVariableName = pSettings.value(QString("Arg") + QString::number(j), "").toString();
                LogVariable* logVariable = DataRepository::instance()->findLogVariable( logVariableName.toStdString() );
                if ( logVariable )
                    arguments.push_back( logVariable );
            }

            bindedSlot(functor, arguments);
        }
        else
        {
            //std::cout << "could not find osg node" << std::endl;
        }

        pSettings.endGroup();
    }
}

void BindDialog::clear()
{
    ui->nodeTree->clear();
    mBindedElements.clear();
}

void BindDialog::on_closeButton_clicked()
{
    hide();
}

void BindDialog::on_nodeTree_itemDoubleClicked( QTreeWidgetItem * pNodeItem, int )
{
    NodeData* nodeData = dynamic_cast<NodeData*>(pNodeItem);
    if ( nodeData )
    {
        mSetArgumentDialog->setNodeData( nodeData );
        mSetArgumentDialog->show();
    }
}

void BindDialog::bindedSlot( NodeData* pNodeData, const QVector<LogVariable *> pArguments )
{
    if( pNodeData->bind( pArguments ) )
    {
        mBindedElements.insert(pNodeData);
    }
}

void BindDialog::unbindedSlot( NodeData* pNodeData )
{
    pNodeData->unbind();
    mBindedElements.remove(pNodeData);
}

QString BindDialog::childToRoot( QTreeWidgetItem* pChildNode )
{
    if ( pChildNode->parent() == NULL )
        return QString::number( ui->nodeTree->indexOfTopLevelItem(pChildNode) );


    int index = pChildNode->parent()->indexOfChild( pChildNode );
    return childToRoot( pChildNode->parent() ) + "/" + QString::number( index );
}

QTreeWidgetItem* BindDialog::rootToChild( const QString& pChildPath )
{
    QStringList path = pChildPath.split("/", QString::SkipEmptyParts);
    QTreeWidgetItem* item = ui->nodeTree->invisibleRootItem();
    for (int i = 0; i < path.size(); ++i)
    {
        int index = path[i].toInt();
        if ( item == NULL || item->childCount() < index )
            return NULL;
        else
            item = item->child( index );
    }

    return item;
}

