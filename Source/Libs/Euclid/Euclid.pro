TEMPLATE = lib
CONFIG += staticlib
DESTDIR = ../../../Static

include(../../Workbench.pri)

HEADERS += Algorithm/Criterion.h \
    Algorithm/LongestEdgeCriterion.h \
    Algorithm/NaiveLeppStrategy.h \
    Algorithm/Strategy.h \
    Geometry/M2dFormatIO.h \
    Geometry/Triangle.h \
    Geometry/TriMesh.h \
    Geometry/TriMeshIO.h \
    Geometry/Vertex.h \
    Type/DefaultKernel.h \
    Type/NumTraits.h \
    Type/Point.h \
    Type/Vector.h

