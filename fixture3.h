#ifndef FIXTURE3_H
#define FIXTURE3_H

#include <osg/Geode>
#include <osg/Geometry>
#include <osgManipulator/Translate2DDragger>
#include <osgManipulator/TrackballDragger>

class Fixture3
{
public:
    Fixture3();
    osg::ref_ptr<osg::MatrixTransform> getFixture(){ return _transG; }
    osg::ref_ptr<osg::Drawable> getDrawable() {return _pyramidGeode->getDrawable(0); }
//    osg::ref_ptr<osg::Geode> getPyramid(){ return _pyramidGeode; }
    void changeColor(osg::Vec3 colorValue, bool overwrite = 1 );
    void changeOpacity( float opacityValue, bool overwrite = 1 );
    void setDraggerGVisibility(bool visible);
    void setDraggerRVisibility(bool visible);


private:
    osg::ref_ptr<osg::Vec4Array> _colors;
    osg::ref_ptr<osg::Geode> _pyramidGeode;

    osg::ref_ptr<osg::MatrixTransform> _transG;
    osg::ref_ptr<osg::MatrixTransform> _transR;
    osg::ref_ptr<osg::MatrixTransform> _transQLC;

    osg::ref_ptr<osgManipulator::Translate2DDragger> _draggerG;
    osg::ref_ptr<osgManipulator::TrackballDragger> _draggerR;
    bool _visibleG;
    bool _visibleR;
};

#endif // FIXTURE3_H
