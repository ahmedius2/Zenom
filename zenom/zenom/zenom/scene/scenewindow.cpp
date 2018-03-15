#include "scenewindow.h"
#include "ui_scenewindow.h"

#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>
#include <QFileInfo>
#include <osgDB/Registry>
#include <osgDB/ReadFile>

SceneWindow::SceneWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SceneWindow)
{
    ui->setupUi(this);

    // Viewpoints combo box
    mViewpointsComboBox = new QComboBox();
    mViewpointsComboBox->setMinimumWidth(150);
    connect(mViewpointsComboBox, SIGNAL(currentIndexChanged(QString)), SLOT(viewpointChangedSlot(QString)) );
    ui->toolBar->insertWidget( ui->actionReturn_to_Viewpoint, mViewpointsComboBox );

    enableActions( false );

    // Bind Dialog
    mBindDialog = new BindDialog(this);
    mBindDialog->setLogVariableList( DataRepository::instance()->logVariables() );
}

SceneWindow::~SceneWindow()
{
    delete ui;
}


void SceneWindow::tick()
{
    ui->viewer->update();
}

void SceneWindow::saveSettings(QSettings &pSettings)
{
    pSettings.setValue("geometry", saveGeometry());
    pSettings.setValue("filename", mSceneFilename);
    pSettings.setValue("viewpointSize", mViewpoints.size());
    int i = 0;
    QMap<QString, Viewpoint>::iterator itr = mViewpoints.begin();
    while (itr != mViewpoints.end())
    {
        pSettings.beginGroup( QString("viewpoint") + QString::number(i) );
        itr.value().saveSettings(pSettings);
        ++itr;
        ++i;
        pSettings.endGroup();
    }
    mBindDialog->saveSettings(pSettings);
}

void SceneWindow::loadSettings(QSettings &pSettings)
{
    restoreGeometry( pSettings.value("geometry").toByteArray() );
    readNodeFile( pSettings.value("filename").toString() );
    int size = pSettings.value("viewpointSize", 0).toInt();
    for ( int i = 0; i < size; ++i )
    {
        pSettings.beginGroup( QString("viewpoint") + QString::number(i) );
        Viewpoint viewpoint;
        viewpoint.loadSettings(pSettings);
        insertViewpoint( viewpoint );
        pSettings.endGroup();
    }
    mBindDialog->loadSettings(pSettings);
}

void SceneWindow::closeEvent(QCloseEvent *pEvent)
{
    emit closed( this );
    QWidget::closeEvent( pEvent );
}

// File Menu
void SceneWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Load OSG File"),
                                                    "",
                                                    tr("OSG Files (*.*)"),
                                                    NULL,
                                                    QFileDialog::DontUseNativeDialog);

    QDir dir;
    readNodeFile( dir.relativeFilePath( fileName ) );
}

void SceneWindow::on_actionClose_triggered()
{
    close();
}

// View Menu
void SceneWindow::viewpointChangedSlot( const QString& pName )
{
    // A Viewpoint was chosen.
    QMap<QString, Viewpoint>::iterator itr = mViewpoints.find( pName );
    if ( itr != mViewpoints.end() )
    {
        Viewpoint viewpoint = itr.value();
        ui->viewer->getCameraManipulator()->setByMatrix( viewpoint.matrix() );
    }
}

void SceneWindow::on_actionPrevious_Viewpoint_triggered()
{
    // Goes to previous viewpoint
    int index = mViewpointsComboBox->currentIndex();
    --index;
    if ( index < 0 )
    {
        index = mViewpointsComboBox->count() - 1;
    }
    mViewpointsComboBox->setCurrentIndex(index);
}

void SceneWindow::on_actionNext_Viewpoint_triggered()
{
    // Goes to next viewpoint
    int index = mViewpointsComboBox->currentIndex();
    ++index;
    if ( index >= mViewpointsComboBox->count() )
    {
        index = 0;
    }
    mViewpointsComboBox->setCurrentIndex(index);
}

void SceneWindow::on_actionReturn_to_Viewpoint_triggered()
{
    viewpointChangedSlot( mViewpointsComboBox->currentText() );
}

