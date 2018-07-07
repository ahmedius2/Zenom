#ifndef GAUGEWIDGET_H
#define GAUGEWIDGET_H

#include <QWidget>
#include "abstractgauge.h"
#include "widget/logvariableitem.h"

namespace Ui {
class GaugeWidget;
}

class GaugeWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit GaugeWidget(QWidget *parent = 0);
    ~GaugeWidget();


    AbstractGauge* gauge();

    void setGauge( AbstractGauge* pGauge );

    void tick();

    void saveSettings( QSettings& pSettings );

    void loadSettings( QSettings& pSettings );

    LogVariableItem logVariable();

    void setLogVariable( const LogVariableItem& pLogVariableItem );

signals:
    void closed( GaugeWidget* ) ;

protected:
    virtual void contextMenuEvent(QContextMenuEvent *pEvent);
    virtual void closeEvent(QCloseEvent *pEvent);

private:
    Ui::GaugeWidget *ui;
    AbstractGauge* mGauge;
    LogVariableItem mLogVariableItem;
};

#endif // GAUGEWIDGET_H
