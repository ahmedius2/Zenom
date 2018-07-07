#ifndef SCENEWINDOW_H
#define SCENEWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include <QComboBox>
#include <QMap>

#include "binddialog.h"
#include "viewpoint.h"

namespace Ui {
class SceneWindow;
}

class SceneWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit SceneWindow(QWidget *parent = 0);

    ~SceneWindow();

    void tick();

    void saveSettings( QSettings& pSettings );

    void loadSettings( QSettings& pSettings );

signals:
    void closed( SceneWindow* ) ;

    void warningMessage( const QString& pText );

protected:
    virtual void closeEvent(QCloseEvent *pEvent);

private slots:
    // File Menu
    void on_actionOpen_triggered();
    void on_actionClose_triggered();

    // View Menu
    void viewpointChangedSlot( const QString& pName );
    void on_actionPrevious_Viewpoint_triggered();
    void on_actionNext_Viewpoint_triggered();
    void on_actionReturn_to_Viewpoint_triggered();
    void on_actionCreate_Viewpoint_triggered();
    void on_actionRemove_Current_Viewpoint_triggered();

    // Simulation Munu
    void on_actionBind_Parameters_triggered();
    
private:
    Ui::SceneWindow *ui;
    QComboBox* mViewpointsComboBox;
    BindDialog* mBindDialog;
    QString mSceneFilename;

    void readNodeFile( const QString& pFilename );

    void insertViewpoint( const Viewpoint& pViewpoint );
    void actionViewpointEnabled();
    QMap<QString, Viewpoint> mViewpoints;

    void enableActions(bool pEnable);
    void clear();
};

#endif // SCENEWINDOW_H
