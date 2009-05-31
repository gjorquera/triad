QT += opengl
TEMPLATE = app
TARGET = Triad
DESTDIR = ../../../bin

include(../../Workbench.pri)

SOURCES += Main.cpp \
    MainWindow.cpp \
    NeighborDecorator.cpp \
    SelectedDecorator.cpp \
    Triangle.cpp
HEADERS += MainWindow.h \
    NeighborDecorator.h \
    SelectedDecorator.h \
    Triangle.h
FORMS += MainWindow.ui

