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
    optiondemowindow.cpp \
    optiontestwindow.cpp \
    testwindow.cpp \
    practicwindow.cpp \
    adminmainwindow.cpp \
    aboutwindowinformation.cpp \
    userprofilewindow.cpp \
    useroptionwindow.cpp \
    adminpanelwindow.cpp \
    adduserwindow.cpp \
    edituserwindow.cpp \
    addpracticwork.cpp \
    editpracticwork.cpp \
    userteststatswindow.cpp \
    admintheorywindow.cpp \
    opentheoryfile.cpp

HEADERS  += mainwindow.h \
    authorizationwindow.h \
    theorywindow.h \
    demonstrationwindow.h \
    geometry.h \
    sphere.h \
    light.h \
    material.h \
    optiondemowindow.h \
    optiontestwindow.h \
    testwindow.h \
    practicwindow.h \
    adminmainwindow.h \
    aboutwindowinformation.h \
    userprofilewindow.h \
    useroptionwindow.h \
    adminpanelwindow.h \
    adduserwindow.h \
    edituserwindow.h \
    addpracticwork.h \
    editpracticwork.h \
    sql_requests.h \
    userteststatswindow.h \
    admintheorywindow.h \
    opentheoryfile.h

FORMS    += mainwindow.ui \
    authorizationwindow.ui \
    theorywindow.ui \
    demonstrationwindow.ui \
    optiondemowindow.ui \
    optiontestwindow.ui \
    testwindow.ui \
    practicwindow.ui \
    adminmainwindow.ui \
    aboutwindowinformation.ui \
    userprofilewindow.ui \
    useroptionwindow.ui \
    adminpanelwindow.ui \
    adduserwindow.ui \
    edituserwindow.ui \
    addpracticwork.ui \
    editpracticwork.ui \
    userteststatswindow.ui \
    admintheorywindow.ui \
    opentheoryfile.ui

RESOURCES += \
    images.qrc \
    files.qrc
