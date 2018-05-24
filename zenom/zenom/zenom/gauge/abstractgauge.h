#ifndef ABSTRACTGAUGE_H
#define ABSTRACTGAUGE_H

#include <QString>
#include <QSettings>

enum GaugeType
{
	LINEAR_GAUGE,
	RADIAL_GAUGE,
	NUMERIC_GAUGE
};

class AbstractGauge
{
public:
	AbstractGauge();

	virtual ~AbstractGauge();

	virtual GaugeType type() = 0;

	virtual void setValue( double pValue ) = 0;
	
	virtual void saveSettings( QSettings& pSettings );

	virtual void loadSettings( QSettings& pSettings );

	virtual QWidget* asWidget() = 0;

	QString title();

	void setTitle( const QString& pTitle );

private:
	QString mTitle;
};

#endif // ABSTRACTGAUGE_H
