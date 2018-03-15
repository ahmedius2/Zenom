#ifndef PLOTCURVE_H
#define PLOTCURVE_H

#include <qwt_plot_curve.h>
#include "widget/logvariableitem.h"

/*
 *  CurveData
 */
class CurveData : public QwtSeriesData<QPointF>
{
public:
    CurveData();

    virtual QPointF sample( size_t i ) const { return mLogVariableItem.heapElement(i); }

    virtual size_t size() const { return mLogVariableItem.isValid() ? mLogVariableItem.size() : 0; }

    virtual QRectF boundingRect() const { return d_boundingRect; }

    void setLogVariableItem(const LogVariableItem &);

    LogVariableItem logVariableItem();

    void updateBoundingRect();

    void saveSettings(QSettings &pSettings);

    void loadSettings(QSettings &pSettings);

private:
     LogVariableItem mLogVariableItem;
     int mLastHeapSize;
};

/*
 *  PlotCurve
 */
class PlotCurve : public QwtPlotCurve
{
public:
    PlotCurve(const QString& = QString("") );

    void setLogVariableItem(const LogVariableItem &);

    LogVariableItem logVariableItem();

    void tick();

    void saveSettings(QSettings &pSettings);

    void loadSettings(QSettings &pSettings);

    virtual QWidget* legendItem() const;

private:
    CurveData *mCurveData;
};

#endif // PLOTCURVE_H
