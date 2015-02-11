#include "mojdialog.h"
#include "ui_mojdialog.h"

#include <osg/Geode>

#include "viewerwidget.h"



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

    _root = new VizualSceny2();
    ViewerWidget* widget = new ViewerWidget(gw, _root );
    widget->setGeometry( 100, 100, 800, 600 );
    widget->show();

}

MojDialog::~MojDialog()
{
    delete ui;
}

void MojDialog::on_pushButton_clicked()
{
   _root->addFixtureChild();
}
