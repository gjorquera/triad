QT += opengl
TEMPLATE = app
TARGET = Triad
DESTDIR = ../../../Bin
LIBS += -lViewer -lEuclid

include(../../Workbench.pri)

SOURCES += Main.cpp \
    MainWindow.cpp \
    MeshViewer.cpp \
    TriangleDecorator.cpp
    Decorator/NeighborDecorator.cpp \
    Decorator/SelectedDecorator.cpp \
HEADERS += Kernel.h \
    MainWindow.h \
    MeshViewer.h \
    TriangleDecorator.h
    Decorator/NeighborDecorator.h \
    Decorator/SelectedDecorator.h \
FORMS += MainWindow.ui

