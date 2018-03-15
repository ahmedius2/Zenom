#ifndef CONTROLVARIABLESWIDGET_H
#define CONTROLVARIABLESWIDGET_H

#include <QWidget>
#include <QTableWidgetItem>
#include <QSettings>

#include <datarepository.h>

namespace Ui {
class ControlVariablesWidget;
}

class ControlVariablesWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit ControlVariablesWidget(QWidget *parent = 0);
    ~ControlVariablesWidget();

    void setControlVariableList( const ControlVariableList& pControlVariableList );

    void clear();

    void saveSettings( QSettings& pSettings );

    void loadSettings( QSettings& pSettings );

    QAction * toggleViewAction() const;

protected:
    bool event(QEvent *pEvent);

private slots:
    void on_apply_clicked();
    void on_cancel_clicked();
    void itemChanged(QTableWidgetItem* pItem);
    void toggleView(bool pChecked);

private:
    void enableButtons(bool pEnable);
    void heapToWidget();
    void widgetToHeap();
    
private:
    Ui::ControlVariablesWidget *ui;
    QAction* mToggleViewAction;
};

#endif // CONTROLVARIABLESWIDGET_H
