#pragma once

#include <iostream>
#include <QList>
#include <QMutableListIterator>
#include <QRunnable>
#include "../Lepp/Library.h"
#include "../../Geometry/TriMesh.h"

namespace Euclid
{

    template <class Kernel>
    class RefineThread : public QRunnable
    {
    public:
        typedef typename Kernel::T      T;
        typedef typename Kernel::Point  Point;
        typedef typename Kernel::Vector Vector;
        typedef Vertex<Kernel>          VertexT;
        typedef Edge<Kernel>            EdgeT;
        typedef Triangle<Kernel>        TriangleT;
        typedef TriMesh<Kernel>         TriMesh;
        typedef LeppLibrary<Kernel>     LeppLibrary;

        RefineThread(TriMesh* trimesh, QList<TriangleT*>* toRefine)
        {
            _trimesh = trimesh;
            _toRefine = toRefine;
        }

        virtual ~RefineThread()
        {
        }

        void run()
        {
            QMutableListIterator<TriangleT*> i(*_toRefine);
            do {
                while (i.hasNext()) {
                    TriangleT* triangle = i.next();
                    bool obtained = triangle->mutex().tryLock();
                    if (! obtained) continue;

                    TriangleT* refined = 0;
                    do {
                        refined = refineTriangle(triangle);
                    } while (refined != 0 && refined != triangle);

                    if (0 != refined) {
                        _trimesh->auxLock().lock();
                        i.remove();
                        _trimesh->auxLock().unlock();
                    }

                    triangle->mutex().unlock();
                }
                i.toFront();
            } while (_toRefine->size() > 0);
        }

    protected:
        TriangleT* refineTriangle(TriangleT* triangle)
        {
            TriangleT* neighbor = LeppLibrary::longestEdgeNeighbor(triangle);
            TriangleT* refined = 0;

            if (0 != neighbor) {
                bool obtained = neighbor->mutex().tryLock();
                if (! obtained) return 0;
            }

            if (LeppLibrary::isTerminal(triangle)) {
                refineTerminal(triangle);
                refined = triangle;
            } else {
                refined = refineTriangle(neighbor);
            }

            if (0 != neighbor) {
                neighbor->mutex().unlock();
            }

            return refined;
        }

        virtual void refineTerminal(TriangleT* triangle)
        {
            TriMesh* trimesh = _trimesh;

            const EdgeT* edge = LeppLibrary::longestEdge(triangle);
            Point point((edge->vector() / 2).terminal());
            VertexT* newVertex = new VertexT(point);
            trimesh->verticesMutex().lock();
            trimesh->addVertex(newVertex);
            trimesh->verticesMutex().unlock();

            TriangleT* neighbor = LeppLibrary::longestEdgeNeighbor(triangle);

            TriangleT* newTriangle1 = LeppLibrary::bisect(triangle, newVertex);
            newTriangle1->mutex().lock();

            trimesh->trianglesMutex().lock();
            trimesh->addTriangle(newTriangle1);
            trimesh->trianglesMutex().unlock();

            if (0 != neighbor) {
                TriangleT* newTriangle2 = LeppLibrary::bisect(neighbor, newVertex);
                newTriangle2->mutex().lock();

                trimesh->trianglesMutex().lock();
                trimesh->addTriangle(newTriangle2);
                trimesh->trianglesMutex().unlock();

                triangle->addNeighbor(newTriangle2);
                newTriangle2->addNeighbor(triangle);

                neighbor->addNeighbor(newTriangle1);
                newTriangle1->addNeighbor(neighbor);

                newTriangle2->mutex().unlock();
            }

            newTriangle1->mutex().unlock();
        }

    private:
        QList<TriangleT*>* _toRefine;
        TriMesh* _trimesh;
    };
}

