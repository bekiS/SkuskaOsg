#include "vizualsceny2.h"
#include "floorgeode.h"
//#include "stagegeode.h"
#include <osgDB/ReadFile>

VizualSceny2::VizualSceny2()
{
    _root = new osg::Group;

    floorGeode floor = floorGeode();
    _root->addChild( floor.get() );

//    stageGeode stage = stageGeode();
     osg::ref_ptr<osg::Node> stage = osgDB::readNodeFile("/home/beki/SceneItems/Stage.osgt");
    _root->addChild( stage.get() );

    addFixtureChild();
}

void VizualSceny2::setToBeMovable(osg::Drawable *shape)
{
    QList<Fixture2>::iterator i;
    for (i = _fixtures.begin(); i != _fixtures.end(); ++i)
    {
        if( shape == i->getDrawable() )
        {
            i->setDraggerGVisibility(true);
        }
        else
        {
            i->setDraggerGVisibility(false);
        }
        i->setDraggerRVisibility(false);
    }
}

void VizualSceny2::setToBeRotatable(osg::Drawable *shape)
{
    QList<Fixture2>::iterator i;
    for (i = _fixtures.begin(); i != _fixtures.end(); ++i)
    {
        if( shape == i->getDrawable() )
        {
            i->setDraggerRVisibility(true);
        }
        else
        {
            i->setDraggerRVisibility(false);
        }
        i->setDraggerGVisibility(false);
    }
}

void VizualSceny2::addFixtureChild()
{
    _fixtures.append(Fixture2());
    _root->addChild( _fixtures.last().getFixture() );
    _fixtures.last().changeColor(osg::Vec3(0.4f, 0.0f, 1.0f));

}
