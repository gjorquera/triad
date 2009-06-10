TEMPLATE = lib
CONFIG += staticlib
DESTDIR = ../../../Static

include(../../Workbench.pri)

HEADERS += Algorithm/ConcurrentLeppStrategy.h \
    Algorithm/Criterion.h \
    Algorithm/LongestEdgeCriterion.h \
    Algorithm/NaiveLeppStrategy.h \
    Algorithm/PercentageCriterion.h \
    Algorithm/Strategy.h \
    Geometry/BlockingTriangle.h \
    Geometry/M2dFormatIO.h \
    Geometry/Triangle.h \
    Geometry/TriMesh.h \
    Geometry/TriMeshIO.h \
    Geometry/Vertex.h \
    Type/DefaultKernel.h \
    Type/NumTraits.h \
    Type/Point.h \
    Type/Vector.h

