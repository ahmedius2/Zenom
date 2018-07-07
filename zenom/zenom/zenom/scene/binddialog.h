#ifndef BINDDIALOG_H
#define BINDDIALOG_H

#include <QDialog>
#include <QSettings>
#include <osg/Node>
#include "setargumentdialog.h"

namespace Ui {
class BindDialog;
}

class BindDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit BindDialog(QWidget *parent = 0);

    ~BindDialog();

    void setSceneData(osg::ref_ptr<osg::Node> pModel);

    void setLogVariableList( const LogVariableList& pLogVariableList );

    void saveSettings( QSettings& pSettings );

    void loadSettings( QSettings& pSettings );

    void clear();

private slots:
    void on_closeButton_clicked();
    void on_nodeTree_itemDoubleClicked( QTreeWidgetItem * pNodeItem, int );
    void bindedSlot( NodeData* pNodeData, const QVector<LogVariable*> pArguments );
    void unbindedSlot( NodeData* pNodeData );
    
private:
    Ui::BindDialog *ui;
    SetArgumentDialog* mSetArgumentDialog;
    QSet<NodeData*> mBindedElements;

    QString childToRoot( QTreeWidgetItem *pChildNode );
    QTreeWidgetItem* rootToChild( const QString& pChildPath );
};

#endif // BINDDIALOG_H
