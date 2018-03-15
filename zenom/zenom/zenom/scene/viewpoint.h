#ifndef VIEWPOINT_H
#define VIEWPOINT_H


#include <QSettings>
#include <osg/Matrixd>

class Viewpoint
{

public:
	Viewpoint();
	Viewpoint( const QString& pName, const osg::Matrixd& pMatrix );

	QString name() const { return mName; }
	void setName(QString val) { mName = val; }

	osg::Matrixd matrix() const { return mMatrix; }
	void setMatrix(osg::Matrixd val) { mMatrix = val; }

	void saveSettings( QSettings& pSettings );
	void loadSettings( QSettings& pSettings );

private:
	QString mName;
	osg::Matrixd mMatrix;
};

#endif // VIEWPOINT_H
