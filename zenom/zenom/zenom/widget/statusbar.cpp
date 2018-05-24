#include "statusbar.h"
#include "ui_statusbar.h"

StatusBar::StatusBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StatusBar)
{
    ui->setupUi(this);
    ui->progressBar->setStyleSheet( "QProgressBar { background-color: palegoldenrod; border-width: 2px; border-radius: 5; }" );
}

StatusBar::~StatusBar()
{
    delete ui;
}

void StatusBar::setDuration(const double pDuration)
{
    ui->progressBar->setMaximum( qRound(pDuration) );
}

void StatusBar::setOverruns(const double pOverruns)
{
    ui->overruns->setText( QString("O=%1").arg( pOverruns ) );
}

void StatusBar::setElapsedTime(const double pElapsedTime)
{
    ui->progressBar->setValue( qRound(pElapsedTime) );
    ui->elapsedTime->setText( QString("T=%1").arg( QString::number(pElapsedTime, 'f', 3) ) );
}
