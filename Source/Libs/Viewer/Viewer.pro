QT += opengl
TEMPLATE = lib
CONFIG += staticlib
DESTDIR = ../../../Static

include(../../Workbench.pri)

SOURCES += ComplexDecorator.cpp \
    Figure.cpp \
    FigureDecorator.cpp \
    FigureIterator.cpp \
    IFigure.cpp \
    Widget.cpp

HEADERS += ComplexDecorator.h \
    Figure.h \
    FigureDecorator.h \
    FigureIterator.h \
    IFigure.h \
    Widget.h

