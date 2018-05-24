#ifndef NUMERICGAUGESETTINGWIDGET_H
#define NUMERICGAUGESETTINGWIDGET_H

#include <QWidget>
#include "abstractgauge.h"

namespace Ui {
class NumericGaugeSettingWidget;
}

class NumericGaugeSettingWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit NumericGaugeSettingWidget(QWidget *parent = 0);
    ~NumericGaugeSettingWidget();

    virtual AbstractGauge* createGauge();

    virtual void initGauge( AbstractGauge* pGauge );

    virtual void initFromGauge( AbstractGauge* pGauge );

private slots:
    void updatePreview();
    
private:
    Ui::NumericGaugeSettingWidget *ui;
};

#endif // NUMERICGAUGESETTINGWIDGET_H
