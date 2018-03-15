#include "scenemanager.h"

SceneManager::SceneManager(QWidget *pParent)
	: QObject(pParent)
{

}

SceneManager::~SceneManager()
{

}

void SceneManager::saveSettings( QSettings& pSettings )
{
	pSettings.beginGroup("Scenes");
	pSettings.setValue("size", mSceneList.size());
	for ( int i = 0; i < mSceneList.size(); ++i )
	{
		pSettings.beginGroup( QString("Scene") + QString::number(i) );
		mSceneList[i]->saveSettings(pSettings);
		pSettings.endGroup();
	}
	pSettings.endGroup();
}

void SceneManager::loadSettings( QSettings& pSettings )
{
	pSettings.beginGroup("Scenes");
	int size = pSettings.value("size", 0).toInt();
	for ( int i = 0; i < size; ++i )
	{
		pSettings.beginGroup( QString("Scene") + QString::number(i) );
        SceneWindow* scene = createScene();
		scene->loadSettings(pSettings);
		pSettings.endGroup();
	}
	pSettings.endGroup();
}

void SceneManager::tick()
{
	for ( int i = 0; i < mSceneList.size(); ++i )
	{
		mSceneList[i]->tick();
	}
}

void SceneManager::clear()
{
	for ( int i = 0; i < mSceneList.size(); ++i )
	{
        mSceneList[i]->disconnect();
		delete mSceneList[i];
	}
	mSceneList.clear();
}

SceneWindow* SceneManager::createScene()
{
    SceneWindow* sceneWindow = new SceneWindow( static_cast<QWidget*>(parent()) );
    sceneWindow->show();
    connect( sceneWindow, SIGNAL(closed(SceneWindow*)), SLOT(sceneWindowDestroyed(SceneWindow*)) );
    connect( sceneWindow, SIGNAL(warningMessage(const QString&)), SIGNAL(warningMessage(const QString&)) );
    mSceneList.push_back( sceneWindow );
	
    return sceneWindow;
}

void SceneManager::sceneWindowDestroyed( SceneWindow* pSceneWindow )
{
    int index = mSceneList.indexOf( pSceneWindow );
    if ( index >= 0 )
        mSceneList.remove( index );
    pSceneWindow->deleteLater();
}
