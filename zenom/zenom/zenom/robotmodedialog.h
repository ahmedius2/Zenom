#ifndef ROBOTMODEDIALOG_H
#define ROBOTMODEDIALOG_H

#include <QDialog>
#include <datarepository.h>

namespace Ui {
class RobotModeDialog;
}

class RobotModeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RobotModeDialog(QWidget *parent = 0);
    ~RobotModeDialog();

private slots:
    void on_headButton_pressed();

    void on_rArmButton_pressed();

    void on_lArmButton_pressed();

    void on_bothArmsButton_pressed();

    void on_walkTowardButton_pressed();

    void on_stopButton_pressed();

    void on_rightHandCheckbox_stateChanged(int arg1);

    void on_leftHandCheckbox_stateChanged(int arg1);

    void on_wholeBodyCheckbox_stateChanged(int arg1);

    void on_distBetwArmsSpinbox_valueChanged(double arg1);

private:
    enum TeleopMode { HEAD, LARM,  RARM, BOTH_ARMS, WALK_TOWARD, STOP };
    void set_controlv(QString name, double value);
    Ui::RobotModeDialog *ui;
    //control variables
    const ControlVariableList& cntrVariables;
};

#endif // ROBOTMODEDIALOG_H
