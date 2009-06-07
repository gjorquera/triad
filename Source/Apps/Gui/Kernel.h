#pragma once

#include <Euclid/Type/DefaultKernel.h>

namespace App
{

    /*!
     * The information hold by every triangle.
     */
    struct TriangleInfoStruct
    {
        bool selected;
        bool lepp;

        TriangleInfoStruct()
        {
            selected = false;
            lepp = false;
        }
    };

    /*!
     * The Kernel structure defines the custom Euclid type templates.
     */
    struct Kernel : public Euclid::DefaultKernel
    {
        typedef TriangleInfoStruct TriangleInfo;
    };
}

