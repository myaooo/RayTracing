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

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../../../usr/local/lib/release/ -lopencv_core.3.0.0
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../../../usr/local/lib/debug/ -lopencv_core.3.0.0
else:unix: LIBS += -L$$PWD/../../../../../../../usr/local/lib/ -lopencv_core.3.0.0
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../../../usr/local/lib/release/ -lopencv_imgproc.3.0.0
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../../../usr/local/lib/debug/ -lopencv_imgproc.3.0.0
else:unix: LIBS += -L$$PWD/../../../../../../../usr/local/lib/ -lopencv_imgproc.3.0.0
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../../../usr/local/lib/release/ -lopencv_imgcodecs.3.0.0
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../../../usr/local/lib/debug/ -lopencv_imgcodecs.3.0.0
else:unix: LIBS += -L$$PWD/../../../../../../../usr/local/lib/ -lopencv_imgcodecs.3.0.0
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../../../usr/local/lib/release/ -lopencv_highgui.3.0.0
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../../../usr/local/lib/debug/ -lopencv_highgui.3.0.0
else:unix: LIBS += -L$$PWD/../../../../../../../usr/local/lib/ -lopencv_highgui.3.0.0

INCLUDEPATH += $$PWD/../../../../../../../usr/local/include


SOURCES += main.cpp\
        mainwindow.cpp \
    ../RayTracing/camera/camera.cpp \
    ../RayTracing/geometry/Matrix.cpp \
    ../RayTracing/geometry/Vec3d.cpp \
    ../RayTracing/geometry/Vec4d.cpp \
    ../RayTracing/scene/light.cpp \
    ../RayTracing/scene/scene.cpp \
    ../RayTracing/scene/SimpleObject.cpp \
    ../RayTracing/color.cpp \
    ../RayTracing/raytracer.cpp \
    ../RayTracing/renderer.cpp

HEADERS  += mainwindow.h \
    ../RayTracing/camera/camera.h \
    ../RayTracing/geometry/bbox.h \
    ../RayTracing/geometry/intersectable.h \
    ../RayTracing/geometry/Matrix.h \
    ../RayTracing/geometry/myMath.h \
    ../RayTracing/geometry/Num.h \
    ../RayTracing/geometry/plane.h \
    ../RayTracing/geometry/ray.h \
    ../RayTracing/geometry/Vec3d.h \
    ../RayTracing/geometry/Vec4d.h \
    ../RayTracing/scene/light.h \
    ../RayTracing/scene/material.h \
    ../RayTracing/scene/renderable.h \
    ../RayTracing/scene/rplane.h \
    ../RayTracing/scene/scene.h \
    ../RayTracing/scene/SimpleObject.h \
    ../RayTracing/scene/texture.h \
    ../RayTracing/color.h \
    ../RayTracing/geometry.h \
    ../RayTracing/raytracer.h \
    ../RayTracing/renderer.h \
    ../RayTracing/util.h

FORMS    += mainwindow.ui
