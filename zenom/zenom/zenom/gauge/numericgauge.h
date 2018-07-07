#ifndef NUMERICGAUGE_H
#define NUMERICGAUGE_H

#include "abstractgauge.h"
#include <QLCDNumber>

class NumericGauge : public QLCDNumber, public AbstractGauge
{
	Q_OBJECT

public:
	NumericGauge(QWidget *pParent = 0);

	~NumericGauge();

	virtual GaugeType type();

	virtual void setValue( double pValue );

	virtual void saveSettings( QSettings& pSettings );

	virtual void loadSettings( QSettings& pSettings );

	virtual QWidget* asWidget();

	void setDecimals( int pPrecision );
	int decimals();

	void setDigitsColor( const QColor& pColor );
	QColor digitsColor();

	void setBackgroundColor( const QColor& pColor );
	QColor backgroundColor();

private:
	int mDecimals;
};

#endif // NUMERICGAUGE_H
