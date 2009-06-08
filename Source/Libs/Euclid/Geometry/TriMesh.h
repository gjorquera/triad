#pragma once

#include <QList>
#include "MutableVertexIterator.h"
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
        typedef typename QList<Triangle*>::Iterator      Iterator;
        typedef typename QList<Triangle*>::ConstIterator ConstIterator;

        TriMesh()
        {
        }

        virtual ~TriMesh()
        {
            Iterator i;
            for (i = _triangles.begin(); i != _triangles.end(); i++)
                delete (*i);
            MutableVertexIterator<Kernel> j(this);
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

        Iterator begin()
        {
            return _triangles.begin();
        }

        ConstIterator begin() const
        {
            return _triangles.begin();
        }

        Iterator end()
        {
            return _triangles.end();
        }

        ConstIterator end() const
        {
            return _triangles.end();
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

