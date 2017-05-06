QT += core
QT -= gui

CONFIG += c++11

TARGET = QtNetCoreSandbox
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

include(QtNetCore.pri)

SOURCES += main.cpp



DEFINES += QT_DEPRECATED_WARNINGS
