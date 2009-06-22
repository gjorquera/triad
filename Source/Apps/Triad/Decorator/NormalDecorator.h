#pragma once

#include <Viewer/FigureDecorator.h>

namespace App
{

    class TriangleFigure;

    /*!
     * Implements a decorator for normal triangles.
     *
     * Normal triangles are drawn with white background and black lines.
     */
    class NormalDecorator : public Viewer::FigureDecorator
    {
    public:
        NormalDecorator(const TriangleFigure* figure);
        void paintGL() const;
    };
}

