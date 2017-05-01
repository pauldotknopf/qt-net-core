DEFINES += QTNETCORE_LIBRARY
DEFINES += _TARGET_AMD64_

DEFINES += HOST_PKG_VER 1.1.0
DEFINES += REPO_COMMIT_HASH 9999

INCLUDEPATH += $$PWD
INCLUDEPATH += $$PWD/common
INCLUDEPATH += $$PWD/cli/fxr

HEADERS += $$PWD/qtnetcore.h\
    $$PWD/qtnetcore_global.h \
    $$PWD/common/pal.h \
    $$PWD/common/trace.h \
    $$PWD/common/utils.h \
    $$PWD/cli/fxr/fx_ver.h \
    $$PWD/error_codes.h

SOURCES += $$PWD/qtnetcore.cpp \
    $$PWD/common/trace.cpp \
    $$PWD/common/utils.cpp \
    $$PWD/cli/fxr/fx_ver.cpp

unix {
    SOURCES += $$PWD/common/pal.unix.cpp
}

windows {
    SOURCES += $$PWD/common/pal.windows.cpp
    LIBS += Shell32.lib
}
