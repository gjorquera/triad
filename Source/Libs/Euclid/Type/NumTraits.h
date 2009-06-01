#pragma once

#include <cmath>

namespace Euclid
{
    /*!
     * Number traits declaration.
     */
    template <typename T>
    struct NumTraits{ };

    /*!
     * Integer traits specialization.
     */
    template <>
    struct NumTraits<int>
    {
        typedef int T;
        static inline T sqrt(T num) { return (int)sqrtf(num*1.0); }
    };

    /*!
     * Float traits specialization.
     */
    template <>
    struct NumTraits<float>
    {
        typedef float T;
        static inline T sqrt(T num) { return sqrtf(num); }
    };

    /*!
     * Double traits specialization.
     */
    template <>
    struct NumTraits<double>
    {
        typedef double T;
        static inline T sqrt(T num) { return sqrt(num); }
    };
}

