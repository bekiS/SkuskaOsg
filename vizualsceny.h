#ifndef VIZUALSCENY_H
#define VIZUALSCENY_H

#include <osg/ShapeDrawable>
#include <osg/MatrixTransform>
#include <osg/Geode>
#include <qlist.h>

#include "commonfuncitons.h"
#include "cone.h"

class vizualSceny
{
public:
    vizualSceny();
    osg::ref_ptr<osg::Group> get(){return _root;}
    QList<Cone> getCone(){ return _cone; }

    void doUserOperation(osg::Drawable *shape);

private:
    osg::ref_ptr<osg::Group> _root;
    QList<Cone> _cone;

};

#endif // VIZUALSCENY_H
