#include "gaugewidget.h"
#include "ui_gaugewidget.h"

#include <QContextMenuEvent>
#include <QMenu>

#include "lineargauge.h"
#include "radialgauge.h"
#include "numericgauge.h"
#include "editgaugedialog.h"

GaugeWidget::GaugeWidget(QWidget *parent) :
    QWidget(parent, Qt::Window | Qt::WindowCloseButtonHint ),
    ui(new Ui::GaugeWidget)
{
    ui->setupUi(this);
    mGauge = NULL;
    setWindowTitle("Gauge");
}

GaugeWidget::~GaugeWidget()
{
    delete ui;
}


AbstractGauge* GaugeWidget::gauge()
{
    return mGauge;
}

void GaugeWidget::setGauge( AbstractGauge* pGauge )
{
    delete mGauge;
    mGauge = pGauge;
    QWidget* w = pGauge->asWidget();
    setWindowTitle( pGauge->title() );
    layout()->addWidget( w );
    resize( w->sizeHint() );
}

void GaugeWidget::tick()
{
    if ( mLogVariableItem.isValid() )
    {
        mGauge->setValue( mLogVariableItem.lastHeapElement() );
    }
}

void GaugeWidget::saveSettings( QSettings& pSettings )
{
    pSettings.setValue("geometry", saveGeometry());
    pSettings.setValue("type", mGauge->type());
    mGauge->saveSettings( pSettings );
    mLogVariableItem.saveSettings( pSettings );
}

void GaugeWidget::loadSettings( QSettings& pSettings )
{
    GaugeType gaugeType = (GaugeType)pSettings.value("type", LINEAR_GAUGE).toInt();
    AbstractGauge* gauge;
    if ( gaugeType == RADIAL_GAUGE )
    {
        gauge = new RadialGauge();
    }
    else if ( gaugeType == NUMERIC_GAUGE )
    {
        gauge = new NumericGauge();
    }
    else/* if ( gaugeType == AbstractGauge::LINEAR )*/
    {
        gauge = new LinearGauge();
    }

    gauge->loadSettings( pSettings );
    setGauge( gauge );
    restoreGeometry( pSettings.value("geometry").toByteArray() );
    mLogVariableItem.loadSettings( pSettings );
    setWindowTitle( mLogVariableItem.name() );
}

LogVariableItem GaugeWidget::logVariable()
{
    return mLogVariableItem;
}

void GaugeWidget::setLogVariable( const LogVariableItem& pLogVariableItem )
{
    mLogVariableItem = pLogVariableItem;
    setWindowTitle( pLogVariableItem.name() );
}

void GaugeWidget::contextMenuEvent( QContextMenuEvent *pEvent )
{
    QMenu menu;
    menu.addAction("Edit...");
    QAction *action = menu.exec( pEvent->globalPos() );
    if ( action )
    {     
        EditGaugeDialog editGaugeDialog;
        editGaugeDialog.initFrom(this);
        editGaugeDialog.exec();
    }

    QWidget::contextMenuEvent(pEvent);
}

void GaugeWidget::closeEvent(QCloseEvent *pEvent)
{
    emit closed( this );
    QWidget::closeEvent( pEvent );
}
