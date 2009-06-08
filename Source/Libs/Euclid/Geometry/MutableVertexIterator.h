#pragma once

#include <QMutableListIterator>
#include "TriMesh.h"
#include "Vertex.h"

namespace Euclid
{

    template <class Kernel>
    class TriMesh;

    template <class Kernel>
    class MutableVertexIterator : public QMutableListIterator<Vertex<Kernel>*>
    {
    public:
        MutableVertexIterator(TriMesh<Kernel>* trimesh)
            : QMutableListIterator<Vertex<Kernel>*>(trimesh->vertices())
        {
        }
    };
}

