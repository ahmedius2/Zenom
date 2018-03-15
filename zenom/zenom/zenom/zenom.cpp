#include "zenom.h"
#include "ui_zenom.h"

#include <QFileDialog>
#include <unistd.h>

#include <iostream>
#include <string>

#include <QFileInfo>
#include <QTime>

#include "utility/matlabstream.h"

Zenom::Zenom(int argc, char *argv[]) :
    QMainWindow( NULL ),
    ui(new Ui::Zenom)
{
    ui->setupUi(this);
    createRecentFileActions();
    updateRecentFileActions();
    ui->output->setReadOnly(true);
    ui->statusBar->addPermanentWidget( mStatusBar = new StatusBar() );

    mDataRepository = DataRepository::instance();

    mControlVariablesWidget = new ControlVariablesWidget(this);
    ui->menu_View->addAction( mControlVariablesWidget->toggleViewAction() );

    mLogVariablesWidget = new LogVariablesWidget(this);
    ui->menu_View->addAction( mLogVariablesWidget->toggleViewAction() );

    mGaugeManager = new GaugeManager(this);
    mPlotManager = new PlotManager(this);
    mSceneManager = new SceneManager(this);
    connect( mSceneManager, SIGNAL(warningMessage(const QString&)), ui->output, SLOT(appendWarningMessage(const QString&)) );


    mMessageListenerTask = new MessageListenerTask(this);

    connect( &mControlBaseProcess, SIGNAL( error(QProcess::ProcessError) ), SLOT( controlBaseProcessError(QProcess::ProcessError) ));
    connect( &mControlBaseProcess, SIGNAL( readyReadStandardOutput() ), SLOT( controlBaseReadyReadStandardOutput() ));
    connect( &mControlBaseProcess, SIGNAL( readyReadStandardError() ), SLOT( controlBaseReadyReadStandardError() ));

    setSimulationState( TERMINATED );

    connect(&mTimer, SIGNAL(timeout()), SLOT(doloop()));

    mAboutDialog = new AboutDialog(this);

    // Parametrelerden birinde proje dosyası verilirse acilir.
    if ( argc >= 2 )
    {
        for ( int i = 0; i < argc; ++i )
        {
            QString projectPath( argv[i] );
            if ( projectPath.contains( ".znm" ) )
            {
                openProject( projectPath );
                break;
            }
        }
    }
}

Zenom::~Zenom()
{
    terminateProject();
    delete mMessageListenerTask;
    delete ui;
}

void Zenom::on_startButton_clicked()
{
    if( simulationState() == STOPPED )	// Start
    {
        setSimulationState( RUNNING );

        mDataRepository->deleteLogVariablesHeap();
        mDataRepository->createLogVariablesHeap();
        mDataRepository->sendStateRequest( R_START );

        ui->output->appendMessage( QString("Simulation started.") );
    }
    else if( simulationState() == RUNNING )	// Pause
    {
        setSimulationState( PAUSED );
        mDataRepository->sendStateRequest( R_PAUSE );

        ui->output->appendMessage( QString("Simulation paused.") );
    }
    else if( simulationState() == PAUSED )	// Resume
    {
        setSimulationState( RUNNING );
        mDataRepository->sendStateRequest( R_RESUME );

        ui->output->appendMessage( QString("Simulation resumed.") );
    }
}

void Zenom::on_stopButton_clicked()
{
    setSimulationState( STOPPED );
    mDataRepository->sendStateRequest( R_STOP );

    ui->output->appendMessage( QString("Simulation stopped.") );
}

void Zenom::on_actionWatch_triggered()
{
    mGaugeManager->showGaugeListDialog();
}

void Zenom::on_actionPlot_triggered()
{
    mPlotManager->createPlot();
}

void Zenom::on_actionScene_triggered()
{
    mSceneManager->createScene();
}

void Zenom::controlBaseProcessError( QProcess::ProcessError pError )
{
    if( pError == QProcess::FailedToStart )
    {
        ui->output->appendErrorMessage( "Error: Failed opening project: The program does not exist." );
    }
    else if( pError == QProcess::Crashed )
    {
        ui->output->appendErrorMessage( "Error: The program has unexpectedly finished. Please, reload the project to start." );
    }
    else
    {
        ui->output->appendErrorMessage( "Error: An unknown error occurred. Please, reload the project to start." );
    }

    setSimulationState( CRASHED );
}

