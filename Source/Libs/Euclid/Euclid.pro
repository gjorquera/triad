TEMPLATE = lib
CONFIG += staticlib
DESTDIR = ../../../Static

include(../../Workbench.pri)

HEADERS += Type/DefaultKernel.h \
    Type/NumTraits.h \
    Type/Point.h \
    Type/Vector.h

