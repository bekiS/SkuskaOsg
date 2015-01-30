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
    cloneobjectroot.cpp \
    auto.cpp \
    vizualsceny.cpp \
    mojdialog.cpp \
    cone.cpp \
    floorgeode.cpp \
    stagegeode.cpp

HEADERS  += \
    viewerwidget.h \
    commonfuncitons.h \
    cloneobjectroot.h \
    auto.h \
    vizualsceny.h \
    mojdialog.h \
    cone.h \
    floorgeode.h \
    stagegeode.h

FORMS    += \
    mojdialog.ui

INCLUDEPATH += . /usr/include

LIBS += -Lusr/lib -losg -losgViewer -lOpenThreads -losgUtil -losgDB -losgGA -losgQt
