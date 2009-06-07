#pragma once

#include <Euclid/Geometry/Triangle.h>
#include <Viewer/Figure.h>
#include <Viewer/FigureDecorator.h>
#include "Kernel.h"

namespace App
{

    /*!
     * The TriangleFigure class defines a drawable triangle.
     *
     * This class is in charge of returning the appropiate decorations based on
     * the state of the current triangle instance and draw a basic triangle.
     *
     * The \b paintGL method is called by decorations.
     */
    class TriangleFigure : public Viewer::Figure
    {
    public:
        TriangleFigure(Euclid::Triangle<Kernel>* triangle);
        Euclid::Triangle<Kernel>* triangle();
        void paintGL() const;
        void clicked();
        Viewer::FigureDecorator* decorations() const;

    private:
        Euclid::Triangle<Kernel>* _triangle;
    };
}

