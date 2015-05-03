#ifndef VIZUALSCENY2_H
#define VIZUALSCENY2_H

#include <osg/MatrixTransform>
#include <osg/LightSource>
#include <osg/Geode>
#include <qlist.h>

#include "commonfuncitons.h"
#include "fixture2.h"


class VizualSceny2
{
public:
    VizualSceny2();
    osg::ref_ptr<osg::Group> get(){ return _root; }
    QList<Fixture2> getFixtures(){ return _fixtures; }
    osg::ref_ptr<osg::LightSource> getLightSource(){ return _light; }


    void setToBeMovable(osg::Drawable *shape);
    void setToBeRotatable(osg::Drawable *shape);
    void addFixtureChild();

    osg::ref_ptr<osg::LightSource> createLight(const osg::Vec3 &pos);

private:
    osg::ref_ptr<osg::Group> _root;
    QList<Fixture2> _fixtures;
    osg::ref_ptr<osg::LightSource> _light;


};

#endif // VIZUALSCENY2_H
