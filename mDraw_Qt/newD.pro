#-------------------------------------------------
#
# Project created by QtCreator 2016-04-08T10:26:04
#
#-------------------------------------------------

QT       += core gui
QT       += serialport
QT      += svg
QT       += opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = newD
TEMPLATE = app


SOURCES += main.cpp\
        newmdraw.cpp \
    carsetup.cpp \
    eggsetup.cpp \
    parsergui.cpp \
    scarasetup.cpp \
    spidersetup.cpp \
    wiregui.cpp \
    wiregui_xy.cpp \
    xysetup.cpp \
    scara.cpp \
    car.cpp \
    xyrobot.cpp \
    robotscene.cpp \
    XGetopt.c \
    svgpath.cpp \
    nanosvg.c \
    gmodel.cpp \
    graph.cpp \
    readgcode.cpp \
    svg2gcode.c


HEADERS  += newmdraw.h \
    carsetup.h \
    eggsetup.h \
    parsergui.h \
    scarasetup.h \
    spidersetup.h \
    wiregui.h \
    wiregui_xy.h \
    xysetup.h \
    scara.h \
    car.h \
    xyrobot.h \
    robotscene.h \
    nanosvg.h \
    XGetopt.h \
    svg2gcode.h \
    svgpath.h \
    gmodel.h \
    graph.h \
    readgcode.h

FORMS    += newmdraw.ui \
    carsetup.ui \
    eggsetup.ui \
    parsergui.ui \
    scarasetup.ui \
    spidersetup.ui \
    wiregui.ui \
    wiregui_xy.ui \
    xysetup.ui

RESOURCES += \
    images.qrc
