#include "vizualsceny2.h"
#include "floorgeode.h"
#include "stagegeode.h"
#include "osgDB/ReadFile"
#include "commonfuncitons.h"

VizualSceny2::VizualSceny2()
{
    _root = new osg::Group;

    floorGeode floor = floorGeode();
    _root->addChild( floor.get() );

    stageGeode stage = stageGeode();
    _root->addChild( stage.get() );


//    int numberOfFixtures = 5;
//    float space = stage.getWidth() / (float)(numberOfFixtures + 1);
//    float posX = stage.getWidth() * -0.5f;
//    for( int i = 0; i < numberOfFixtures; ++i){
//    _fixture.append(Fixture2());
//        osg::ref_ptr<osg::MatrixTransform> trans = new osg::MatrixTransform;
//        posX += space;
//        trans->setMatrix( osg::Matrix::rotate(osg::PI / 4, osg::Vec3d(-1, 0,  0)) * osg::Matrix::translate( osg::Vec3(posX, 8.0f, 7.0f)) );
//        trans->addChild( osgCookBook::addDraggerToScene( _fixture.last().getFixture() ) );
//        _root->addChild( trans );
//        _fixture.last().changeColor(osg::Vec3((float)(i+ 1)/(float)numberOfFixtures, 1.0f, 0.0f));
//        _fixture.last().changeOpacity(0.6f);
//    }
    addFixtureChild();
}

void VizualSceny2::doUserOperation(osg::Drawable *shape)
{
    QList<Fixture2>::iterator i;
    for (i = _fixture.begin(); i != _fixture.end(); ++i)
    {
        if( shape == i->getPyramid()->getDrawable(0) )
        {
            i->changeColor(osg::Vec3( 0.0f, 0.0f, 1.0f ) );
        }
    }
}

void VizualSceny2::addFixtureChild()
{
    _fixture.append(Fixture2());
    osg::ref_ptr<osg::MatrixTransform> trans = new osg::MatrixTransform;
    trans->setMatrix( osg::Matrix::rotate(osg::PI / 4, osg::Vec3d(-1, 0,  0)) * osg::Matrix::translate( osg::Vec3(0.0f, 8.0f, 7.0f)) );
    trans->addChild( osgCookBook::addDraggerToScene( _fixture.last().getFixture() ) );
    _root->addChild( trans );
    _fixture.last().changeColor(osg::Vec3(0.4f, 0.0f, 1.0f));
    _fixture.last().changeOpacity(0.6f);

}
