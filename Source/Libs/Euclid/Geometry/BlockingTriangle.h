#pragma once

#include <QMutex>
#include "Triangle.h"

namespace Euclid
{

    template <class Kernel>
    class BlockingTriangle
    {
    public:
        typedef typename Kernel::Vector       Vector;
        typedef typename Kernel::TriangleInfo Info;
        typedef Vertex<Kernel>                Vertex;

        BlockingTriangle(Vertex* v1, Vertex* v2, Vertex* v3)
            : Triangle<Kernel>(v1, v2, v3)
        {
        }

        ~BlockingTriangle()
        {
        }

        QMutex& mutex()
        {
            return lock;
        }

    private:
        QMutex lock;
    };
}

