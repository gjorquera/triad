QT += opengl
TEMPLATE = app
TARGET = TriadGui
DESTDIR = ../../../Bin
LIBS += -lViewer -lEuclid

include(../../Workbench.pri)

SOURCES += Algorithm/LeppStrategy.cpp \
    Decorator/LeppDecorator.cpp \
    Decorator/NeighborDecorator.cpp \
    Decorator/NormalDecorator.cpp \
    Decorator/SelectedDecorator.cpp \
    Dialog/LongestEdgeDialog.cpp \
    Dialog/PercentageDialog.cpp \
    Main.cpp \
    MainWindow.cpp \
    MeshViewer.cpp \
    TriangleFigure.cpp
HEADERS += Algorithm/LeppStrategy.h \
    Decorator/LeppDecorator.h \
    Decorator/NeighborDecorator.h \
    Decorator/NormalDecorator.h \
    Decorator/SelectedDecorator.h \
    Dialog/LongestEdgeDialog.h \
    Dialog/PercentageDialog.h \
    Kernel.h \
    MainWindow.h \
    MeshViewer.h \
    TriangleFigure.h
FORMS += Dialog/LongestEdgeDialog.ui \
    Dialog/PercentageDialog.ui \
    MainWindow.ui

