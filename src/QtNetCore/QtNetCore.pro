#-------------------------------------------------
#
# Project created by QtCreator 2017-04-30T21:33:37
#
#-------------------------------------------------

QT       -= gui

TARGET = QtNetCore
TEMPLATE = lib

DEFINES += QT_DEPRECATED_WARNINGS

include(QtNetCore.pri)

unix {
    target.path = /usr/lib
    INSTALLS += target
}
