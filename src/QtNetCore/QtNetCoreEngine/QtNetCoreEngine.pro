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
DEFINES += _TARGET_AMD64_
DEFINES += REPO_COMMIT_HASH=\\\"9999\\\"
DEFINES += HOST_PKG_VER=\\\"1.1.0\\\"

INCLUDEPATH += $$PWD/common \
    $$PWD/cli/fxr

SOURCES += $$PWD/qtnetcoreengine.cpp \
    $$PWD/common/utils.cpp \
    $$PWD/common/trace.cpp \
    $$PWD/cli/fxr/fx_ver.cpp

HEADERS += qtnetcoreengine.h \
    $$PWD/qtnetcoreengine_global.h \
    $$PWD/error_codes.h \
    $$PWD/common/utils.h \
    $$PWD/common/trace.h \
    $$PWD/common/pal.h \
    $$PWD/cli/fxr/fx_ver.h

windows {
    SOURCES += $$PWD/common/pal.windows.cpp
    LIBS += Shell32.lib
} else {
    SOURCES += $$PWD/common/pal.unix.cpp
}

unix {
    target.path = /usr/lib
    INSTALLS += target
}
