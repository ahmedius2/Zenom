#include "robotmodedialog.h"
#include "ui_robotmodedialog.h"

RobotModeDialog::RobotModeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RobotModeDialog),
    cntrVariables(DataRepository::instance()->controlVariables())
{
    ui->setupUi(this);
}

RobotModeDialog::~RobotModeDialog()
{
    delete ui;
}

void RobotModeDialog::on_headButton_pressed()
{
    set_controlv("_selected_mode",HEAD);
}

void RobotModeDialog::on_rArmButton_pressed()
{
    set_controlv("_selected_mode",RARM);
}

void RobotModeDialog::on_lArmButton_pressed()
{
    set_controlv("_selected_mode",LARM);
}

void RobotModeDialog::on_bothArmsButton_pressed()
{
    set_controlv("_selected_mode",BOTH_ARMS);
}

void RobotModeDialog::on_walkTowardButton_pressed()
{
    set_controlv("_selected_mode",WALK_TOWARD);
}

void RobotModeDialog::on_stopButton_pressed()
{
    set_controlv("_selected_mode",STOP);
}

void RobotModeDialog::on_rightHandCheckbox_stateChanged(int arg1)
{
    set_controlv("_rightHandState",arg1);
}

void RobotModeDialog::on_leftHandCheckbox_stateChanged(int arg1)
{
    set_controlv("_leftHandState",arg1);
}

void RobotModeDialog::on_wholeBodyCheckbox_stateChanged(int arg1)
{
    set_controlv("_wholeBodyState",arg1);
}

void RobotModeDialog::on_distBetwArmsSpinbox_valueChanged(double arg1)
{
    set_controlv("_distBetwArms",arg1);
}

void RobotModeDialog::set_controlv(QString name, double value)
{
    for(unsigned int i=0; i<cntrVariables.size(); i++)
    {
        if(name.compare(QString::fromStdString(cntrVariables[i]->name())) == 0)
        {
            cntrVariables[i]->setHeapElement(0,value);
            break;
        }
    }
}
