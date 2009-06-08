#pragma once

#include "Strategy.h"

namespace Euclid
{

    template <class Kernel>
    class NaiveLeppStrategy : public Strategy<Kernel>
    {
    public:
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
            typename TriMesh<Kernel>::Iterator i;
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
    };
}

