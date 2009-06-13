#pragma once

#include "../Type/Point.h"

namespace Euclid
{

    /*!
     * The Vertex< Kernel > class defines a triangle's vertex.
     */
    template <class Kernel>
    class Vertex
    {
    public:
        typedef typename Kernel::Point      Point;
        typedef typename Kernel::VertexInfo Info;
        typedef Vertex<Kernel>              VertexT;

        Vertex()
        {
            _point = Point();
            _info = Info();
        }

        Vertex(const Point& point)
        {
            _point = point;
            _info = Info();
        }

        Vertex(const Info& info)
        {
            _point = Point();
            _info = info;
        }

        Vertex(const Point& point, const Info &info)
        {
            _point = point;
            _info = info;
        }

        Point& point()
        {
            return _point;
        }

        const Point& point() const
        {
            return _point;
        }

        Info& info()
        {
            return _info;
        }

        const Info& info() const
        {
            return _info;
        }

    protected:
        Point _point;
        Info _info;
    };
}

