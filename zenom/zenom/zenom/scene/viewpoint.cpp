#include "viewpoint.h"

Viewpoint::Viewpoint()
{

}

Viewpoint::Viewpoint( const QString& pName, const osg::Matrixd& pMatrix )
	: mName( pName ), mMatrix( pMatrix )
{

}

void Viewpoint::saveSettings( QSettings& pSettings )
{
	pSettings.setValue( "name", mName );

	for( int i = 0; i < 4; ++i )
	{
		for( int j = 0; j < 4; ++j )
		{
			pSettings.setValue( QString("matrix[%1][%2]").arg(i).arg(j), mMatrix(i,j) );
		}
	}
}

void Viewpoint::loadSettings( QSettings& pSettings )
{
	mName = pSettings.value("name").toString();
	mMatrix.set( pSettings.value("matrix[0][0]").toDouble(), pSettings.value("matrix[0][1]").toDouble(),
		pSettings.value("matrix[0][2]").toDouble(),	pSettings.value("matrix[0][3]").toDouble(),
		pSettings.value("matrix[1][0]").toDouble(),	pSettings.value("matrix[1][1]").toDouble(),
		pSettings.value("matrix[1][2]").toDouble(),	pSettings.value("matrix[1][3]").toDouble(),
		pSettings.value("matrix[2][0]").toDouble(),	pSettings.value("matrix[2][1]").toDouble(),
		pSettings.value("matrix[2][2]").toDouble(),	pSettings.value("matrix[2][3]").toDouble(),
		pSettings.value("matrix[3][0]").toDouble(),	pSettings.value("matrix[3][1]").toDouble(),
		pSettings.value("matrix[3][2]").toDouble(),	pSettings.value("matrix[3][3]").toDouble() );
}