#ifndef FLOORGEODE_H
#define FLOORGEODE_H

#include <osg/Geometry>
#include <osg/Geode>

class floorGeode
{
public:
    floorGeode();
    osg::ref_ptr<osg::Geode> get(){return _floorGeode;}

private:
    osg::ref_ptr<osg::Geode> _floorGeode;
    float _radius;

};

#endif // FLOORGEODE_H
