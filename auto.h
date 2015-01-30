#ifndef AUTO_H
#define AUTO_H

#include <osg/ShapeDrawable>
#include <osg/AnimationPath>
#include <osg/MatrixTransform>
//#include <osgDB/ReadFile>
#include <osg/Geode>

class Auto
{
public:
    Auto();
    osg::ref_ptr<osg::Group> get(){return _root;}
private:
    osg::ref_ptr<osg::Group> _root;
    osg::MatrixTransform *createTransformNodeAuto( osg::Drawable* shape, const osg::Matrix& matrix );
    osg::AnimationPathCallback *createWheelAnimationAuto( const osg::Vec3& base );
};

#endif // AUTO_H
