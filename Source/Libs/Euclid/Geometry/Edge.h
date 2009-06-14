#pragma once

#include "../Type/Point.h"

namespace Euclid
{

    /*!
     * Defines a triangle's edge.
     *
     * An edge contains a Vector in an euclidean coordinate system.
     *
     * You can query it with \b vector.
     */
    template <class Kernel>
    class Edge
    {
    public:
        typedef typename Kernel::Vector Vector;

        Edge()
        {
            _vector = Vector();
        }

        Edge(const Vector& vector)
        {
            _vector = vector;
        }

        Vector& vector()
        {
            return _vector;
        }

        const Vector& vector() const
        {
            return _vector;
        }

    protected:
        Vector _vector;
    };
}

