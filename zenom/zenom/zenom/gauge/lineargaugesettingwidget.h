#ifndef LINEARGAUGESETTINGWIDGET_H
#define LINEARGAUGESETTINGWIDGET_H

#include <QWidget>
#include "abstractgauge.h"

namespace Ui {
class LinearGaugeSettingWidget;
}

class LinearGaugeSettingWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit LinearGaugeSettingWidget(QWidget *parent = 0);
    ~LinearGaugeSettingWidget();

    virtual AbstractGauge* createGauge();

    virtual void initGauge( AbstractGauge* pGauge );

    virtual void initFromGauge( AbstractGauge* pGauge );

private slots:
    void updatePreview();
    
private:
    Ui::LinearGaugeSettingWidget *ui;
};

#endif // LINEARGAUGESETTINGWIDGET_H
