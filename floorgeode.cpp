#include "floorgeode.h"

floorGeode::floorGeode()
{
    _radius = 100.0f;
    _floorGeode = new osg::Geode();

    osg::ref_ptr<osg::Geometry> floorGeometry = new osg::Geometry();
    _floorGeode->addDrawable( floorGeometry );

    osg::ref_ptr<osg::Vec3Array> floorVertices = new osg::Vec3Array();
    floorVertices->push_back( osg::Vec3( -1.0f * _radius, -1.0f * _radius, 0.0f) );
    floorVertices->push_back( osg::Vec3( -1.0f * _radius,  1.0f * _radius, 0.0f) );
    floorVertices->push_back( osg::Vec3(  1.0f * _radius,  1.0f * _radius, 0.0f) );
    floorVertices->push_back( osg::Vec3(  1.0f * _radius, -1.0f * _radius, 0.0f) );

    floorGeometry->setVertexArray( floorVertices );

    osg::ref_ptr<osg::DrawElementsUInt> floorFace =
            new osg::DrawElementsUInt( osg::PrimitiveSet::QUADS , 0);
    for(unsigned int i = 0; i < 4; ++i ){
        floorFace->push_back( i );
    }

    floorGeometry->addPrimitiveSet( floorFace );

    osg::ref_ptr<osg::Vec4Array> colors = new osg::Vec4Array();
    for (int i = 0; i < 4; ++i)
    {
    colors->push_back(osg::Vec4(0.54f, 0.27f, 0.07f, 1.0f) ); //brown
    }
    floorGeometry->setColorArray(colors);
    floorGeometry->setColorBinding(osg::Geometry::BIND_PER_VERTEX);


}
