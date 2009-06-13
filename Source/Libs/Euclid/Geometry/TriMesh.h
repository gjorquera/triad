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
        typedef Triangle<Kernel> TriangleT;
        typedef Vertex<Kernel>   VertexT;

        TriMesh()
        {
        }

        virtual ~TriMesh()
        {
            QMutableListIterator<TriangleT*> i(triangles());
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

        void addVertex(Vertex* vertex)
        {
            assert(0 != vertex);
            _vertices.append(vertex);
        }

        void addTriangle(TriangleT* triangle)
        {
            assert(0 != triangle);
            _triangles.append(triangle);
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
            mem += numTriangles() * sizeof(TriangleT);
            mem += numTriangles() * sizeof(TriangleT*);
            mem += numVertices() * sizeof(Vertex);
            mem += numVertices() * sizeof(Vertex*);
            mem += sizeof(TriMesh<Kernel>);
            return mem;
        }

        const QList<TriangleT*>& triangles() const
        {
            return _triangles;
        }

        QList<TriangleT*>& triangles()
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

    private:
        QList<TriangleT*> _triangles;
        QList<Vertex*> _vertices;
    };
}

