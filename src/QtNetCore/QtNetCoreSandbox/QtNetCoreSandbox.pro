QT += core
QT -= gui

CONFIG += c++11

TARGET = QtNetCoreSandbox
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app
DESTDIR = ../

SOURCES += main.cpp

DEFINES += QT_DEPRECATED_WARNINGS

LIBS += -L$$OUT_PWD/../ -lQtNetCoreEngine

INCLUDEPATH += $$PWD/../QtNetCoreEngine
DEPENDPATH += $$PWD/../QtNetCoreEngine
