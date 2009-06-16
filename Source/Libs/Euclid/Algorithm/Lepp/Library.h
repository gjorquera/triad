#pragma once

namespace Euclid
{

    template <class Kernel>
    class LeppLibrary
    {
    public:
        typedef typename Kernel::T      T;
        typedef Edge<Kernel>            EdgeT;
        typedef Triangle<Kernel>        TriangleT;

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

        static const EdgeT* longestEdge(const TriangleT* triangle)
        {
            int index = LeppLibrary::longestEdgeIndex(triangle);
            return triangle->edge(index);
        }

        static TriangleT* longestEdgeNeighbor(TriangleT* triangle)
        {
            int index = LeppLibrary::longestEdgeIndex(triangle);
            return triangle->neighbor(index);
        }

        static bool isTerminal(TriangleT* triangle)
        {
            TriangleT* neighbor = LeppLibrary::longestEdgeNeighbor(triangle);
            neighbor = LeppLibrary::longestEdgeNeighbor(neighbor);
            if (0 == neighbor || triangle == neighbor) {
                return true;
            }
            return false;
        }
    };
}

