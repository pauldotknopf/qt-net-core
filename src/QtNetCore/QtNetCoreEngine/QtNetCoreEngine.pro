#-------------------------------------------------
#
# Project created by QtCreator 2017-05-06T20:10:28
#
#-------------------------------------------------

QT       -= gui

TARGET = QtNetCoreEngine
TEMPLATE = lib
DESTDIR = ../

DEFINES += QTNETCOREENGINE_LIBRARY

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += qtnetcoreengine.cpp

HEADERS += qtnetcoreengine.h\
        qtnetcoreengine_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
