#pragma once

#include <Euclid/Geometry/Triangle.h>
#include <Euclid/Type/DefaultKernel.h>
#include <Viewer/Figure.h>

namespace App
{

    /*!
     * The Triangle class is the renderizable figure of the Viewer section.
     *
     * This class is in charge of returning the appropiate decorations based on
     * the state of the current triangle instance.
     */
    class TriangleDecorator : public Viewer::Figure
    {
    public:
        typedef Euclid::DefaultKernel Kernel;

        TriangleDecorator(Euclid::Triangle<Kernel>* triangle);

    protected:
        Euclid::Triangle<Kernel>* _triangle;
        Viewer::IFigure* decorate() const;
    };
}

