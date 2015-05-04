#ifndef DEREFERRED_H
#define DEREFERRED_H

#include <osg/Camera>
#include <osg/Group>
#include <osg/MatrixTransform>
#include <osg/Texture2D>
#include <osg/TextureRectangle>
#include <osgShadow/ShadowedScene>
#include <osg/LightSource>

#include "vizualsceny2.h"

class Deferred
{
public:
    Deferred(VizualSceny2* scene);
    ~Deferred();

    int _textureSize;
    osg::ref_ptr<osg::Group> _graph;
    osg::Texture * _pass1Shadows;
    osg::Texture * _pass2Colors;
    osg::Texture * _pass2Normals;
    osg::Texture * _pass2Positions;
    osg::Texture * _pass3Final;




    osg::TextureRectangle *createFloatTextureRectangle(int textureSize);
    osg::Camera *createHUDCamera(double left   = 0,
                                 double right  = 1,
                                 double bottom = 0,
                                 double top    = 1);

    osg::Camera *createRTTCamera(osg::Camera::BufferComponent buffer,
                                 osg::Texture *tex,
                                 bool isAbsolute = false);
    osg::Geode *createScreenQuad(float width,
                                 float height,
                                 float scale = 1,
                                 osg::Vec3 corner = osg::Vec3());
    osg::Texture2D *createTexture(const std::string &fileName);
    osg::ref_ptr<osg::Camera> createTextureDisplayQuad(const osg::Vec3 &pos,
                                                       osg::StateAttribute *tex,
                                                       float scale,
                                                       float width  = 0.3,
                                                       float height = 0.2);
    osg::ref_ptr<osg::StateSet> setShaderProgram(osg::ref_ptr<osg::Camera> pass,
                                                 std::string vert,
                                                 std::string frag);

private:
};

#endif // DEREFERRED_H
