#ifndef RADIALGAUGE_H
#define RADIALGAUGE_H

#include <qwt_dial.h>
#include "abstractgauge.h"

class RadialGauge : public QwtDial, public AbstractGauge
{
	Q_OBJECT

public:
	enum NeedleType
	{
		SIMPLE_NEEDLE,
		MAGNET_NEEDLE,
		WIND_ARROW_NEEDLE
	};

	enum NeedleStyle
	{
		NEEDLE_STYLE_1,
		NEEDLE_STYLE_2,
	};

	RadialGauge(QWidget *pParent = 0);

	~RadialGauge();

	virtual GaugeType type();

	virtual void setValue( double pValue );

	virtual void saveSettings( QSettings& pSettings );

	virtual void loadSettings( QSettings& pSettings );

	virtual QWidget* asWidget();

	// Ticks
	virtual void setScale( int maxMajIntv, int maxMinIntv, double step = 0.0 );
	int scaleMaxMajor();
	int scaleMaxMinor();
	
	// Needle
	void setNeedle( NeedleType pNeedleType, NeedleStyle pNeedleStyle, QColor c1, QColor c2 );
	NeedleType needleType();
	NeedleStyle needleStyle();
	QColor needleColor1();
	QColor needleColor2();

	// Color
	void setTextColor( const QColor& pColor );
	QColor textColor();
	void setBackgroundColor( const QColor& pColor );
	QColor backgroundColor();

private:
	// Ticks
	int mScaleMaxMajor;
	int mScaleMaxMinor;

	// Needle
	NeedleType mNeedleType;
	NeedleStyle mNeedleStyle;
	QColor mNeedleColor1;
	QColor mNeedleColor2;
};

#endif // RADIALGAUGE_H
