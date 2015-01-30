#ifndef VIZUALSCENY_H
#define VIZUALSCENY_H

#include <osg/ShapeDrawable>
#include <osg/MatrixTransform>
#include <osg/Geode>
#include "commonfuncitons.h"

class vizualSceny
{
public:
    vizualSceny();
    osg::ref_ptr<osg::Group> get(){return _root;}

private:
    osg::ref_ptr<osg::Group> _root;

};

#endif // VIZUALSCENY_H
