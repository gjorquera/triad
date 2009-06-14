#pragma once

#include <Euclid/Type/DefaultKernel.h>

namespace App
{

    /*!
     * The Kernel structure defines the custom Euclid type templates.
     */
    struct Kernel : public Euclid::DefaultKernel
    {
        typedef bool TriangleInfo;
    };
}

