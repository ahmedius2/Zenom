#include "colorbutton.h"
#include <QColorDialog>


ColorButton::ColorButton( QWidget *pParent/*=0*/ )
	: QPushButton( pParent )
{
	connect(this, SIGNAL( clicked() ), SLOT( on_clicked() ));
    setColor( palette().color( QPalette::Button ) );
}

void ColorButton::on_clicked()
{
    QColor col = QColorDialog::getColor( color() );
	if (!col.isValid())
		return;

	setColor( col );
	emit colorChanged( col );
}

void ColorButton::setColor( const QColor& pColor )
{
    mColor = pColor;

    QColor lightColor = pColor.lighter( 125 );
    QColor darkColor = pColor.darker( 150 );
    QString buttonStyleSheet;
    buttonStyleSheet = QString(
            "QPushButton {"
            "background-color: %1;"
            "border-width: 2px;"
            "border-color: %2;"
            "border-style: solid;"
            "border-radius: 5;"
            "}"
            "QPushButton:hover {"
            "background-color: %3;"
            "}"
            "QPushButton:pressed {"
            "background-color: %4;"
            "}").arg( pColor.name() ).arg( darkColor.name() ).arg( lightColor.name() ).arg( pColor.name() );

    setStyleSheet( buttonStyleSheet );
}

QColor ColorButton::color()
{
    return mColor;
}
