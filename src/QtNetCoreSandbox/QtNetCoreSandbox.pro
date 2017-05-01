QT += core
QT -= gui

CONFIG += c++11

TARGET = QtNetCoreSandbox
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp

include(../QtNetCore/QtNetCore.pri)

DEFINES += QT_DEPRECATED_WARNINGS
