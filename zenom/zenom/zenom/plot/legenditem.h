#ifndef LEGENDITEM_H
#define LEGENDITEM_H

#include <QWidget>

namespace Ui {
class LegendItem;
}

class LegendItem : public QWidget
{
    Q_OBJECT
    
public:
    explicit LegendItem(QWidget *parent = 0);
    ~LegendItem();

    void setName( const QString& pName );

    void setColor( const QColor& pColor );

    void setSize( const int );

signals:
    void colorChanged( const QColor& );
    void removeRequest();
    void sizeChanged( int );
    
private:
    Ui::LegendItem *ui;
};

#endif // LEGENDITEM_H
