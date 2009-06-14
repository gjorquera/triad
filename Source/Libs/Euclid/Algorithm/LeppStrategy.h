#pragma once

#include "Strategy.h"

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
                    refineTriangle(triangle);
                }
            }
        }

        virtual const EdgeT* longestEdge(const TriangleT* triangle)
        {
            int index = longestEdgeIndex(triangle);
            return triangle->edge(index);
        }

    protected:
        virtual TriangleT* refineTriangle(TriangleT* triangle)
        {
            TriangleT* refined;
            do {
                if (isTerminal(triangle)) {
                    refineTerminal(triangle);
                    refined = triangle;
                } else {
                    refined = refineTriangle(longestEdgeNeighbor(triangle));
                }
            } while (refined != triangle);

            return triangle;
        }

        virtual void refineTerminal(TriangleT* triangle)
        {
            TriMesh* trimesh = this->trimesh();
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

        virtual TriangleT* cut(TriangleT* triangle, VertexT* newVertex)
        {
            TriMesh* trimesh = Strategy<Kernel>::trimesh();
            int index = longestEdgeIndex(triangle);

            VertexT* v1 = const_cast<VertexT*>(triangle->vertex(index));
            VertexT* v2 = newVertex;
            VertexT* v3 = const_cast<VertexT*>(triangle->vertex((index+2)%3));

            TriangleT* newTriangle = new TriangleT(v1, v2, v3);
            trimesh->addTriangle(newTriangle);

            triangle->setVertex((index+2)%3, newVertex);

            TriangleT* neighbor = const_cast<TriangleT*>(
                triangle->neighbor((index+1)%3));
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

        virtual bool isTerminal(TriangleT* triangle)
        {
            TriangleT* neighbor = longestEdgeNeighbor(triangle);
            if (0 == neighbor || triangle == longestEdgeNeighbor(neighbor)) {
                return true;
            }
            return false;
        }
    };
}

