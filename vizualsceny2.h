#ifndef VIZUALSCENY2_H
#define VIZUALSCENY2_H

#include <osg/ShapeDrawable>
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
    QList<Fixture2> getCone(){ return _fixture; }

    void doUserOperation(osg::Drawable *shape);
    void addFixtureChild();

private:
    osg::ref_ptr<osg::Group> _root;
    QList<Fixture2> _fixture;

};

#endif // VIZUALSCENY2_H