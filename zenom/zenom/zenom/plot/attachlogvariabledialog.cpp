#include "attachlogvariabledialog.h"
#include "ui_attachlogvariabledialog.h"

#include <datarepository.h>

AttachLogVariableDialog::AttachLogVariableDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AttachLogVariableDialog)
{
    ui->setupUi(this);

    ui->logVariableList->setLogVariableList( DataRepository::instance()->logVariables() );
}

AttachLogVariableDialog::~AttachLogVariableDialog()
{
    delete ui;
}


QList<LogVariableItem> AttachLogVariableDialog::selectedLogVariableItems() const
{
    return ui->logVariableList->selectedLogVariableItems();
}
