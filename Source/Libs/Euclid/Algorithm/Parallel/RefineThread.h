#pragma once

#include <iostream>
#include <QList>
#include <QMutableListIterator>
#include <QRunnable>
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
        typedef Triangle<Kernel> TriangleT;
        typedef TriMesh<Kernel>         TriMesh;

        RefineThread(TriMesh* trimesh, QList<TriangleT*> toRefine)
        {
            _trimesh = trimesh;
            _toRefine = toRefine;
        }

        virtual ~RefineThread()
        {
        }

        void run()
        {
                std::cout << ".";
            QMutableListIterator<TriangleT*> i(_toRefine);
            //do {
                while (i.hasNext()) {
                    TriangleT* triangle = i.next();
                    bool taken = triangle->mutex().tryLock();
                    if (! taken) continue;

                    if (0 != refineTriangle(triangle)) {
                        //triangle->setSelected(false);
                        i.remove();
                    }

                    triangle->mutex().unlock();
                }
                //i.toFront();
            //} while (_toRefine.size() > 0);
        }

    protected:
        TriangleT* refineTriangle(TriangleT* triangle)
        {
            std::cout << ".";
            TriangleT* neighbor = longestEdgeNeighbor(triangle);
            if (0 != neighbor) {
                bool taken = neighbor->mutex().tryLock();
                if (! taken) return 0;
            }

            TriangleT* refined = 0;

            do {
                if (0 == neighbor || longestEdgeNeighbor(neighbor) == triangle) {
                    //refineTerminal(triangle);
                    refined = triangle;
                } else {
                    refined = refineTriangle(neighbor);
                }
            } while (refined != 0 && refined != triangle);

            if (0 != neighbor) {
                neighbor->mutex().unlock();
            }

            return refined;
        }

        virtual const EdgeT* longestEdge(const TriangleT* triangle)
        {
            int index = longestEdgeIndex(triangle);
            return triangle->edge(index);
        }

        virtual void refineTerminal(TriangleT* triangle)
        {
            TriMesh* trimesh = _trimesh;

            const EdgeT* edge = longestEdge(triangle);
            Point point((edge->vector() / 2).terminal());
            VertexT* newVertex = new VertexT(point);
            trimesh->addVertex(newVertex);

            TriangleT* neighbor = longestEdgeNeighbor(triangle);

            TriangleT* newTriangle1 = cut(triangle, newVertex);

            if (0 != neighbor) {
                TriangleT* newTriangle2 = cut(neighbor, newVertex);

                triangle->addNeighbor(newTriangle2);
                newTriangle2->addNeighbor(triangle);

                neighbor->addNeighbor(newTriangle1);
                newTriangle1->addNeighbor(neighbor);
            }
        }

        virtual int longestEdgeIndex(const TriangleT* triangle)
        {
            T max = T();
            int index = -1;

            for (int i=0; i<3; i++)
            {
                const EdgeT* e = triangle->edge(i);
                if (max < e->vector().distance()) {
                    max = e->vector().distance();
                    index = i;
                }
            }

            assert(-1 != index);

            return index;
        }

        virtual TriangleT* cut(TriangleT* triangle, VertexT* newVertex)
        {
            TriMesh* trimesh = _trimesh;
            int index = longestEdgeIndex(triangle);

            VertexT* v1 = const_cast<VertexT*>(triangle->vertex(index));
            VertexT* v2 = newVertex;
            VertexT* v3 = const_cast<VertexT*>(triangle->vertex((index+2)%3));

            TriangleT* newTriangle = new TriangleT(v1, v2, v3);
            trimesh->addTriangle(newTriangle);

            triangle->setVertex((index+2)%3, newVertex);

            TriangleT* neighbor = triangle->neighbor((index+1)%3);
            if (0 != neighbor) {
                newTriangle->addNeighbor(neighbor);
                neighbor->addNeighbor(newTriangle);
            }

            newTriangle->addNeighbor(triangle);
            triangle->addNeighbor(newTriangle);

            return newTriangle;
        }

        TriangleT* longestEdgeNeighbor(TriangleT* triangle)
        {
            int index = longestEdgeIndex(triangle);
            return triangle->neighbor(index);
        }

    private:
        QList<TriangleT*> _toRefine;
        TriMesh* _trimesh;
    };
}

