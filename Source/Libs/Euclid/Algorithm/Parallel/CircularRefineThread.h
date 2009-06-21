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
        typedef Triangle<Kernel>  TriangleT;
        typedef TriMesh<Kernel>   TriMesh;
        typedef Criterion<Kernel> Criterion;

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
                            //refined = refineTriangle(triangle);
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
    };
}

