#include "deferred.h"
#include <osg/PolygonMode>
#include <osgDB/ReadFile>
#include <osgShadow/SoftShadowMap>
#include <QString>
#include <QList>
#include "vizualsceny2.h"


Deferred::Deferred(VizualSceny2 * scene )
{

     _graph = new osg::Group;
     _textureSize = 1024;
      // Pass 1 (positions, normals, colors).
     _pass2Positions = createFloatTextureRectangle(_textureSize);
     _pass2Normals   = createFloatTextureRectangle(_textureSize);
     _pass2Colors    = createFloatTextureRectangle(_textureSize);
     osg::ref_ptr<osg::Camera> pass1 =
         createRTTCamera(osg::Camera::COLOR_BUFFER0, _pass2Positions);
     pass1->attach(osg::Camera::COLOR_BUFFER1,_pass2Normals);
     pass1->attach(osg::Camera::COLOR_BUFFER2, _pass2Colors);
     pass1->addChild(scene->get());
     osg::StateSet *ss = setShaderProgram(pass1, "shaders/pass1.vert", "shaders/pass1.frag");

     // Pass 2 (final).
     _pass3Final = createFloatTextureRectangle(_textureSize);

     osg::ref_ptr<osg::Camera> pass2 =
                   createRTTCamera(osg::Camera::COLOR_BUFFER, _pass3Final, true);
     ss = setShaderProgram(pass2, "shaders/pass2.vert", "shaders/fragment.frag");
     ss->setTextureAttributeAndModes(0, _pass2Positions);
     ss->setTextureAttributeAndModes(1, _pass2Normals);
     ss->setTextureAttributeAndModes(2, _pass2Colors);
     ss->addUniform(new osg::Uniform("posMap",    0));
     ss->addUniform(new osg::Uniform("normalMap", 1));
     ss->addUniform(new osg::Uniform("colorMap",  2));
     // Light position.

     QList<Fixture2> fixtures = scene->getFixtures();
     int properties = 5;
     int maxLights = 1;   //check also in fragment shader
     int LightCount = (maxLights < fixtures.length() ? fixtures.length() : maxLights);
     osg::Vec4 lights[ maxLights * properties];

     for(int i = 0; i < LightCount; ++i)
     {
        lights[i]     =  fixtures.at(i).getColor();
        lights[i + 1] =  fixtures.at(i).getPosition();
        lights[i + 2] =  fixtures.at(i).getAttenuation();
        lights[i + 3] =  fixtures.at(i).getSpot_dir();
        lights[i + 4] =  fixtures.at(i).getSpot_param();
     }
     ss->addUniform(new osg::Uniform("lightsCount", LightCount));
     ss->addUniform(new osg::Uniform("lights", maxLights * properties, lights ));

     // Graph.
     _graph->addChild(pass1);
     _graph->addChild(pass2);


     // Quads to display 1 pass textures.
     osg::ref_ptr<osg::Camera> qTexN =
         createTextureDisplayQuad(osg::Vec3(0, 0.7, 0),
                                  _pass2Normals,
                                  _textureSize);
     osg::ref_ptr<osg::Camera> qTexP =
         createTextureDisplayQuad(osg::Vec3(0, 0.35, 0),
                                  _pass2Positions,
                                  _textureSize);
     osg::ref_ptr<osg::Camera> qTexC =
         createTextureDisplayQuad(osg::Vec3(0, 0.05, 0),
                                  _pass2Colors,
                                  _textureSize);
//      Quad to display 3 pass final (screen) texture.
     osg::ref_ptr<osg::Camera> qTexFinal =
         createTextureDisplayQuad(osg::Vec3(0, 0, 0),
                                  _pass3Final,
                                  _textureSize,
                                  1,
                                  1);
     // Quads are displayed in order, so the biggest one (final) must be first,
     // otherwise other quads won't be visible.
     _graph->addChild(qTexFinal.get());
     _graph->addChild(qTexN.get());
     _graph->addChild(qTexP.get());
     _graph->addChild(qTexC.get());
}

Deferred::~Deferred()
{
}

osg::TextureRectangle *Deferred::createFloatTextureRectangle(int textureSize)
{
    osg::ref_ptr<osg::TextureRectangle> tex2D = new osg::TextureRectangle;
    tex2D->setTextureSize(textureSize, textureSize);
    tex2D->setInternalFormat(GL_RGBA16F_ARB);
    tex2D->setSourceFormat(GL_RGBA);
    tex2D->setSourceType(GL_FLOAT);
    return tex2D.release();
}

