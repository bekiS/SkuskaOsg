#ifndef COMMONFUNCITONS_H
#define COMMONFUNCITONS_H

#include <osgGA/GUIEventHandler>
#include <osgUtil/LineSegmentIntersector>

namespace osgCookBook
{

    class PickHandler : public osgGA::GUIEventHandler
    {
    public:
        virtual bool handle( const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa );
        virtual void doUserOperations( osgUtil::LineSegmentIntersector::Intersection& result, const osgGA::GUIEventAdapter& ea ) = 0;
    };

}
#endif // COMMONFUNCITONS_H
