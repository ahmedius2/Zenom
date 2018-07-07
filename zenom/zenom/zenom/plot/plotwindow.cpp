#include "plotwindow.h"
#include "ui_plotwindow.h"

#include <QGridLayout>
#include <QInputDialog>
#include <QFileDialog>
#include <QImageWriter>
#include "attachlogvariabledialog.h"

PlotWindow::PlotWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::PlotWindow)
{
    ui->setupUi(this);

    connect( ui->plot, SIGNAL(autoscaleOff()), this, SLOT(autoscaleOffSlot()) );
}

PlotWindow::~PlotWindow()
{
    delete ui;
}

void PlotWindow::tick()
{
    ui->plot->tick();
}

void PlotWindow::saveSettings(QSettings &pSettings)
{
    pSettings.setValue("geometry", saveGeometry());
    ui->plot->saveSettings( pSettings );
}

void PlotWindow::loadSettings(QSettings &pSettings)
{
    restoreGeometry( pSettings.value("geometry").toByteArray() );
    ui->plot->loadSettings( pSettings );
}

void PlotWindow::closeEvent(QCloseEvent *pEvent)
{
    emit closed( this );
    QWidget::closeEvent( pEvent );
}


void PlotWindow::on_action_Open_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Import File Name"),
                                                    QString(),
                                                    tr("Zenom Plot Files (*.zplot)"),
                                                    NULL,
                                                    QFileDialog::DontUseNativeDialog);

    if ( !fileName.isEmpty() )
    {
        ui->plot->importCurvesFromText( fileName );
    }
}

void PlotWindow::on_action_Save_triggered()
{
    QStringList filter;
    filter += "Zenom Plot Files (*.zplot)";

    QString fileName = QFileDialog::getSaveFileName( this,
                                             tr("Export File Name"),
                                             QString(),
                                             filter.join( ";;" ),
                                             NULL,
                                             QFileDialog::DontUseNativeDialog);

    if ( !fileName.isEmpty() )
    {
        if ( !fileName.endsWith(".zplot") )
            fileName += ".zplot";

        ui->plot->exportCurvesAsBinary( fileName );
    }
}

void PlotWindow::on_action_Export_triggered()
{
    QStringList filter;    
    filter += "Matlab Files (*.m)";

    const QList<QByteArray> imageFormats =
        QImageWriter::supportedImageFormats();

    // Supported Image Formats
    if( imageFormats.contains("png") )
        filter += "PNG (*.png)";

    if( imageFormats.contains("bmp") )
        filter += "BMP (*.bmp)";

    if( imageFormats.contains("jpg") )
        filter += "JPG (*.jpg)";

    filter += "Zenom Plot Files (*.zplot)";

    QString selectedFilter;
    QString fileName = QFileDialog::getSaveFileName( this,
                                             tr("Export File Name"),
                                             QString(),
                                             filter.join( ";;" ),
                                             &selectedFilter,
                                             QFileDialog::DontUseNativeDialog);

    if ( !fileName.isEmpty() )
    {
        if( selectedFilter == "Zenom Plot Files (*.zplot)" )    // Binary File
        {
            if ( !fileName.endsWith(".zplot") )
                fileName += ".zplot";

            ui->plot->exportCurvesAsBinary( fileName );
        }
        else if( selectedFilter == "Matlab Files (*.m)" )   // Matlab File
        {
            if ( !fileName.endsWith(".m") )
                fileName += ".m";

            ui->plot->exportCurvesAsMatlab( fileName );
        }
        else    // Image File
        {
            if( selectedFilter == "PNG (*.png)" )
            {
                if ( !fileName.endsWith(".png") )
                    fileName += ".png";
            }
            else if( selectedFilter == "BMP (*.bmp)" )
            {
                if ( !fileName.endsWith(".bmp") )
                    fileName += ".bmp";
            }
            else if( selectedFilter == "JPG (*.jpg)" )
            {
                if ( !fileName.endsWith(".jpg") )
                    fileName += ".jpg";
            }

            ui->plot->exportCurvesAsImage( fileName );
        }
    }
}

void PlotWindow::on_action_Close_triggered()
{
    close();
}

void PlotWindow::on_actionAttach_Log_Variable_triggered()
{
    AttachLogVariableDialog attachLogVariableDialog(this);
    int res = attachLogVariableDialog.exec();
    if ( res == QDialog::Accepted )
    {
        ui->plot->attactLogVariableItems( attachLogVariableDialog.selectedLogVariableItems() );
    }
}

void PlotWindow::on_actionSet_Time_Interval_triggered()
{
    bool isAccepted;
    int newInterval = QInputDialog::getInt ( this, "Set Time Interval", "Time Interval", ui->plot->timeInterval(), 1, 2147483647, 1, &isAccepted );
    if (isAccepted)
    {
        ui->plot->setTimeInterval( newInterval );
    }
}

void PlotWindow::on_actionAutoscale_triggered(bool pChecked)
{
    ui->plot->setAutoscale(pChecked);
}

void PlotWindow::autoscaleOffSlot()
{
    ui->actionAutoscale->setChecked( false );
}
