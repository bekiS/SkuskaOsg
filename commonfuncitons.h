#ifndef COMMONFUNCITONS_H
#define COMMONFUNCITONS_H

#include <osg/AnimationPath>
#include <osg/Texture>
#include <osg/Camera>
#include <osgGA/GUIEventHandler>
#include <osgText/Text>
#include <osgUtil/LineSegmentIntersector>

namespace osgCookBook
{

//    osg::AnimationPathCallback* createAnimationPathCallback( float radius, float time );
//    osg::Camera* createRTTCamera( osg::Camera::BufferComponent buffer, osg::Texture* tex, bool isAbsolute=false );
//    osg::Camera* createHUDCamera( double left, double right, double bottom, double top );
//    osg::Geode* createScreenQuad( float width, float height, float scale=1.0f );
//    extern osgText::Text* createText( const osg::Vec3& pos, const std::string& content, float size );

//    float randomValue( float min, float max );
//    osg::Vec3 randomVector( float min, float max );
//    osg::Matrix randomMatrix( float min, float max );

    class PickHandler : public osgGA::GUIEventHandler
    {
    public:
        virtual bool handle( const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa );
        virtual void doUserOperations( osgUtil::LineSegmentIntersector::Intersection& result, const osgGA::GUIEventAdapter& ea ) = 0;
    };
    osg::Group *addDraggerToScene( osg::Node* scene );

}
#endif // COMMONFUNCITONS_H
