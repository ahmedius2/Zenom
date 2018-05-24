#ifndef LOGVARIABLESWIDGET_H
#define LOGVARIABLESWIDGET_H

#include <QWidget>
#include <QTableWidgetItem>
#include <QSettings>

#include "datarepository.h"
#include "widget/checkedheader.h"

namespace Ui {
class LogVariablesWidget;
}

class LogVariablesWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit LogVariablesWidget(QWidget *parent = 0);
    ~LogVariablesWidget();

    void setLogVariableList( const LogVariableList& pLogVariableList );

    void clear();

    void mainFrequencyChanged( double pFrequency );

	void mainDurationChanged( double pDuration );

    void saveSettings( QSettings& pSettings );

    void loadSettings( QSettings& pSettings );

    QAction * toggleViewAction() const;

protected:
    bool event(QEvent *pEvent);

private slots:
    void on_logVariableTable_itemChanged(QTableWidgetItem * item);
	void setLogVariableChecked(int pIndex, bool pChecked);
    void toggleView(bool pChecked);
    
private:
    Ui::LogVariablesWidget *ui;
	CheckedHeader* mHeaderView;
    QAction* mToggleViewAction;

	void setFrequency( int pIndex, double pFrequency );
	void setStartTime( int pIndex, double pStartTime );
    void setDuration( int pIndex, double pDuration );
};

#endif // LOGVARIABLESWIDGET_H
