#include "stagegeode.h"

stageGeode::stageGeode()
{
    _width = 20.0;
    _depth = 10.0;
    _height = 1.0;
    _stageGeode = new osg::Geode();

    osg::ref_ptr<osg::Geometry> stageGeometry = new osg::Geometry();
    _stageGeode->addDrawable( stageGeometry );

    osg::ref_ptr<osg::Vec3Array> stageVertices = new osg::Vec3Array();
    stageVertices->push_back( osg::Vec3( -0.5 * _width, 0, 0 ) );
    stageVertices->push_back( osg::Vec3(  0.5 * _width, 0, 0 ) );
    stageVertices->push_back( osg::Vec3(  0.5 * _width, _depth, 0 ) );
    stageVertices->push_back( osg::Vec3( -0.5 * _width, _depth, 0 ) );
    stageVertices->push_back( osg::Vec3( -0.5 * _width, 0, _height ) );
    stageVertices->push_back( osg::Vec3(  0.5 * _width, 0, _height ) );
    stageVertices->push_back( osg::Vec3(  0.5 * _width, _depth, _height ) );
    stageVertices->push_back( osg::Vec3( -0.5 * _width, _depth, _height ) );
    stageGeometry->setVertexArray( stageVertices );

    osg::ref_ptr<osg::DrawElementsUInt> frontFace =
            new osg::DrawElementsUInt( osg::PrimitiveSet::QUADS);
    frontFace->push_back( 0 );
    frontFace->push_back( 1 );
    frontFace->push_back( 5 );
    frontFace->push_back( 4 );
    stageGeometry->addPrimitiveSet( frontFace );

    osg::ref_ptr<osg::DrawElementsUInt> rightFace =
            new osg::DrawElementsUInt( osg::PrimitiveSet::QUADS);
    rightFace->push_back( 1 );
    rightFace->push_back( 2 );
    rightFace->push_back( 6 );
    rightFace->push_back( 5 );
    stageGeometry->addPrimitiveSet( rightFace );

    osg::ref_ptr<osg::DrawElementsUInt> leftFace =
            new osg::DrawElementsUInt( osg::PrimitiveSet::QUADS);
    leftFace->push_back( 0 );
    leftFace->push_back( 4 );
    leftFace->push_back( 7 );
    leftFace->push_back( 3 );
    stageGeometry->addPrimitiveSet( leftFace );

    osg::ref_ptr<osg::DrawElementsUInt> backFace =
            new osg::DrawElementsUInt( osg::PrimitiveSet::QUADS);
    backFace->push_back( 2 );
    backFace->push_back( 3 );
    backFace->push_back( 7 );
    backFace->push_back( 6 );
    stageGeometry->addPrimitiveSet( backFace );

    osg::ref_ptr<osg::DrawElementsUInt> topFace =
            new osg::DrawElementsUInt( osg::PrimitiveSet::QUADS);
    topFace->push_back( 4 );
    topFace->push_back( 5 );
    topFace->push_back( 6 );
    topFace->push_back( 7 );
    stageGeometry->addPrimitiveSet( topFace );


}


