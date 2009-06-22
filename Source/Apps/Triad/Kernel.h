#pragma once

#include <Euclid/Type/DefaultKernel.h>

namespace App
{

    /*!
     * Defines the custom Euclid type templates.
     */
    struct Kernel : public Euclid::DefaultKernel
    {
        typedef bool TriangleInfo;
    };
}