void Zenom::controlBaseReadyReadStandardOutput()
{
    ui->output->appendUserMessage( mControlBaseProcess.readAllStandardOutput() );
}

void Zenom::controlBaseReadyReadStandardError()
{
    ui->output->appendUserErrorMessage( mControlBaseProcess.readAllStandardError() );
}

void Zenom::doloop()
{
    mStatusBar->setElapsedTime( mDataRepository->elapsedTimeSecond() );
    mStatusBar->setOverruns( mDataRepository->overruns() );
    mGaugeManager->tick();
    mPlotManager->tick();
    mSceneManager->tick();
}

State Zenom::simulationState()
{
    return mSimState;
}

void Zenom::setSimulationState(State pState)
{
    mSimState = pState;

    // File Menu
    ui->actionSave_Project->setEnabled( pState != TERMINATED );
    ui->actionReload->setEnabled( pState != TERMINATED );
    ui->actionExport_as_Matlab->setEnabled( pState == STOPPED );

    // View Menu
    ui->actionWatch->setEnabled( pState != TERMINATED );
    ui->actionPlot->setEnabled( pState != TERMINATED );
    ui->actionScene->setEnabled( pState != TERMINATED );
    mLogVariablesWidget->toggleViewAction()->setEnabled( pState != TERMINATED );
    mControlVariablesWidget->toggleViewAction()->setEnabled( pState != TERMINATED );

    // Zenom
    ui->frequency->setEnabled( pState == STOPPED );
    ui->duration->setEnabled( pState == STOPPED );

    ui->startButton->setIcon( style()->standardIcon( pState == RUNNING ? QStyle::SP_MediaPause : QStyle::SP_MediaPlay ) );
    ui->startButton->setEnabled( pState != TERMINATED && pState != CRASHED );
    ui->stopButton->setIcon( style()->standardIcon(QStyle::SP_MediaStop) );
    ui->stopButton->setEnabled( pState == RUNNING || pState == PAUSED );

    mStatusBar->setVisible( pState != TERMINATED );

    // Log Variable Widget
    mLogVariablesWidget->setDisabled( pState == RUNNING || pState == PAUSED );
}

void Zenom::on_actionOpen_Project_triggered()
{
    QFileDialog dialog( this );
    dialog.setFileMode( QFileDialog::ExistingFile );
    dialog.setNameFilter( "Zenom Files (*.znm)" );
    dialog.setViewMode( QFileDialog::Detail );
    if ( dialog.exec() == QDialog::Accepted )
    {
        openProject( dialog.selectedFiles()[0] );
    }
}

