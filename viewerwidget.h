#ifndef VIEWERWIDGET_H
#define VIEWERWIDGET_H

#include <QWidget>
#include <QTimer>
#include <osg/Geode>
#include <osgViewer/Viewer>
#include <osgQt/GraphicsWindowQt>
#include <vizualsceny.h>

class ViewerWidget : public QWidget
{
    Q_OBJECT
public:
    ViewerWidget( osgQt::GraphicsWindowQt* gw, vizualSceny* scene );
    vizualSceny *_scene;
signals:

public slots:

protected:
    virtual void paintEvent( QPaintEvent* /*event*/ )
    { _viewer.frame(); }

    osgViewer::Viewer _viewer;
    QTimer _timer;


};

#endif // VIEWERWIDGET_H
