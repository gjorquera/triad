QT += opengl
TEMPLATE = app
TARGET = Triad
DESTDIR = ../../../Bin
LIBS += -lViewer -lEuclid

include(../../Workbench.pri)

SOURCES += Main.cpp \
    MainWindow.cpp \
    MeshViewer.cpp \
    TriangleFigure.cpp \
    Decorator/NeighborDecorator.cpp \
    Decorator/SelectedDecorator.cpp
HEADERS += Kernel.h \
    MainWindow.h \
    MeshViewer.h \
    TriangleFigure.h \
    Decorator/NeighborDecorator.h \
    Decorator/SelectedDecorator.h
FORMS += MainWindow.ui

