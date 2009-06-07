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
    TriMesh.cpp \
    Decorator/LeppDecorator.cpp \
    Decorator/NeighborDecorator.cpp \
    Decorator/NormalDecorator.cpp \
    Decorator/SelectedDecorator.cpp
HEADERS += Kernel.h \
    MainWindow.h \
    MeshViewer.h \
    TriangleFigure.h \
    TriMesh.h \
    Decorator/LeppDecorator.h \
    Decorator/NeighborDecorator.h \
    Decorator/NormalDecorator.h \
    Decorator/SelectedDecorator.h
FORMS += MainWindow.ui

