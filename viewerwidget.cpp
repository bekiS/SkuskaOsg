#include "viewerwidget.h"

#include <QVBoxLayout>

#include <osgGA/TrackballManipulator>
#include "commonfuncitons.h"
#include <osgViewer/ViewerEventHandlers>

class SetShapeColorHandler : public osgCookBook::PickHandler
{
public:
    SetShapeColorHandler( VizualSceny2 * scene ) : _scene( scene ) {}

    virtual void doUserOperations( osgUtil::LineSegmentIntersector::Intersection& result,
                                   const osgGA::GUIEventAdapter& ea)
    {
        osg::Drawable* shape = dynamic_cast<osg::Drawable*>( result.drawable.get() );
        if ( shape ){
           if(ea.getModKeyMask()&osgGA::GUIEventAdapter::MODKEY_SHIFT)
           {
               _scene->setToBeRotatable(shape);
           }
           else //in case both shift and ctrl or only ctrl
            _scene->setToBeMovable(shape);
        }
    }

private:
    VizualSceny2 *_scene;
};


ViewerWidget::ViewerWidget(osgQt::GraphicsWindowQt* gw, VizualSceny2 *scene )
    : QWidget()
    , _scene(scene)
    , _pipe(scene->get(), scene->getLightSource())
{

    const osg::GraphicsContext::Traits* traits = gw->getTraits();
    osg::Camera* camera = _viewer.getCamera();
    camera->setGraphicsContext( gw );
    camera->setClearColor( osg::Vec4(0.2, 0.2, 0.6, 1.0) );
    camera->setViewport( new osg::Viewport(0, 0, traits->width, traits->height) );
    camera->setProjectionMatrixAsPerspective(
        30.0f, static_cast<double>(traits->width)/static_cast<double>(traits->height), 1.0f, 1000.0f );
    camera->setComputeNearFarMode(osg::CullSettings::DO_NOT_COMPUTE_NEAR_FAR);
    _viewer.setSceneData( _pipe._graph.get() );
//    _viewer.addEventHandler( new osgViewer::StatsHandler );
    _viewer.addEventHandler( new SetShapeColorHandler( _scene ) );
    _viewer.setCameraManipulator( new osgGA::TrackballManipulator );
    _viewer.setThreadingModel( osgViewer::Viewer::SingleThreaded );

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget( gw->getGLWidget() );
    setLayout( layout );

    connect( &_timer, SIGNAL(timeout()), this, SLOT(update()) );
    _timer.start( 40 );
}



