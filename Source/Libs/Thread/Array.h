#pragma once

namespace Thread
{

    template <int N, typename T>
    class Array
    {
    public:
        Array()
        {
            assert(0 < N);
            for (int i=0; i<N; i++) {
                _elems[i] = T();
            }
        }

        Array(const Array<N,T>& array)
        {
            for (int i=0; i<N; i++) {
                _elems[i] = array._elems[i];
            }
        }

        Array<N,T>& operator=(const Array<N,T>& array)
        {
            if (this == &array) return *this;

            for (int i=0; i<N; i++) {
                _elems[i] = array._elems[i];
            }

            return *this;
        }

        T& operator[](const int i)
        {
            assert(0 <= i && i < N);
            return _elems[i];
        }

        const T& operator[](const int i) const
        {
            assert(0 <= i && i < N);
            return _elems[i];
        }

        T* toArray()
        {
            return _elems;
        }

        const T* toArray() const
        {
            return _elems;
        }

    private:
        T _elems[N];
    };
}

