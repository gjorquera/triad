#pragma once

#include <cassert>
#include "NumTraits.h"
#include "Point.h"

namespace Euclid
{

    /*!
     * The Vector class defines a vector in an \b N dimensional vector space
     * with \b T precision.
     */
    template <int N, typename T>
    class Vector
    {
    public:
        Vector()
        {
            _initial = Point<N,T>();
            _terminal = Point<N,T>();
        }

        Vector(const Point<N,T>& terminal)
        {
            _initial = Point<N,T>();
            _terminal = terminal;
        }

        Vector(const Point<N,T>& initial, const Point<N,T>& terminal)
        {
            _initial = initial;
            _terminal = terminal;
        }

        Vector<N,T>& operator=(const Vector<N,T>& vector)
        {
            if (this == &vector) return *this;

            _initial = vector._initial;
            _terminal = vector._terminal;

            return *this;
        }

        const Point<N,T>& initial() const
        {
            return _initial;
        }

        void setInitial(const Point<N,T>& initial)
        {
            _initial = initial;
        }

        const Point<N,T>& terminal() const
        {
            return _terminal;
        }

        void setTerminal(const Point<N,T>& terminal)
        {
            _terminal = terminal;
        }

        const T distance() const
        {
            Vector<N,T> c(*this);
            T res = dot(c);
            return NumTraits<T>::sqrt(res);
        }

        const T dot(const Vector<N,T> &vector) const
        {
            T res = T();

            for (int i=0; i<N; i++)
            {
                Point<N,T> p = _terminal - _initial;
                Point<N,T> pv = vector._terminal - vector._initial;
                res += p[i] * pv[i];
            }

            return res;
        }

        const Vector<N,T> cross(const Vector<N,T> &vector) const
        {
            assert(3 == N);
            Vector<N,T> res;
            res.setInitial(_initial);

            Point<N,T> a = _terminal - _initial;
            Point<N,T> b = vector._terminal - vector._initial;

            Point<N,T> t;
            t[0] = a[1]*b[2] - a[2]*b[1];
            t[1] = a[2]*b[0] - a[0]*b[2];
            t[2] = a[0]*b[1] - a[1]*b[1];

            res.setTerminal(t);

            return res;
        }

        Vector<N,T> &operator+=(const Vector<N,T> &vector)
        {
            _terminal += (vector._terminal - vector._initial);

            return *this;
        }

        Vector<N,T> &operator-=(const Vector<N,T> &vector)
        {
            _terminal -= (vector._terminal - vector._initial);

            return *this;
        }

        Vector<N,T> &operator*=(const T scale)
        {
            _terminal = _initial + (_terminal - _initial) * scale;

            return *this;
        }

        Vector<N,T> &operator/=(const T scale)
        {
            _terminal = _initial + (_terminal - _initial) / scale;

            return *this;
        }

        const Vector<N,T> operator+(const Vector<N,T> &vector) const
        {
            return Vector<N,T>(*this) += vector;
        }

        const Vector<N,T> operator-(const Vector<N,T> &vector) const
        {
            return Vector<N,T>(*this) -= vector;
        }

        const Vector<N,T> operator*(const T scale) const
        {
            return Vector<N,T>(*this) *= scale;
        }

        const Vector<N,T> operator/(const T scale) const
        {
            return Vector<N,T>(*this) /= scale;
        }

        bool operator==(const Vector<N,T> &vector) const
        {
            return (_terminal == vector._terminal
                && _initial == vector._initial);
        }

        bool operator!=(const Vector<N,T> &vector) const
        {
            return (! *this == vector);
        }


    private:
        Point<N,T> _initial;
        Point<N,T> _terminal;
    };
}

