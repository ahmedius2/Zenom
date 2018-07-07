#include "radialgauge.h"
#include <qwt_dial_needle.h>

RadialGauge::RadialGauge(QWidget *pParent)
	: QwtDial(pParent)
{
	setReadOnly( true );
	setOrigin( 135.0 );
	setScaleArc( 0.0, 270.0 );
    setRange( 0.0, 120.0 );
	setScale( 12, 4 );
	setNeedle( SIMPLE_NEEDLE, NEEDLE_STYLE_1, Qt::red, QColor( Qt::gray ).light( 130 ) );
	setTextColor( Qt::white );
	setBackgroundColor( QColor( Qt::darkGray ).dark( 150 ) );
    setLineWidth( 4 );
	setFrameShadow( QwtDial::Sunken );
}

RadialGauge::~RadialGauge()
{

}

GaugeType RadialGauge::type()
{
	return RADIAL_GAUGE;
}

void RadialGauge::setValue( double pValue )
{
	QwtDial::setValue( pValue );
}

void RadialGauge::saveSettings( QSettings& pSettings )
{
	// Scale
	pSettings.setValue("direction", direction());
	pSettings.setValue("minValue", minValue());
	pSettings.setValue("maxValue", maxValue());
	pSettings.setValue("origin", origin());
	pSettings.setValue("sweepAngle", maxScaleArc());

	// Ticks
	pSettings.setValue("scaleMaxMajor", scaleMaxMajor());
	pSettings.setValue("scaleMaxMinor", scaleMaxMinor());
	pSettings.setValue("labels", scaleDraw()->hasComponent( QwtAbstractScaleDraw::Labels ));
	pSettings.setValue("font", font().family());
	pSettings.setValue("fontSize", font().pointSize());

	// Needle
	pSettings.setValue("value", value());
	pSettings.setValue("needleType", needleType());
	pSettings.setValue("needleStyle", needleStyle());
	pSettings.setValue("needleColor1", needleColor1().rgb());
	pSettings.setValue("needleColor2", needleColor2().rgb());

	// Color
	pSettings.setValue("textColor", textColor().rgb());
	pSettings.setValue("backgroundColor", backgroundColor().rgb());

	AbstractGauge::saveSettings( pSettings );
}

void RadialGauge::loadSettings( QSettings& pSettings )
{
	// Scale
	setDirection( (QwtDial::Direction) pSettings.value("direction", QwtDial::Clockwise).toInt() );
	setRange( pSettings.value("minValue", 0).toDouble(), pSettings.value("maxValue", 240).toDouble() );
	setOrigin( pSettings.value("origin", 135).toDouble() );
	setScaleArc( 0, pSettings.value("sweepAngle", 270).toDouble() );

	// Ticks
	setScale( pSettings.value("scaleMaxMajor", 12).toDouble(), pSettings.value("scaleMaxMinor", 4).toDouble() );
	scaleDraw()->enableComponent( QwtAbstractScaleDraw::Labels, pSettings.value("labels", true).toBool() );
	setFont( QFont(	pSettings.value("font").toString(), pSettings.value("fontSize", 8).toDouble()) );

	// Needle
	setValue( pSettings.value("value", 0).toDouble() );
	RadialGauge::NeedleType needleType = (RadialGauge::NeedleType)pSettings.value("needleType", RadialGauge::SIMPLE_NEEDLE).toInt();
	RadialGauge::NeedleStyle needleStyle = (RadialGauge::NeedleStyle)pSettings.value("needleStyle", RadialGauge::NEEDLE_STYLE_1).toInt();
	QColor c1( pSettings.value("needleColor1").toUInt() );
	QColor c2( pSettings.value("needleColor2").toUInt() );
	setNeedle( needleType, needleStyle, c1, c2 );

	// Color
	setTextColor( pSettings.value("textColor").toUInt() );
	setBackgroundColor( pSettings.value("backgroundColor").toUInt() );

	AbstractGauge::loadSettings( pSettings );
}

QWidget* RadialGauge::asWidget()
{
	return this;
}

void RadialGauge::setNeedle( NeedleType pNeedleType, NeedleStyle pNeedleStyle, QColor c1, QColor c2 )
{
	mNeedleType = pNeedleType;
	mNeedleStyle = pNeedleStyle;
	mNeedleColor1 = c1;
	mNeedleColor2 = c2;

	switch ( pNeedleType )
	{
	case MAGNET_NEEDLE:
		{
			QwtCompassMagnetNeedle::Style style = pNeedleStyle == NEEDLE_STYLE_1 ? 
				QwtCompassMagnetNeedle::ThinStyle : QwtCompassMagnetNeedle::TriangleStyle;
			QwtDial::setNeedle(	new QwtCompassMagnetNeedle( style, c1, c2 ) );
		}
		break;

	case WIND_ARROW_NEEDLE:
		{
			QwtCompassWindArrow::Style style = pNeedleStyle == NEEDLE_STYLE_1 ? 
				QwtCompassWindArrow::Style1 : QwtCompassWindArrow::Style2;
			QwtDial::setNeedle(	new QwtCompassWindArrow( style, c1, c2 ) );
		}
		break;

	default:	// Simple Needle
		{
			QwtDialSimpleNeedle::Style style = pNeedleStyle == NEEDLE_STYLE_1 ? 
				QwtDialSimpleNeedle::Arrow : QwtDialSimpleNeedle::Ray;
			QwtDial::setNeedle( new QwtDialSimpleNeedle( style, true, c1, c2 ) );
		}
		break;
	}
}

RadialGauge::NeedleType RadialGauge::needleType()
{
	return mNeedleType;
}

RadialGauge::NeedleStyle RadialGauge::needleStyle()
{
	return mNeedleStyle;
}

QColor RadialGauge::needleColor1()
{
	return mNeedleColor1;
}

QColor RadialGauge::needleColor2()
{
	return mNeedleColor2;
}

void RadialGauge::setTextColor( const QColor& pColor )
{	
	QPalette& p = (QPalette&)palette();
	p.setColor(QPalette::All, QPalette::Text, pColor);
}

QColor RadialGauge::textColor()
{
	return palette().color( QPalette::Text );
}

void RadialGauge::setBackgroundColor( const QColor& pColor )
{
	QPalette& p = (QPalette&)palette();
	p.setColor( QPalette::Base, pColor );
	p.setColor( QPalette::Window, pColor.dark( 150 ) );
	p.setColor( QPalette::Mid, pColor.dark( 110 ) );
	p.setColor( QPalette::Light, pColor.light( 170 ) );
	p.setColor( QPalette::Dark, pColor.dark( 170 ) );
	p.setColor( QPalette::WindowText, pColor );
}

QColor RadialGauge::backgroundColor()
{
	return palette().color( QPalette::Base );
}

void RadialGauge::setScale( int maxMajIntv, int maxMinIntv, double step /*= 0.0 */ )
{
	mScaleMaxMajor = maxMajIntv;
	mScaleMaxMinor = maxMinIntv;
	QwtDial::setScale( maxMajIntv, maxMinIntv, step );
}

int RadialGauge::scaleMaxMajor()
{
	return mScaleMaxMajor;
}

int RadialGauge::scaleMaxMinor()
{
	return mScaleMaxMinor;
}
