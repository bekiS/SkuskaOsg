#include "cone.h"
#include <osg/BlendFunc>


Cone::Cone()
{
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
        pyramidVertices->push_back( osg::Vec3( sin(position), cos(position), -6) ); // points at base
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

}

void Cone::changeColor(osg::Vec3 colorValue, bool overwrite)
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

void Cone::changeOpacity(float opacityValue, bool overwrite)
{
    osg::Vec4 *color = &_colors->operator [](0);
    if (overwrite){
        color->w() = opacityValue;
    }
    else{
        color->w() += opacityValue;
    }
}
