#pragma once

#include "Strategy.h"
#include "Lepp/Library.h"

namespace Euclid
{

    /*!
     * A secuential lepp bisection refinement algorithm.
     */
    template <class Kernel>
    class LeppStrategy : public Strategy<Kernel>
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

        LeppStrategy(TriMesh* trimesh = 0)
            : Strategy<Kernel>(trimesh)
        {
        }

        ~LeppStrategy()
        {
        }

        void refine(const Criterion<Kernel>& criterion)
        {
            TriMesh* trimesh = Strategy<Kernel>::trimesh();
            QListIterator<TriangleT*> i(trimesh->triangles());
            while (i.hasNext())
            {
                TriangleT* triangle = i.next();
                while (criterion.test(triangle)) {
                    TriangleT* refined = 0;
                    do {
                        refined = refineTriangle(triangle);
                    } while (refined != triangle);
                }
            }
        }

    protected:
        virtual TriangleT* refineTriangle(TriangleT* triangle)
        {
            TriangleT* neighbor = LeppLibrary::longestEdgeNeighbor(triangle);
            TriangleT* refined = 0;

            if (LeppLibrary::isTerminal(triangle)) {
                refineTerminal(triangle);
                triangle->setSelected(false);
                refined = triangle;
            } else {
                refined = refineTriangle(neighbor);
            }

            return refined;
        }

        virtual void refineTerminal(TriangleT* triangle)
        {
            TriMesh* trimesh = this->trimesh();

            const EdgeT* edge = LeppLibrary::longestEdge(triangle);
            Point point((edge->vector() / 2).terminal());
            VertexT* newVertex = new VertexT(point);
            trimesh->addVertex(newVertex);

            TriangleT* neighbor = LeppLibrary::longestEdgeNeighbor(triangle);

            TriangleT* newTriangle1 = LeppLibrary::bisect(triangle, newVertex);
            trimesh->addTriangle(newTriangle1);

            if (0 != neighbor) {
                TriangleT* newTriangle2 = LeppLibrary::bisect(neighbor, newVertex);
                trimesh->addTriangle(newTriangle2);

                triangle->addNeighbor(newTriangle2);
                newTriangle2->addNeighbor(triangle);

                neighbor->addNeighbor(newTriangle1);
                newTriangle1->addNeighbor(neighbor);
            }
        }
    };
}

