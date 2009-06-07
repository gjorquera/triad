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
        Iterator i;
        for (i = begin(); i != end(); i++)
        {
            if (criterion.test(*i)) {
                (*i)->info().selected = true;
            }
        }
    }
}

