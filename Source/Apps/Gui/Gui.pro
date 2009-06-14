QT += opengl
TEMPLATE = app
TARGET = TriadGui
DESTDIR = ../../../Bin
LIBS += -lViewer -lEuclid

include(../../Workbench.pri)

SOURCES += Main.cpp \
    MainWindow.cpp \
    MeshViewer.cpp \
    TriangleFigure.cpp \
    TriMesh.cpp \
    Algorithm/LeppStrategy.cpp \
    Decorator/LeppDecorator.cpp \
    Decorator/NeighborDecorator.cpp \
    Decorator/NormalDecorator.cpp \
    Decorator/SelectedDecorator.cpp \
    Dialog/LongestEdgeDialog.cpp \
    Dialog/PercentageDialog.cpp
HEADERS += Kernel.h \
    MainWindow.h \
    MeshViewer.h \
    TriangleFigure.h \
    TriMesh.h \
    Algorithm/LeppStrategy.h \
    Decorator/LeppDecorator.h \
    Decorator/NeighborDecorator.h \
    Decorator/NormalDecorator.h \
    Decorator/SelectedDecorator.h \
    Dialog/LongestEdgeDialog.h \
    Dialog/PercentageDialog.h
FORMS += MainWindow.ui \
    Dialog/LongestEdgeDialog.ui \
    Dialog/PercentageDialog.ui

