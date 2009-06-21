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
        typedef typename Kernel::Point  Point;
        typedef Vertex<Kernel>      VertexT;
        typedef Edge<Kernel>        EdgeT;
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
                        if (! obtained) {
                            continue;
                        }

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
                if (! obtained) {
                    return 0;
                }
            }

            TriangleT* refined = 0;

            if (LeppLibrary::isTerminal(triangle, neighbor)) {
                bool result;
                if (0 != neighbor) {
                    result = refineTerminal(triangle, neighbor);
                } else {
                    result = refineTerminal(triangle);
                }
                if (result) {
                    refined = triangle;
                } else {
                    refined = 0;
                }
            } else {
                assert(0 != neighbor);
                refined = refineTriangle(neighbor);
            }

            if (0 != neighbor) {
                neighbor->mutex().unlock();
            }

            return refined;
        }

        VertexT* bisectedVertex(TriangleT* triangle)
        {
            const EdgeT* edge = LeppLibrary::longestEdge(triangle);
            Point point((edge->vector() / 2).terminal());
            VertexT* newVertex = new VertexT(point);
            _trimesh->verticesMutex().lock();
            _trimesh->addVertex(newVertex);
            _trimesh->verticesMutex().unlock();
            return newVertex;
        }

        bool refineTerminal(TriangleT* triangle)
        {
            assert(0 != triangle);

            /*int index = LeppLibrary::longestEdgeIndex(triangle);
            TriangleT* sideNeighbor = triangle->neighbor((index+1)%3);
            if (0 != sideNeighbor) {
                bool obtained = sideNeighbor->mutex().tryLock();
                if (! obtained) {
                    return false;
                }
            }*/

            VertexT* newVertex = bisectedVertex(triangle);

            TriangleT* newTriangle = LeppLibrary::bisect(triangle, newVertex);
            newTriangle->mutex().lock();

            _trimesh->trianglesMutex().lock();
            _trimesh->addTriangle(newTriangle);
            _trimesh->trianglesMutex().unlock();

            newTriangle->mutex().unlock();
            /*if (0 != sideNeighbor) {
                sideNeighbor->mutex().unlock();
            }*/

            return true;
        }

        bool refineTerminal(TriangleT* triangle, TriangleT* neighbor)
        {
            assert(0 != triangle && 0 != neighbor);

            /*int index1 = LeppLibrary::longestEdgeIndex(triangle);
            int index2 = LeppLibrary::longestEdgeIndex(neighbor);
            TriangleT* sideNeighbor1 = triangle->neighbor((index1+1)%3);
            TriangleT* sideNeighbor2 = neighbor->neighbor((index2+1)%3);
            if (0 != sideNeighbor1) {
                bool obtained = sideNeighbor1->mutex().tryLock();
                if (! obtained) {
                    return false;
                }
            }
            if (0 != sideNeighbor2) {
                bool obtained = sideNeighbor2->mutex().tryLock();
                if (! obtained) {
                    if (0 != sideNeighbor1) {
                        sideNeighbor1->mutex().unlock();
                    }
                    return false;
                }
            }*/

            VertexT* newVertex = bisectedVertex(triangle);

            TriangleT* newTriangle1 = LeppLibrary::bisect(triangle, newVertex);
            newTriangle1->mutex().lock();

            _trimesh->trianglesMutex().lock();
            _trimesh->addTriangle(newTriangle1);
            _trimesh->trianglesMutex().unlock();

            TriangleT* newTriangle2 = LeppLibrary::bisect(neighbor, newVertex);
            newTriangle2->mutex().lock();

            _trimesh->trianglesMutex().lock();
            _trimesh->addTriangle(newTriangle2);
            _trimesh->trianglesMutex().unlock();

            triangle->addNeighbor(newTriangle2);
            newTriangle2->addNeighbor(triangle);

            neighbor->addNeighbor(newTriangle1);
            newTriangle1->addNeighbor(neighbor);

            newTriangle1->mutex().unlock();
            newTriangle2->mutex().unlock();
            /*if (0 != sideNeighbor1) {
                sideNeighbor1->mutex().unlock();
            }
            if (0 != sideNeighbor2) {
                sideNeighbor2->mutex().unlock();
            }*/

            // We have just refined this triangle
            triangle->setSelected(false);

            return true;
        }
    };
}