void SceneWindow::on_actionCreate_Viewpoint_triggered()
{
    bool ok;
    QString name = QInputDialog::getText(this, tr("Create new point"), tr("Name:"),
        QLineEdit::Normal, "", &ok );

    if ( ok )	// OK button was clicked
    {
        if ( name.isEmpty() )
        {
            // The name must not be empty!
            QMessageBox::critical(this, tr("Viewpoint not created"),
                "You have to enter the name of viewpoint.",
                QMessageBox::Ok);
        }
        else
        {
            if ( mViewpoints.contains( name ) )
            {
                // The name must be unique!
                QMessageBox::critical(this, tr("Viewpoint not created"),
                    "Viewpoint already exists. Please pick an unique name.",
                    QMessageBox::Ok);
            }
            else
            {
                // Creates a new viewpoint.
                insertViewpoint( Viewpoint( name, ui->viewer->getCameraManipulator()->getMatrix()) );
                mViewpointsComboBox->setCurrentIndex( mViewpointsComboBox->findText(name) );
            }
        }
    }
}

void SceneWindow::on_actionRemove_Current_Viewpoint_triggered()
{
    // Removes current viewpoint.
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, tr("Confirm viewpoint removal"),
        "Do you want to remove the current viewpoint?",
        QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
    if (reply == QMessageBox::Yes)
    {
        QString text = mViewpointsComboBox->currentText();
        int index = mViewpointsComboBox->currentIndex();
        mViewpointsComboBox->removeItem( index );
        mViewpoints.remove( text );
        actionViewpointEnabled();
    }
}

void SceneWindow::on_actionBind_Parameters_triggered()
{
    mBindDialog->show();
}

void SceneWindow::readNodeFile(const QString &pFilename)
{
    if ( !pFilename.isEmpty() )
    {
        QFileInfo fileInfo( pFilename );
        if ( !fileInfo.exists() )
        {
            emit warningMessage( QString("Warning: Failed opening file: '%1' does not exist.").arg(pFilename) );
            return;
        }

        osgDB::ReaderWriter::ReadResult rr = osgDB::Registry::instance()->readNode(pFilename.toStdString(),
                                                                                   osgDB::Registry::instance()->getOptions());
        if ( rr.validNode() )
        {
            osg::ref_ptr<osg::Node> loadedModel = rr.takeNode();

            clear();    // Clear

            ui->viewer->setSceneData( loadedModel );
            insertViewpoint( Viewpoint( "Default", ui->viewer->getCameraManipulator()->getMatrix()) );

            mBindDialog->setSceneData( loadedModel );

            QFileInfo fileInfo( pFilename );
            setWindowTitle( fileInfo.fileName() );

            mSceneFilename = pFilename;

            enableActions( true );
        }

        if ( rr.error() )
        {
            emit warningMessage( QString::fromStdString(rr.message()) );
        }

        if ( rr.notEnoughMemory() )
        {
            emit warningMessage( QString("Warning: Not enough memory to load file %1.").arg( pFilename ) );
        }
    }
}

void SceneWindow::insertViewpoint( const Viewpoint& pViewpoint )
{
    if ( !mViewpoints.contains( pViewpoint.name() ) )
    {
        mViewpoints.insert( pViewpoint.name(), pViewpoint );
        mViewpointsComboBox->addItem( pViewpoint.name() );

        actionViewpointEnabled();
    }
}

void SceneWindow::actionViewpointEnabled()
{
    ui->actionNext_Viewpoint->setEnabled( mViewpoints.size() > 1 );
    ui->actionPrevious_Viewpoint->setEnabled( mViewpoints.size() > 1 );
    ui->actionRemove_Current_Viewpoint->setEnabled( mViewpoints.size() );
}

void SceneWindow::enableActions(bool pEnable)
{
    ui->actionPrevious_Viewpoint->setEnabled( mViewpoints.size() > 1 );
    ui->actionNext_Viewpoint->setEnabled( mViewpoints.size() > 1 );
    mViewpointsComboBox->setEnabled( pEnable );
    ui->actionReturn_to_Viewpoint->setEnabled( pEnable );
    ui->actionCreate_Viewpoint->setEnabled( pEnable );
    ui->actionRemove_Current_Viewpoint->setEnabled( mViewpoints.size() );
    ui->actionBind_Parameters->setEnabled( pEnable );
}

void SceneWindow::clear()
{
    mSceneFilename = "";
    mViewpointsComboBox->clear();
    mViewpoints.clear();
    mBindDialog->clear();
}

