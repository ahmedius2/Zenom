#include "plotmagnifier.h"

PlotMagnifier::PlotMagnifier(QwtPlotCanvas *pCanvas) :
    QwtPlotMagnifier(pCanvas)
{
}

void PlotMagnifier::rescale(double factor)
{
    emit zoomed();
    QwtPlotMagnifier::rescale(factor);
}