void Zenom::openProject(const QString& pProjectPath)
{
    terminateProject();     // close project if already a project was opened.

    // TODO catch blogu ve return kontrol et hersey silindigine emin ol
    try
    {
        QString projectAbsolutePath = QFileInfo( pProjectPath ).absoluteFilePath();

        QFileInfo fileInfo( projectAbsolutePath );
        if ( !fileInfo.exists() )
        {
            ui->output->appendErrorMessage( QString("Error: Failed opening project: '%1' does not exist.").arg(pProjectPath) );
            return;
        }

        QDir::setCurrent( fileInfo.path() );
        const QString projectName = fileInfo.baseName();
        const QString controlBaseProgram = fileInfo.dir().filePath( fileInfo.baseName() );

        mDataRepository->setProjectName( projectName.toStdString() );

        mDataRepository->createMessageQueues();


        mMessageListenerTask->create( mDataRepository->projectName() + "MessageListenerTask" );
        mMessageListenerTask->start();

        mControlBaseProcess.start( controlBaseProgram, QStringList() << projectName );
        if ( mControlBaseProcess.waitForStarted() )
        {
            // Controlbase'den mesaj gelene kadar beklenir.
            if ( !mMessageListenerTask->waitForInitMessage() )
            {
                ui->output->appendErrorMessage( QString("Error: Failed connecting program: The program does not implemented specified format.") );
                return;
            }

            if( !mDataRepository->readVariablesFromFile() )
            {
                ui->output->appendErrorMessage( QString("Error: Failed connecting program: The program does not implemented specified format.") );
                return;
            }

            mDataRepository->createMainControlHeap();

            // Controlbase main control heap'e baglanmasi ve
            // control variable degerlerini main control heap'e yazmasi beklenir.
            if ( !mMessageListenerTask->waitForInitMessage() )
            {
                ui->output->appendErrorMessage( QString("Error: Failed connecting program: The program does not implemented specified format.") );
                return;
            }

            mControlVariablesWidget->setControlVariableList( mDataRepository->controlVariables() );
            mLogVariablesWidget->setLogVariableList( mDataRepository->logVariables() );
            mGaugeManager->setLogVariableList( mDataRepository->logVariables() );

            loadSettings( projectAbsolutePath );

            setSimulationState( STOPPED );
            mTimer.start(50);

            setWindowTitle( fileInfo.baseName() );

            mProjectPath = projectAbsolutePath;

            insertRecentFileList( projectAbsolutePath );

            ui->output->appendMessage( QString("%1 succesfully loaded.").arg(projectName) );
        }
    }
    catch( ZnmException e )
    {
        // TODO file exist ise ne olacak
        std::cout << "openProject" << std::string( e.what() ) << std::endl;
    }
}

void Zenom::loadSettings(const QString &pProjectName)
{
    QApplication::setOverrideCursor(Qt::WaitCursor);

    // load widgets
    QSettings settings( pProjectName , QSettings::IniFormat);

    settings.beginGroup("zenom");
    setFrequency( settings.value("frequency", 1).toDouble() );
    setDuration( settings.value("duration", 100).toDouble() );
    restoreGeometry( settings.value("geometry").toByteArray() );
    mLogVariablesWidget->loadSettings( settings );      // log variable values
    mControlVariablesWidget->loadSettings( settings );	// control variable values
    mGaugeManager->loadSettings( settings );            // gauges
    mPlotManager->loadSettings( settings );             // plots
    mSceneManager->loadSettings( settings );            // scenes
    settings.endGroup();

    QApplication::restoreOverrideCursor();
}

void Zenom::on_actionSave_Project_triggered()
{
    QApplication::setOverrideCursor(Qt::WaitCursor);

    QSettings settings( mProjectPath, QSettings::IniFormat );
    settings.clear();

    settings.beginGroup("zenom");
    settings.setValue("frequency", ui->frequency->text());
    settings.setValue("duration", ui->duration->text());
    settings.setValue("geometry", saveGeometry());
    mLogVariablesWidget->saveSettings( settings );      // log variable values
    mControlVariablesWidget->saveSettings( settings );  // control variable values
    mGaugeManager->saveSettings( settings );            // gauges
    mPlotManager->saveSettings( settings );             // plots
    mSceneManager->saveSettings( settings );            // scenes
    settings.endGroup();

    QApplication::restoreOverrideCursor();
}

void Zenom::on_actionReload_triggered()
{
    terminateProject();
    openProject( mProjectPath );
}

void Zenom::on_actionExit_triggered()
{
    close();
}

void Zenom::on_frequency_editingFinished()
{
    setFrequency( ui->frequency->text().toDouble() );
}

void Zenom::setFrequency(double pFrequency)
{
    if ( pFrequency > 0 )
    {
        mDataRepository->setFrequency( pFrequency );
        ui->frequency->setText( QString::number(pFrequency) );
        mLogVariablesWidget->mainFrequencyChanged( pFrequency );
    }
    else
    {
        ui->frequency->setText( QString::number(mDataRepository->frequency()) );
    }
}

void Zenom::on_duration_editingFinished()
{
    setDuration( ui->duration->text().toDouble() );
}

void Zenom::setDuration(double pDuration)
{
    if ( pDuration > 0 )
    {
        mStatusBar->setDuration( pDuration );
        mDataRepository->setDuration( pDuration );
        ui->duration->setText( QString::number(pDuration) );
        mLogVariablesWidget->mainDurationChanged( pDuration );
    }
    else
    {
        ui->duration->setText( QString::number(mDataRepository->duration()) );
    }
}

