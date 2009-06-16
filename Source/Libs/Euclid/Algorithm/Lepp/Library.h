#pragma once

namespace Euclid
{

    template <class Kernel>
    class LeppLibrary
    {
    public:
        typedef typename Kernel::T T;
        typedef Vertex<Kernel>     VertexT;
        typedef Edge<Kernel>       EdgeT;
        typedef Triangle<Kernel>   TriangleT;

        static const EdgeT* longestEdge(const TriangleT* triangle)
        {
            int index = LeppLibrary::longestEdgeIndex(triangle);
            return triangle->edge(index);
        }

        static int longestEdgeIndex(const TriangleT* triangle)
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

        static TriangleT* longestEdgeNeighbor(TriangleT* triangle)
        {
            int index = LeppLibrary::longestEdgeIndex(triangle);
            return triangle->neighbor(index);
        }

        static bool isTerminal(TriangleT* triangle)
        {
            TriangleT* neighbor = LeppLibrary::longestEdgeNeighbor(triangle);
            if (0 == neighbor) {
                return true;
            }

            neighbor = LeppLibrary::longestEdgeNeighbor(neighbor);

            return (triangle == neighbor);
        }

        static TriangleT* bisect(TriangleT* triangle, VertexT* newVertex)
        {
            int index = LeppLibrary::longestEdgeIndex(triangle);

            VertexT* v1 = const_cast<VertexT*>(triangle->vertex(index));
            VertexT* v2 = newVertex;
            VertexT* v3 = const_cast<VertexT*>(triangle->vertex((index+2)%3));

            TriangleT* newTriangle = new TriangleT(v1, v2, v3);

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
    };
}

