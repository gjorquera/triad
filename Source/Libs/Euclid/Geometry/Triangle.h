#pragma once

#include "Vertex.h"

namespace Euclid
{

    /*!
     * The Triangle class defines a triangle in a coordinate system.
     *
     * Deleting a triangle do not delete it's vertices as they can be shared
     * with other triangles.
     */
    template <class Kernel>
    class Triangle
    {
    public:
        typedef typename Kernel::Vector       Vector;
        typedef typename Kernel::TriangleInfo Info;

        Triangle(Vertex<Kernel> *v1, Vertex<Kernel> *v2, Vertex<Kernel> *v3)
        {
            assert(0 != v1 && 0 != v2 && 0 != v3);
            _selected = false;
            _info = Info();
            _vertices[0] = v1;
            _vertices[1] = v2;
            _vertices[2] = v3;
            for (int i=0; i<3; i++) {
                /// @todo _edges[i] = new Edge(_vertices[i], _vertices[(i+1)%3]);
            }
            for (int i=0; i<3; i++) {
                _neighbors[i] = 0;
            }
        }

        const Vertex<Kernel> *vertex(const int i) const
        {
            assert(0 <= i && i < 3);
            return _vertices[i];
        }

        void setVertex(const int i, Vertex<Kernel> *vertex)
        {
            assert(0 <= i && i < 3 && 0 != vertex);
            _vertices[i] = vertex;
        }

        const Vector* edge(const int i) const
        {
            assert(0 <= i && i < 3);
            /// @todo use _edges and return Edge;
            Vector* v = new Vector;
            v->setInitial(vertex((i+1)%3)->point());
            v->setTerminal(vertex((i+2)%3)->point());
            return v;
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

        bool isSelected() const
        {
            return _selected;
        }

        void setSelected(bool selected)
        {
            _selected = selected;
        }

        Info& info()
        {
            return _info;
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
        bool _selected;
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

