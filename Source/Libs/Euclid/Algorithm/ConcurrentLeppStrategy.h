#pragma once

#include "LeppStrategy.h"

namespace Euclid
{

    template <class Kernel>
    class ConcurrentLeppStrategy : public LeppStrategy<Kernel>
    {
    public:
        typedef typename Kernel::Point  Point;
        typedef typename Kernel::Vector Vector;
        typedef typename Euclid::Vertex<Kernel>   Vertex;
        typedef typename Euclid::Triangle<Kernel> Triangle;
        typedef typename Euclid::TriMesh<Kernel>  TriMesh;

        ConcurrentLeppStrategy(TriMesh* trimesh = 0)
            : LeppStrategy<Kernel>(trimesh)
        {
        }

        ~ConcurrentLeppStrategy()
        {
        }

        void refine(Criterion<Kernel>& criterion)
        {
        }
    };
}

