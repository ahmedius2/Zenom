#ifndef PLOTMANAGER_H
#define PLOTMANAGER_H

#include <QObject>
#include "plotwindow.h"

class PlotManager : public QObject
{
    Q_OBJECT
public:
    explicit PlotManager(QObject *parent = 0);
    
    void saveSettings( QSettings& pSettings );

    void loadSettings( QSettings& pSettings );

    void tick();

    void clear();

public slots:
    PlotWindow* createPlot();

private slots:
    void plotWindowDestroyed( PlotWindow* pPlotWindow );

private:
    QVector<PlotWindow*> mPlotList;
};

#endif // PLOTMANAGER_H
