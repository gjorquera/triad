QT += opengl
TEMPLATE = app
TARGET = Triad
DESTDIR = ../../../bin

include(../../qworkbench.pri)

SOURCES += Main.cpp \
    MainWindow.cpp \
    decoratedtriangle.cpp \
    Triangle.cpp \
    neighbordecorator.cpp
HEADERS += MainWindow.h \
    decoratedtriangle.h \
    Triangle.h \
    neighbordecorator.h
FORMS += MainWindow.ui

