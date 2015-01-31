#include "mojdialog.h"
#include "ui_mojdialog.h"

#include <osg/Geode>
//#include <osgDB/ReadFile>

#include "viewerwidget.h"
//#include "cloneobjectroot.h"
//#include "auto.h"
#include "vizualsceny.h"

osgQt::GraphicsWindowQt* createGraphicsWindow( int x, int y, int w, int h )
{
    osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits;
    traits->windowDecoration = false;
    traits->x = x;
    traits->y = y;
    traits->width = w;
    traits->height = h;
    traits->doubleBuffer = true;

    return new osgQt::GraphicsWindowQt(traits.get());
}

MojDialog::MojDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MojDialog)
{
    ui->setupUi(this);
    osgQt::GraphicsWindowQt* gw = createGraphicsWindow( 50, 50, 640, 480 );
    //osg::Node* scene = osgDB::readNodeFile("/home/beki/OpenSceneGraph-Data-3.0.0/cow.osg");

    //CloneObjectRoot root = CloneObjectRoot();
    //Auto root = Auto();
    vizualSceny* root = new vizualSceny();
    ViewerWidget* widget = new ViewerWidget(gw, root /* scene */);
    widget->setGeometry( 100, 100, 800, 600 );
    widget->show();

}

MojDialog::~MojDialog()
{
    delete ui;
}
