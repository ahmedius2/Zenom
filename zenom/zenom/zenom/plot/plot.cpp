#include "plot.h"

#include <QFile>
#include <QFileInfo>
#include <QImageWriter>
#include <qwt_legend.h>
#include <qwt_plot_grid.h>
#include <qwt_plot_marker.h>
#include <qwt_plot_renderer.h>
#include "plotmagnifier.h"
#include "utility/matlabstream.h"
#include <datarepository.h>


Plot::Plot(QWidget* pParent): QwtPlot(pParent)
{
    setAxisTitle( QwtPlot::xBottom, "Time [s]" );
    setCanvasBackground( Qt::white );
    insertLegend( new QwtLegend, QwtPlot::RightLegend );

    // panning with the left mouse button
    QwtPlotPanner* plotPanner = new QwtPlotPanner( canvas() );
    connect( plotPanner, SIGNAL(panned(int,int)), this, SLOT(zoommed_or_panned()) );

    // zoom in/out with the wheel
    PlotMagnifier* plotMagnifier = new PlotMagnifier( canvas() );
    connect( plotMagnifier, SIGNAL(zoomed()), this, SLOT(zoommed_or_panned()) );

    QwtPlotGrid *grid = new QwtPlotGrid();
    grid->setPen( QPen( Qt::gray, 0.0, Qt::DotLine ) );
    grid->attach( this );

    QwtPlotMarker *d_origin = new QwtPlotMarker();
    d_origin->setLineStyle( QwtPlotMarker::Cross );
    d_origin->setValue( 0.0, 0.0 );
    d_origin->setLinePen( QPen( Qt::gray, 0.0, Qt::DashLine ) );
    d_origin->attach( this );

    setAutoscaleAndInterval( true, 0, 10 );
}

Plot::~Plot()
{

}

void Plot::saveSettings( QSettings& pSettings )
{
    pSettings.setValue("timeInterval", timeInterval());
    pSettings.setValue("curveCount", mCurveVec.size());
    for (int i = 0; i < mCurveVec.size(); ++i)
    {
        pSettings.beginGroup( QString("curve") + QString::number(i) );
        mCurveVec[i]->saveSettings(pSettings);
        pSettings.endGroup();
    }
}

void Plot::loadSettings( QSettings& pSettings )
{
    mColorGenerator.reset();
    setTimeInterval( pSettings.value("timeInterval", 10).toInt() );
    int curveCount = pSettings.value("curveCount").toInt();
    for (int i = 0; i < curveCount; ++i)
    {
        pSettings.beginGroup( QString("curve") + QString::number(i) );
        PlotCurve* newCurve = new PlotCurve( );
        newCurve->loadSettings(pSettings);
        pSettings.endGroup();

        // Konfigurasyon dosyasında silinen bir log degiskenine ait
        // kayit varsa, o log değişkeni plota eklenmez.
        if ( newCurve->logVariableItem().isNull() )
        {
            delete newCurve;
        }
        else
        {
            newCurve->attach( this );
            mCurveVec.push_back(newCurve);
            mColorGenerator.increaseIndex();
        }
    }
}

void Plot::attactLogVariableItems( const QList<LogVariableItem>& pLogVariableItems )
{
    for ( int i = 0; i < pLogVariableItems.size(); ++i )
    {
        PlotCurve* newCurve = new PlotCurve( pLogVariableItems[i].name() );
        newCurve->setLogVariableItem( pLogVariableItems[i]);
        newCurve->setPen( QPen( mColorGenerator.generateColor() ));
        newCurve->attach( this );
        mCurveVec.push_back(newCurve);
    }
}

void Plot::tick()
{
    double maxTime = -1;
    for (int i = 0 ; i < mCurveVec.size(); ++i)
    {
        mCurveVec[i]->tick();
        maxTime = qMax( maxTime, mCurveVec[i]->data()->boundingRect().right() );
    }

    // Increment interval
    if ( maxTime > d_interval.maxValue() )
    {
        setAutoscaleAndInterval( autoscale(), d_interval.maxValue(), d_interval.maxValue() + timeInterval() );
    }

    // rescale when simulation start
    if ( maxTime < d_interval.minValue() )
    {
        setAutoscaleAndInterval( autoscale(), 0, timeInterval() );
    }

    replot();
}

