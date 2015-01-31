#ifndef STAGEGEODE_H
#define STAGEGEODE_H

#include <osg/Geometry>
#include <osg/Geode>

class stageGeode
{
public:
    stageGeode();
    osg::ref_ptr<osg::Geode> get() {return _stageGeode;}
    float getWidth() {return _width;}

private:
    osg::ref_ptr<osg::Geode> _stageGeode;
    float _width;
    float _height;
    float _depth;
};

#endif // STAGEGEODE_H
