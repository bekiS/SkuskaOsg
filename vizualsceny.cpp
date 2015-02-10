#include "vizualsceny.h"
#include "floorgeode.h"
#include "stagegeode.h"
#include "osgDB/ReadFile"
#include "commonfuncitons.h"

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
    osg::Node* scene = osgDB::readNodeFile("/home/beki/par.osgt");

    _root->addChild( scene );


    int numberOfFixtures = 5;
    float space = stage.getWidth() / (float)(numberOfFixtures + 1);
    float posX = stage.getWidth() * -0.5f;
    for( int i = 0; i < numberOfFixtures; ++i){
    _cone.append(Cone());
//    _root->addChild( _cone.getGeode() );
    //cone.changeColor(osg::Vec3(0.4f, 0.8f, 0.2f));
        osg::ref_ptr<osg::MatrixTransform> trans = new osg::MatrixTransform;
        posX += space;
        trans->setMatrix( osg::Matrix::rotate(osg::PI / 4, osg::Vec3d(-1, 0,  0)) * osg::Matrix::translate( osg::Vec3(posX, 8.0f, 7.0f)) );
//        trans->addChild( _cone.last().getGeode() );
//        _root->addChild( osgCookBook::addDraggerToScene(trans) );
        trans->addChild( osgCookBook::addDraggerToScene( _cone.last().getGeode() ) );
        _root->addChild( trans );
        _cone.last().changeColor(osg::Vec3((float)(i+ 1)/(float)numberOfFixtures, 1.0f, 0.0f));
        _cone.last().changeOpacity(0.6f);
    }
   // _cone.changeOpacity(0.2f);
}

void vizualSceny::doUserOperation( osg::Drawable *shape)
{
    QList<Cone>::iterator i;
    for (i = _cone.begin(); i != _cone.end(); ++i)
    {
        if( shape == i->getGeode()->getDrawable(0) )
        {
            i->changeColor(osg::Vec3( 0.0f, 0.0f, 1.0f ) );
        }
    }
}
