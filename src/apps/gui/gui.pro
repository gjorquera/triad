QT += opengl
TEMPLATE = app
TARGET = Triad
DESTDIR = ../../../bin

include(../../qworkbench.pri)

SOURCES += main.cpp \
    mainwindow.cpp \
    decoratedtriangle.cpp \
    triangle.cpp
HEADERS += mainwindow.h \
    decoratedtriangle.h \
    triangle.h
FORMS += mainwindow.ui

