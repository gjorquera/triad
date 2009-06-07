#pragma once

#include <Viewer/FigureDecorator.h>

namespace App
{

    class TriangleFigure;

    /*!
     * The LeppDecorator class implements a decorator for lepp triangles.
     *
     * Lepp triangles are drawn with gray background.
     */
    class LeppDecorator : public Viewer::FigureDecorator
    {
    public:
        LeppDecorator(const TriangleFigure* figure);
        void paintGL() const;
    };
}

