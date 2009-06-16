#pragma once

#include "LeppStrategy.h"

namespace Euclid
{

    template <class Kernel>
    class QThreadLeppStrategy : public LeppStrategy<Kernel>
    {
    public:
        typedef Triangle<Kernel>  TriangleT;
        typedef Criterion<Kernel> Criterion;
        typedef TriMesh<Kernel>   TriMesh;

        QThreadLeppStrategy(TriMesh* trimesh = 0)
            : LeppStrategy<Kernel>(trimesh)
        {
        }

        ~QThreadLeppStrategy()
        {
        }

        void refine(const Criterion& criterion)
        {
            TriMesh* trimesh = this->trimesh();
            QListIterator<TriangleT*> i(trimesh->triangles());
            bool selected = false;
            do {
                while (i.hasNext()) {
                    TriangleT* t = i.next();
                    if (criterion.test(t)) {
                        selected = true;
                        // refine
                    }
                }
            } while (selected);
        }
    };
}

