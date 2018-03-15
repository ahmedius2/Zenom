#ifndef ATTACHLOGVARIABLEDIALOG_H
#define ATTACHLOGVARIABLEDIALOG_H

#include <QDialog>
#include "widget/logvariableitem.h"

namespace Ui {
class AttachLogVariableDialog;
}

class AttachLogVariableDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit AttachLogVariableDialog(QWidget *parent = 0);

    ~AttachLogVariableDialog();

    QList<LogVariableItem> selectedLogVariableItems() const;
    
private:
    Ui::AttachLogVariableDialog *ui;
};

#endif // ATTACHLOGVARIABLEDIALOG_H
