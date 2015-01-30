#include "cloneobjectroot.h"

CloneObjectRoot::CloneObjectRoot()
{
    osg::ref_ptr<osg::ShapeDrawable> shape = new osg::ShapeDrawable( new osg::Sphere );
    shape->setColor( osg::Vec4(1.0f, 1.0f, 0.0f, 1.0f) );
    shape->setDataVariance( osg::Object::DYNAMIC );
    shape->setUseDisplayList( false );

    osg::ref_ptr<osg::Geode> geode1 = new osg::Geode;
    geode1->addDrawable( shape.get() );

    osg::ref_ptr<osg::Geode> geode2 = dynamic_cast<osg::Geode*>( geode1->clone(osg::CopyOp::SHALLOW_COPY) );
    osg::ref_ptr<osg::Geode> geode3 = dynamic_cast<osg::Geode*>( geode1->clone(osg::CopyOp::DEEP_COPY_ALL) );

    _root = new osg::Group;
    _root->addChild( createMatrixTransform(geode1.get(), osg::Vec3(0.0f, 0.0f, 0.0f)) );
    _root->addChild( createMatrixTransform(geode2.get(), osg::Vec3(-2.0f, 0.0f, 0.0f)) );
    _root->addChild( createMatrixTransform(geode3.get(), osg::Vec3(2.0f, 0.0f, 0.0f)) );

}

osg::Node *CloneObjectRoot::createMatrixTransform(osg::Geode *geode, const osg::Vec3 &pos)
{
    osg::ref_ptr<osg::MatrixTransform> trans = new osg::MatrixTransform;
    trans->setMatrix( osg::Matrix::translate(pos) );
    trans->addChild( geode );
    return trans.release();
}

