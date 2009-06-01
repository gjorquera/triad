TEMPLATE = lib
CONFIG += staticlib
DESTDIR = ../../../Static

include(../../Workbench.pri)

HEADERS += Geometry/Vertex.h \
    Type/DefaultKernel.h \
    Type/NumTraits.h \
    Type/Point.h \
    Type/Vector.h

