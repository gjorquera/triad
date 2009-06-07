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

        void refine(Criterion& criterion)
        {
            TriMesh<Kernel>* trimesh = Strategy<Kernel>::trimesh();
            TriMesh<Kernel>::Iterator i;
            for (i = trimesh->begin(); i != trimesh->end(); i++)
            {
                if (criterion.test(*i)) {
                    refineTriangle(*i);
                }
            }
        }

    protected:
        void refineTriangle(Triangle<Kernel>* triangle)
        {
        }
    };
}

