#pragma once

#include "Strategy.h"

namespace Euclid
{

    /*!
     * Parallel version of the Lepp-Bisection algorithm implemented with
     * QThreads.
     */
    template <class Kernel>
    class QThreadLeppStrategy : public Strategy<Kernel>
    {
    public:
        typedef Triangle<Kernel>  TriangleT;
        typedef Criterion<Kernel> Criterion;
        typedef TriMesh<Kernel>   TriMesh;

        QThreadLeppStrategy(TriMesh* trimesh = 0)
            : Strategy<Kernel>(trimesh)
        {
        }

        ~QThreadLeppStrategy()
        {
        }

        void refine(const Criterion& criterion)
        {
            TriMesh* trimesh = this->trimesh();
            QListIterator<TriangleT*> i(trimesh->triangles());

            QList<TriangleT*> toRefine;
            while (i.hasNext()) {
                TriangleT* t = i.next();
                if (criterion.test(t)) {
                    toRefine.append(t);
                }
            }
        }
    };
}

