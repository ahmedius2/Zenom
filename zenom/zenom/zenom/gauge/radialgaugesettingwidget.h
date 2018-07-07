#ifndef RADIALGAUGESETTINGWIDGET_H
#define RADIALGAUGESETTINGWIDGET_H

#include <QWidget>
#include "abstractgauge.h"

namespace Ui {
class RadialGaugeSettingWidget;
}

class RadialGaugeSettingWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit RadialGaugeSettingWidget(QWidget *parent = 0);
    ~RadialGaugeSettingWidget();

    virtual AbstractGauge* createGauge();

    virtual void initGauge( AbstractGauge* pGauge );

    virtual void initFromGauge( AbstractGauge* pGauge );

private slots:
    void updatePreview();
    
private:
    Ui::RadialGaugeSettingWidget *ui;
};

#endif // RADIALGAUGESETTINGWIDGET_H
