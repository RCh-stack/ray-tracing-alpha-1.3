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
    adminpanelwindow.cpp \
    adduserwindow.cpp \
    edituserwindow.cpp \
    addpracticwork.cpp \
    editpracticwork.cpp \
    userteststatswindow.cpp \
    admintheorywindow.cpp \
    opentheoryfile.cpp \
    editingtoolswindow.cpp \
    adminpracticwindow.cpp \
    admintestwindow.cpp \
    checkpracticworkwindow.cpp \
    formatnotewindow.cpp \
    createpracticwindow.cpp \
    openpracticfile.cpp \
    changepracticwindow.cpp \
    userpracticstatswindow.cpp \
    usersteststatswindow.cpp \
    createtestwindow.cpp \
    opentestfile.cpp \
    changetestwindow.cpp \
    userhelpwindow.cpp \
    adminhelpwindow.cpp \
    instructionwindow.cpp \
    viewresulttestwindow.cpp \
    adminoptionwindow.cpp \
    listformatfile.cpp \
    addformatfile.cpp \
    editformatfile.cpp

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
    adminpanelwindow.h \
    adduserwindow.h \
    edituserwindow.h \
    addpracticwork.h \
    editpracticwork.h \
    sql_requests.h \
    userteststatswindow.h \
    admintheorywindow.h \
    opentheoryfile.h \
    editingtoolswindow.h \
    adminpracticwindow.h \
    admintestwindow.h \
    checkpracticworkwindow.h \
    formatnotewindow.h \
    createpracticwindow.h \
    openpracticfile.h \
    changepracticwindow.h \
    userpracticstatswindow.h \
    usersteststatswindow.h \
    createtestwindow.h \
    opentestfile.h \
    changetestwindow.h \
    userhelpwindow.h \
    adminhelpwindow.h \
    instructionwindow.h \
    viewresulttestwindow.h \
    adminoptionwindow.h \
    listformatfile.h \
    addformatfile.h \
    editformatfile.h

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
    adminpanelwindow.ui \
    adduserwindow.ui \
    edituserwindow.ui \
    addpracticwork.ui \
    editpracticwork.ui \
    userteststatswindow.ui \
    admintheorywindow.ui \
    opentheoryfile.ui \
    editingtoolswindow.ui \
    adminpracticwindow.ui \
    admintestwindow.ui \
    checkpracticworkwindow.ui \
    formatnotewindow.ui \
    createpracticwindow.ui \
    openpracticfile.ui \
    changepracticwindow.ui \
    userpracticstatswindow.ui \
    usersteststatswindow.ui \
    createtestwindow.ui \
    opentestfile.ui \
    changetestwindow.ui \
    userhelpwindow.ui \
    adminhelpwindow.ui \
    instructionwindow.ui \
    viewresulttestwindow.ui \
    adminoptionwindow.ui \
    listformatfile.ui \
    addformatfile.ui \
    editformatfile.ui

RESOURCES += \
    images.qrc \
    files.qrc
