QT       += core gui  x11extras dbus dtkcore
greaterThan(QT_MAJOR_VERSION, 4) {
  QT += widgets core gui
  # Qt >= 5.8
  greaterThan(QT_MAJOR_VERSION, 5)|greaterThan(QT_MINOR_VERSION, 7): QT += gui-private
  else: QT += platformsupport-private
}

TEMPLATE = lib
TARGET = dtkwm
DEFINES += LIBDTKWM_LIBRARY

load(dtk_build)
load(dtk_module)
load(dtk_cmake)

#linux* {
    CONFIG += link_pkgconfig
    PKGCONFIG += xcb xcb-util dtkcore
    LIBS += -lX11 -lXext
#}

SOURCES += \
    dscreenwindowsutil.cpp \
    dwindowmanager.cpp

HEADERS += \
    dtkwm_global.h \
    dscreenwindowsutil.h \
    dwindowmanager.h

INCLUDEPATH += $$PWD

# ----------------------------------------------
#install config
includes.files += $$PWD/*.h

INSTALLS += includes target
