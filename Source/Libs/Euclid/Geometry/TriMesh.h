#pragma once

#include <QList>
#include <QListIterator>
#include "Triangle.h"
#include "Vertex.h"

namespace Euclid
{

    /*!
     * The TriMesh< Kernel > class defines a triangle mesh.
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
            QListIterator<TriangleT*> i(triangles());
            while (i.hasNext())
            {
                delete i.next();
            }
            QListIterator<VertexT*> j(vertices());
            while (j.hasNext())
            {
                delete j.next();
            }
        }

        void addVertex(VertexT* vertex)
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
            mem += numVertices() * sizeof(VertexT);
            mem += numVertices() * sizeof(VertexT*);
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

        const QList<VertexT*>& vertices() const
        {
            return _vertices;
        }

        QList<VertexT*>& vertices()
        {
            return _vertices;
        }

    private:
        QList<TriangleT*> _triangles;
        QList<VertexT*> _vertices;
    };
}

