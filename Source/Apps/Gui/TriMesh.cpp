#include "TriMesh.h"

namespace App
{

    TriMesh::TriMesh()
        : Euclid::TriMesh<Kernel>()
    {
    }

    void
    TriMesh::select(const Euclid::Criterion<Kernel>& criterion)
    {
        QMutableListIterator<Euclid::Triangle<Kernel>*> i(triangles());
        while (i.hasNext())
        {
            if (criterion.test(i.next())) {
                i.next()->info().selected = true;
            }
        }
    }
}

