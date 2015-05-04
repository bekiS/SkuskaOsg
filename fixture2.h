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
    osg::ref_ptr<osg::MatrixTransform> getFixture(){ return _transG; }
    osg::ref_ptr<osg::Drawable> getDrawable() {return _pyramidGeode->getDrawable(0); }
//    osg::ref_ptr<osg::Geode> getPyramid(){ return _pyramidGeode; }
    void changeColor(osg::Vec3 colorValue, bool overwrite = 1 );
    void changeOpacity( float opacityValue, bool overwrite = 1 );
    void setDraggerGVisibility(bool visible);
    void setDraggerRVisibility(bool visible);
    osg::Vec4 getColor()       const { return _colors->operator [](0); }
    osg::Vec4 getPosition()    const { return osg::Vec4(_transG->getMatrix().getTrans(), 1.0); }
    osg::Vec4 getAttenuation() const { return osg::Vec4(.1, 0.0, 0.0, 1.0); }
    osg::Vec4 getSpot_dir()    const;
    osg::Vec4 getSpot_param()  const { return osg::Vec4(0, 1.15, 0.0, 1.0); }

private:
    osg::ref_ptr<osg::Vec4Array> _colors;
    osg::ref_ptr<osg::Geode> _pyramidGeode;

    osg::ref_ptr<osg::MatrixTransform> _transG;
    osg::ref_ptr<osg::MatrixTransform> _transR;
    osg::ref_ptr<osg::MatrixTransform> _transQLC;

    osg::ref_ptr<osgManipulator::TranslateAxisDragger> _draggerG;
    osg::ref_ptr<osgManipulator::TrackballDragger> _draggerR;
    bool _visibleG;
    bool _visibleR;

//    const int LIGHT_COUNT = %s;
//    const int LIGHT_SIZE = %s;
//    const int AMBIENT = 0; -bude mat len jedno vseobecne svetlo
//    const int DIFFUSE = 01; diff a spec su rovnake
//    const int SPECULAR = 0;
//    const int POSITION = 1;
//    const int ATTENUATION = 2;
//    //SPOT_PARAMS [ cos_spot_cutoff, spot_exponent, ignored, is_spot ]
//    const int SPOT_PARAMS = 3;
//    const int SPOT_DIR = 4;

//    osg::Vec4 _color; 0
    osg::Vec4 _position; //malo by sa zistit z polohy 1
//    osg::Vec4 _attenuation;2
    osg::Vec4 _spot_dir; //3
    osg::Vec4 _spot_param; //4
    float cos_spot_cutoff;
};

#endif // FIXTURE2_H
