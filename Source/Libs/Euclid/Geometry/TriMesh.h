#pragma once

#include <QList>
#include "Triangle.h"
#include "Vertex.h"

namespace Euclid
{

    /*!
     * The TriMesh class defines a triangle mesh.
     *
     * This class holds vertices as well as triangles. Deleting this class will
     * delete all added vertices and triangles.
     *
     * @todo Maybe represent triangles and vertices with QMap
     */
    template <class Kernel>
    class TriMesh
    {
    public:
        typedef Triangle<Kernel>                         Triangle;
        typedef Vertex<Kernel>                           Vertex;
        typedef typename QList<Triangle*>::Iterator      Iterator;
        typedef typename QList<Triangle*>::ConstIterator ConstIterator;
        typedef typename QList<Vertex*>::Iterator        VertexIterator;
        typedef typename QList<Vertex*>::ConstIterator   VertexCostIterator;

        TriMesh()
        {
        }

        virtual ~TriMesh()
        {
            Iterator i;
            for (i = _triangles.begin(); i != _triangles.end(); i++)
                delete (*i);
            VertexIterator j;
            for (j = _vertices.begin(); j != _vertices.end(); j++)
                delete (*j);
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

    protected:
        QList<Triangle*> _triangles;
        QList<Vertex*> _vertices;
    };
}

