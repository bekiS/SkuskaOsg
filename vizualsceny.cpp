#include "vizualsceny.h"
#include "floorgeode.h"
#include "stagegeode.h"
#include "cone.h"

vizualSceny::vizualSceny()
{
    _root = new osg::Group;
//    osg::ref_ptr<osg::ShapeDrawable> sceneShape =
//        new osg::ShapeDrawable( new osg::Box(osg::Vec3(), 20.0f, 12.0f, 2.5f) );

//    osg::ref_ptr<osg::Geode> geode = new osg::Geode;
//    geode->addDrawable( sceneShape );

//    _root->addChild( geode);

    floorGeode floor = floorGeode();
    _root->addChild( floor.get() );

    stageGeode stage = stageGeode();
    _root->addChild( stage.get() );

    Cone cone = Cone();
    _root->addChild( cone.get() );
    //cone.changeColor(osg::Vec3(0.4f, 0.8f, 0.2f));
    cone.changeOpacity(0.2f);
}
