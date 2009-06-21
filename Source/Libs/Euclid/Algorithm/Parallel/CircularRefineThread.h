#pragma once

#include <QListIterator>
#include <QRunnable>
#include "../Lepp/Library.h"
#include "../../Geometry/Triangle.h"
#include "../../Geometry/TriMesh.h"

namespace Euclid
{

    template <class Kernel>
    class CircularRefineThread : public QRunnable
    {
    public:
        typedef Triangle<Kernel>    TriangleT;
        typedef TriMesh<Kernel>     TriMesh;
        typedef Criterion<Kernel>   Criterion;
        typedef LeppLibrary<Kernel> LeppLibrary;

        CircularRefineThread(TriMesh* trimesh, const Criterion* criterion)
        {
            _trimesh = trimesh;
            _criterion = criterion;
        }

        void run()
        {
            QListIterator<TriangleT*> i(_trimesh->triangles());
            bool done;
            do {
                done = true;
                while (i.hasNext()) {
                    TriangleT* triangle = i.next();
                    if (_criterion->test(triangle)) {
                        done = false;

                        bool obtained = triangle->mutex().tryLock();
                        if (! obtained) continue;

                        TriangleT* refined = 0;
                        do {
                            refined = refineTriangle(triangle);
                        } while (refined != 0 && refined != triangle);

                        triangle->mutex().unlock();
                    }
                }
                i.toFront();
            } while (! done);
        }

    private:
        TriMesh* _trimesh;
        const Criterion* _criterion;

        TriangleT* refineTriangle(TriangleT* triangle)
        {
            TriangleT* neighbor = LeppLibrary::longestEdgeNeighbor(triangle);

            if (0 != neighbor) {
                bool obtained = neighbor->mutex().tryLock();
                if (! obtained) return 0;
            }

            TriangleT* refined = 0;

            if (LeppLibrary::isTerminal(triangle, neighbor)) {
                refineTerminal(triangle);
                refined = triangle;
            } else {
                assert(0 != neighbor);
                refined = refineTriangle(neighbor);
            }

            if (0 != neighbor) {
                neighbor->mutex().unlock();
            }

            return refined;
        }

        void refineTerminal(TriangleT* triangle)
        {
            triangle->setSelected(false);
        }
    };
}