void Zenom::terminateProject()
{
    QApplication::setOverrideCursor(Qt::WaitCursor);

    // if the controlbase is running, stop it and then terminate.
    if( simulationState() == RUNNING || simulationState() == PAUSED )
    {
        on_stopButton_clicked();
    }

    mMessageListenerTask->deleteTask();

    if ( mControlBaseProcess.state() != QProcess::NotRunning )
    {
        mDataRepository->sendStateRequest( R_TERMINATE );
        if ( !mControlBaseProcess.waitForFinished() )    // Finish the process
        {
            //appendTextToOutput("Terminating unsuccesful");
            mControlBaseProcess.kill(); // TODO process bir sure sonlanmaz ise kill etsek mi? kill edince crashed oluyor.
        }
    }

    setSimulationState( TERMINATED );

    mTimer.stop();

    mDataRepository->deleteMessageQueues();
    mDataRepository->deleteMainControlHeap();
    mDataRepository->deleteLogVariablesHeap();

    mControlVariablesWidget->clear();
    mLogVariablesWidget->clear();

    mDataRepository->clear();

    mGaugeManager->clear();
    mPlotManager->clear();
    mSceneManager->clear();

    ui->output->clear();

    QApplication::restoreOverrideCursor();
}

void Zenom::createRecentFileActions()
{
    for (int i = 0; i < MaxRecentFiles; ++i)
    {
        recentFileActs[i] = new QAction( QString::number(i), this);
        ui->menuRecent_P_rojects->insertAction( ui->actionClear_Recent_Projects_Menu, recentFileActs[i] );
        recentFileActs[i]->setVisible(false);
        connect(recentFileActs[i], SIGNAL(triggered()),
                this, SLOT(openRecentFile()));
    }

    ui->menuRecent_P_rojects->insertSeparator( ui->actionClear_Recent_Projects_Menu );
}

void Zenom::updateRecentFileActions()
{
    QSettings settings;
    QStringList files = settings.value("recentProjectList").toStringList();

    int numRecentFiles = qMin(files.size(), (int)MaxRecentFiles);

    for (int i = 0; i < numRecentFiles; ++i)
    {
        recentFileActs[i]->setText(files[i]);
        recentFileActs[i]->setVisible(true);
    }

    for (int j = numRecentFiles; j < MaxRecentFiles; ++j)
        recentFileActs[j]->setVisible(false);

    ui->menuRecent_P_rojects->setEnabled( numRecentFiles > 0 );
}

void Zenom::insertRecentFileList(const QString &pProjectPath)
{
    QSettings settings;
    QStringList files = settings.value("recentProjectList").toStringList();
    files.removeAll( pProjectPath );
    files.prepend( pProjectPath );
    while (files.size() > MaxRecentFiles)
        files.removeLast();

    settings.setValue("recentProjectList", files);

    updateRecentFileActions();
}

void Zenom::on_actionClear_Recent_Projects_Menu_triggered()
{
    QSettings settings;
    settings.setValue("recentProjectList", QStringList());

    updateRecentFileActions();
}

void Zenom::openRecentFile()
{
    QAction *action = qobject_cast<QAction *>(sender());
    if (action)
        openProject( action->text() );
}

void Zenom::on_action_About_zenom_triggered()
{
    mAboutDialog->show();
}

void Zenom::on_actionExport_as_Matlab_triggered()
{
    QString fileName = QFileDialog::getSaveFileName( this,
                                             tr("Export File Name"),
                                             QString(),
                                             "Matlab (*.m)",
                                             NULL,
                                             QFileDialog::DontUseNativeDialog);

    if ( !fileName.isEmpty() )
    {
        if ( !fileName.endsWith(".m") )
            fileName += ".m";

        QFile file( fileName );
        if (!file.open(QIODevice::WriteOnly))
            return;

        // Log variable listesi dosyaya yazilir.
        MatlabStream out(&file);
        for ( unsigned int i = 0; i < DataRepository::instance()->logVariables().size(); ++i )
        {
            out.writeLogVariable( DataRepository::instance()->logVariables().at(i) );
        }
    }
}
