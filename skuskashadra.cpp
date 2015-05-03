#include "skuskashadra.h"
#include <osg/Geode>
#include <osgShadow/ShadowMap>
#include <osgShadow/ShadowedScene>
#include <osgDB/ReadFile>
#include <osg/Matrix>

SkuskaShadra::SkuskaShadra()
{

           const int ReceivesShadowTraversalMask = 0x1;

           const int CastsShadowTraversalMask = 0x2;

           shadowedScene = new osgShadow::ShadowedScene;

           shadowedScene->setReceivesShadowTraversalMask(ReceivesShadowTraversalMask);
           shadowedScene->setCastsShadowTraversalMask(CastsShadowTraversalMask);

           osg::ref_ptr<osgShadow::ShadowMap> sm = new osgShadow::ShadowMap;
           shadowedScene->setShadowTechnique(sm.get());

           int mapres = 1024;
           sm->setTextureSize(osg::Vec2s(mapres,mapres));

           osg::Group* cessna1 = (osg::Group*) osgDB::readNodeFile("/home/beki/OpenSceneGraph-Data-3.0.0/cessna.osg");
           cessna1->getChild(0)->setNodeMask(CastsShadowTraversalMask);

           osg::Group* cessna2 = (osg::Group*) osgDB::readNodeFile("/home/beki/OpenSceneGraph-Data-3.0.0/cessna.osg");
           cessna2->getChild(0)->setNodeMask(ReceivesShadowTraversalMask);

           osg::MatrixTransform* positioned = new osg::MatrixTransform;
           positioned->setMatrix(osg::Matrix::translate(40,0,0));
           positioned->addChild(cessna1);

           shadowedScene->addChild(positioned);
           shadowedScene->addChild(cessna2);
}



