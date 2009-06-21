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
                bool obtained = triangle->tryLockNeighbors();
                if (! obtained) {
                    return 0;
                }
                if (0 != neighbor) {
                    obtained = neighbor->tryLockNeighbors();
                    if (! obtained) {
                        return 0;
                    }
                }
                refineTerminal(triangle, neighbor);
                refined = triangle;
                triangle->unlockNeighbors();
                if (0 != neighbor) {
                    neighbor->unlockNeighbors();
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

        void refineTerminal(TriangleT* triangle, TriangleT* neighbor)
        {
            // Calculating the bisection vertex
            const EdgeT* edge = LeppLibrary::longestEdge(triangle);
            Point point((edge->vector() / 2).terminal());
            VertexT* newVertex = new VertexT(point);
            _trimesh->verticesMutex().lock();
            _trimesh->addVertex(newVertex);
            _trimesh->verticesMutex().unlock();

            // Bisecting triangle
            int index = LeppLibrary::longestEdgeIndex(triangle);

            VertexT* v1 = const_cast<VertexT*>(triangle->vertex(index));
            VertexT* v2 = newVertex;
            VertexT* v3 = const_cast<VertexT*>(triangle->vertex((index+2)%3));

            TriangleT* newTriangle1 = new TriangleT(v1, v2, v3);
            newTriangle1->mutex().lock();

            triangle->setVertex((index+2)%3, newVertex);

            TriangleT* newNeighbor1 = triangle->neighbor((index+1)%3);
            if (0 != newNeighbor1) {
                newTriangle1->addNeighbor(newNeighbor1);
                newNeighbor1->addNeighbor(newTriangle1);
            }

            newTriangle1->addNeighbor(triangle);
            triangle->addNeighbor(newTriangle1);

            _trimesh->trianglesMutex().lock();
            _trimesh->addTriangle(newTriangle1);
            _trimesh->trianglesMutex().unlock();

            if (0 != neighbor) {
                // Bisection neighbor
                index = LeppLibrary::longestEdgeIndex(neighbor);

                VertexT* v1 = const_cast<VertexT*>(neighbor->vertex(index));
                VertexT* v2 = newVertex;
                VertexT* v3 = const_cast<VertexT*>(neighbor->vertex((index+2)%3));

                TriangleT* newTriangle2 = new TriangleT(v1, v2, v3);
                newTriangle2->mutex().lock();

                neighbor->setVertex((index+2)%3, newVertex);

                TriangleT* newNeighbor2 = neighbor->neighbor((index+1)%3);
                if (0 != newNeighbor2) {
                    newTriangle2->addNeighbor(newNeighbor2);
                    newNeighbor2->addNeighbor(newTriangle2);
                }

                newTriangle2->addNeighbor(neighbor);
                neighbor->addNeighbor(newTriangle2);

                _trimesh->trianglesMutex().lock();
                _trimesh->addTriangle(newTriangle2);
                _trimesh->trianglesMutex().unlock();

                triangle->addNeighbor(newTriangle2);
                newTriangle2->addNeighbor(triangle);

                neighbor->addNeighbor(newTriangle1);
                newTriangle1->addNeighbor(neighbor);

                newTriangle2->mutex().unlock();
            }

            newTriangle1->mutex().unlock();

            // We have just refined this triangle
            triangle->setSelected(false);
        }
    };
}

