#ifndef EDITGAUGEDIALOG_H
#define EDITGAUGEDIALOG_H

#include <QDialog>
#include "gaugewidget.h"

namespace Ui {
class EditGaugeDialog;
}

class EditGaugeDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit EditGaugeDialog(QWidget *parent = 0);

    ~EditGaugeDialog();

    void initFrom(GaugeWidget* gaugeWidget);

    virtual void accept();
    
private:
    Ui::EditGaugeDialog *ui;
    GaugeWidget* mGaugeWidget;
};

#endif // EDITGAUGEDIALOG_H
