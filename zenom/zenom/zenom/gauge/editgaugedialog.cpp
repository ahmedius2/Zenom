#include "editgaugedialog.h"
#include "ui_editgaugedialog.h"

#include <datarepository.h>
#include "radialgaugesettingwidget.h"
#include "lineargaugesettingwidget.h"
#include "numericgaugesettingwidget.h"

EditGaugeDialog::EditGaugeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditGaugeDialog)
{
    ui->setupUi(this);

    ui->stackedWidget->addWidget(new RadialGaugeSettingWidget);
    ui->stackedWidget->addWidget(new LinearGaugeSettingWidget);
    ui->stackedWidget->addWidget(new NumericGaugeSettingWidget);
}

EditGaugeDialog::~EditGaugeDialog()
{
    delete ui;
}

void EditGaugeDialog::initFrom( GaugeWidget* pGaugeWidget )
{
    mGaugeWidget = pGaugeWidget;

    if( pGaugeWidget->gauge()->type() == RADIAL_GAUGE )
    {
        ui->stackedWidget->setCurrentIndex(0);
        RadialGaugeSettingWidget* gaugeSettingsWidget = qobject_cast<RadialGaugeSettingWidget*>(ui->stackedWidget->currentWidget());
        gaugeSettingsWidget->initFromGauge( pGaugeWidget->gauge() );
    }
    else if( pGaugeWidget->gauge()->type() == LINEAR_GAUGE )
    {
        ui->stackedWidget->setCurrentIndex(1);
        LinearGaugeSettingWidget* gaugeSettingsWidget = qobject_cast<LinearGaugeSettingWidget*>(ui->stackedWidget->currentWidget());
        gaugeSettingsWidget->initFromGauge( pGaugeWidget->gauge() );
    }
    else if( pGaugeWidget->gauge()->type() == NUMERIC_GAUGE )
    {
        ui->stackedWidget->setCurrentIndex(2);
        NumericGaugeSettingWidget* gaugeSettingsWidget = qobject_cast<NumericGaugeSettingWidget*>(ui->stackedWidget->currentWidget());
        gaugeSettingsWidget->initFromGauge( pGaugeWidget->gauge() );
    }

    ui->logVariableList->setLogVariableList( DataRepository::instance()->logVariables() );
    ui->logVariableList->setCurrentLogVariableItem( pGaugeWidget->logVariable() );
}

void EditGaugeDialog::accept()
{
    if( ui->stackedWidget->currentIndex() == 0 )
    {
        RadialGaugeSettingWidget* gaugeSettingsWidget = qobject_cast<RadialGaugeSettingWidget*>(ui->stackedWidget->currentWidget());
        gaugeSettingsWidget->initGauge( mGaugeWidget->gauge() );
    }
    else if( ui->stackedWidget->currentIndex() == 1 )
    {
        LinearGaugeSettingWidget* gaugeSettingsWidget = qobject_cast<LinearGaugeSettingWidget*>(ui->stackedWidget->currentWidget());
        gaugeSettingsWidget->initGauge( mGaugeWidget->gauge() );
    }
    else if( ui->stackedWidget->currentIndex() == 2 )
    {
        NumericGaugeSettingWidget* gaugeSettingsWidget = qobject_cast<NumericGaugeSettingWidget*>(ui->stackedWidget->currentWidget());
        gaugeSettingsWidget->initGauge( mGaugeWidget->gauge() );
    }

    mGaugeWidget->setLogVariable( ui->logVariableList->currentLogVariableItem() );
    QDialog::accept();
}