void Plot::legendColorChanged( const QColor& pColor )
{
    if ( legend() && sender()->isWidgetType() )
    {
        PlotCurve* curve = (PlotCurve*) legend()->find( ( QWidget * )sender() );
        QPen currentPen = curve->pen();
        currentPen.setColor( pColor );
        curve->setPen( currentPen );
        replot();
    }
}

void Plot::legendRemoveRequest()
{
    if ( legend() && sender()->isWidgetType() )
    {
        PlotCurve* curve = (PlotCurve*) legend()->find( ( QWidget * )sender() );

        for (int i = 0; i < mCurveVec.size(); ++i)
        {
            if ( mCurveVec[i] == curve )
            {
                mCurveVec.remove( i );
                break;
            }
        }

        delete curve;
        replot();
        updateLayout();
    }
}

void Plot::legendSizeChanged(int pWidth)
{
    if ( legend() && sender()->isWidgetType() )
    {
        PlotCurve* curve = (PlotCurve*) legend()->find( ( QWidget * )sender() );
        QPen currentPen = curve->pen();
        currentPen.setWidth(pWidth);
        curve->setPen( currentPen );
        replot();
    }
}

double Plot::timeInterval()
{
    return d_interval.width();
}

void Plot::setTimeInterval(double pInterval)
{
    setAutoscaleAndInterval( autoscale(), d_interval.minValue(), d_interval.minValue() + pInterval );
}

bool Plot::autoscale()
{
    return mAutoscale;
}

void Plot::setAutoscale( bool pOn )
{
    setAutoscaleAndInterval( pOn, d_interval.minValue(), d_interval.maxValue() );
}

void Plot::zoommed_or_panned()
{
    setAutoscale(false);
    emit autoscaleOff();
}

void Plot::setAutoscaleAndInterval( bool pOn, double pMin, double pMax )
{
    mAutoscale = pOn;

    d_interval.setMinValue( pMin );
    d_interval.setMaxValue( pMax );

    if ( pOn )
    {
        setAxisAutoScale( QwtPlot::yLeft );
        setAxisScale(QwtPlot::xBottom, d_interval.minValue(), d_interval.maxValue());
    }
}

void Plot::importCurvesFromText( const QString &pFileName )
{
    QFile file( pFileName );
    if (!file.open(QIODevice::ReadOnly))
        return;

    QDataStream in(&file);
    QString baseFileName = QFileInfo(pFileName).baseName();

    QString name;
    QVector<QPointF> data;
    while ( !in.atEnd() )
    {
        in >> name >> data;

        PlotCurve* newCurve = new PlotCurve( QString("%1_%2").arg(baseFileName).arg(name) );
        newCurve->setPen( QPen( mColorGenerator.generateColor() ));
        newCurve->setSamples( data );
        newCurve->attach( this );
    }
}

void Plot::exportCurvesAsBinary( const QString& pFileName )
{
    QFile file( pFileName );
    if (!file.open(QIODevice::WriteOnly))
        return;

    QDataStream out(&file);

    // Writes the points to stream out
    for( int i = 0; i < mCurveVec.size(); ++i )
    {
        QVector<QPointF> data;
        for(size_t j = 0; j < mCurveVec[i]->data()->size(); ++j)
        {
            data.push_back( mCurveVec[i]->data()->sample(j) );
        }
        out << mCurveVec[i]->title().text() << data;
    }
}

void Plot::exportCurvesAsImage( const QString& pFileName )
{
    // Legend item'da yer alan X  butonu resime katılmaz.
    QRect rectangle( 0, 0, size().width() - 20 , size().height() );

    QPixmap pixmap(rectangle.size());
    render(&pixmap, QPoint(), QRegion(rectangle));

    pixmap.save( pFileName );
}

void Plot::exportCurvesAsMatlab(const QString &pFileName)
{
    QFile file( pFileName );
    if (!file.open(QIODevice::WriteOnly))
        return;

    MatlabStream out(&file);

    // Writes the points to stream out
    for( int i = 0; i < mCurveVec.size(); ++i )
    {
        LogVariableItem logVariableItem = mCurveVec[i]->logVariableItem();
        out.writeLogVariableItem( logVariableItem.logVariable(), logVariableItem.row(), logVariableItem.column() );
        out.writeLogVariableTime( logVariableItem.logVariable() );
    }
}
