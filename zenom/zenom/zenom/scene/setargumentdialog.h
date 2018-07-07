#ifndef SETARGUMENTDIALOG_H
#define SETARGUMENTDIALOG_H

#include <QDialog>
#include <datarepository.h>
#include "nodedata.h"

namespace Ui {
class SetArgumentDialog;
}

class SetArgumentDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit SetArgumentDialog(QWidget *parent = 0);

    ~SetArgumentDialog();

    void setLogVariableList( const LogVariableList& pLogVariableList );

    void setNodeData( NodeData* pNodeData );

signals:
    void binded(NodeData*, const QVector<LogVariable*> pArguments);
    void unbinded(NodeData*);

protected:
    virtual void accept ();

private slots:
    void on_bindButton_clicked();
    void on_unbindButton_clicked();
    void on_argumentTable_itemSelectionChanged();
    
private:
    Ui::SetArgumentDialog *ui;
    NodeData* mNodeData;

    bool isValid();
    void bindLogVariable(int pArgumentRow, LogVariable* pLogVariable);
    void unbindLogVariable(int pArgumentRow);
    void filterLogVariableBySize( int pSize );
};

#endif // SETARGUMENTDIALOG_H
