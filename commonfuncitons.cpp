#include "commonfuncitons.h"

#include <osgViewer/View>
#include <osgUtil/Optimizer>

namespace osgCookBook
{



    bool PickHandler::handle( const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa )
    {
        if ( ea.getEventType()!=osgGA::GUIEventAdapter::RELEASE ||
             ea.getButton()!=osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON ||
             !((ea.getModKeyMask()&osgGA::GUIEventAdapter::MODKEY_CTRL) ||
             (ea.getModKeyMask()&osgGA::GUIEventAdapter::MODKEY_SHIFT)))
            return false;

        osgViewer::View* viewer = dynamic_cast<osgViewer::View*>(&aa);
        if ( viewer )
        {
            osg::ref_ptr<osgUtil::LineSegmentIntersector> intersector =
                new osgUtil::LineSegmentIntersector(osgUtil::Intersector::WINDOW, ea.getX(), ea.getY());
            osgUtil::IntersectionVisitor iv( intersector.get() );
            viewer->getCamera()->accept( iv );

            if ( intersector->containsIntersections() )
            {
                osgUtil::LineSegmentIntersector::Intersection result = *(intersector->getIntersections().begin());
                doUserOperations( result, ea );
            }
        }
        return false;
    }


}
