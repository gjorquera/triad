QT += opengl
TEMPLATE = lib
CONFIG += staticlib
DESTDIR = ../../../Static

include(../../Workbench.pri)

SOURCES += ComplexDecorator.cpp \
    Figure.cpp \
    FigureDecorator.cpp \
    IFigure.cpp \
    Widget.cpp

HEADERS += ComplexDecorator.h \
    Figure.h \
    FigureDecorator.h \
    IFigure.h \
    Widget.h

