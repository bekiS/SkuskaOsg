#ifndef VIEWERWIDGET_H
#define VIEWERWIDGET_H

#include <QWidget>
#include <QTimer>
#include <osg/Geode>
#include <osgViewer/Viewer>
#include <osgQt/GraphicsWindowQt>


class ViewerWidget : public QWidget
{
    Q_OBJECT
public:
    ViewerWidget( osgQt::GraphicsWindowQt* gw, osg::Node* scene );

signals:

public slots:

protected:
    virtual void paintEvent( QPaintEvent* event )
    { _viewer.frame(); }

    osgViewer::Viewer _viewer;
    QTimer _timer;
};

#endif // VIEWERWIDGET_H
