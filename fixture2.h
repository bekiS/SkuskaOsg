#ifndef FIXTURE2_H
#define FIXTURE2_H

#include <osg/Geode>
#include <osg/Geometry>
#include <osgManipulator/TranslateAxisDragger>
#include <osgManipulator/TrackballDragger>

class Fixture2
{
public:
    Fixture2();
    osg::ref_ptr<osg::Group> getFixture(){ return _fixture; }
    osg::ref_ptr<osg::Geode> getPyramid(){ return _pyramidGeode; }
    void changeColor(osg::Vec3 colorValue, bool overwrite = 1 );
    void changeOpacity( float opacityValue, bool overwrite = 1 );
    void setDraggerGVisibility(bool visible);
    void setDraggerRVisibility(bool visible);

private:
    osg::ref_ptr<osg::Vec4Array> _colors;
    osg::ref_ptr<osg::Geode> _pyramidGeode;
    osg::ref_ptr<osg::Group> _fixture;

    osg::ref_ptr<osg::MatrixTransform> _transG;
    osg::ref_ptr<osg::MatrixTransform> _transR;
    osg::ref_ptr<osg::MatrixTransform> _transQLC;

    osg::ref_ptr<osgManipulator::TranslateAxisDragger> _draggerG;
    osg::ref_ptr<osgManipulator::TrackballDragger> _draggerR;
    bool _visibleG;
    bool _visibleR;
};

#endif // FIXTURE2_H
