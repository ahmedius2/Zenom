#ifndef PLOTMAGNIFIER_H
#define PLOTMAGNIFIER_H

#include <qwt_plot_magnifier.h>
#include <qwt_plot_canvas.h>

class PlotMagnifier : public QwtPlotMagnifier
{
    Q_OBJECT
public:
    explicit PlotMagnifier(QwtPlotCanvas *pCanvas);
    
signals:
    void zoomed();
    
protected:
    void rescale(double factor);
};

#endif // PLOTMAGNIFIER_H
