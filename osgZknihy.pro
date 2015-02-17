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
    vizualsceny2.cpp

HEADERS  += \
    viewerwidget.h \
    commonfuncitons.h \
    mojdialog.h \
    floorgeode.h \
    stagegeode.h \
    fixture2.h \
    vizualsceny2.h

FORMS    += \
    mojdialog.ui

INCLUDEPATH += . /usr/include

LIBS += -Lusr/lib -losg -losgViewer -lOpenThreads -losgUtil -losgDB -losgGA -losgQt -losgManipulator

OTHER_FILES += \
    SceneItems/Stage.osgt \
    SceneItems/PAR64.osgt
