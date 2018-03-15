#include "viewerwidget.h"

#include <QtGui/QGridLayout>
#include <osgViewer/ViewerEventHandlers>
#include <osgGA/TrackballManipulator>
#include <osgQt/GraphicsWindowQt>


ViewerWidget::ViewerWidget(QWidget *parent) :
    QWidget(parent)
{
    setThreadingModel(osgViewer::Viewer::SingleThreaded);

    osg::DisplaySettings* ds = osg::DisplaySettings::instance().get();
    osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits;
    traits->windowName = "";
    traits->windowDecoration = false;
    traits->x = 0;
    traits->y = 0;
    traits->width = 600;
    traits->height = 400;
    traits->doubleBuffer = true;
    traits->alpha = ds->getMinimumNumAlphaBits();
    traits->stencil = ds->getMinimumNumStencilBits();
    traits->sampleBuffers = ds->getMultiSamples();
    traits->samples = ds->getNumMultiSamples();

    osg::ref_ptr<osgQt::GraphicsWindowQt> gw = new osgQt::GraphicsWindowQt(traits.get());

    osg::ref_ptr<osg::Camera> camera = new osg::Camera;
    camera->setGraphicsContext( gw );
    camera->setClearColor( osg::Vec4(0.2, 0.2, 0.6, 1.0) );
    camera->setViewport( new osg::Viewport(0, 0, traits->width, traits->height) );
    camera->setProjectionMatrixAsPerspective(
        30.0f, static_cast<double>(traits->width)/static_cast<double>(traits->height), 1.0f, 10000.0f );
    setCamera( camera );

    addEventHandler( new osgViewer::StatsHandler );
    setCameraManipulator( new osgGA::TrackballManipulator );

    QGridLayout* grid = new QGridLayout;
    grid->addWidget( gw->getGLWidget(), 0, 0 );
    setLayout( grid );
}

void ViewerWidget::paintEvent( QPaintEvent* )
{
    frame();
}
