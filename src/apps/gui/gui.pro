TEMPLATE = app
TARGET = Triad
DESTDIR = ../../../bin

include(../../qworkbench.pri)

SOURCES += main.cpp \
    mainwindow.cpp
HEADERS += mainwindow.h
FORMS += mainwindow.ui

