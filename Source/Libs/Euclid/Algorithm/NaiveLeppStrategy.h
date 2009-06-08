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
            typename QList<Triangle<Kernel>*>::Iterator i;
            for (i = trimesh->begin(); i != trimesh->end(); i++)
            {
                if (criterion.test(*i)) {
                    refineTriangle(*i);
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
            if (longestEdgeNeighbor(triangle) == 0
                || longestEdgeNeighbor(triangle) == triangle)
                return true;
            return false;
        }
    };
}

