#include "viewerwidget.h"

#include <QVBoxLayout>

#include <osgGA/TrackballManipulator>
#include "commonfuncitons.h"
#include <osg/ShapeDrawable>
#include "commonfuncitons.h"
#include <osg/ShapeDrawable>
#include <osgViewer/ViewerEventHandlers>

class SetShapeColorHandler : public osgCookBook::PickHandler
{
public:
    SetShapeColorHandler( vizualSceny * scene ) : _scene( scene ) {}

    virtual void doUserOperations( osgUtil::LineSegmentIntersector::Intersection& result )
    {
        osg::Drawable* shape = dynamic_cast<osg::Drawable*>( result.drawable.get() );
        if ( shape )
            _scene->doUserOperation(shape);
    }

private:
    vizualSceny *_scene;
};


ViewerWidget::ViewerWidget(osgQt::GraphicsWindowQt* gw, vizualSceny* scene )
    : QWidget()
    , _scene(scene)
{
    const osg::GraphicsContext::Traits* traits = gw->getTraits();
    osg::Camera* camera = _viewer.getCamera();
    camera->setGraphicsContext( gw );
    camera->setClearColor( osg::Vec4(0.2, 0.2, 0.6, 1.0) );
    camera->setViewport( new osg::Viewport(0, 0, traits->width, traits->height) );
    camera->setProjectionMatrixAsPerspective(
        30.0f, static_cast<double>(traits->width)/static_cast<double>(traits->height), 1.0f, 10000.0f );

    _viewer.setSceneData( scene->get() );
    _viewer.addEventHandler( new osgViewer::StatsHandler );
    _viewer.addEventHandler( new SetShapeColorHandler( _scene ) );
    _viewer.setCameraManipulator( new osgGA::TrackballManipulator );
    _viewer.setThreadingModel( osgViewer::Viewer::SingleThreaded );

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget( gw->getGLWidget() );
    setLayout( layout );

    connect( &_timer, SIGNAL(timeout()), this, SLOT(update()) );
    _timer.start( 40 );
}

