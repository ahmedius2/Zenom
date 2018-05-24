#ifndef STATUSBAR_H
#define STATUSBAR_H

#include <QWidget>

namespace Ui {
class StatusBar;
}

class StatusBar : public QWidget
{
    Q_OBJECT
    
public:
    explicit StatusBar(QWidget *parent = 0);

    ~StatusBar();

    void setDuration( const double pDuration );

    void setOverruns( const double pOverruns );

    void setElapsedTime( const double pElapsedTime );
    
private:
    Ui::StatusBar *ui;
};

#endif // STATUSBAR_H
