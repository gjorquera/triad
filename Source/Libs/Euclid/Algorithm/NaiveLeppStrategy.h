#pragma once

#include "Strategy.h"

namespace Euclid
{

    /*!
     * A naive lepp bisection refinement algorithm
     */
    template <class Kernel>
    class NaiveLeppStrategy : public Strategy<Kernel>
    {
    public:
        typedef typename Kernel::Vector Vector;

        NaiveLeppStrategy(TriMesh<Kernel>* trimesh)
            : Strategy<Kernel>(trimesh)
        {
        }

        ~NaiveLeppStrategy()
        {
        }

        void refine(Criterion<Kernel>& criterion)
        {
            TriMesh<Kernel>* trimesh = Strategy<Kernel>::trimesh();
            QMutableListIterator<Triangle<Kernel>*> i(trimesh->triangles());
            while (i.hasNext())
            {
                if (criterion.test(i.next())) {
                    refineTriangle(i.next());
                }
            }
        }

    protected:
        void refineTriangle(Triangle<Kernel>*)
        {
            /// @todo implement this method
        }

        Triangle<Kernel>* longestEdgeNeighbor(Triangle<Kernel>* triangle)
        {
            Vector max;
            int index = -1;

            for (int i=0; i<3; i++)
            {
                const Vector* e = triangle->edge(i);
                if (max.distance() < e->distance()) {
                    max = *e;
                    index = i;
                }
                delete e;
            }

            assert(-1 != index);

            return const_cast<Triangle<Kernel>*>(triangle->neighbor(index));
        }

        bool isTerminal(Triangle<Kernel>* triangle)
        {
            Triangle<Kernel>* neighbor = longestEdgeNeighbor(triangle);
            if (0 == neighbor || triangle == longestEdgeNeighbor(neighbor)) {
                return true;
            }
            return false;
        }
    };
}

