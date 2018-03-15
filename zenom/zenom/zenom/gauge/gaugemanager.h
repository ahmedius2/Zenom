#ifndef GAUGEMANAGER_H
#define GAUGEMANAGER_H

#include <QObject>
#include "gaugewidget.h"
#include "creategaugedialog.h"

class GaugeManager : public QObject
{
    Q_OBJECT
public:
    explicit GaugeManager(QWidget *parent = 0);

    void setLogVariableList( const LogVariableList& pLogVariableList );
    
    void saveSettings( QSettings& pSettings );

    void loadSettings( QSettings& pSettings );

    void tick();

    void clear();
    
public slots:
    void showGaugeListDialog();

private slots:
    void gaugeWidgetCreated( GaugeWidget* pGaugeWidget );
    void gaugeWidgetDestroyed( GaugeWidget *pGaugeWidget );

private:
    QVector<GaugeWidget*> mGaugeList;
    CreateGaugeDialog* mCreateGaugeDialog;
};

#endif // GAUGEMANAGER_H
