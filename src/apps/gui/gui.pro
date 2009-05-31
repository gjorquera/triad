QT += opengl
TEMPLATE = app
TARGET = Triad
DESTDIR = ../../../bin

include(../../qworkbench.pri)

SOURCES += main.cpp \
    mainwindow.cpp \
    decoratedtriangle.cpp \
    triangle.cpp \
    neighbordecorator.cpp
HEADERS += mainwindow.h \
    decoratedtriangle.h \
    triangle.h \
    neighbordecorator.h
FORMS += mainwindow.ui

