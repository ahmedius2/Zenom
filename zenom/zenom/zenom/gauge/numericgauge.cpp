#include "numericgauge.h"

NumericGauge::NumericGauge(QWidget *pParent)
	: QLCDNumber(pParent)
{
	// LCD
	setFrameShadow( QFrame::Plain );
	setSegmentStyle( QLCDNumber::Flat );
	setLineWidth(0);
	setAutoFillBackground( true );

	setBackgroundColor( QColor(150, 220, 120) );
	setDigitsColor( QColor(0, 0, 0) );
	setDecimals( 1 );
	setValue( 0 );
}

NumericGauge::~NumericGauge()
{

}

GaugeType NumericGauge::type()
{
	return NUMERIC_GAUGE;
}

void NumericGauge::setValue( double pValue )
{
	QString str;
	if ( mode() == QLCDNumber::Hex )
		str = QString::number( qRound(pValue), 16);
	else if ( mode() == QLCDNumber::Dec )
		str = QString::number(pValue, 'f', decimals());
	else if ( mode() == QLCDNumber::Oct )
		str = QString::number( qRound(pValue), 8);
	else if ( mode() == QLCDNumber::Bin )
		str = QString::number( qRound(pValue), 2);
	
	setDigitCount( str.length() );
	display( str );
}

void NumericGauge::saveSettings( QSettings& pSettings )
{
	// General
	pSettings.setValue("value", value());
	pSettings.setValue("decimals", decimals());
	pSettings.setValue("mode", mode());

	// Color
	pSettings.setValue("digitsColor", digitsColor().rgb());
	pSettings.setValue("backgroundColor", backgroundColor().rgb());

	AbstractGauge::saveSettings( pSettings );
}

void NumericGauge::loadSettings( QSettings& pSettings )
{
	// Needle
	setValue( pSettings.value("value", 0).toDouble() );
	setDecimals( pSettings.value("decimals", 1).toInt() );
	setMode( (QLCDNumber::Mode) pSettings.value("mode", QLCDNumber::Dec).toInt() );

	// Color
	setDigitsColor( pSettings.value("digitsColor").toUInt() );
	setBackgroundColor( pSettings.value("backgroundColor").toUInt() );

	AbstractGauge::loadSettings( pSettings );
}

QWidget* NumericGauge::asWidget()
{
	return this;
}

void NumericGauge::setDecimals( int pPrecision )
{
	mDecimals = pPrecision;
	setValue( value() );
}

int NumericGauge::decimals()
{
	return mDecimals;
}

void NumericGauge::setDigitsColor( const QColor& pColor )
{	
	QPalette& p = (QPalette&)palette();
	p.setColor(QPalette::All, QPalette::WindowText, pColor);
}

QColor NumericGauge::digitsColor()
{
	return palette().color( QPalette::WindowText );
}

void NumericGauge::setBackgroundColor( const QColor& pColor )
{
	QPalette& p = (QPalette&)palette();
	p.setColor(QPalette::All, QPalette::Window, pColor);
}

QColor NumericGauge::backgroundColor()
{
	return palette().color( QPalette::Window );
}
