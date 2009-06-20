#pragma once

#include <cassert>
#include <Thread/Array.h>

namespace Euclid
{

    /*!
     * Defines a point in an \b N dimensional vector space with \b T precision.
     */
    template <int N, typename T>
    class Point
    {
    public:
        Point()
        {
            assert(N > 0);
        }

        Point(const T coord)
        {
            assert(N > 0);
            for (int i=0; i<N; i++) {
                _coords[i] = coord;
            }
        }

        Point<N,T>& operator=(const Point<N,T>& point)
        {
            if (this == &point) return *this;

            for (int i=0; i<N; i++)
            {
                _coords[i] = point._coords[i];
            }

            return *this;
        }

        const T* toArray() const
        {
            return _coords.toArray();
        }

        T& operator[](const int i)
        {
            assert(0 <= i && i < N);
            return _coords[i];
        }

        const T& operator[](const int i) const
        {
            assert(0 <= i && i < N);
            return _coords[i];
        }

        Point<N,T>& operator+=(const Point<N,T>& point)
        {
            for (int i=0; i<N; i++) _coords[i] += point._coords[i];

            return *this;
        }

        Point<N,T>& operator-=(const Point<N,T>& point)
        {
            for (int i=0; i<N; i++) _coords[i] -= point._coords[i];

            return *this;
        }

        Point<N,T>& operator*=(const T scale)
        {
            for (int i=0; i<N; i++) _coords[i] *= scale;

            return *this;
        }

        Point<N,T>& operator/=(const T scale)
        {
            for (int i=0; i<N; i++) _coords[i] /= scale;

            return *this;
        }

        const Point<N,T> operator+(const Point<N,T>& point) const
        {
            return Point<N,T>(*this) += point;
        }

        const Point<N,T> operator-(const Point<N,T>& point) const
        {
            return Point<N,T>(*this) -= point;
        }

        const Point<N,T> operator*(const T scale) const
        {
            return Point<N,T>(*this) *= scale;
        }

        const Point<N,T> operator/(const T scale) const
        {
            return Point<N,T>(*this) /= scale;
        }

        bool operator==(const Point<N,T>& point) const
        {
            for (int i=0; i<N; i++)
                if (_coords[i] != point._coords[i]) return false;

            return true;
        }

        bool operator!=(const Point<N,T>& point) const
        {
            return (! *this == point);
        }

    protected:
        Thread::Array<N,T> _coords;
    };
}

