#pragma once

#include <cassert>
#include "Criterion.h"
#include "../Geometry/TriMesh.h"

namespace Euclid
{

    /*!
     * Represents refinement algorithms applicable to trimeshes.
     *
     * Concrete refinement algorithms must implement the \b refine method which
     * get's the \b trimesh and refines using the given criterion.
     */
    template <class Kernel>
    class Strategy
    {
    public:
        Strategy(TriMesh<Kernel>* trimesh = 0)
        {
            _trimesh = trimesh;
        }

        virtual ~Strategy()
        {
        }

        void setTriMesh(TriMesh<Kernel>* trimesh)
        {
            assert(0 != trimesh);
            _trimesh = trimesh;
        }

        virtual void refine(Criterion<Kernel>& criterion) = 0;

    protected:
        TriMesh<Kernel>* trimesh()
        {
            assert(0 != _trimesh);
            return _trimesh;
        }

    private:
        TriMesh<Kernel>* _trimesh;
    };
}

