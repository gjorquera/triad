#pragma once

#include <cassert>
#include "../Geometry/TriMesh.h"

namespace Euclid
{

    template <class Kernel>
    class Validation
    {
    public:
        typedef TriMesh<Kernel> TriMesh;

        Validation(TriMesh* trimesh)
        {
            assert(0 != trimesh);
            _trimesh = trimesh;
        }

        virtual ~Validation()
        {
        }

        virtual bool validate() = 0;

    protected:
        TriMesh* trimesh()
        {
            return _trimesh;
        }

    private:
        TriMesh* _trimesh;
    };
}

