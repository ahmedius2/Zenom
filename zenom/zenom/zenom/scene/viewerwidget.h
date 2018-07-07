#ifndef VIEWERWIDGET_H
#define VIEWERWIDGET_H

#include <QWidget>
#include <osgViewer/Viewer>

class ViewerWidget : public QWidget, public osgViewer::Viewer
{
    Q_OBJECT
public:
    explicit ViewerWidget(QWidget *parent = 0);

protected:
    virtual void paintEvent( QPaintEvent* );
    
signals:
    
public slots:
    
};

#endif // VIEWERWIDGET_H
