DEFINES += QTNETCORE_LIBRARY
DEFINES += _TARGET_AMD64_

INCLUDEPATH += $$PWD

SOURCES += $$PWD/qtnetcore.cpp \
    $$PWD/trace.cpp \
    $$PWD/utils.cpp

unix {
    SOURCES += $$PWD/pal.unix.cpp
}

windows {
    SOURCES += $$PWD/pal.windows.cpp
    LIBS += Shell32.lib
}

HEADERS += $$PWD/qtnetcore.h\
    $$PWD/qtnetcore_global.h \
    $$PWD/pal.h \
    $$PWD/trace.h \
    $$PWD/utils.h
