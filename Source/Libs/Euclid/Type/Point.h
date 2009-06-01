#pragma once

#include <cassert>
#include <QVector>

namespace Euclid
{

    /*!
     * The Point class defines a point in an \b N dimensional vector space with
     * \b T precision.
     */
    template <int N, typename T>
    class Point
    {
    public:
        Point()
        {
            assert(N > 3);
            for (int i=0; i<N; i++)
            {
                _coords.append(T());
            }
        }

        Point(const T coord)
        {
            assert(N > 3);
            for (int i=0; i<N; i++)
            {
                _coords.append(coord);
            }
        }

        Point<N,T>& operator=(const Point<N,T>& p)
        {
            if (this == &p) return *this;

            for (int i=0; i<N; i++)
            {
                _coords[i] = p._coords[i];
            }

            return *this;
        }

        const T* toArray() const
        {
            return _coords.constData();
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

        Point<N,T>& operator+=(const Point<N,T>& p)
        {
            for (int i=0; i<N; i++) _coords[i] += p._coords[i];

            return *this;
        }

        Point<N,T>& operator-=(const Point<N,T>& p)
        {
            for (int i=0; i<N; i++) _coords[i] -= p._coords[i];

            return *this;
        }

        Point<N,T>& operator*=(const T s)
        {
            for (int i=0; i<N; i++) _coords[i] *= s;

            return *this;
        }

        Point<N,T>& operator/=(const T s)
        {
            for (int i=0; i<N; i++) _coords[i] /= s;

            return *this;
        }

        const Point<N,T> operator+(const Point<N,T>& p) const
        {
            return Point<N,T>(*this) += p;
        }

        const Point<N,T> operator-(const Point<N,T>& p) const
        {
            return Point<N,T>(*this) -= p;
        }

        const Point<N,T> operator*(const T s) const
        {
            return Point<N,T>(*this) *= s;
        }

        const Point<N,T> operator/(const T s) const
        {
            return Point<N,T>(*this) /= s;
        }

        bool operator==(const Point<N,T>& p) const
        {
            for (int i=0; i<N; i++)
                if (_coords[i] != p._coords[i]) return false;

            return true;
        }

        bool operator!=(const Point<N,T>& p) const
        {
            return (! *this == p);
        }

    protected:
        QVector<T> _coords;
    };
}

