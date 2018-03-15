#include "lineargaugesettingwidget.h"
#include "ui_lineargaugesettingwidget.h"

LinearGaugeSettingWidget::LinearGaugeSettingWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LinearGaugeSettingWidget)
{
    ui->setupUi(this);
    // Orientation
    ui->orientation->setItemData ( 0, Qt::Vertical );
    ui->orientation->setItemData ( 1, Qt::Horizontal );

    // Scale Position
    ui->scalePosition->setItemData ( 0, QwtThermo::NoScale );
    ui->scalePosition->setItemData ( 1, QwtThermo::LeftScale );
    ui->scalePosition->setItemData ( 2, QwtThermo::RightScale );
    ui->scalePosition->setItemData ( 3, QwtThermo::TopScale );
    ui->scalePosition->setItemData ( 4, QwtThermo::BottomScale );

    // Font Size
    QFontDatabase db;
    foreach(int size, db.standardSizes())
        ui->fontSize->addItem(QString::number(size));

    initFromGauge( ui->preview );

    // Scale
    connect( ui->orientation, SIGNAL(currentIndexChanged(int)), SLOT(updatePreview()) );
    connect( ui->scalePosition, SIGNAL(currentIndexChanged(int)), SLOT(updatePreview()) );
    connect( ui->rangeMin, SIGNAL(valueChanged(double)), SLOT(updatePreview()) );
    connect( ui->rangeMax, SIGNAL(valueChanged(double)), SLOT(updatePreview()) );

    // Ticks
    connect( ui->majorTick, SIGNAL(valueChanged(int)), SLOT(updatePreview()) );
    connect( ui->minorTick, SIGNAL(valueChanged(int)), SLOT(updatePreview()) );
    connect( ui->labelGroupBox, SIGNAL(toggled(bool)), SLOT(updatePreview()) );
    connect( ui->font, SIGNAL(currentFontChanged(const QFont&)), SLOT(updatePreview()) );
    connect( ui->fontSize, SIGNAL(editTextChanged(const QString&)), SLOT(updatePreview()) );

    // Pipe
    connect( ui->value, SIGNAL(valueChanged(int)), SLOT(updatePreview()) );
    connect( ui->pipeWidth, SIGNAL(valueChanged(int)), SLOT(updatePreview()) );
    connect( ui->pipeColor, SIGNAL(colorChanged(const QColor&)), SLOT(updatePreview()) );

    // Alarm
    connect( ui->alarmGroupBox, SIGNAL(toggled(bool)), SLOT(updatePreview()) );
    connect( ui->alarmLevel, SIGNAL(valueChanged(double)), SLOT(updatePreview()) );
    connect( ui->alarmColor, SIGNAL(colorChanged(const QColor&)), SLOT(updatePreview()) );

    // Color
    connect( ui->textColor, SIGNAL(colorChanged(const QColor&)), SLOT(updatePreview()) );
    connect( ui->backgroundColor, SIGNAL(colorChanged(const QColor&)), SLOT(updatePreview()) );
}

LinearGaugeSettingWidget::~LinearGaugeSettingWidget()
{
    delete ui;
}

AbstractGauge* LinearGaugeSettingWidget::createGauge()
{
    LinearGauge* linearGauge = new LinearGauge();
    initGauge( linearGauge );
    return linearGauge;
}


void LinearGaugeSettingWidget::initGauge( AbstractGauge* pGauge )
{
    LinearGauge* linearGauge = dynamic_cast<LinearGauge*>(pGauge);
    if ( linearGauge )
    {
        int index;

         // Scale
        index = ui->orientation->currentIndex();
        Qt::Orientation orientation = (Qt::Orientation)ui->orientation->itemData( index ).toInt();
        index = ui->scalePosition->currentIndex();
        QwtThermo::ScalePos scalePosition = (QwtThermo::ScalePos)ui->scalePosition->itemData( index ).toInt();
        linearGauge->setOrientation( orientation, scalePosition );
        linearGauge->setMinValue( ui->rangeMin->value() );
        linearGauge->setMaxValue( ui->rangeMax->value() );

        // Ticks
        linearGauge->setScaleMaxMinor( ui->minorTick->value() );
        linearGauge->setScaleMaxMajor( ui->majorTick->value() );
        linearGauge->scaleDraw()->enableComponent( QwtAbstractScaleDraw::Labels, ui->labelGroupBox->isChecked() );
        QFont font = ui->font->currentFont();
        int fontSize = ui->fontSize->currentText().toInt();
        font.setPointSize( fontSize < 1 ? 1 : fontSize );
        linearGauge->setFont( font );

        // Pipe
        linearGauge->setValue( ui->value->value() );
        linearGauge->setPipeWidth( ui->pipeWidth->value() );
        linearGauge->setFillBrush( ui->pipeColor->color() );

        // Alarm
        linearGauge->setAlarmLevel( ui->alarmLevel->value() );
        linearGauge->setAlarmEnabled( ui->alarmGroupBox->isChecked() );
        linearGauge->setAlarmBrush( ui->alarmColor->color() );

        // Color
        linearGauge->setTitle( ui->title->text() );
        linearGauge->setTextColor( ui->textColor->color() );
        linearGauge->setBackgroundColor( ui->backgroundColor->color() );
    }
}

void LinearGaugeSettingWidget::initFromGauge( AbstractGauge* pGauge )
{
    LinearGauge* linearGauge = dynamic_cast<LinearGauge*>(pGauge);
    if ( linearGauge )
    {
        // Scale
        int index = ui->orientation->findData( linearGauge->orientation() );
        ui->orientation->setCurrentIndex( index );
        index = ui->scalePosition->findData( linearGauge->scalePosition() );
        ui->scalePosition->setCurrentIndex( index );
        ui->rangeMin->setValue( linearGauge->minValue() );
        ui->rangeMax->setValue( linearGauge->maxValue() );

        // Ticks
        ui->majorTick->setValue( linearGauge->scaleMaxMajor() );
        ui->minorTick->setValue( linearGauge->scaleMaxMinor() );
        ui->labelGroupBox->setChecked( linearGauge->scaleDraw()->hasComponent( QwtAbstractScaleDraw::Labels ) );
        ui->font->setCurrentFont( linearGauge->font() );
        ui->fontSize->setEditText( QString::number(linearGauge->font().pointSize()) );

        // Pipe
        ui->value->setValue( linearGauge->value() );
        ui->pipeWidth->setValue( linearGauge->pipeWidth() );
        ui->pipeColor->setColor( linearGauge->fillBrush().color() );

        // Alarm
        ui->alarmGroupBox->setChecked( linearGauge->alarmEnabled() );
        ui->alarmLevel->setValue( linearGauge->alarmLevel() );
        ui->alarmColor->setColor( linearGauge->alarmBrush().color() );

        // Color
        ui->title->setText( linearGauge->title() );
        ui->textColor->setColor( linearGauge->textColor() );
        ui->backgroundColor->setColor( linearGauge->backgroundColor() );

        // Preview update
        initGauge( ui->preview );
    }
}


void LinearGaugeSettingWidget::updatePreview()
{
    initGauge( ui->preview );
}
