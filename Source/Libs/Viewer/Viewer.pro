QT += opengl
TEMPLATE = lib
CONFIG += staticlib
DESTDIR = ../../../Static

include(../../Workbench.pri)

SOURCES += ComplexDecorator.cpp \
    Figure.cpp \
    FigureDecorator.cpp \
    IFigure.cpp

HEADERS += ComplexDecorator.h \
    Figure.h \
    FigureDecorator.h \
    IFigure.h \
    Initializer.h \
    OrthographicProjection.h \
    Projection.h \
    Widget.h

