#include "auto.h"

Auto::Auto()
{
    osg::ref_ptr<osg::ShapeDrawable> mainRodShape =
        new osg::ShapeDrawable( new osg::Cylinder(osg::Vec3(), 0.4f, 10.0f) );
    osg::ref_ptr<osg::ShapeDrawable> wheelRodShape =
        new osg::ShapeDrawable( new osg::Cylinder(osg::Vec3(), 0.4f, 8.0f) );
    osg::ref_ptr<osg::ShapeDrawable> wheelShape =
        new osg::ShapeDrawable( new osg::Cylinder(osg::Vec3(), 2.0f, 1.0f) );
    osg::ref_ptr<osg::ShapeDrawable> bodyShape =
        new osg::ShapeDrawable( new osg::Box(osg::Vec3(), 6.0f, 4.0f, 14.0f) );

    // The scene graph
    osg::MatrixTransform* wheel1 = createTransformNodeAuto(
        wheelShape.get(), osg::Matrix::translate(0.0f, 0.0f,-4.0f) );
    wheel1->addUpdateCallback( createWheelAnimationAuto(osg::Vec3(0.0f, 0.0f,-4.0f)) );

    osg::MatrixTransform* wheel2 = createTransformNodeAuto(
        wheelShape.get(), osg::Matrix::translate(0.0f, 0.0f, 4.0f) );
    wheel2->addUpdateCallback( createWheelAnimationAuto(osg::Vec3(0.0f, 0.0f, 4.0f)) );

    osg::MatrixTransform* wheelRod1 = createTransformNodeAuto( wheelRodShape.get(),
        osg::Matrix::rotate(osg::Z_AXIS, osg::X_AXIS) * osg::Matrix::translate(0.0f, 0.0f,-5.0f) );
    wheelRod1->addChild( wheel1 );
    wheelRod1->addChild( wheel2 );

    osg::MatrixTransform* wheelRod2 = static_cast<osg::MatrixTransform*>( wheelRod1->clone(osg::CopyOp::SHALLOW_COPY) );
    wheelRod2->setMatrix( osg::Matrix::rotate(osg::Z_AXIS, osg::X_AXIS) * osg::Matrix::translate(0.0f, 0.0f, 5.0f) );

    osg::MatrixTransform* body = createTransformNodeAuto(
        bodyShape.get(), osg::Matrix::translate(0.0f, 2.2f, 0.0f) );

    osg::MatrixTransform* mainRod = createTransformNodeAuto( mainRodShape.get(), osg::Matrix::identity() );
    mainRod->addChild( wheelRod1 );
    mainRod->addChild( wheelRod2 );
    mainRod->addChild( body );

    _root = new osg::Group;
    _root->addChild( mainRod );
}

osg::MatrixTransform *Auto::createTransformNodeAuto(osg::Drawable *shape, const osg::Matrix &matrix)
{
    osg::ref_ptr<osg::Geode> geode = new osg::Geode;
    geode->addDrawable( shape );

    osg::ref_ptr<osg::MatrixTransform> trans = new osg::MatrixTransform;
    trans->addChild( geode.get() );
    trans->setMatrix( matrix );
    return trans.release();
}

osg::AnimationPathCallback *Auto::createWheelAnimationAuto(const osg::Vec3 &base)
{
    osg::ref_ptr<osg::AnimationPath> wheelPath = new osg::AnimationPath;
    wheelPath->setLoopMode( osg::AnimationPath::LOOP );
    wheelPath->insert( 0.0, osg::AnimationPath::ControlPoint(base, osg::Quat()) );
    wheelPath->insert( 0.01, osg::AnimationPath::ControlPoint(
        base + osg::Vec3(0.0f, 0.02f, 0.0f), osg::Quat(osg::PI_2, osg::Z_AXIS)) );
    wheelPath->insert( 0.02, osg::AnimationPath::ControlPoint(
        base + osg::Vec3(0.0f,-0.02f, 0.0f), osg::Quat(osg::PI, osg::Z_AXIS)) );

    osg::ref_ptr<osg::AnimationPathCallback> apcb = new osg::AnimationPathCallback;
    apcb->setAnimationPath( wheelPath.get() );
    return apcb.release();
}
