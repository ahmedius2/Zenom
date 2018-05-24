#include "plotmanager.h"

PlotManager::PlotManager(QObject *parent) :
    QObject(parent)
{
}

void PlotManager::saveSettings( QSettings& pSettings )
{
    pSettings.beginGroup("Plots");
    pSettings.setValue("size", mPlotList.size());
    for ( int i = 0; i < mPlotList.size(); ++i )
    {
        pSettings.beginGroup( QString("Plot") + QString::number(i) );
        mPlotList[i]->saveSettings(pSettings);
        pSettings.endGroup();
    }
    pSettings.endGroup();
}

void PlotManager::loadSettings( QSettings& pSettings )
{
    pSettings.beginGroup("Plots");
    int size = pSettings.value("size", 0).toInt();
    for ( int i = 0; i < size; ++i )
    {
        pSettings.beginGroup( QString("Plot") + QString::number(i) );
        PlotWindow* plotWindow = createPlot();
        plotWindow->loadSettings(pSettings);
        pSettings.endGroup();
    }
    pSettings.endGroup();
}

void PlotManager::tick()
{
    for ( int i = 0; i < mPlotList.size(); ++i )
    {
        mPlotList[i]->tick();
    }
}

void PlotManager::clear()
{
    for ( int i = 0; i < mPlotList.size(); ++i )
    {
        mPlotList[i]->disconnect();
        delete mPlotList[i];
    }
    mPlotList.clear();
}

PlotWindow* PlotManager::createPlot()
{
    PlotWindow* plotWindow = new PlotWindow( static_cast<QWidget*>(parent()) );
    plotWindow->show();
    connect( plotWindow, SIGNAL(closed(PlotWindow*)), SLOT(plotWindowDestroyed(PlotWindow*)) );
    mPlotList.push_back( plotWindow );

    return plotWindow;
}

void PlotManager::plotWindowDestroyed( PlotWindow* pPlotWindow )
{
    int index = mPlotList.indexOf( pPlotWindow );
    if ( index >= 0 )
        mPlotList.remove( index );
    pPlotWindow->deleteLater();
}
