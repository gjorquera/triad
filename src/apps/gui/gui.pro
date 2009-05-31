QT += opengl
TEMPLATE = app
TARGET = Triad
DESTDIR = ../../../bin

include(../../qworkbench.pri)

SOURCES += Main.cpp \
    MainWindow.cpp \
    decoratedtriangle.cpp \
    triangle.cpp \
    neighbordecorator.cpp
HEADERS += MainWindow.h \
    decoratedtriangle.h \
    triangle.h \
    neighbordecorator.h
FORMS += MainWindow.ui

