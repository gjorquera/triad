QT += opengl
TEMPLATE = app
TARGET = Triad
DESTDIR = ../../../Bin
LIBS += -lViewer -lEuclid

include(../../Workbench.pri)

SOURCES += Main.cpp \
    MainWindow.cpp \
    Decorator/NeighborDecorator.cpp \
    Decorator/SelectedDecorator.cpp \
    Figure/TriangleDecorator.cpp
HEADERS += MainWindow.h \
    Decorator/NeighborDecorator.h \
    Decorator/SelectedDecorator.h \
    Figure/TriangleDecorator.h
FORMS += MainWindow.ui

