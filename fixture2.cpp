#include "fixture2.h"
#include <osgDB/ReadFile>
#include <osg/BlendFunc>
#include <osg/MatrixTransform>
#include "commonfuncitons.h"

Fixture2::Fixture2()
{
    osg::ref_ptr<osg::Node> head = osgDB::readNodeFile("/home/beki/SceneItems/PAR64.osgt");

    _pyramidGeode = new osg::Geode();
    osg::ref_ptr<osg::Geometry> pyramidGeometry = new osg::Geometry();
    _pyramidGeode->addDrawable(pyramidGeometry);
    pyramidGeometry->setDataVariance( osg::Object::DYNAMIC );
    pyramidGeometry->setUseDisplayList( false );

    osg::ref_ptr<osg::Vec3Array> pyramidVertices = new osg::Vec3Array();
    pyramidVertices->push_back( osg::Vec3(  0,  0, 0) ); // peak
    int faces = 16;
    double partOfCircle = osg::PI * 2.0 / (double)faces ;
    double position = 0.0;
    for (int i = 0; i < faces; ++i){
        pyramidVertices->push_back( osg::Vec3( sin(position), cos(position), -4) ); // points at base
        position += partOfCircle;
    }
    pyramidGeometry->setVertexArray( pyramidVertices );

    //cone faces creation
    osg::ref_ptr<osg::DrawElementsUInt> pyramidFace =
        new osg::DrawElementsUInt(osg::PrimitiveSet::TRIANGLE_FAN, 0);
    pyramidFace->push_back(0);
    for(int i = 1; i <= faces; ++i){
        pyramidFace->push_back(i);
    }
    pyramidFace->push_back(1);
    pyramidGeometry->addPrimitiveSet(pyramidFace);

    // transparent cone
    _colors = new osg::Vec4Array();
    _colors->push_back(osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f) ); //index 0 white
    for (int i = 0; i < faces; ++i)
    {
    _colors->push_back(osg::Vec4(1.0f, 1.0f, 1.0f, 0.0f) ); //index i off
    }

    pyramidGeometry->setColorArray(_colors);
    pyramidGeometry->setColorBinding(osg::Geometry::BIND_PER_VERTEX);

    osg::StateSet* stateset = _pyramidGeode->getOrCreateStateSet();
    stateset->setRenderingHint( osg::StateSet::TRANSPARENT_BIN );
    stateset->setMode(GL_LIGHTING, osg::StateAttribute::OFF);

    osg::ref_ptr<osg::BlendFunc> blendFunc = new osg::BlendFunc;
    blendFunc->setFunction( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    stateset->setAttributeAndModes( blendFunc );

    //all fixture transformations
    _transG = new osg::MatrixTransform;
    _transR = new osg::MatrixTransform;
    _transQLC = new osg::MatrixTransform;
    _transG->setMatrix(osg::Matrix::translate( osg::Vec3(0.0f, 8.0f, 3.0f) ) );
    _transR->setMatrix( osg::Matrix::rotate( osg::PI / 4, osg::Vec3d(-1, 0,  0) ) );
    _transQLC->addChild( head );
    _transQLC->addChild( _pyramidGeode );
    _transR->addChild( _transQLC );

/// translation by user with mouse
    _transR->getOrCreateStateSet()->setMode(GL_NORMALIZE, osg::StateAttribute::ON);
    _transG->addChild( _transR );
    _draggerG = new osgManipulator::Translate2DDragger();
    _draggerG->setupDefaultGeometry();
    _transG->addChild(_draggerG);
    _draggerG->setMatrix(osg::Matrix::scale(3, 3, 3));
    _draggerG->setHandleEvents(false);
//    _draggerG->setActivationKeyEvent('g');
    _draggerG->addTransformUpdating( _transR );
    _draggerG->setNodeMask(0);

/// rotation by user with mouse
    _transQLC->getOrCreateStateSet()->setMode(GL_NORMALIZE, osg::StateAttribute::ON);
    _transR->addChild( _transQLC );
    _draggerR = new osgManipulator::TrackballDragger();
    _draggerR->setupDefaultGeometry();
    _transR->addChild(_draggerR);
    _draggerR->setHandleEvents(false);
//    _draggerR->setActivationKeyEvent('r');
    _draggerR->addTransformUpdating( _transQLC );
    _draggerR->setNodeMask(0);





}

void Fixture2::changeColor(osg::Vec3 colorValue, bool overwrite)
{
    if(_colors){
        for(unsigned int i = 0; i < _colors->size(); ++i){
            osg::Vec4 *color = &_colors->operator [](i);
            if(overwrite){
                color->x() = colorValue.x();
                color->y() = colorValue.y();
                color->z() = colorValue.z();
            }
            else{
                color->x() += colorValue.x();
                color->y() += colorValue.y();
                color->z() += colorValue.z();
            }
        }
    }

}

void Fixture2::changeOpacity(float opacityValue, bool overwrite)
{
    osg::Vec4 *color = &_colors->operator [](0);
    if (overwrite){
        color->w() = opacityValue;
    }
    else{
        color->w() += opacityValue;
    }
}

void Fixture2::setDraggerGVisibility(bool visible)
{
    if(_visibleG == visible){ return; }
    _visibleG = visible;
    if(_visibleG){
        _draggerG->setNodeMask(~0);
        setDraggerRVisibility(false);
    }
    else{
        _draggerG->setNodeMask(0);
    }
    _draggerG->setHandleEvents(_visibleG);

}

void Fixture2::setDraggerRVisibility(bool visible)
{
    if(_visibleR == visible){ return; }
    _visibleR = visible;
    if(_visibleR){
        _draggerR->setNodeMask(~0);
        setDraggerGVisibility(false);
    }
    else{
        _draggerR->setNodeMask(0);
    }
    _draggerR->setHandleEvents(_visibleR);
}

