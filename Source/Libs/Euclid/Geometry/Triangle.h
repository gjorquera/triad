#pragma once

#include <QMutex>
#include <Thread/Array.h>
#include "Edge.h"
#include "Vertex.h"

namespace Euclid
{

    /*!
     * Defines a triangle in a coordinate system.
     *
     * This class holds pointers to the vertices of the triangle. The vertice's
     * indexes must be ordered in CCW, this means that \b vertex(1) is the CCW
     * vertex of \b vertex(0).
     *
     * You can get a \b vertex given it's index as well as \b setVertex to a
     * given index.
     *
     * You can get an \b edge given it's index. \b Note: The edge with index 0
     * is the one opposed to vertex 0, this means, the edge formed by vertices 1
     * and 2.
     *
     * You can also \b setNeighbor and get a \b neighbor given it's index. When
     * you set or get a neighbor, the index is calculated automatically using
     * the same convention as edges.
     *
     * You can query if \b isSelected or \b setSelected to select this
     * triangle for refinement.
     *
     * Finally, you can query for the custom \b info structure.
     *
     * Deleting a triangle does not delete it's vertices as they can be shared
     * with other triangles.
     */
    template <class Kernel>
    class Triangle
    {
    public:
        typedef typename Kernel::Vector       Vector;
        typedef typename Kernel::TriangleInfo Info;
        typedef Vertex<Kernel>                VertexT;
        typedef Edge<Kernel>                  EdgeT;
        typedef Triangle<Kernel>              TriangleT;

        Triangle(VertexT *v1, VertexT *v2, VertexT *v3)
            : _selected(false), _mutex(QMutex::Recursive)
        {
            assert(0 != v1 && 0 != v2 && 0 != v3);
            _info = Info();
            _vertices[0] = v1;
            _vertices[1] = v2;
            _vertices[2] = v3;
            for (int i=0; i<3; i++) {
                _edges[i] = 0;
            }
            fixEdges();
            for (int i=0; i<3; i++) {
                _neighbors[i] = 0;
            }
        }

        virtual ~Triangle()
        {
            for (int i=0; i<3; i++) {
                delete _edges[i];
            }
        }

        const VertexT *vertex(const int i) const
        {
            assert(0 <= i && i < 3);
            return _vertices[i];
        }

        void setVertex(const int i, VertexT *vertex)
        {
            assert(0 <= i && i < 3 && 0 != vertex);
            _vertices[i] = vertex;
            fixEdges();
        }

        const EdgeT* edge(const int i) const
        {
            assert(0 <= i && i < 3);
            return _edges[i];
        }

        TriangleT *neighbor(const int i)
        {
            assert(0 <= i && i < 3);
            return _neighbors[i];
        }

        void addNeighbor(TriangleT* neighbor)
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

        QMutex& mutex()
        {
            return _mutex;
        }

        bool tryLockNeighbors()
        {
            for (int i=0; i<3; i++) {
                if (0 != neighbor(i)) {
                    bool obtained = neighbor(i)->mutex().tryLock();
                    if (! obtained) {
                        for (int j=0; j<i; j++) {
                            if (0 != neighbor(j)) {
                                neighbor(j)->mutex().unlock();
                            }
                        }
                    }
                }
            }

            return true;
        }

        void unlockNeighbors()
        {
            for (int i=0; i<3; i++) {
                if (0 != neighbor(i)) {
                    neighbor(i)->mutex().unlock();
                }
            }
        }

    protected:
        bool _selected;
        Info _info;
        Thread::Array<3,VertexT*> _vertices;
        Thread::Array<3,EdgeT*> _edges;
        Thread::Array<3,TriangleT*> _neighbors;
        QMutex _mutex;

        void fixEdges()
        {
            for (int i=0; i<3; i++) {
                if (0 != _edges[i]) {
                    delete _edges[i];
                }
            }
            for (int i=0; i<3; i++) {
                Vector v;
                v.setInitial(_vertices[(i+1)%3]->point());
                v.setTerminal(_vertices[(i+2)%3]->point());
                _edges[i] = new EdgeT(v);
            }
        }

        int neighborIndex(const TriangleT *triangle) const
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

