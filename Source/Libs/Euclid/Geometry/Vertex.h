#pragma once

#include "../Type/Point.h"

namespace Euclid
{

    /*!
     * The Vertex class defines a triangle's vertex.
     */
    template <class Kernel>
    class Vertex
    {
    public:
        typedef typename Kernel::Point Point;
        typedef typename Kernel::VertexInfo Info;

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

        Vertex(const Vertex<Kernel>& vertex)
        {
            _point = vertex._point;
            _info = vertex._info;
        }

        Vertex<Kernel>& operator=(const Vertex<Kernel>& vertex)
        {
            if (this == &vertex) return *this;

            _point = vertex._point;
            _info = vertex._info;

            return *this;
        }

        const Point& point() const
        {
            return _point;
        }

        void setPoint(const Point& point)
        {
            _point = point;
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
        Point _point;
        Info _info;
    };
}

