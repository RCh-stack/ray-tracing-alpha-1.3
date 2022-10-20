#-------------------------------------------------
#
# Project created by QtCreator 2022-09-26T18:20:02
#
#-------------------------------------------------

QT       += widgets
QT       += core gui
QT       += sql

CONFIG  +=   c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RayTracing
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    authorizationwindow.cpp \
    theorywindow.cpp \
    demonstrationwindow.cpp \
    testwindow.cpp

HEADERS  += mainwindow.h \
    authorizationwindow.h \
    theorywindow.h \
    demonstrationwindow.h \
    testwindow.h \
    geometry.h \
    sphere.h \
    light.h \
    material.h

FORMS    += mainwindow.ui \
    authorizationwindow.ui \
    theorywindow.ui \
    demonstrationwindow.ui \
    testwindow.ui

RESOURCES += \
    images.qrc \
    files.qrc
