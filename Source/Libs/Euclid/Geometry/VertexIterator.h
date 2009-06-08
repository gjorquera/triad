#pragma once

#include <QListIterator>
#include "Vertex.h"

namespace Euclid
{

    template <class Kernel>
    class VertexIterator : public QListIterator<Vertex<Kernel>*>
    {
    public:
        VertexIterator(TriMesh<Kernel>& trimesh)
            : QListIterator<Vertex<Kernel>*>(trimesh->vertices())
        {
        }
    };
}

