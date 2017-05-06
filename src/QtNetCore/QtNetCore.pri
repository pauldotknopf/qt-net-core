DEFINES += QTNETCORE_LIBRARY
DEFINES += _TARGET_AMD64_

include(setup.pri)

INCLUDEPATH += $$PWD \
    $$PWD/common \
    $$PWD/cli/fxr \
    $$PWD/cli/json/casablanca/include


HEADERS += $$PWD/qtnetcore_global.h \
    $$PWD/qtnetcore.h \
    $$PWD/cli/fxr/fx_ver.h \
    $$PWD/common/trace.h \
    $$PWD/common/utils.h \
    $$PWD/common/pal.h \
    $$PWD/cli/libhost.h \
    $$PWD/cli/runtime_config.h \
    $$PWD/cli/json/casablanca/include/cpprest/json.h \
    $$PWD/cli/breadcrumbs.h \
    $$PWD/cli/args.h \
    $$PWD/cli/coreclr.h \
    $$PWD/cli/deps_resolver.h \
    $$PWD/cli/deps_format.h \
    $$PWD/cli/deps_entry.h

SOURCES += $$PWD/qtnetcore.cpp \
    $$PWD/cli/fxr/fx_ver.cpp \
    $$PWD/common/trace.cpp \
    $$PWD/common/utils.cpp \
    $$PWD/cli/libhost.cpp \
    $$PWD/cli/runtime_config.cpp \
    $$PWD/cli/json/casablanca/src/json/json.cpp \
    $$PWD/cli/json/casablanca/src/json/json_parsing.cpp \
    $$PWD/cli/json/casablanca/src/json/json_serialization.cpp \
    $$PWD/cli/json/casablanca/src/utilities/asyncrt_utils.cpp \
    $$PWD/cli/breadcrumbs.cpp \
    $$PWD/cli/args.cpp \
    $$PWD/cli/hostpolicy.cpp \
    $$PWD/cli/coreclr.cpp \
    $$PWD/cli/deps_resolver.cpp \
    $$PWD/cli/deps_format.cpp \
    $$PWD/cli/deps_entry.cpp

windows {
    SOURCES += $$PWD/common/pal.windows.cpp
    LIBS += Shell32.lib
} else {
    SOURCES += $$PWD/common/pal.unix.cpp
}

