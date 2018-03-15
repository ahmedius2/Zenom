#include "radialgaugesettingwidget.h"
#include "ui_radialgaugesettingwidget.h"

RadialGaugeSettingWidget::RadialGaugeSettingWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RadialGaugeSettingWidget)
{
    ui->setupUi(this);

    // Direction Enums
    ui->direction->setItemData ( 0, QwtDial::Clockwise );
    ui->direction->setItemData ( 1, QwtDial::CounterClockwise );

    // Needle Type Enums
    ui->needleType->setItemData ( 0, RadialGauge::SIMPLE_NEEDLE );
    ui->needleType->setItemData ( 1, RadialGauge::MAGNET_NEEDLE );
    ui->needleType->setItemData ( 2, RadialGauge::WIND_ARROW_NEEDLE );

    // Needle Style Enums
    ui->needleStyle->setItemData ( 0, RadialGauge::NEEDLE_STYLE_1 );
    ui->needleStyle->setItemData ( 1, RadialGauge::NEEDLE_STYLE_2 );

    // Font Size
    QFontDatabase db;
    foreach(int size, db.standardSizes())
        ui->fontSize->addItem(QString::number(size));

    initFromGauge( ui->preview );

    // Scale
    connect( ui->direction, SIGNAL(currentIndexChanged(int)), SLOT(updatePreview()) );
    connect( ui->rangeMin, SIGNAL(valueChanged(double)), SLOT(updatePreview()) );
    connect( ui->rangeMax, SIGNAL(valueChanged(double)), SLOT(updatePreview()) );
    connect( ui->startAngle, SIGNAL(valueChanged(double)), SLOT(updatePreview()) );
    connect( ui->sweepAngle, SIGNAL(valueChanged(double)), SLOT(updatePreview()) );

    // Ticks
    connect( ui->majorTick, SIGNAL(valueChanged(int)), SLOT(updatePreview()) );
    connect( ui->minorTick, SIGNAL(valueChanged(int)), SLOT(updatePreview()) );
    connect( ui->labelGroupBox, SIGNAL(toggled(bool)), SLOT(updatePreview()) );
    connect( ui->font, SIGNAL(currentFontChanged(const QFont&)), SLOT(updatePreview()) );
    connect( ui->fontSize, SIGNAL(editTextChanged(const QString&)), SLOT(updatePreview()) );

    // Needle
    connect( ui->value, SIGNAL(valueChanged(int)), SLOT(updatePreview()) );
    connect( ui->needleType, SIGNAL(currentIndexChanged(int)), SLOT(updatePreview()) );
    connect( ui->needleStyle, SIGNAL(currentIndexChanged(int)), SLOT(updatePreview()) );
    connect( ui->needleColor1, SIGNAL(colorChanged(const QColor&)), SLOT(updatePreview()) );
    connect( ui->needleColor2, SIGNAL(colorChanged(const QColor&)), SLOT(updatePreview()) );

    // Color
    connect( ui->textColor, SIGNAL(colorChanged(const QColor&)), SLOT(updatePreview()) );
    connect( ui->backgroundColor, SIGNAL(colorChanged(const QColor&)), SLOT(updatePreview()) );
}

RadialGaugeSettingWidget::~RadialGaugeSettingWidget()
{
    delete ui;
}

AbstractGauge* RadialGaugeSettingWidget::createGauge()
{
    RadialGauge* radialGauge = new RadialGauge();
    initGauge( radialGauge );
    return radialGauge;
}

void RadialGaugeSettingWidget::initGauge( AbstractGauge* pGauge )
{
    RadialGauge* radialGauge = dynamic_cast<RadialGauge*>(pGauge);
    if ( radialGauge )
    {
        int index;

        // Scale
        index = ui->direction->currentIndex();
        radialGauge->setDirection( (QwtDial::Direction)ui->direction->itemData( index ).toInt() );
        radialGauge->setRange( ui->rangeMin->value(), ui->rangeMax->value() );
        radialGauge->setOrigin( ui->startAngle->value() );
        radialGauge->setScaleArc( 0, ui->sweepAngle->value() );

        // Ticks
        radialGauge->setScale( ui->majorTick->value(), ui->minorTick->value() );
        radialGauge->scaleDraw()->enableComponent( QwtAbstractScaleDraw::Labels, ui->labelGroupBox->isChecked() );
        QFont font = ui->font->currentFont();
        int fontSize = ui->fontSize->currentText().toInt();
        font.setPointSize( fontSize < 1 ? 1 : fontSize );
        radialGauge->setFont( font );

        // Needle
        radialGauge->setValue( ui->value->value() );
        index = ui->needleType->currentIndex();
        RadialGauge::NeedleType needleType = (RadialGauge::NeedleType)ui->needleType->itemData( index ).toInt();
        index = ui->needleStyle->currentIndex();
        RadialGauge::NeedleStyle needleStyle = (RadialGauge::NeedleStyle)ui->needleStyle->itemData( index ).toInt();
        QColor c1 = ui->needleColor1->color();
        QColor c2 = ui->needleColor2->color();
        radialGauge->setNeedle( needleType, needleStyle, c1, c2 );

        // Color
        radialGauge->setTitle( ui->title->text() );
        radialGauge->setTextColor( ui->textColor->color() );
        radialGauge->setBackgroundColor( ui->backgroundColor->color() );
    }
}

void RadialGaugeSettingWidget::initFromGauge( AbstractGauge* pGauge )
{
    RadialGauge* radialGauge = dynamic_cast<RadialGauge*>(pGauge);
    if ( radialGauge )
    {
        int index;

        // Scale
        index = ui->direction->findData( radialGauge->direction() );
        ui->direction->setCurrentIndex( index );
        ui->rangeMin->setValue( radialGauge->minValue() );
        ui->rangeMax->setValue( radialGauge->maxValue() );
        ui->startAngle->setValue( radialGauge->origin() );
        ui->sweepAngle->setValue( radialGauge->maxScaleArc() );

        // Ticks
        ui->majorTick->setValue( radialGauge->scaleMaxMajor() );
        ui->minorTick->setValue( radialGauge->scaleMaxMinor() );
        ui->labelGroupBox->setChecked( radialGauge->scaleDraw()->hasComponent( QwtAbstractScaleDraw::Labels ) );
        ui->font->setCurrentFont( radialGauge->font() );
        ui->fontSize->setEditText( QString::number(radialGauge->font().pointSize()) );

        // Needle
        ui->value->setValue( radialGauge->value() );
        index = ui->needleType->findData( radialGauge->needleType() );
        ui->needleType->setCurrentIndex( index );
        index = ui->needleStyle->findData( radialGauge->needleStyle() );
        ui->needleStyle->setCurrentIndex( index );
        ui->needleColor1->setColor( radialGauge->needleColor1() );
        ui->needleColor2->setColor( radialGauge->needleColor2() );

        // Color
        ui->title->setText( radialGauge->title() );
        ui->textColor->setColor( radialGauge->textColor() );
        ui->backgroundColor->setColor( radialGauge->backgroundColor() );

        // Preview update
        initGauge( ui->preview );
    }
}

void RadialGaugeSettingWidget::updatePreview()
{
    initGauge( ui->preview );
}
