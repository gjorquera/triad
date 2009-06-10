#pragma once

#include "Strategy.h"

namespace Euclid
{

    /*!
     * A naive lepp bisection refinement algorithm
     */
    template <class Kernel>
    class LeppStrategy : public Strategy<Kernel>
    {
    public:
        typedef typename Kernel::Point  Point;
        typedef typename Kernel::Vector Vector;
        typedef typename Euclid::Vertex<Kernel>   Vertex;
        typedef typename Euclid::Triangle<Kernel> Triangle;
        typedef typename Euclid::TriMesh<Kernel>  TriMesh;

        LeppStrategy(TriMesh* trimesh = 0)
            : Strategy<Kernel>(trimesh)
        {
        }

        ~LeppStrategy()
        {
        }

        void refine(Criterion<Kernel>& criterion)
        {
            TriMesh* trimesh = Strategy<Kernel>::trimesh();
            QListIterator<Triangle*> i(trimesh->triangles());
            while (i.hasNext())
            {
                if (criterion.test(i.peekNext())) {
                    refineTriangle(i.peekNext());
                }
                i.next();
            }
        }

        const Vector* longestEdge(Triangle* triangle)
        {
            int index = longestEdgeIndex(triangle);
            return triangle->edge(index);
        }

    protected:
        Triangle* refineTriangle(Triangle* triangle)
        {
            Triangle* refined;
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

        void refineTerminal(Triangle* triangle)
        {
            TriMesh* trimesh = Strategy<Kernel>::trimesh();
            const Vector* edge = longestEdge(triangle);
            Point point((*edge / 2).terminal());
            Vertex* newVertex = new Vertex(point);
            trimesh->addVertex(newVertex);

            Triangle* neighbor = longestEdgeNeighbor(triangle);

            Triangle* newTriangle1 = cut(triangle, newVertex);

            if (0 != neighbor) {
                Triangle* newTriangle2 = cut(neighbor, newVertex);

                triangle->addNeighbor(newTriangle2);
                newTriangle2->addNeighbor(triangle);

                neighbor->addNeighbor(newTriangle1);
                newTriangle1->addNeighbor(neighbor);
            }
        }

        Triangle* cut(Triangle* triangle, Vertex* newVertex)
        {
            TriMesh* trimesh = Strategy<Kernel>::trimesh();
            int index = longestEdgeIndex(triangle);

            Vertex* v1 = const_cast<Vertex*>(triangle->vertex(index));
            Vertex* v2 = newVertex;
            Vertex* v3 = const_cast<Vertex*>(triangle->vertex((index+2)%3));

            Triangle* newTriangle = new Triangle(v1, v2, v3);
            trimesh->addTriangle(newTriangle);

            triangle->setVertex((index+2)%3, newVertex);

            Triangle* neighbor = const_cast<Triangle*>(
                triangle->neighbor((index+1)%3));
            if (0 != neighbor) {
                newTriangle->addNeighbor(neighbor);
                neighbor->addNeighbor(newTriangle);
            }

            newTriangle->addNeighbor(triangle);
            triangle->addNeighbor(newTriangle);

            return newTriangle;
        }

        Triangle* longestEdgeNeighbor(Triangle* triangle)
        {
            int index = longestEdgeIndex(triangle);
            return const_cast<Triangle*>(triangle->neighbor(index));
        }

        int longestEdgeIndex(Triangle* triangle)
        {
            Vector max;
            int index = -1;

            for (int i=0; i<3; i++)
            {
                const Vector* e = triangle->edge(i);
                if (max.distance() < e->distance()) {
                    max = *e;
                    index = i;
                }
                delete e;
            }

            assert(-1 != index);

            return index;
        }

        bool isTerminal(Triangle* triangle)
        {
            Triangle* neighbor = longestEdgeNeighbor(triangle);
            if (0 == neighbor || triangle == longestEdgeNeighbor(neighbor)) {
                return true;
            }
            return false;
        }
    };
}

