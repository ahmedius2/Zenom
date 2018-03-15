#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <QObject>
#include "scenewindow.h"

class SceneManager : public QObject
{
	Q_OBJECT

public:
	SceneManager(QWidget *pParent);

    ~SceneManager();
	
	void saveSettings( QSettings& pSettings );

	void loadSettings( QSettings& pSettings );

	void tick();

	void clear();

public slots:
    SceneWindow* createScene();

signals:
    void warningMessage( const QString& pText );

private slots:
    void sceneWindowDestroyed( SceneWindow* pSceneWindow );

private:
    QVector<SceneWindow*> mSceneList;
};

#endif // SCENEMANAGER_H
