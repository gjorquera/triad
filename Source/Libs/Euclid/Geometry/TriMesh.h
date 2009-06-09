#pragma once

#include <QList>
#include <QMutableListIterator>
#include "Triangle.h"
#include "Vertex.h"

namespace Euclid
{

    /*!
     * The TriMesh class defines a triangle mesh.
     *
     * This class holds vertices as well as triangles. Deleting this class will
     * delete all added vertices and triangles.
     */
    template <class Kernel>
    class TriMesh
    {
    public:
        typedef Triangle<Kernel>                         Triangle;
        typedef Vertex<Kernel>                           Vertex;

        TriMesh()
        {
        }

        virtual ~TriMesh()
        {
            QMutableListIterator<Triangle*> i(triangles());
            while (i.hasNext())
            {
                delete i.next();
                i.remove();
            }
            QMutableListIterator<Vertex*> j(vertices());
            while (j.hasNext())
            {
                delete j.next();
                j.remove();
            }
        }

        void addVertex(const Vertex* vertex)
        {
            _vertices.append(const_cast<Vertex*>(vertex));
        }

        void addTriangle(const Triangle* triangle)
        {
            _triangles.append(const_cast<Triangle*>(triangle));
        }

        int numVertices() const
        {
            return _vertices.size();
        }

        int numTriangles() const
        {
            return _triangles.size();
        }

        int memory() const
        {
            int mem = 0;
            mem += numTriangles() * sizeof(Triangle);
            mem += numTriangles() * sizeof(Triangle*);
            mem += numVertices() * sizeof(Vertex);
            mem += numVertices() * sizeof(Vertex*);
            mem += sizeof(TriMesh<Kernel>);
            return mem;
        }

        const QList<Triangle*>& triangles() const
        {
            return _triangles;
        }

        QList<Triangle*>& triangles()
        {
            return _triangles;
        }

        const QList<Vertex*>& vertices() const
        {
            return _vertices;
        }

        QList<Vertex*>& vertices()
        {
            return _vertices;
        }

    protected:
        QList<Triangle*> _triangles;
        QList<Vertex*> _vertices;
    };
}

