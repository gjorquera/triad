#pragma once

#include <Euclid/Geometry/Triangle.h>
#include <Viewer/Figure.h>
#include <Viewer/FigureDecorator.h>
#include "Kernel.h"

namespace App
{

    /*!
     * The Triangle class is the renderizable figure of the Viewer section.
     *
     * This class is in charge of returning the appropiate decorations based on
     * the state of the current triangle instance.
     */
    class TriangleFigure : public Viewer::Figure
    {
    public:
        TriangleFigure(const Euclid::Triangle<Kernel>* triangle);
        Viewer::FigureDecorator* decorations() const;

    private:
        const Euclid::Triangle<Kernel>* _triangle;
    };
}

