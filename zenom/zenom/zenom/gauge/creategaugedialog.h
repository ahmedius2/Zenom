#ifndef CREATEGAUGEDIALOG_H
#define CREATEGAUGEDIALOG_H

#include <QDialog>
#include <QListWidgetItem>
#include <datarepository.h>
#include "gaugewidget.h"

namespace Ui {
class CreateGaugeDialog;
}

class CreateGaugeDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit CreateGaugeDialog(QWidget *parent = 0);
    ~CreateGaugeDialog();

    void setLogVariableList( const LogVariableList& pLogVariableList );

signals:
    void gaugeCreated( GaugeWidget* pGauge );

protected:
    virtual void accept();
    
private:
    Ui::CreateGaugeDialog *ui;

    GaugeWidget* create();
};

#endif // CREATEGAUGEDIALOG_H
