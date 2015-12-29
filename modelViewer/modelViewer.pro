#-------------------------------------------------
#
# Project created by QtCreator 2015-12-28T18:23:42
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = modelViewer
TEMPLATE = app

CONFIG += c++11


SOURCES += main.cpp\
        mainwindow.cpp \
    ../RayTracing/camera/camera.cpp \
    ../RayTracing/geometry/Matrix.cpp \
    ../RayTracing/ray/ray.cpp \
    ../RayTracing/scene/light.cpp \
    ../RayTracing/scene/scene.cpp \
    ../RayTracing/scene/SimpleObject.cpp \
    ../RayTracing/raytracer.cpp \
    ../RayTracing/geometry/Vec3d.cpp

HEADERS  += mainwindow.h \
    ../RayTracing/util.h \
    ../RayTracing/camera/camera.h \
    ../RayTracing/geometry/geometry.h \
    ../RayTracing/geometry/Matrix.h \
    ../RayTracing/geometry/myMath.h \
    ../RayTracing/geometry/Num.h \
    ../RayTracing/ray/color.h \
    ../RayTracing/ray/ray.h \
    ../RayTracing/scene/entity.h \
    ../RayTracing/scene/light.h \
    ../RayTracing/scene/Material.h \
    ../RayTracing/scene/scene.h \
    ../RayTracing/scene/SimpleObject.h \
    ../RayTracing/scene/texture.h \
    ../RayTracing/raytracer.h \
    ../RayTracing/geometry/Vec3d.h

FORMS    += mainwindow.ui
