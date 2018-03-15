#include "numericgaugesettingwidget.h"
#include "ui_numericgaugesettingwidget.h"

NumericGaugeSettingWidget::NumericGaugeSettingWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NumericGaugeSettingWidget)
{
    ui->setupUi(this);
    ui->mode->setItemData ( 0, QLCDNumber::Hex );
    ui->mode->setItemData ( 1, QLCDNumber::Dec );
    ui->mode->setItemData ( 2, QLCDNumber::Oct );
    ui->mode->setItemData ( 3, QLCDNumber::Bin );

    initFromGauge( ui->preview );

    // General
    connect( ui->value, SIGNAL(valueChanged(double)), SLOT(updatePreview()) );
    connect( ui->decimals, SIGNAL(valueChanged(int)), SLOT(updatePreview()) );
    connect( ui->mode, SIGNAL(currentIndexChanged(int)), SLOT(updatePreview()) );

    // Color
    connect( ui->textColor, SIGNAL(colorChanged(const QColor&)), SLOT(updatePreview()) );
    connect( ui->backgroundColor, SIGNAL(colorChanged(const QColor&)), SLOT(updatePreview()) );
}

NumericGaugeSettingWidget::~NumericGaugeSettingWidget()
{
    delete ui;
}

AbstractGauge* NumericGaugeSettingWidget::createGauge()
{
    NumericGauge* numericGauge = new NumericGauge();
    initGauge( numericGauge );
    return numericGauge;
}

void NumericGaugeSettingWidget::initGauge(AbstractGauge *pGauge)
{
    NumericGauge* numericGauge = dynamic_cast<NumericGauge*>(pGauge);
    if ( numericGauge )
    {
        // General
        ui->value->setDecimals( ui->decimals->value() );
        numericGauge->setDecimals( ui->decimals->value() );
        int index = ui->mode->currentIndex();
        numericGauge->setMode( (QLCDNumber::Mode)ui->mode->itemData( index ).toInt() );

        // Color
        numericGauge->setTitle( ui->title->text() );
        numericGauge->setDigitsColor( ui->textColor->color() );
        numericGauge->setBackgroundColor( ui->backgroundColor->color() );

        numericGauge->setValue( ui->value->value() );
    }
}

void NumericGaugeSettingWidget::initFromGauge(AbstractGauge *pGauge)
{
    NumericGauge* numericGauge = dynamic_cast<NumericGauge*>(pGauge);
    if ( numericGauge )
    {
        // General
        ui->value->setValue( numericGauge->value() );
        ui->decimals->setValue( numericGauge->decimals() );
        int index = ui->mode->findData( numericGauge->mode() );
        ui->mode->setCurrentIndex( index );

        // Color
        ui->title->setText( numericGauge->title() );
        ui->textColor->setColor( numericGauge->digitsColor() );
        ui->backgroundColor->setColor( numericGauge->backgroundColor() );

        // Preview update
        initGauge( ui->preview );
    }
}

void NumericGaugeSettingWidget::updatePreview()
{
    initGauge( ui->preview );
}
