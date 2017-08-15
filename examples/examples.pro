QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4) {
  QT += widgets
  # Qt >= 5.8
  greaterThan(QT_MAJOR_VERSION, 5)|greaterThan(QT_MINOR_VERSION, 7): QT += gui-private
  else: QT += platformsupport-private
}

TEMPLATE = app
TARGET = examples

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

LIBS += -L$$OUT_PWD/../src/ -ldtkwm

message($$OUT_PWD)

CONFIG += link_pkgconfig
PKGCONFIG +=  dtkcore

INCLUDEPATH += $$PWD/../src

