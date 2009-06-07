#pragma once

#include <Viewer/FigureDecorator.h>

namespace App
{

    class TriangleFigure;

    /*!
     * The SelectedDecorator class implements a decorator for selected
     * triangles.
     *
     * Selected triangles are drawn with red color lines.
     */
    class SelectedDecorator : public Viewer::FigureDecorator
    {
    public:
        SelectedDecorator(const TriangleFigure* figure);
        void paintGL() const;
    };
}

