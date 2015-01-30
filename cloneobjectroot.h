#ifndef CLONEOBJECTROOT_H
#define CLONEOBJECTROOT_H

#include <osg/ShapeDrawable>
#include <osg/Geode>
#include <osg/MatrixTransform>
#include <osgViewer/Viewer>

#include "commonfuncitons.h"


class CloneObjectRoot
{
public:
    CloneObjectRoot();
    osg::ref_ptr<osg::Group> get(){return _root;}
private:
    osg::ref_ptr<osg::Group> _root;
    osg::Node *createMatrixTransform( osg::Geode* geode, const osg::Vec3& pos );
};

#endif // CLONEOBJECTROOT_H
