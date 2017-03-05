#-------------------------------------------------
#
# Project created by QtCreator 2017-03-05T11:36:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = IHMEcluse
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    vanne.cpp \
    porte.cpp \
    ecluse.cpp \
    signallum.cpp

HEADERS  += mainwindow.h \
    vanne.h \
    porte.h \
    ecluse.h \
    signallum.h \
    common.h

FORMS    += mainwindow.ui

RESOURCES += \
    images.qrc
