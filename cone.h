#ifndef CONE_H
#define CONE_H

#include <osg/Geode>
#include <osg/Geometry>

class Cone
{
public:
    Cone();
    osg::ref_ptr<osg::Geode> get(){ return _pyramidGeode; }
    void changeColor(osg::Vec3 colorValue, bool overwrite = 1 );
    void changeOpacity( float opacityValue, bool overwrite = 1 );
private:
    osg::ref_ptr<osg::Group> _rootz; //preco musi byt group, ked sa nepouziva nikde?
    osg::ref_ptr<osg::Geode> _pyramidGeode;
   // osg::ref_ptr<osg::Geometry> _pyramidGeometry;
    osg::ref_ptr<osg::Vec4Array> _colors;

};

#endif // CONE_H
