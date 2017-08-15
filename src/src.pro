include($$PWD/lib.pri)

QT       += core gui  x11extras dbus
greaterThan(QT_MAJOR_VERSION, 4) {
  QT += widgets core gui
  # Qt >= 5.8
  greaterThan(QT_MAJOR_VERSION, 5)|greaterThan(QT_MINOR_VERSION, 7): QT += gui-private
  else: QT += platformsupport-private
}

TEMPLATE = lib
TARGET = dtkwm
DEFINES += LIBDTKWM_LIBRARY

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
includes.path = $${DTK_INCLUDEPATH}/DWm

QMAKE_PKGCONFIG_LIBDIR = $$target.path
QMAKE_PKGCONFIG_VERSION = $$VERSION
QMAKE_PKGCONFIG_DESTDIR = pkgconfig

QMAKE_PKGCONFIG_NAME = DTK_WM
QMAKE_PKGCONFIG_DESCRIPTION = Deepin Tool Kit WM Header Files
QMAKE_PKGCONFIG_INCDIR = $$includes.path


