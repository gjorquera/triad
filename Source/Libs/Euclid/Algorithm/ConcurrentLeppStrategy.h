#pragma once

#include <qtconcurrentmap.h>
#include "LeppStrategy.h"

namespace Euclid
{
    template <class Kernel>
    class Refined
    {
    public:
        typedef typename Kernel::Point  Point;
        typedef typename Kernel::Vector Vector;
        typedef typename Euclid::Vertex<Kernel>   Vertex;
        typedef typename Euclid::Triangle<Kernel> Triangle;
        typedef typename Euclid::TriMesh<Kernel>  TriMesh;

        Refined(Criterion<Kernel>* criterion)
        {
            _criterion = criterion;
        }

        void operator()(Triangle* triangle)
        {
            if (_criterion->test(triangle)) {
                /// @todo refine triangle
            }
        }

    private:
        Criterion<Kernel>* _criterion;
    };

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
            TriMesh* trimesh = Strategy<Kernel>::trimesh();
            QtConcurrent::map(trimesh->triangles(), Refined<Kernel>(&criterion));
        }
    };
}

