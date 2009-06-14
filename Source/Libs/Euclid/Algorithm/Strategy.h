#pragma once

#include <cassert>
#include <QListIterator>
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
        typedef Criterion<Kernel> Criterion;
        typedef TriMesh<Kernel>   TriMesh;

        Strategy(TriMesh* trimesh = 0)
        {
            _trimesh = trimesh;
        }

        virtual ~Strategy()
        {
        }

        void setTriMesh(TriMesh* trimesh)
        {
            assert(0 != trimesh);
            _trimesh = trimesh;
        }

        virtual void refine(const Criterion& criterion) = 0;

    protected:
        TriMesh* trimesh()
        {
            assert(0 != _trimesh);
            return _trimesh;
        }

    private:
        TriMesh* _trimesh;
    };
}

