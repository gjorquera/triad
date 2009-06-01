QT += opengl
TEMPLATE = lib
CONFIG += staticlib
DESTDIR = ../../../Static

include(../../Workbench.pri)

HEADERS += $$PWD/ComplexDecorator.h \
    $$PWD/Figure.h \
    $$PWD/FigureDecorator.h \
    $$PWD/IFigure.h \
    $$PWD/Initializer.h \
    $$PWD/OrthographicProjection.h \
    $$PWD/Projection.h \
    $$PWD/Widget.h

