#include "setargumentdialog.h"
#include "ui_setargumentdialog.h"

#include <QMessageBox>

SetArgumentDialog::SetArgumentDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetArgumentDialog)
{
    ui->setupUi(this);
}

SetArgumentDialog::~SetArgumentDialog()
{
    delete ui;
}

void SetArgumentDialog::setLogVariableList(const LogVariableList &pLogVariableList)
{
    ui->logVariableList->clear();
    for (unsigned int i = 0; i < pLogVariableList.size(); ++i)
    {
        QListWidgetItem* logVarItem = new QListWidgetItem();
        logVarItem->setText( QString::fromStdString(pLogVariableList[i]->name()) );
        logVarItem->setData(Qt::UserRole, QVariant::fromValue((void*)pLogVariableList[i]) );
        ui->logVariableList->addItem( logVarItem );
    }
}

void SetArgumentDialog::setNodeData( NodeData* pNodeData )
{
    mNodeData = pNodeData;

    // Fill arguments of the function
    UpdateFunctor* updateFunctor = pNodeData->updateFunctor();
    ui->argumentTable->setRowCount( updateFunctor->arity() );
    for (int i = 0; i < updateFunctor->arity(); ++i)
    {
        Argument arg = updateFunctor->argument(i);

        ui->argumentTable->setItem(i, 0, new QTableWidgetItem( arg.mType ));
        ui->argumentTable->setItem(i, 1, new QTableWidgetItem( arg.mName ));
        ui->argumentTable->setItem(i, 2, new QTableWidgetItem());

        bindLogVariable(i, arg.mVariant.logVariable());

        if ( i == 0 )
        {
            ui->argumentTable->setCurrentCell(0, 0);
            filterLogVariableBySize( arg.size() );
        }
    }
}

void SetArgumentDialog::accept()
{
    if ( isValid() )
    {
        QTableWidgetItem* argumentlogVariableItem = ui->argumentTable->item( 0, 2 );
        if ( argumentlogVariableItem->text().isEmpty() )
        {
            emit unbinded( mNodeData );
        }
        else
        {
            // All arguments are assigned.
            QVector<LogVariable*> arguments;
            for (int i = 0; i < ui->argumentTable->rowCount(); ++i)
            {
                LogVariable* logVariable = (LogVariable*)(ui->argumentTable->item( i, 2 )->data( Qt::UserRole ).value<void*>());
                arguments.push_back(logVariable);
            }
            emit binded( mNodeData, arguments );
        }

        QDialog::accept();
    }
    else
    {
        QMessageBox::critical(this, "Error",
            QString("the function takes %1 or 0 argument(s).").arg(ui->argumentTable->rowCount()) );
    }
}

bool SetArgumentDialog::isValid()
{
    // Ya hicbirine atanmayacak ya da hepsine atanacak
    bool none = true;
    bool all = true;
    QTableWidgetItem* argumentlogVariableItem;
    for (int i = 0; i < ui->argumentTable->rowCount(); ++i)
    {
        argumentlogVariableItem = ui->argumentTable->item( i, 2 );
        none = none && argumentlogVariableItem->text().isEmpty();
        all = all && !argumentlogVariableItem->text().isEmpty();
    }

    return all || none;
}

void SetArgumentDialog::on_bindButton_clicked()
{
    QListWidgetItem* logVariableItem = ui->logVariableList->currentItem();
    if ( logVariableItem && !logVariableItem->flags().testFlag(Qt::NoItemFlags) )
    {
        LogVariable* logVariable = (LogVariable*)(logVariableItem->data( Qt::UserRole ).value<void*>());
        bindLogVariable( ui->argumentTable->currentRow(), logVariable );
    }
}

void SetArgumentDialog::bindLogVariable( int pArgumentRow, LogVariable* pLogVariable )
{
    QTableWidgetItem* argumentlogVariableItem = ui->argumentTable->item( pArgumentRow, 2 );
    if ( argumentlogVariableItem && pLogVariable )
    {
        argumentlogVariableItem->setText( QString::fromStdString(pLogVariable->name()) );
        argumentlogVariableItem->setData(Qt::UserRole, QVariant::fromValue((void*)pLogVariable) );
    }
}

void SetArgumentDialog::on_unbindButton_clicked()
{
    unbindLogVariable( ui->argumentTable->currentRow() );
}

void SetArgumentDialog::unbindLogVariable( int pArgumentRow )
{
    QTableWidgetItem* argumentlogVariableItem = ui->argumentTable->item( pArgumentRow, 2 );
    if ( argumentlogVariableItem )
    {
        argumentlogVariableItem->setText( "" );
        argumentlogVariableItem->setData(Qt::UserRole, QVariant() );
    }
}

void SetArgumentDialog::on_argumentTable_itemSelectionChanged()
{
    UpdateFunctor* updateFunctor = mNodeData->updateFunctor();
    int row = ui->argumentTable->currentRow();
    if ( row >= 0 )
    {
        Argument arg = updateFunctor->argument(row);
        filterLogVariableBySize( arg.size() );
    }
}

void SetArgumentDialog::filterLogVariableBySize( int pSize )
{
    for ( int i = 0; i < ui->logVariableList->count(); ++i )
    {
        LogVariable* logVariable = (LogVariable*)(ui->logVariableList->item(i)->data( Qt::UserRole ).value<void*>());

        if ( logVariable && (int)logVariable->size() >= pSize && pSize > 0 )
        {
            ui->logVariableList->item(i)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsUserCheckable);
        }
        else
        {
            ui->logVariableList->item(i)->setFlags(Qt::NoItemFlags);
        }
    }
}
