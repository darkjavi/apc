#-------------------------------------------------
#
# Project created by QtCreator 2014-05-03T04:41:58
#
#-------------------------------------------------

QT       += core gui opengl

CONFIG += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets network

TARGET = printer_controller
TEMPLATE = app

INCLUDEPATH += vpgles2 vpgles2/geo vpgles2/gl

SOURCES += main.cpp\
        pcontrollergui.cpp \
    pprinter.cpp \
    pprinterserial.cpp \
    pprintercontroller.cpp \
    pprinterwidget.cpp \
    vpgles2/gl/vpgles2scene.cpp \
    vpgles2/gl/vpgles2shader.cpp \
    vpgles2/gl/vphud.cpp \
    vpgles2/gl/vpgles2widget.cpp \
    vpgles2/gl/vpgles2textureloader.cpp \
    vpgles2/gl/vphudbuttonrect.cpp \
    vpgles2/gl/vphudelement.cpp \
    vpgles2/gl/vptcamera.cpp \
    vpgles2/gl/vphudscrollbar.cpp \
    vpgles2/geo/vp3dgeoaxis.cpp \
    vpgles2/geo/vp3dgeocamera.cpp \
    vpgles2/geo/vp3dgeoobj.cpp \
    vpgles2/geo/vp3dgeopart.cpp \
    vpgles2/geo/vp3dgeoprimitive.cpp

HEADERS  += pcontrollergui.h \
    pprinter.h \
    pprinterserial.h \
    pprintercontroller.h \
    pprinterwidget.h \
    vpgles2/gl/vpgles2scene.h \
    vpgles2/gl/vpgles2shader.h \
    vpgles2/gl/vphud.h \
    vpgles2/gl/vpgles2widget.h \
    vpgles2/gl/vpgles2textureloader.h \
    vpgles2/gl/vphudbuttonrect.h \
    vpgles2/gl/vphudelement.h \
    vpgles2/gl/vptcamera.h \
    vpgles2/gl/vphudscrollbar.h \
    vpgles2/gl/vphudincludes.h \
    vpgles2/geo/vp3dgeoaxis.h \
    vpgles2/geo/vp3dgeocamera.h \
    vpgles2/geo/vp3dgeoincludes.h \
    vpgles2/geo/vp3dgeoobj.h \
    vpgles2/geo/vp3dgeoprimitive.h \
    vpgles2/geo/vp3dgeopart.h

FORMS    += pcontrollergui.ui \
    pprinterwidget.ui

CONFIG += mobility
MOBILITY = 

include(vpgles2/qserialport/serialport-lib.pri)
#include(vpgles2/ViewportGLES2.pri) #Igual no hace falta cargar toda la libreria sino solo los modulos de gl

RESOURCES += \
    vpgles2/gl/shaders.qrc

OTHER_FILES += \
    vpgles2/gl/ShaderFTest.fsh \
    vpgles2/gl/simpleshader.fsh \
    vpgles2/gl/v_frag.fsh \
    vpgles2/gl/ShaderVTest.vsh \
    vpgles2/gl/simpleshader.vsh
