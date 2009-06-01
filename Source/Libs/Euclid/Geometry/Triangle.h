#pragma once

#include "Vertex.h"

namespace Euclid
{

    /*!
     * The Triangle class defines a triangle in a coordinate system.
     */
    template <class Kernel>
    class Triangle
    {
    public:

        typedef typename Kernel::TriangleInfo Info;

        Triangle(Vertex<Kernel> *v1, Vertex<Kernel> *v2, Vertex<Kernel> *v3)
        {
            assert(0 != v1 && 0 != v2 && 0 != v3);
            _info = Info();
            _vertices[0] = v1;
            _vertices[1] = v2;
            _vertices[2] = v3;
            for (int i=0; i<3; i++) _neighbors[i] = 0;
        }

        const Vertex<Kernel> *vertex(const int i) const
        {
            assert(0 <= i && i < 3);
            return _vertices[i];
        }

        void setVertex(const int i, const Vertex<Kernel> *vertex)
        {
            assert(0 <= i && i < 3 && 0 != vertex);
            _vertices[i] = const_cast<Vertex<Kernel>*>(vertex);
        }

        const Triangle<Kernel> *neighbor(const int i) const
        {
            assert(0 <= i && i < 3);
            return _neighbors[i];
        }

        void addNeighbor(Triangle<Kernel>* neighbor)
        {
            assert(0 != neighbor);
            _neighbors[neighborIndex(neighbor)] = neighbor;
        }

        const Info& info() const
        {
            return _info;
        }

        void setInfo(const Info& info)
        {
            _info = info;
        }

    protected:
        Info _info;
        Vertex<Kernel>* _vertices[3];
        Triangle<Kernel>* _neighbors[3];

        int neighborIndex(const Triangle<Kernel> *triangle) const
        {
            assert(0 != triangle);
            int index = -1;
            for (int i=0; i<3; i++)
            {
                bool shared = false;
                for (int j=0; j<3; j++)
                {
                    if (_vertices[i] == triangle->_vertices[j])
                    {
                        shared = true;
                        break;
                    }
                }

                assert((!shared && index == -1) || shared);

                if (!shared) index = i;
            }

            assert(index != -1 && 0 <= index && index < 3);

            return index;
        }
    };
}

