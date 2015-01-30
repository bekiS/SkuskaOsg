#include "viewerwidget.h"

#include <QVBoxLayout>

#include <osgGA/TrackballManipulator>
#include <osgViewer/ViewerEventHandlers>
#include "commonfuncitons.h"
#include <osg/ShapeDrawable>
#include "cone.h"

class SetShapeColorHandler : public osgCookBook::PickHandler
{
    virtual void doUserOperations( osgUtil::LineSegmentIntersector::Intersection& result )
    {
        osg::ShapeDrawable* shape = dynamic_cast<osg::ShapeDrawable*>( result.drawable.get() );
        if ( shape ) shape->setColor( osg::Vec4(1.0f, 1.0f, 1.0f, 2.0f) - shape->getColor() );

//      osg::ShapeDrawable* shape = dynamic_cast<osg::ShapeDrawable*>( result.drawable.get() );
//      if ( shape ) shape->setColor(osg::Vec4(1.0f, 0.3f, 0.5f, 0.6f));
    }
};


ViewerWidget::ViewerWidget( osgQt::GraphicsWindowQt* gw, osg::Node* scene )
    : QWidget()
{
    const osg::GraphicsContext::Traits* traits = gw->getTraits();

    osg::Camera* camera = _viewer.getCamera();
    camera->setGraphicsContext( gw );
    camera->setClearColor( osg::Vec4(0.2, 0.2, 0.6, 1.0) );
    camera->setViewport( new osg::Viewport(0, 0, traits->width, traits->height) );
    camera->setProjectionMatrixAsPerspective(
        30.0f, static_cast<double>(traits->width)/static_cast<double>(traits->height), 1.0f, 10000.0f );

    _viewer.setSceneData( scene );
    _viewer.addEventHandler( new osgViewer::StatsHandler );
    _viewer.addEventHandler( new SetShapeColorHandler );
    _viewer.setCameraManipulator( new osgGA::TrackballManipulator );
    _viewer.setThreadingModel( osgViewer::Viewer::SingleThreaded );

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget( gw->getGLWidget() );
    setLayout( layout );

    connect( &_timer, SIGNAL(timeout()), this, SLOT(update()) );
    _timer.start( 40 );
}

