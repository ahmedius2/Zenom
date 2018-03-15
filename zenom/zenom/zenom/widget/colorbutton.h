#ifndef COLORBUTTON_H
#define COLORBUTTON_H

#include <QPushButton>

class ColorButton : public QPushButton
{
	Q_OBJECT
public:
	ColorButton(QWidget *pParent=0);

	void setColor( const QColor& pColor );

	QColor color();

signals:
	void colorChanged(const QColor&);

private slots:
	void on_clicked();

private:
    QColor mColor;
};

#endif // COLORBUTTON_H
