#include "abstractgauge.h"

AbstractGauge::AbstractGauge()
{

}

AbstractGauge::~AbstractGauge()
{

}

QString AbstractGauge::title()
{
	return mTitle;
}

void AbstractGauge::setTitle( const QString& pTitle )
{
	mTitle = pTitle;
}

void AbstractGauge::saveSettings( QSettings& pSettings )
{
	pSettings.setValue("title", title()); 
}

void AbstractGauge::loadSettings( QSettings& pSettings )
{
	setTitle( pSettings.value("title").toString() );
}