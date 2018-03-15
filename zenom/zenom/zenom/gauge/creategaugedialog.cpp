#include "creategaugedialog.h"
#include "ui_creategaugedialog.h"

#include "radialgaugesettingwidget.h"
#include "lineargaugesettingwidget.h"
#include "numericgaugesettingwidget.h"

CreateGaugeDialog::CreateGaugeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateGaugeDialog)
{
    ui->setupUi(this);

    ui->stackedWidget->addWidget(new RadialGaugeSettingWidget);
    ui->stackedWidget->addWidget(new LinearGaugeSettingWidget);
    ui->stackedWidget->addWidget(new NumericGaugeSettingWidget);
    ui->gaugeList->setCurrentRow(0);

    connect( ui->gaugeList, SIGNAL(currentRowChanged(int)), ui->stackedWidget, SLOT(setCurrentIndex(int)) );
}

CreateGaugeDialog::~CreateGaugeDialog()
{
    delete ui;
}

void CreateGaugeDialog::setLogVariableList(const LogVariableList &pLogVariableList)
{
    ui->logVariableList->setLogVariableList( pLogVariableList );
}

void CreateGaugeDialog::accept()
{
    emit gaugeCreated( create() );
    QDialog::accept();
}

GaugeWidget* CreateGaugeDialog::create()
{
    AbstractGauge* gauge;
    if( ui->stackedWidget->currentIndex() == 0 )
    {
        RadialGaugeSettingWidget* gaugeSettingsWidget = qobject_cast<RadialGaugeSettingWidget*>(ui->stackedWidget->currentWidget());
        gauge = gaugeSettingsWidget->createGauge();
    }
    else if( ui->stackedWidget->currentIndex() == 1 )
    {
        LinearGaugeSettingWidget* gaugeSettingsWidget = qobject_cast<LinearGaugeSettingWidget*>(ui->stackedWidget->currentWidget());
        gauge = gaugeSettingsWidget->createGauge();
    }
    else/* if( ui->stackedWidget->currentIndex() == 2 )*/
    {
        NumericGaugeSettingWidget* gaugeSettingsWidget = qobject_cast<NumericGaugeSettingWidget*>(ui->stackedWidget->currentWidget());
        gauge = gaugeSettingsWidget->createGauge();
    }

    GaugeWidget* gaugeWidget = new GaugeWidget( parentWidget() );
    gaugeWidget->setGauge( gauge );
    gaugeWidget->setLogVariable( ui->logVariableList->currentLogVariableItem() );

    return gaugeWidget;
}
