#-------------------------------------------------
#
# Project created by QtCreator 2014-09-11T13:49:54
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = osgZknihy
TEMPLATE = app


SOURCES += main.cpp \
    viewerwidget.cpp \
    commonfuncitons.cpp \
    mojdialog.cpp \
    floorgeode.cpp \
    stagegeode.cpp \
    fixture2.cpp \
    vizualsceny2.cpp \
    skuskashadra.cpp \
    dereferred.cpp \
    fixture3.cpp

HEADERS  += \
    viewerwidget.h \
    commonfuncitons.h \
    mojdialog.h \
    floorgeode.h \
    stagegeode.h \
    fixture2.h \
    vizualsceny2.h \
    skuskashadra.h \
    dereferred.h \
    fixture3.h

FORMS    += \
    mojdialog.ui

INCLUDEPATH += . /usr/include

LIBS += -Lusr/lib -losg -losgViewer -lOpenThreads -losgUtil -losgDB -losgGA -losgQt -losgManipulator -losgShadow

OTHER_FILES += \
    SceneItems/Stage.osgt \
    SceneItems/PAR64.osgt

DISTFILES += \
    shaders/pass2.frag \
    shaders/pass3.frag \
    shaders/pass2.vert \
    shaders/pass3.vert \
    shaders/pass1Shadow.frag \
    shaders/rockwall.png \
    shaders/rockwall_NH.png