osg::Camera *Deferred::createHUDCamera(double left, double right, double bottom, double top)
{
    osg::ref_ptr<osg::Camera> camera = new osg::Camera;
    camera->setReferenceFrame(osg::Transform::ABSOLUTE_RF);
    camera->setClearMask(GL_DEPTH_BUFFER_BIT);
    camera->setRenderOrder(osg::Camera::POST_RENDER);
    camera->setAllowEventFocus(false);
    camera->setProjectionMatrix(osg::Matrix::ortho2D(left, right, bottom, top));
    camera->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
    return camera.release();
}

osg::Camera *Deferred::createRTTCamera( osg::Camera::BufferComponent buffer
                                        , osg::Texture *tex
                                        , bool isAbsolute)
{
    osg::ref_ptr<osg::Camera> camera = new osg::Camera;
    camera->setClearColor(osg::Vec4());
    camera->setClearMask(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    camera->setRenderTargetImplementation(osg::Camera::FRAME_BUFFER_OBJECT);
    camera->setRenderOrder(osg::Camera::PRE_RENDER);
    if (tex)
    {
        tex->setFilter(osg::Texture2D::MIN_FILTER, osg::Texture2D::LINEAR);
        tex->setFilter(osg::Texture2D::MAG_FILTER, osg::Texture2D::LINEAR);
        camera->setViewport(0, 0, tex->getTextureWidth(), tex->getTextureHeight());
        camera->attach(buffer, tex);
    }
    if (isAbsolute)
    {
        camera->setReferenceFrame(osg::Transform::ABSOLUTE_RF);
        camera->setProjectionMatrix(osg::Matrix::ortho2D(0.0, 1.0, 0.0, 1.0));
        camera->setViewMatrix(osg::Matrix::identity());
        camera->addChild(createScreenQuad(1.0f, 1.0f));
    }
    return camera.release();
}

osg::Geode *Deferred::createScreenQuad(float width, float height, float scale, osg::Vec3 corner)
{
    osg::Geometry* geom = osg::createTexturedQuadGeometry(
         corner,
         osg::Vec3(width, 0, 0),
         osg::Vec3(0, height, 0),
         0,
         0,
         scale,
         scale);
     osg::ref_ptr<osg::Geode> quad = new osg::Geode;
     quad->addDrawable(geom);
     int values = osg::StateAttribute::OFF | osg::StateAttribute::PROTECTED;
     quad->getOrCreateStateSet()->setAttribute(
         new osg::PolygonMode(osg::PolygonMode::FRONT_AND_BACK,
                              osg::PolygonMode::FILL),
         values);
     quad->getOrCreateStateSet()->setMode(GL_LIGHTING, values);
     return quad.release();

}

osg::Texture2D *Deferred::createTexture(const std::string &fileName)
{
    osg::ref_ptr<osg::Texture2D> texture = new osg::Texture2D;
    texture->setImage(osgDB::readImageFile(fileName));
    texture->setWrap(osg::Texture2D::WRAP_S, osg::Texture2D::REPEAT);
    texture->setWrap(osg::Texture2D::WRAP_T, osg::Texture2D::REPEAT);
    texture->setFilter(osg::Texture::MIN_FILTER, osg::Texture::LINEAR_MIPMAP_LINEAR);
    texture->setFilter(osg::Texture::MAG_FILTER, osg::Texture::LINEAR);
    return texture.release();
}

osg::ref_ptr<osg::Camera> Deferred::createTextureDisplayQuad( const osg::Vec3 &pos
                                                              , osg::StateAttribute *tex
                                                              , float scale
                                                              , float width
                                                              , float height
                                                              )
{
    osg::ref_ptr<osg::Camera> hc = createHUDCamera();
    hc->addChild(createScreenQuad(width, height, scale, pos));
    hc->getOrCreateStateSet()->setTextureAttributeAndModes(0, tex);
    return hc;
}



osg::ref_ptr<osg::StateSet> Deferred::setShaderProgram( osg::ref_ptr<osg::Camera> pass
                                                        , std::string vert
                                                        , std::string frag
                                                        )
{
    osg::ref_ptr<osg::Program> program = new osg::Program;
    program->addShader(osgDB::readShaderFile(vert));
    program->addShader(osgDB::readShaderFile(frag));
    osg::ref_ptr<osg::StateSet> ss = pass->getOrCreateStateSet();
    ss->setAttributeAndModes(
        program.get(),
        osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
    return ss;

}

