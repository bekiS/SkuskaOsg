#ifndef VIZUALSCENY2_H
#define VIZUALSCENY2_H

#include <osg/MatrixTransform>
#include <osg/Geode>
#include <qlist.h>

#include "commonfuncitons.h"
#include "fixture2.h"

class VizualSceny2
{
public:
    VizualSceny2();
    osg::ref_ptr<osg::Group> get(){return _root;}
    QList<Fixture2> getFixtures(){ return _fixtures; }

    void setToBeMovable(osg::Drawable *shape);
    void setToBeRotatable(osg::Drawable *shape);
    void addFixtureChild();

private:
    osg::ref_ptr<osg::Group> _root;
    QList<Fixture2> _fixtures;

};

#endif // VIZUALSCENY2_H
